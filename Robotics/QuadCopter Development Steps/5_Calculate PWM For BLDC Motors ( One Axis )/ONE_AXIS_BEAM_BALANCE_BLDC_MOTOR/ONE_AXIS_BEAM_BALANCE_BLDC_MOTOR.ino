#include <Servo.h>
#include <Wire.h>
#include <MPU6050.h>


#define ESC1_PWM 6
#define ESC2_PWM 5

#define max_axis_value  12
#define mpu_6050_resolution 500
#define max_pwm_speed   20
#define balanced_speed  40

MPU6050 mpu;
Servo ESC1;
Servo ESC2;
#define WindowSize 10
float DataArr[WindowSize];
Vector MPU6050_Read_Data_Average(void);
void DataInit(void);

int esc1_Speed, esc2_Speed,speed, error,error_speed;

void setup() {
  pinMode(ESC1_PWM,OUTPUT);
  pinMode(ESC2_PWM,OUTPUT);
  ESC1.attach(ESC1_PWM, 1000, 2000);
  ESC2.attach(ESC2_PWM, 1000, 2000);
  Serial.begin(9600);
  while (!mpu.begin(MPU6050_SCALE_2000DPS, MPU6050_RANGE_2G)) {
    Serial.println("Could not find a valid MPU6050 sensor, check wiring!");
    delay(500);
  }
  mpu.calibrateGyro();
  mpu.setThreshold(3);
  DataInit(); 
  ESC1.write(0);
  ESC2.write(0);
  delay(2000);
}


void loop() {
  Vector rawAccel = MPU6050_Read_Data_Average();
  error=int(rawAccel.YAxis/mpu_6050_resolution);
  if (error > max_axis_value) {
    error = max_axis_value;
  }
  if (error < -max_axis_value) {
    error = -max_axis_value;
  }
  error_speed = map(error, -max_axis_value, max_axis_value, -max_pwm_speed, max_pwm_speed);


  speed=balanced_speed+abs(error_speed);

  if (error < 0) {
    esc1_Speed = balanced_speed+abs(error_speed);
    esc2_Speed = balanced_speed-abs(error_speed);
  } else if (error > 0) {
    esc1_Speed = balanced_speed-abs(error_speed);
    esc2_Speed = balanced_speed+abs(error_speed);
  } else {
    esc1_Speed = balanced_speed;
    esc2_Speed = balanced_speed;
  }

  Serial.print("YAxis = ");
  Serial.print(rawAccel.YAxis);  
  Serial.print(" ,error = ");
  Serial.print(error);  
  Serial.print(" ,error_speed = ");
  Serial.print(error_speed);  
  Serial.print(" ,esc1_Speed = ");
  Serial.print(esc1_Speed);
  Serial.print(" ,esc2_Speed = ");
  Serial.println(esc2_Speed);

  ESC1.write(esc1_Speed+20);
  ESC2.write(esc2_Speed);
}

Vector MPU6050_Read_Data_Average(void) {
  Vector rawAccel = mpu.readRawAccel();
  Vector Data;
  float sum0 = 0;
  for (int i = 0; i < WindowSize - 1; i++) {
    DataArr[i] = DataArr[i + 1];
    sum0 += DataArr[i];
  }
  DataArr[WindowSize - 1] = rawAccel.YAxis;
  sum0 += DataArr[WindowSize - 1];
  Data.YAxis = sum0 / WindowSize;
  return Data;
}


void DataInit(void) {
  for (int i = 0; i < WindowSize; i++) {
    Vector rawAccel = mpu.readRawAccel();
    DataArr[i] = rawAccel.YAxis;
  }
}
