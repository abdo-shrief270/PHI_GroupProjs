#include <Wire.h>
#include "string.h"
#include <LiquidCrystal_I2C.h>

//I2C pins declaration
LiquidCrystal_I2C lcd(0x27, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE);

//Variables Decleration
String chrs,codes,mes,msgDecoded,code;

void setup() {
  lcd.begin(16, 2);
  lcd.backlight();
  Serial.begin(9600);
}

void loop() {
  //Set Position Of Cursor In LCD
  lcd.setCursor(0, 0);

  //Clear All Variables
  String codebook[20]={"","","","","","","","","","","","","","","","","","","",""};
  chrs="";
  codes="";
  mes="";
  msgDecoded="";
  code="";

  //Recieve From Labtop
  while(!Serial.available());
  chrs=Serial.readStringUntil('\n');
  codes=Serial.readStringUntil('\n');
  mes=Serial.readStringUntil('\n');

  // Clear LCD
  lcd.clear();

  //Convert Codes String Into Codebook Array
  int k=0;
  for(int j=0;j<codes.length();j++){
    if(codes.charAt(j)==','){
      k++;
    }else{
      codebook[k]+=codes.charAt(j);
    }
  }

  // Decoed Binary Message
  for(int i=0;i<mes.length();i++){
    code += mes.charAt(i);
    boolean flag = false;
    for (int j = 0; j < 20; j++) {
      if (code.equals(codebook[j])) {
        msgDecoded += chrs.charAt(j);
        flag = true;
        break;
      }
    }
    if (flag) {
      code = "";
    }
  }
  
  // Print Message On Lcd
  for(int i=0;i<msgDecoded.length();i++){
    lcd.print(msgDecoded.charAt(i));
    delay(100);
  }

}
