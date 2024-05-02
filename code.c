//This file will be split up into mulltiple files to represent necessary parts later on

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
#include "SevSeg.h"

/* ULTRASONIC SENSORS: MOTION SENSOR */                                 
#define motionEchoPin 2                 //pin that sends out output for ultrasonic motion sensor (motion sensor to open trash)      
#define motionTrigPin 3                 //pin that will listen for response for unltrasonic motion sensor 

/* ULTRASONIC SENSORS: FULLNESS SENSOR */
#define motionEchoPin 4                   //pin that sends out output for ultrasonic motion sensor (sensor to detect fullness of trash)       
#define fullTrigPin 5                   //pin that will listen for response for unltrasonic motion sensor

/* SERVO MOTOR */
Servo myServo; 
int servoPin = 0;                      //change to pin servo is connected to
//int motionSensPin = A0;                //input device that is controlling our motor (motion sensor), change to correct pin that is connected
int motionSensVal = 0;                 //value in sensor
int pos = 0;                           //position

/* LED */
#define ledPin = 13;                   //lights up when trash is full, change to pin LED is connected to 
//int fullSensPin = A0;                  //input device that is controlling our LED (fullness sensor), change to correct pin that is connected
int fullSensVal = 0;                   //value in sensor


void setup() {
  /* MOTION SENSOR - OPEN LID */
  pinMode(motionTrigPin, INPUT);      //listen for response
  pinMode(motionEchoPin, OUTPUT);       //sends out output
  Serial.begin(9600);

  /* MOTION SENSOR - DETECT IF TRASH IS FULL */
  pinMode(fullTrigPin, INPUT);        //listen for response
  pinMode(fullEchoPin, OUTPUT);         //sends out output
  Serial.begin(9600);
  
  /* SERVO MOTOR */
//pinMode(motionSensPin, INPUT);
  myServo.attach(servoPin);
  Serial.begin(9600); 
  myServo.write(pos);                  //initial value is 0 
  
  /* LED */
  //pinMode(fullSensPin, INPUT);
  pinMode(ledPin, OUTPUT); 
  Serial.begin(9600);
}


void loop() {
  read_motionsensor();
  read_fullsensor();
  delay(100);
}


void read_servo(){
  for(pos = 0; pos <= 90; pos++){     //in a for loop so motor opens slowly to 90 degrees
    myServo.write(pos);
    delay(20);                        //delay of 20ms each time
  }
  delay(3000);                        //stay open for 3s
  for(pos = 90; pos >= 0; pos--){     //in a for loop so motor closes slowly
    myServo.write(pos);
    delay(20);    
  }
}


void read_motionsensor() {
  motionSensVal = digitalRead(motiontTrigPin);  //am i reading input or output
  if(motionSensVal == HIGH){ read_servo(); }
}


void read_fullsensor() {
  fullSensVal = digitalRead(fullTrigPin);
  digitalWrite(ledPin, fullSensVal);
}
