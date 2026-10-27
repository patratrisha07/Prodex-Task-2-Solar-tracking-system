#include <Servo.h> //include the servo library

Servo hservo;
Servo vservo; //create two servo objects to control both servos

const int tlpin = A0;
const int trpin = A1;
const int blpin = A2;
const int brpin = A3; //naming the pins (top-left, top-right, bottom-left, bottom-right)

int hangle = 90;
int vangle = 90; //setting the current angles of both servos at 90° (the middle position) so that the solar panel is centred

int threshold = 500; //limit within which rotation of panel not required based on real-world projections and testing

void setup() {
  hservo.attach(9);
  vservo.attach(10);
  hservo.write(hangle);
  vservo.write(vangle);
  
  Serial.begin(9600);
}

void loop() {
  int tl = analogRead(tlpin);
  int tr = analogRead(trpin);
  int bl = analogRead(blpin);
  int br = analogRead(brpin);
  
  int left = tl + bl;
  int right = tr + br;
  int top = tl + tr;
  int bottom = bl + br;
  
  int hdiff = left - right;
  int vdiff = top - bottom;
  
  if (hdiff > threshold) {
    hangle = hangle - 1; //when light intensity higher on left than right, horizontal angle is decreased by 1 degree
  }
  else if (hdiff < -threshold) {
    hangle = hangle + 1; //when light intensity higher on right than left, horizontal angle is increased by 1 degree
  }
  
    if (vdiff > threshold) {
    vangle = vangle + 1; //when light intensity higher on top than bottom, vertical angle is increased by 1 degree
  }
  else if (vdiff < -threshold) {
    vangle = vangle - 1; //when light intensity higher on bottom than top, vertical angle is decreased by 1 degree
  }
 
  //as the angle range of servo is 0 to 180 degrees, so this stops the angle from growing outside 0-180
  if (hangle > 180) hangle = 180;
  if (hangle < 0) hangle = 0;
  if (vangle > 180) vangle = 180;
  if (vangle < 0) vangle = 0;
  
  hservo.write(hangle);
  vservo.write(vangle); // to send the new angles to the serv0
  
  if (hdiff > threshold || hdiff < -threshold || vdiff > threshold || vdiff < -threshold) {
    Serial.print("\nTracking");
  }
  else Serial.print("\nStable");
  
  Serial.print("\nH: ");
  Serial.print(hangle);
  Serial.print("\nV: ");
  Serial.print(vangle);
  
  Serial.print("\nhdiff: ");
Serial.print(hdiff);
Serial.print("  vdiff: ");
Serial.print(vdiff);
  
  delay(300); // waits for 300ms before next loop starts, giving the servo sufficient time to move
}  
  