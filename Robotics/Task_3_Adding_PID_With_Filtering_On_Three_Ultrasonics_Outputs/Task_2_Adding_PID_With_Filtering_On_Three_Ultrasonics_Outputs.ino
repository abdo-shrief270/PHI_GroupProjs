#define trigPin_R 1
#define echoPin_R 2

#define trigPin_F 3
#define echoPin_F 4

#define trigPin_L 5
#define echoPin_L 6

#define IN1 7
#define IN2 8
#define IN3 12
#define IN4 13

#define EN1 10
#define EN2 11

#define WindowSize 5

long duration;
float distanceCm;
float DataArr[WindowSize][3];
float UltrData[3];

char TrigArr[]={trigPin_R,trigPin_F,trigPin_L};
char EchoArr[]={echoPin_R,echoPin_F,echoPin_L};

////
void DataInit(void);
float UltrasonicRead(char Ultranum);
float UltrasonicRead_WithAverage(char Ultranum);

/////////// PID Section
float elapsedTime, time, timePrev;
int i;

float PID, pwmLeft, pwmRight, error, previous_error;
float pid_p=0;
float pid_i=0;
float pid_d=0;

/////////////////PID CONSTANTS/////////////////
double kp=10;
double ki=2;
double kd=5;


void setup() {

  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  pinMode(EN1, OUTPUT);
  pinMode(EN2, OUTPUT);
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);

  pinMode(trigPin_R, OUTPUT);
  pinMode(echoPin_R, INPUT);
  pinMode(trigPin_F, OUTPUT);
  pinMode(echoPin_F, INPUT);
  pinMode(trigPin_L, OUTPUT);
  pinMode(echoPin_L, INPUT);
  Serial.begin(9600);
  time = millis();
  DataInit();
}

void loop() {

    timePrev = time; 
    time = millis();
    elapsedTime = (time - timePrev) / 1000;
    
    for(char i=0;i<3;i++){
      UltrData[i]=UltrasonicRead_WithAverage(i);
    }

    error = UltrData[0] - UltrData[2];

    pid_p = kp*error;

    if(-10 < error < 10)
    {
      pid_i += ki*error;  
    }

    pid_d = kd*((error - previous_error)/elapsedTime);

    PID = pid_p + pid_i + pid_d;

    pwmLeft=255;
    pwmRight=255;
    
    analogWrite(EN1, pwmLeft);
    analogWrite(EN2, pwmRight);


    Serial.print(UltrData[0]);
    Serial.print(" , ");
    Serial.print(UltrData[1]);
    Serial.print(" , ");
    Serial.print(UltrData[2]);
    Serial.print(" , ");
    Serial.println(error);    
    Serial.print(" , ");
    Serial.print(PID);
    Serial.print(" , ");
    Serial.print(pwmRight);
    Serial.print(" , ");
    Serial.println(pwmLeft); 
}


float UltrasonicRead(char Ultranum){
 
  digitalWrite(TrigArr[Ultranum], LOW);
  delayMicroseconds(2);
  digitalWrite(TrigArr[Ultranum], HIGH);
  delayMicroseconds(10);
  digitalWrite(TrigArr[Ultranum], LOW);
  
  duration = pulseIn(EchoArr[Ultranum], HIGH);
  distanceCm = (duration * 0.0343) / 2.0;
  return distanceCm;
} 


float UltrasonicRead_WithAverage(char Ultranum){

  float sum=0;
  for(int i = 0; i < WindowSize - 1; i++) {
    DataArr[i][Ultranum] = DataArr[i + 1][Ultranum];
    sum+=DataArr[i][Ultranum];
  }
  
  DataArr[WindowSize - 1][Ultranum] = UltrasonicRead(Ultranum);
  sum+=DataArr[WindowSize - 1][Ultranum];
  return (sum/WindowSize);
}

void DataInit(void){
  for(int j=0;j<3;j++){
    for(int i = 0; i < WindowSize; i++){
    DataArr[i][j]=UltrasonicRead(j);
    }
  }
}
