#include <SoftwareSerial.h>
#define PIN_TX 10
#define PIN_RX 11
SoftwareSerial SIM808(PIN_TX, PIN_RX);

String serialRes, smsindex, phone_number, message_text, MES, lat_str, lon_str, emgMes = "help", password = "weeka", gpsKeyword = "GET_GPS";
boolean GPS_Data_Flag;

double lat, lon;

void WaitForRespSIM808(String key) {
  String str = "";
  waitResp:
  while (!SIM808.available())
    ;
  str = SIM808.readString();
  if (str.indexOf(key) >= 0 || str.indexOf("ROR") >= 0)
    return;
  else
    goto waitResp;
}

void sendSMSUsingSIM808(String phone, String Mes) {
  if(SendComToSIM808AndCheckForResp("AT+CMGS=\""+phone+"\"\r\n",">"))
  {
    if(SendComToSIM808AndCheckForResp(Mes,">"))
    {
      SIM808.print((char)26);
    }
  }
  WaitForRespSIM808("OK");
}

void getGPSDataFromSIM808() {
  String data = "";
  if (SendComToSIM808AndCheckForResp("AT+CGPSSTATUS?", "D")) {
    // Serial.println("Location is Fixed");
    GPS_Data_Flag = true;
    serialRes = SendComToSIM808("AT+CGPSINF=0");
    serialRes = serialRes.substring(12, 35);

    lon_str = serialRes.substring(12, serialRes.indexOf(","));
    lon = ddm_to_dd(atof(lon_str.c_str()));
    // Serial.println("lon : " + lon_str);

    lat_str = serialRes.substring(serialRes.indexOf(","));
    lat = ddm_to_dd(atof(lat_str.c_str()));
    // Serial.println("lat : " + lat_str);

  } else {
    // Serial.println("Location Is Not Fixed");
    GPS_Data_Flag = false;
  }
}

double ddm_to_dd(double ddm) {
  double degrees = floor(ddm / 100.0);
  double minutes = ddm - degrees * 100.0;
  return (degrees + minutes / 60.0);
}

boolean SendComToSIM808AndCheckForResp(String Com, String res) {
  String str;
  SIM808.println(Com);
  delay(10);
  while (!SIM808.available())
    ;
  str = SIM808.readString();
  // Serial.println(str);
  if (str.indexOf(res) >= 0)
    return true;
  else
    return false;
}

String SendComToSIM808(String value) {
  String Out;
  SIM808.println(value);
  delay(10);
  while (!SIM808.available())
    ;
  Out = SIM808.readString();

  Out.trim();
  Out.remove(0, value.length() + 3);
  return Out;
}

void InitSIM808(void) {

  // Serial.print("Check For Connection : ");
  while (!SendComToSIM808AndCheckForResp("AT", "OK"))
    ;
  // Serial.println("OK");

  // Serial.print("Check For GPS Power : ");
  if (SendComToSIM808AndCheckForResp("AT+CGPSPWR?", "1")) {
    // Serial.println("OK");
  } else {
    // Serial.println("No");
    // Serial.print("Power UP The GPS : ");
    while (!SendComToSIM808AndCheckForResp("AT+CGPSPWR=1", "OK"))
      ;
    // Serial.println("OK");
  }

  // Serial.print("Check GPS Output Mode : ");
  if (SendComToSIM808AndCheckForResp("AT+CGPSOUT?", "0")) {
    // Serial.println("OK");
  } else {
    // Serial.println("No");
    // Serial.print("Set GPS Output Mode : ");
    while (!SendComToSIM808AndCheckForResp("AT+CGPSOUT=0", "OK"))
      ;
    // Serial.println("OK");
  }

  Serial.print("Check SMS Text Mode : ");
  if (SendComToSIM808AndCheckForResp("AT+CMGF?", "1")) {
    // Serial.println("OK");
  } else {
    // Serial.println("No");
    // Serial.print("Put The Module in SMS Text Mode : ");
    while (!SendComToSIM808AndCheckForResp("AT+CMGF=1", "OK"))
      ;
    // Serial.println("OK");
  }

  // Serial.print("Check GPS Location Fix : ");
  // while(!SendComToSIM808AndCheckForResp("AT+CGPSSTATUS?","D Fix"));
  // Serial.println("OK");
}

void processOnSMSMessage(String mes) {
  String str;
  if (mes.indexOf(password) > -1)  // message contains password keyword
  {
    mes.remove(mes.indexOf(password), mes.indexOf(password) + password.length() + 1);
    if (mes.indexOf(gpsKeyword) > -1)  // send gps data
    {
      mes.remove(mes.indexOf(gpsKeyword), mes.indexOf(gpsKeyword) + gpsKeyword.length());
      // Serial.println(mes);
      getGPSDataFromSIM808();
      if (GPS_Data_Flag) {
        MES = "https://www.google.com/maps?z=18&t=m&q=loc:";
        MES += lon;
        MES += "+";
        MES += lat;
        sendSMSUsingSIM808(phone_number, MES);
      } else {
        sendSMSUsingSIM808(phone_number, "Gps Location Is Not Fixed Yet :(");
      }
    }
    if (mes.indexOf("AT") > -1)  // perform AT command
    {
      if(mes.indexOf("ATD")>-1){
        sendSMSUsingSIM808(phone_number, "Call is goining now :) ");
        str = SendComToSIM808(mes);
        delay(10000);
        str = SendComToSIM808("ATH");
      }else{
        str = SendComToSIM808(mes);
        sendSMSUsingSIM808(phone_number, str);
      }

    }
  } else {
    if (mes.indexOf(emgMes) > -1)  // emergency message
    {
      str = SendComToSIM808("ATD+201270989676;");
      delay(10000);
      str = SendComToSIM808("ATH");
      sendSMSUsingSIM808(phone_number, "Emergency Call was Sent !");
    }
  }
}

void makeCallUsingSIM808(String phone) {
  SIM808.println("ATD" + phone + ";");
  WaitForRespSIM808("OK");
  delay(10000);
  SIM808.println("ATH");
  WaitForRespSIM808("OK");
  delay(1000);
}

void setup() {
  Serial.begin(9600);
  SIM808.begin(9600);
  InitSIM808();
  // makeCallUsingSIM808("01270989676");
  sendSMSUsingSIM808("+201270989676", "SIM808 is ready to use :)");
  // Serial.println("\nWaiting for new Messages or Calls :) \n");
}

void loop() {
  while (!SIM808.available());
  serialRes = SIM808.readString();

  if (serialRes.indexOf("SM") > -1)  // Message Recieved
  {
    smsindex = serialRes.substring(14, 15);
    serialRes = SendComToSIM808("AT+CMGR=" + smsindex);
    phone_number = serialRes.substring(23, 34);
    message_text = serialRes.substring(63, serialRes.length() - 6);
    // Serial.println("Phone Number : " + phone_number);
    // Serial.println("Message Text : " + message_text);
    processOnSMSMessage(message_text);
    // Delete sms messages
    // Serial.print("Delete All Previous Messages : ");
    while (!SendComToSIM808AndCheckForResp("AT+CMGD=1,4", "OK"))
      ;
    // Serial.println("OK");

    // Serial.println("\nWaiting for new Messages or Calls :) \n");
  } else if (serialRes.indexOf("+CLCC") > -1)  // New Call
  {
    delay(2000);

    // Hang The Call
    // Serial.print("Close The Call : ");
    while (!SendComToSIM808AndCheckForResp("ATH", "OK"))
      ;
    // Serial.println("OK");

    phone_number = serialRes.substring(20, 31);
    // Serial.println(phone_number);
    getGPSDataFromSIM808();
    processOnSMSMessage(password + " " + gpsKeyword);
    // Serial.println("\nWaiting for new Messages or Calls :) \n");
  }
}
