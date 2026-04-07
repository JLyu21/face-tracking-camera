#include <Servo.h>

// create servo objects
Servo x;
Servo y;

// values sent by python
int cx;
int cy;
int w;
int h;

int xpos = 90;
int ypos = 130;

// frame center
int frameCenterX = 320;
int frameCenterY = 240;

// tracking parameters
int deadZone = 20;     // pixels where no movement occurs
float gain = 0.02;     // movement sensitivity

void setup() {
  Serial.begin(9600);
  Serial.setTimeout(10); // Very fast timeout

  x.attach(9);
  y.attach(10);

  x.write(90);
  y.write(130);
}

void loop() {

  if (Serial.available() > 0) {

    // DATA RETRIEVAL
    String msg = Serial.readStringUntil('\n');
    msg.trim();

    int firstComma = msg.indexOf(",");
    int secondComma = msg.indexOf(",", firstComma + 1);
    int thirdComma = msg.indexOf(",", secondComma + 1);

    cx = msg.substring(0, firstComma).toInt();
    cy = msg.substring(firstComma + 1, secondComma).toInt();
    w  = msg.substring(secondComma + 1, thirdComma).toInt();
    h  = msg.substring(thirdComma + 1).toInt();

    // ================================
    // CAMERA TRACKING
    // ================================

    // move right 
    if ((cx > 160) && (cx - 160 > 40)) { xpos +=1; } 
    // move left 
    if ((cx < 160) && (160 - cx > 40)) { xpos -=1; } 

    // move up
    if ((cy < 120) && (120 - cy > 30)){ ypos +=1; } 
    // move down
    if ((cy > 120) && (cy - 120 > 30)) { ypos -=1; }

    constrain(xpos, 0, 180);
    x.write(xpos);
    ypos = constrain(ypos, 0, 145);
    y.write(ypos);
    //delay(300);


    // ================================
    // DEBUG OUTPUT
    // ================================

    /*
    if (msg.length() > 0) {
      Serial.print("X_MIDDLE: ");
      Serial.print(cx);
      Serial.print(", Y_MIDDLE: ");
      Serial.print(cy);
      Serial.print(", ");
      Serial.print(w);
      Serial.print(", ");
      Serial.println(h);
      
    }
    */

  }
}