/* www.learningbuz.com */
/*Impport following Libraries*/
#include <Wire.h>
#include "string.h"
#include <LiquidCrystal_I2C.h>
//I2C pins declaration
LiquidCrystal_I2C lcd(0x27, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE);
String chrs,mes,msgDecoded,code,codes;

void setup() {
  lcd.begin(16, 2);
  lcd.backlight();
  Serial.begin(9600);
}

void loop() {
  lcd.setCursor(0, 0);
  String codebook[10]={"","","","","","","","","",""};
  while(!Serial.available());
  chrs="";
  chrs=Serial.readStringUntil('\n');
  Serial.println(chrs);
  code="";
  codes=Serial.readStringUntil('\n');
  mes="";
  mes=Serial.readStringUntil('\n');

  lcd.clear();
  int k=0;
  for(int j=0;j<codes.length();j++){
    if(codes.charAt(j)==','){
      // Serial.println("ok1");
      k++;
      continue;
    }else{
      codebook[k]+=codes.charAt(j);
    }
  }
  msgDecoded="";
  code="";
  for(int i=0;i<mes.length();i++){
    code += mes.charAt(i);
    boolean flag = false;
    for (int j = 0; j < 10; j++) {
        if (code.equals(codebook[j])) {
          msgDecoded += chrs.charAt(j);
          // Serial.println("ok2");
          flag = true;
          break;
        }
    }
    if (flag) {
        code = "";
    }
  }
  
  for(int i=0;i<msgDecoded.length();i++){
    lcd.print(msgDecoded.charAt(i));
  }
}
