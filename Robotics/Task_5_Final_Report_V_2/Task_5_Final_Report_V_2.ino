// Ultrasonic Configuration
#define TRIG_PIN_R 8
#define TRIG_PIN_L 10
#define TRIG_PIN_F 12
#define ECHO_PIN_R 9
#define ECHO_PIN_L 11
#define ECHO_PIN_F 13

const int TRIG_PINS[] = {TRIG_PIN_R, TRIG_PIN_F, TRIG_PIN_L};
const int ECHO_PINS[] = {ECHO_PIN_R, ECHO_PIN_F, ECHO_PIN_L};

// Filter Configuration
const int WINDOW_SIZE = 2;

// Motor Driver Configuration
const int IN1 = 1, IN2 = 2, IN3 = 3, IN4 = 4, EN1 = 5, EN2 = 6;

// Speed and Distance Configuration
const int POT_SPEED_PIN = A0;
const int MAX_DISTANCE = 400; // in centimeters
const float MAX_TRACK_SPEED_CHANGE = 0.45;
const float MAX_TURN_SPEED_CHANGE = 0.85;
int speed = 0;

// Program Variables
long duration;
float distanceCm;
float dataArr[WINDOW_SIZE][3];
float ultrData[3];

// PID Variables and Configuration
const int POT_KP_PIN = A1;
const int POT_KI_PIN = A2;
const int POT_KD_PIN = A3;

unsigned long time;
float elapsedTime, timePrev;
float kp, ki, kd, error, previous_error;
float pid_p = 0, pid_i = 0, pid_d = 0, pid_integral = 0,PID = 0,maxSpeedChange = 0;
float pwmLeft = 0, pwmRight = 0;

void setup() {
  initPins();
  Serial.begin(9600);
  timePrev = millis();
  dataInit();
}

void loop() {
  // Read Speed and PID Constants from Potentiometers
  speed = map(analogRead(POT_SPEED_PIN), 0, 1023, 0, 255);
  kp = 0.7 * speed;
  ki = 0.1 * speed;
  kd = 0.2 * speed;

  // Calculate Time for Derivative Part
  time = millis();
  elapsedTime = (time - timePrev) / 1000.0;

  // Read Filtered Data from Ultrasonic Sensors
  for (int i = 0; i < 3; i++) {
    ultrData[i] = ultrasonicReadWithAverage(i);
  }

  // Calculate PID
  error = ultrData[0] - ultrData[2];
  pid_p = kp * error;
  pid_integral += ki * error * elapsedTime;
  pid_d = kd * (error - previous_error) / elapsedTime;
  PID = pid_p + pid_integral + pid_d;

  // Apply Limits to PID
  maxSpeedChange = ultrData[1] > 300 ? MAX_TRACK_SPEED_CHANGE : MAX_TURN_SPEED_CHANGE;
  PID = constrain(PID, -maxSpeedChange * speed, maxSpeedChange * speed);

  // Adjust Motor Speeds
  pwmLeft = speed + PID;
  pwmRight = speed - PID;

  // Apply Speeds to Motors
  analogWrite(EN1, constrain(pwmLeft, 0, speed));
  analogWrite(EN2, constrain(pwmRight, 0, speed));

  // Send Data to Serial Monitor
  sendDataToSerial();

  // Update Previous Time and Error
  timePrev = time;
  previous_error = error;
}

// Helper Functions

float ultrasonicRead(int ultranum) {
  digitalWrite(TRIG_PINS[ultranum], LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PINS[ultranum], HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PINS[ultranum], LOW);
  
  duration = pulseIn(ECHO_PINS[ultranum], HIGH);
  distanceCm = (duration * 0.0343) / 2.0;
  return min(distanceCm, MAX_DISTANCE) / 100.0;
}

float ultrasonicReadWithAverage(int ultranum) {
  float sum = 0;
  for (int i = 0; i < WINDOW_SIZE - 1; i++) {
    dataArr[i][ultranum] = dataArr[i + 1][ultranum];
    sum += dataArr[i][ultranum];
  }
  dataArr[WINDOW_SIZE - 1][ultranum] = ultrasonicRead(ultranum);
  sum += dataArr[WINDOW_SIZE - 1][ultranum];
  return sum / WINDOW_SIZE;
}

void dataInit() {
  for (int j = 0; j < 3; j++) {
    for (int i = 0; i < WINDOW_SIZE; i++) {
      dataArr[i][j] = ultrasonicRead(j);
    }
  }
}

void initPins() {
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

  for (int i = 0; i < 3; i++) {
    pinMode(TRIG_PINS[i], OUTPUT);
    pinMode(ECHO_PINS[i], INPUT);
  }

  pinMode(POT_SPEED_PIN, INPUT);
  pinMode(POT_KP_PIN, INPUT);
  pinMode(POT_KI_PIN, INPUT);
  pinMode(POT_KD_PIN, INPUT);
}

void sendDataToSerial() {
  Serial.print("Car Speed: ");
  Serial.print(speed);
  Serial.print(", kp: ");
  Serial.print(kp);
  Serial.print(", ki: ");
  Serial.print(ki);
  Serial.print(", kd: ");
  Serial.print(kd);
  Serial.print(", Right Distance: ");
  Serial.print(ultrData[0]);
  Serial.print(", Front Distance: ");
  Serial.print(ultrData[1]);
  Serial.print(", Left Distance: ");
  Serial.print(ultrData[2]);
  Serial.print(", Tracking Error: ");
  Serial.print(error);
  Serial.print(", Proportional Gain: ");
  Serial.print(pid_p);
  Serial.print(", Integral Gain: ");
  Serial.print(pid_integral);
  Serial.print(", Derivative Gain: ");
  Serial.print(pid_d);
  Serial.print(", Total PID: ");
  Serial.print(pid_p + pid_integral + pid_d);
  Serial.print(", PWM Right: ");
  Serial.print(pwmRight);
  Serial.print(", PWM Left: ");
  Serial.print(pwmLeft);
  Serial.print(", Elapsed Time: ");
  Serial.println(elapsedTime);
}
