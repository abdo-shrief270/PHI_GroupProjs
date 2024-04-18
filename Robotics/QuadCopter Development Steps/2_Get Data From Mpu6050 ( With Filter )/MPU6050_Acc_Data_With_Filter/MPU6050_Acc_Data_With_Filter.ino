#include <Wire.h>
#include <MPU6050.h>
#define WindowSize 10
float DataArr[WindowSize][3];
Vector MPU6050_Read_Data_Average(void);

void DataInit(void);
MPU6050 mpu;

void setup() 
{
  Serial.begin(115200);

  Serial.println("Initialize MPU6050");

  while(!mpu.begin(MPU6050_SCALE_2000DPS, MPU6050_RANGE_2G))
  {
    Serial.println("Could not find a valid MPU6050 sensor, check wiring!");
    delay(500);
  }

  DataInit();
}



void loop()
{
  Vector rawAccel = MPU6050_Read_Data_Average();

  Serial.print(" Xraw = ");
  Serial.print(rawAccel.XAxis);
  Serial.print(" ,Yraw = ");
  Serial.print(rawAccel.YAxis);
  Serial.print(" ,Zraw = ");
  Serial.println(rawAccel.ZAxis);

  
  delay(10);
}

Vector MPU6050_Read_Data_Average(void){
  Vector rawAccel = mpu.readRawAccel();
  Vector Data;
  float sum0=0,sum1=0,sum2=0;
  for(int i = 0; i < WindowSize - 1; i++) {
    DataArr[i][0] = DataArr[i + 1][0];
    DataArr[i][1] = DataArr[i + 1][1];
    DataArr[i][2] = DataArr[i + 1][2];
    sum0+=DataArr[i][0];
    sum1+=DataArr[i][1];
    sum2+=DataArr[i][2];
  }
  
  DataArr[WindowSize - 1][0]=rawAccel.XAxis;
  DataArr[WindowSize - 1][1]=rawAccel.YAxis;
  DataArr[WindowSize - 1][2]=rawAccel.ZAxis;
  sum0+=DataArr[WindowSize - 1][0];
  sum1+=DataArr[WindowSize - 1][1];
  sum2+=DataArr[WindowSize - 1][2];
  Data.XAxis=sum0/WindowSize;
  Data.YAxis=sum1/WindowSize;
  Data.ZAxis=sum2/WindowSize;
  return Data;
}


void DataInit(void){
  for(int i = 0; i < WindowSize; i++){
    Vector rawAccel = mpu.readRawAccel();
    DataArr[i][0]=rawAccel.XAxis;
    DataArr[i][0]=rawAccel.YAxis;
    DataArr[i][0]=rawAccel.ZAxis;
  }
}

