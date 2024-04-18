#define trigPin A0
#define echoPin A1
#define WindowSize 5


float DataArr[WindowSize];
int DataSize;
long duration = 0;
float distanceCm = 0;


void DataInit(void);
float UltrasonicRead(void);
float UltrasonicRead_WithAverage(void);

void setup() {
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  Serial.begin(9600);
  DataSize = sizeof(DataArr) / sizeof(DataArr[0]);
  DataInit();
}

void loop() {
  Serial.println(UltrasonicRead_WithAverage());
}

void DataInit(void) {
  for (int i = 0; i < DataSize; i++) {
    DataArr[i] = UltrasonicRead();
  }
}

float UltrasonicRead(void) {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distanceCm = (duration * 0.0343) / 2.0;
  return distanceCm;
}

float UltrasonicRead_WithAverage(void) {
  float sum = 0;
  for (int i = 0; i < DataSize - 1; i++) {
    DataArr[i] = DataArr[i + 1];
    sum += DataArr[i];
  }
  DataArr[DataSize - 1] = UltrasonicRead();
  sum += DataArr[DataSize - 1];
  return (sum / DataSize);
}
