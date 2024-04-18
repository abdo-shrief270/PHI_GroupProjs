#include <Servo.h>

Servo ESC;

int Speed;

void setup() {
  ESC.attach(10, 1000, 2000);
  Serial.begin(9600);
}

void loop() {
  Speed = analogRead(A0);
  Speed = map(Speed, 0, 1023, 0, 180);
  ESC.write(60);
  Serial.print(" , Speed = ");
  Serial.println(Speed);
}