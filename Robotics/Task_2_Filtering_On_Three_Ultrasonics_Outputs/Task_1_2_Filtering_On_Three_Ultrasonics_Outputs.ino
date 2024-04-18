#define trigPin_R 8
#define echoPin_R 9

#define trigPin_F 7
#define echoPin_F 6

#define trigPin_L 11
#define echoPin_L 10

#define WindowSize 5


float DataArr[WindowSize][3];


long duration;
float distanceCm;

char TrigArr[]={trigPin_R,trigPin_F,trigPin_L};
char EchoArr[]={echoPin_R,echoPin_F,echoPin_L};

void DataInit(void);
float UltrasonicRead(int Ultranum);
float UltrasonicRead_WithAverage(int Ultranum);

void setup() {
  pinMode(trigPin_R, OUTPUT);
  pinMode(echoPin_R, INPUT);
  pinMode(trigPin_F, OUTPUT);
  pinMode(echoPin_F, INPUT);
  pinMode(trigPin_L, OUTPUT);
  pinMode(echoPin_L, INPUT);
  
  Serial.begin(9600);
 
  DataInit();
}

void loop() {
  Serial.print(UltrasonicRead_WithAverage(0));
  Serial.print(" , ");
  Serial.print(UltrasonicRead_WithAverage(1));
  Serial.print(" , ");
  Serial.println(UltrasonicRead_WithAverage(2));
}

void DataInit(void){
  for(int j=0;j<3;j++){
    for(int i = 0; i < WindowSize; i++){
    DataArr[i][j]=UltrasonicRead(j);
    }
  }
}

float UltrasonicRead(int Ultranum){
 
  digitalWrite(TrigArr[Ultranum], LOW);
  delayMicroseconds(2);
  digitalWrite(TrigArr[Ultranum], HIGH);
  delayMicroseconds(10);
  digitalWrite(TrigArr[Ultranum], LOW);
  
  duration = pulseIn(EchoArr[Ultranum], HIGH);
  distanceCm = (duration * 0.0343) / 2.0;
return distanceCm;
} 

float UltrasonicRead_WithAverage(int Ultranum){
   float sum=0;
   for(int i = 0; i < WindowSize - 1; i++) {
      DataArr[i][Ultranum] = DataArr[i + 1][Ultranum];
      sum+=DataArr[i][Ultranum];
   }
  DataArr[WindowSize - 1][Ultranum] = UltrasonicRead(Ultranum);
  sum+=DataArr[WindowSize - 1][Ultranum];
  return (sum/WindowSize);
}
