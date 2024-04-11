//This file will be split up into mulltiple files to represent necessary parts later on

// Main Programmer: Vianey Rivera
// Other programmers: Tami Sojinrin
// Date: March 29, 2024 at 8:00pm

/*
Ultrasonic Sensor -
Purpose: Be able to detect when the trash bin is full. 
Purpose: Be able to count how much trash has been thrown out. If possible 
track what kind of trash it is such as metal, plastic, paper, and etc.
*** Important Note: This may be change for another sensor. ***
4 Digit 7 Segment Display (Not Needed But would be fun to include) -
Purpose: Should be able to display the sum of waste in the trash bin. 
Should work with the ultrasonic sensor or the capactive sensor.

Ultrasonic Sensor 2 -
Purpose: It could be used for motion sensor to open the trash bin lid.

Servo Motor -
Purpose: Be able to ratate about 90 degrees to open the lid, wait for a few 
miliseconds, and then rotate the opposite way to close the lid back.
*** Important Note: Will need some hardware components to help with rotation. ***

LEDs -
Purpose: One led blinks when trash is dispose in the trashbin. Another led 
will lit up when trashbin is full and turn off when its not full.
*/


#include <Servo.h>
#include "SevSeg.h"
SevSeg sevseg;

//Ultrasonic senors
const int anPin = 0; long anVolt, cm; //Sum of trash 
const int anPin2 = 1; long anVolt2, cm2; //Full trash bin?
  //motion sensor
long duration;                    //time it takes for the waves to bounce back after hitting an object
int distance;                     //distance from the object
  //pin that sends out output for ultrasonic motion sensor 
#define echoPin 2 
  //pin that will listen for response for unltrasonic motion sensor
#define trigPin 3 
  //max object distance between motion sensor and object to activate sensor
#define maxDistance 10     

//Servo motor
Servo myservo; 
int pos = 0;

//LEDs
int LED = 13; 
int LED2 = 12;
int trash = 0;

//setup code here, to run once:
void setup() {
  //Motion Sensor
  pinMode(trigPin, OUTPUT);    //sends out output
  pinMode(echoPin, INPUT);     //listen for response
  Serial.begin(9600);
  
  //Servo Motor
  Serial.begin(9600); 
  myservo.attach(9);
  
  //LEDs
  pinMode(LED, OUTPUT); 
  pinMode(LED2, OUTPUT); 
  
  //7 seg Display
  byte numDigits = 4; 
  byte digitPins[] = {2,3,4,5};
  byte segmentPins[] = {6,7,8,9,10,11,12,13};
  bool resistorsOnSegments = 0;
  sevseg.begin(COMMON_CATHODE, numDigits, digitPins, segmentPins, resistorsOnSegments);
  sevseg.setBrightness(90);
}

//main code here, to run repeatedly:
void loop() {
  read_ultrasensor();         // Initialize the range of an object
  print_range();              // Test out code to know how far an object is.
  //blink_count(); // Count the amount of trash
  //full_bin();
  delay(100);

}

void read_ultrasensor() {
  //TAMI
  digitalWrite(trigPin, HIGH):
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW):
  delayMicroseconds(2);

  duration = pulseIn(echoPin, HIGH);
  distance = duration * 0.034 / 2;    //read duration and distance(cm)

  if(distance == maxDistance){
    //do something with LEDS
  };

  
  //VIANEY
  // Vcc to 5V. GND to GND. Trig or Echo to A0.
  // First sensor
  anVolt = analogRead(anPin); //aPin = A0
  cm = anVolt/2;
  // Second sensor
  anVolt2 = analogRead(anPin2); //aPin = A1
  cm2 = anVolt2/2;
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

void open_lid() {
  // Servo motor will be connect to the hinges of the trashbin.
  // Yellow wire connected to pin 9. Brown wire to GND. Red wire to 5V.
  // Using the ultrasonic sensor and a servo motor to detect hand's movement and 
  // make the lid turn 180 degrees counter-clockwise and clockwise.
  if(cm2 <= 5) {
    for(pos = 0; pos <= 180; pos += 1) { //Turn clockwise 180 degrees
      myservo.write(pos);
      delay(15);
    } 
    delay(2000); // Wait 2 seconds at this position
    for(pos = 180; pos >= 0; pos -= 1) { // Turn counter-clockwise 180 degrees
      myservo.write(pos);
      delay(15);
    }
  }
}
