// Date: March 29, 2024 at 8:00pm

/* 
Ultrasonic Sensor 1 (Motion Sensor) -
Purpose: It could be used for motion sensor to open the trash bin lid.

Ultrasonic Sensor 2 (Fullness Sensor) -
Purpose: Be able to detect when the trash bin is full.

Servo Motor -
Purpose: Be able to ratate about 90 degrees to open the lid, wait for a few 
miliseconds, and then rotate the opposite way to close the lid back.
*** Important Note: Will need some hardware components to help with rotation. ***

LED -
Purpose: led will lit up when trashbin is full and turn off when its not full.
*/


#include <Servo.h>
#include <NewPing.h>

#define motionTrigPin 3
#define motionEchoPin 2
#define fullTrigPin 5
#define fullEchoPin 4
#define ledPin 13
#define servoPin 9
#define MAX_DISTANCE 200             // Maximum distance we want to ping for (in centimeters).
#define MOTION_THRESHOLD 20          // Distance threshold for motion detection (cm).
#define FULLNESS_THRESHOLD 10        // Distance threshold for fullness detection (cm).
#define DEBOUNCE_TIME 1000           // Debounce time in milliseconds.

Servo myServo;
NewPing motionSensor(motionTrigPin, motionEchoPin, MAX_DISTANCE);
NewPing fullnessSensor(fullTrigPin, fullEchoPin, MAX_DISTANCE);

unsigned long lastMotionTime = 0;
bool lidOpen = false;

void setup() {
  pinMode(ledPin, OUTPUT);
  myServo.attach(servoPin);
  myServo.write(0); // Initial position
  Serial.begin(9600);
}

void loop() {
  readMotionSensor();
  readFullnessSensor();
  delay(100); // Short delay to reduce sensor reading frequency
}

void readMotionSensor() {
  if (millis() - lastMotionTime > DEBOUNCE_TIME) {
    unsigned int distance = motionSensor.ping_cm();
    if (distance > 0 && distance < MOTION_THRESHOLD && !lidOpen) {
      operateServo(true);
      lastMotionTime = millis();
      lidOpen = true;
      delay(3000);
      operateServo(false);
      lidOpen = false;  
    }
  }
}


void readFullnessSensor() {
  unsigned int distance = fullnessSensor.ping_cm();
  bool isFull = distance > 0 && distance < FULLNESS_THRESHOLD;
  digitalWrite(ledPin, isFull);
}

void operateServo(bool opening) {
  int startPos = opening ? 0 : 90;
  int endPos = opening ? 90 : 0;
  for (int pos = startPos; pos != endPos; opening ? pos++ : pos--) {
    myServo.write(pos);
    delay(20);
  }
 
}
