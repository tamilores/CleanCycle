//This file will be split up into mulltiple files to represent necessary parts later on

// Programmers: Vianey Rivera, Tami Sojinrin
// Date: March 29, 2024 at 8:00pm

/* 
Ultrasonic Sensor -
Purpose: It could be used for motion sensor to open the trash bin lid.

Ultrasonic Sensor 2 -
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
long duration;                   //time it takes for the waves to bounce back after hitting an object
int distance;                    //distance from the object
                                 //pin that sends out output for ultrasonic motion sensor 
#define echoPin 2                 
                                 //pin that will listen for response for unltrasonic motion sensor
#define trigPin 3 
                                 //max object distance between motion sensor and object to activate sensor
#define maxDistance 10     


/* SERVO MOTOR */
Servo myServo; 
int servoPin = 0;                //change to pin servo is connected to
int sensPin = A0;                //input device that is controlling our motor (motion sensor), change to correct pin that is connected
int sensStat = 0;                //value in sensor
int pos = 0;                     //position


/* LED */
int LED = 13;                    //lights up when trash is full


void setup() {
  /* MOTION SENSOR */
  pinMode(trigPin, OUTPUT);      //sends out output
  pinMode(echoPin, INPUT);       //listen for response
  Serial.begin(9600);
  
  /* SERVO MOTOR */
  pinMode(sensPin, INPUT);
  myServo.attach(servoPin);
  Serial.begin(9600); 
  myServo.write(pos);            //initial value is 0 
  
  /* LED */
  pinMode(LED, OUTPUT); 
}


void loop() {
  read_ultrasensor();        
  delay(100);
}


void read_servo(){
  for(pos = 0; pos <= 90; pos++){     //in a for loop so motor opens slowly
    myServo.write(pos);
    delay(20);                        //delay of 20ms each time
  }
  delay(3000);                        //stay open for 3s
  for(pos = 90; pos >= 0; pos--){     //in a for loop so motor closes slowly
    myServo.write(pos);
    delay(20);    
  }
}


void read_ultrasensor() {
  digitalWrite(trigPin, HIGH):
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW):
  delayMicroseconds(2);

  duration = pulseIn(echoPin, HIGH);
  distance = duration * 0.034 / 2;    //read duration and distance(cm)

  if(distance <= maxDistance){
    read_servo();
  };
  ////////////////////////////////////////////////
  sensStat = digitalRead(sensPin);
  if(sensStat == HIGH){
    read_servo();
  }
}







void full_trashbin() {
  // Expect the ultrasonic senor to be on bottom of the trashbin lid.
  // Or it could be placed on the side of the trashbin.
  if(cm2 <= 5) { 
    Serial.println("Trash bin is full!!!"); 
    // LED+ & one 1k-ohms reisitor to pin 12 and LED- to GND.
    pinMode(LED2,HIGH);
  }
  else { pinMode(LED2,LOW); }
}

//Placeholder to know if an object is drop into bin.
//Also should count how much trash is thrown out.
void blink_count() {
  // Light up when it detect an object in front of the sensor.
  // LED+ & one 1k-ohms reisitor to pin 13 and LED- to GND.
  pinMode(LED,HIGH); delay(500);
  pinMode(LED,LOW); delay(500);
  // Ultrasonic sensor 
  if(cm >= 2 && cm <= 300) { trash += 1; } 
  // 4 Digit 7-Segment Display
  // Rows 22 to 27 for 10 pins. Five 1k-ohms resistors.
  sevseg.setNumber(trash);
  sevseg.refreshDisplay();
}

void print_range() { // This function will be deleted.
  if(cm <= 500 && cm >= 2) {
    blink_count();
    // Detect how far an object is from the ultrasonic sensor.
    Serial.print("Range = ");
    Serial.print(cm);
    Serial.println(" cm");
  }
  else { Serial.println("Detect nothing or item is out of Range!"); }
}
