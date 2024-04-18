#include <Servo.h>
#include <Wire.h>
#include <MPU6050.h>
#include <PID_v1.h>

#define ENA 9
#define ENB 10
#define IN1 5
#define IN2 6
#define IN3 7
#define IN4 8
#define min_pwm_speed 40
#define max_pwm_speed 255

MPU6050 mpu;

#define WindowSize 25
float DataArr[WindowSize][3];
Vector MPU6050_Read_Data_Average(void);
void DataInit(void);

double Setpoint, Input, Output;

//Specify the links and initial tuning parameters
double Kp=2, Ki=5, Kd=1;

PID myPID(&Input, &Output, &Setpoint, Kp, Ki, Kd, DIRECT);

int dc1_Speed, dc2_Speed,speed, error;

void setup() {
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  pinMode(ENA, OUTPUT);
  pinMode(ENB, OUTPUT);
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
  Serial.begin(115200);
  while (!mpu.begin(MPU6050_SCALE_2000DPS, MPU6050_RANGE_2G)) {
    Serial.println("Could not find a valid MPU6050 sensor, check wiring!");
    delay(500);
  }
  mpu.calibrateGyro();
  mpu.setThreshold(3);
  DataInit(); 
  myPID.SetMode(AUTOMATIC);
}


void loop() {
  Vector rawAccel = MPU6050_Read_Data_Average();
  error = map(rawAccel.XAxis, -10000, 10000, -max_pwm_speed, max_pwm_speed);
  if (error > max_pwm_speed) {
    error = max_pwm_speed;
  }
  if (error < -max_pwm_speed) {
    error = -max_pwm_speed;
  }

  speed=abs(error);

  if(speed<min_pwm_speed){
    speed=min_pwm_speed;
  }

  if (error < 0) {
    dc1_Speed = speed;
    dc2_Speed = 0;
  } else if (error > 0) {
    dc1_Speed = 0;
    dc2_Speed = speed;
  } else {
    dc1_Speed = 0;
    dc2_Speed = 0;
  }

  Serial.print(" Xraw = ");
  Serial.print(rawAccel.XAxis);
  Serial.print(" ,Yraw = ");
  Serial.print(rawAccel.YAxis);
  Serial.print(" ,Zraw = ");
  Serial.print(rawAccel.ZAxis);
  Serial.print(" ,error = ");
  Serial.print(error);  
  Serial.print(" ,dc1_Speed = ");
  Serial.print(dc1_Speed);
  Serial.print(" ,dc2_Speed = ");
  Serial.println(dc2_Speed);
  analogWrite(ENA, dc1_Speed);
  analogWrite(ENB, dc2_Speed);
  delay(10);
}

Vector MPU6050_Read_Data_Average(void) {
  Vector rawAccel = mpu.readRawAccel();
  Vector Data;
  float sum0 = 0, sum1 = 0, sum2 = 0;
  for (int i = 0; i < WindowSize - 1; i++) {
    DataArr[i][0] = DataArr[i + 1][0];
    DataArr[i][1] = DataArr[i + 1][1];
    DataArr[i][2] = DataArr[i + 1][2];
    sum0 += DataArr[i][0];
    sum1 += DataArr[i][1];
    sum2 += DataArr[i][2];
  }

  DataArr[WindowSize - 1][0] = rawAccel.XAxis;
  DataArr[WindowSize - 1][1] = rawAccel.YAxis;
  DataArr[WindowSize - 1][2] = rawAccel.ZAxis;
  sum0 += DataArr[WindowSize - 1][0];
  sum1 += DataArr[WindowSize - 1][1];
  sum2 += DataArr[WindowSize - 1][2];
  Data.XAxis = sum0 / WindowSize;
  Data.YAxis = sum1 / WindowSize;
  Data.ZAxis = sum2 / WindowSize;
  return Data;
}


void DataInit(void) {
  for (int i = 0; i < WindowSize; i++) {
    Vector rawAccel = mpu.readRawAccel();
    DataArr[i][0] = rawAccel.XAxis;
    DataArr[i][0] = rawAccel.YAxis;
    DataArr[i][0] = rawAccel.ZAxis;
  }
}
