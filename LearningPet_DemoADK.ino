/*

 Learning Pet ADK Demo
 ---------------------
 RobotGrrl.com/LearningPet
 
 Licensed under BSD 3-Clause license
 
 Based off of the ADK usb digitalRead example:
 
 (c) 2011 D. Cuartielles & A. Goransson
 http://arduino.cc, http://1scale1.com
 
 */

#include <Max3421e.h>
#include <Usb.h>
#include <AndroidAccessory.h>

#define  LED1_RED       8       // eyes
#define  LED1_GREEN     10      // eyes
#define  LED1_BLUE      9       // eyes

int R_start = 0;
int G_start = 0;
int B_start = 0;
int R_pre = 0;
int G_pre = 0;
int B_pre = 0;

// accessory descriptor. It's how Arduino identifies itself to Android
char applicationName[] = "LearningPet_DemoADK"; // the app on your phone
char accessoryName[] = "LearningPet_DemoADK"; // your Arduino board
char companyName[] = "RobotGrrl.com";

// make up anything you want for these
char versionNumber[] = "1.0";
char serialNumber[] = "1";
char url[] = "http://robotgrrl.com"; // the URL of your app online

// button variables
int irPin = A14;
int val;

// counters
long timer = millis();

// initialize the accessory:
AndroidAccessory usb(companyName, applicationName,
accessoryName,versionNumber,url,serialNumber);

void setup() {
  // start the connection to the device over the USB host:
  usb.powerOn();
  pinMode(irPin, INPUT); 

  digitalWrite(LED1_RED, 1);
  digitalWrite(LED1_GREEN, 1);
  digitalWrite(LED1_BLUE, 1);

  pinMode(LED1_RED, OUTPUT);
  pinMode(LED1_GREEN, OUTPUT);
  pinMode(LED1_BLUE, OUTPUT);

  analogWrite(LED1_RED, 128);
  analogWrite(LED1_GREEN, 128);
  analogWrite(LED1_BLUE, 128);

}

void loop() {
  /* Read button state */
  val = analogRead(irPin);
  val /= 4;

  /* Print to usb */
  if(millis()-timer>100) { // sending 10 times per second
    if (usb.isConnected()) { // isConnected makes sure the USB connection is ope
      usb.beginTransmission();
      usb.write(val);
      usb.endTransmission();
    }
    //updateLights();
    timer = millis();
  }

}

void updateLights() {

  R_start = int(random(0, 200));
  G_start = int(random(0, 200));
  B_start = int(random(0, 200));

  fade2( R_pre,    G_pre,      B_pre, 
  R_start,  G_start,    B_start, 
  1);

  R_pre = R_start;
  G_pre = G_start;
  B_pre = B_start;

}

void fade2 ( int start_R,  int start_G,  int start_B, 
int finish_R, int finish_G, int finish_B,
int stepTime ) {

  int skipEvery_R = 256/abs(start_R-finish_R); 
  int skipEvery_G = 256/abs(start_G-finish_G);
  int skipEvery_B = 256/abs(start_B-finish_B);

  for(int i=0; i<256; i++) {

    if(start_R<finish_R) {
      if(i<=finish_R) {
        if(i%skipEvery_R == 0) {
          analogWrite(LED1_RED, i);
        } 
      }
    } 
    else if(start_R>finish_R) {
      if(i>=(256-start_R)) {
        if(i%skipEvery_R == 0) {
          analogWrite(LED1_RED, 256-i); 
        }
      } 
    }

    if(start_G<finish_G) {
      if(i<=finish_G) {
        if(i%skipEvery_G == 0) {
          analogWrite(LED1_GREEN, i);
        } 
      }
    } 
    else if(start_G>finish_G) {
      if(i>=(256-start_G)) {
        if(i%skipEvery_G == 0) {
          analogWrite(LED1_GREEN, 256-i); 
        }
      } 
    }

    if(start_B<finish_B) {
      if(i<=finish_B) {
        if(i%skipEvery_B == 0) {
          analogWrite(LED1_BLUE, i);
        } 
      }
    } 
    else if(start_B>finish_B) {
      if(i>=(256-start_B)) {
        if(i%skipEvery_B == 0) {
          analogWrite(LED1_BLUE, 256-i); 
        }
      } 
    }

    delay(stepTime);

  }

}

