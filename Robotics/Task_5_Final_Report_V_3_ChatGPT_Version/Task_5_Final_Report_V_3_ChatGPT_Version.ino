// Constants
const int WINDOW_SIZE = 5;
const float DEFAULT_KP = 0.7;
const float DEFAULT_KI = 0.1;
const float DEFAULT_KD = 0.2;
const float MAX_SPEED_CHANGE = 0.45;
const float MAX_TURN_SPEED_CHANGE = 0.85;
const int MIN_SPEED = 0;
const int MAX_SPEED = 255;
const int MAX_DISTANCE_CM = 400;
const int MIN_DISTANCE_CM = 2;
const int ULTRASONIC_TIMEOUT_MS = 1000;
const int POT_READ_DELAY_MS = 10;

// Pin Configuration
const int POT_SPEED_PIN = A0;
const int TRIG_PINS[] = {8, 12, 10}; // {TRIG_PIN_R, TRIG_PIN_F, TRIG_PIN_L}
const int ECHO_PINS[] = {9, 13, 11}; // {ECHO_PIN_R, ECHO_PIN_F, ECHO_PIN_L}
const int IN1 = 1, IN2 = 2, IN3 = 3, IN4 = 4, EN1 = 5, EN2 = 6;

// Variables
float kp, ki, kd;
unsigned long lastPotReadTime = 0;
float ultrasonicData[3];
float ultrasonicMovingAvg[3];
float previousError = 0;
unsigned long lastSensorReadTime = 0;
int speed = 0;
float PID = 0; // Declare PID variable

void setup() {
  initPins(); // Initialize pins
  Serial.begin(9600); // Start serial communication
  initVariables(); // Initialize variables
}

void loop() {
  updatePIDConstants();
  readSensorData();
  calculatePID();
  adjustMotorSpeeds();
  sendDataToSerial();
}

// Function to update PID constants from potentiometer
void updatePIDConstants() {
  if (millis() - lastPotReadTime >= POT_READ_DELAY_MS) {
    int potSpeed = analogRead(POT_SPEED_PIN);
    speed = map(potSpeed, 0, 1023, MIN_SPEED, MAX_SPEED);
    kp = DEFAULT_KP * speed;
    ki = DEFAULT_KI * speed;
    kd = DEFAULT_KD * speed;
    lastPotReadTime = millis();
  }
}

// Function to read sensor data and calculate moving average
void readSensorData() {
  for (int i = 0; i < 3; i++) {
    float distance = ultrasonicRead(i);
    if (distance >= MIN_DISTANCE_CM && distance <= MAX_DISTANCE_CM) {
      ultrasonicData[i] = distance;
      ultrasonicMovingAvg[i] = updateMovingAvg(distance, ultrasonicMovingAvg[i], WINDOW_SIZE);
    }
    else {
      // Handle out-of-range or invalid readings
    }
  }
}

// Function to calculate moving average
float updateMovingAvg(float newValue, float oldValue, int windowSize) {
  return ((oldValue * (windowSize - 1)) + newValue) / windowSize;
}

// Function to calculate PID control
void calculatePID() {
  unsigned long currentTime = millis();
  float elapsedTime = (currentTime - lastSensorReadTime) / 1000.0;
  lastSensorReadTime = currentTime;

  float error = ultrasonicMovingAvg[0] - ultrasonicMovingAvg[2];
  float pid_p = kp * error;
  float pid_i = ki * error * elapsedTime;
  float pid_d = kd * (error - previousError) / elapsedTime;
  PID = pid_p + pid_i + pid_d; // Store PID value in the global variable

  float maxSpeedChange = ultrasonicMovingAvg[1] > 300 ? MAX_SPEED_CHANGE : MAX_TURN_SPEED_CHANGE;
  PID = constrain(PID, -maxSpeedChange * speed, maxSpeedChange * speed);

  previousError = error;
}

// Function to adjust motor speeds based on PID control
void adjustMotorSpeeds() {
  int leftSpeed = constrain(speed + PID, MIN_SPEED, MAX_SPEED);
  int rightSpeed = constrain(speed - PID, MIN_SPEED, MAX_SPEED);

  analogWrite(EN1, leftSpeed);
  analogWrite(EN2, rightSpeed);
}

// Function to send data to serial monitor
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
  Serial.print(ultrasonicMovingAvg[0]);
  Serial.print(", Front Distance: ");
  Serial.print(ultrasonicMovingAvg[1]);
  Serial.print(", Left Distance: ");
  Serial.print(ultrasonicMovingAvg[2]);
  // Add more data as needed
  Serial.println();
}

// Function to initialize pins
void initPins() {
  pinMode(POT_SPEED_PIN, INPUT);
  // Initialize motor pins
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  pinMode(EN1, OUTPUT);
  pinMode(EN2, OUTPUT);
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
  // Initialize ultrasonic pins
  for (int i = 0; i < 3; i++) {
    pinMode(TRIG_PINS[i], OUTPUT);
    pinMode(ECHO_PINS[i], INPUT);
  }
}

// Function to initialize variables
void initVariables() {
  // Initialize any necessary variables
}

// Function to read ultrasonic sensor
float ultrasonicRead(int ultranum) {
  digitalWrite(TRIG_PINS[ultranum], LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PINS[ultranum], HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PINS[ultranum], LOW);
  
  unsigned long duration = pulseIn(ECHO_PINS[ultranum], HIGH, ULTRASONIC_TIMEOUT_MS);
  float distanceCm = (duration * 0.0343) / 2.0;
  return distanceCm;
}
