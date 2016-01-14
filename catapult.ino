#include "Wire.h"       // I2C library (for WiiChuck)
#include "WiiChuck.h"   // WiiChuck library
#include <Servo.h>      // Servo library

WiiChuck chuck = WiiChuck();  // Instance WiiChuck

int z = 0;

Servo servoTurn;
int degreeMinimum = 65;              // Minimum position of servoTurn
int degreeMaximum = 115;             // Maximum position of servoTurn
int servoTurnPosition = 90;          // ServoTurn start position
int servoTurnPin = 6;
int joyX = 0;                        // X Axis of NunChuck
int velX = 0;                        // Turning speed of servoTurn

Servo servoTensor;
int servoTensorPin = 11;

Servo servoBlock;
int servoBlockPin = 8;

Servo servoReload;
int servoReloadPin = 2;

void setup() {
  chuck.begin();                               // Start WiiChuck

  servoTurn.attach(servoTurnPin);              // Start servoTurn
  servoTurn.write(servoTurnPosition);          // Initial position of servoTurn
  delay(1000);

  servoBlock.attach(servoBlockPin);            // Start servoBlock
  servoBlock.write(135);
  delay(1000);

  servoTensor.attach(servoTensorPin);          // Start servoTensor
  servoTensor.write(180);
  delay(1000);

  servoReload.attach(servoReloadPin);          // Start servoReload
  servoReload.write(90);
  delay(1000);

}

void loop() {
  delay(70);
  chuck.update();                                       // Update value of NunChuck

  z = chuck.zPressed();
  joyX = chuck.readJoyX();                              // Read joyX value of NunChuck

  if (joyX >= 20 | joyX <= -20) {                       // Check joyX value
    if (joyX >= 20) {                                   // If rotate right
      velX = map(joyX, 20, 102, 0, -2);
    } else {                                            // Else left
      velX = map(joyX, -20, -102, 0, 2);
    }

    servoTurnPosition = servoTurnPosition + velX;
    if (servoTurnPosition < degreeMinimum) {            // Left limit
      servoTurnPosition = degreeMinimum;
    } else if (servoTurnPosition > degreeMaximum) {     // Right limit
      servoTurnPosition = degreeMaximum;
    }

    servoTurn.write(servoTurnPosition);
  }

  // If shot
  if (z == 1) {
    servoBlock.write(170);          // Release servoBlock
    delay(200);

    servoTensor.write(35);          // Take down catapult
    delay(500);

    servoBlock.write(135);          // Block

    servoReload.write(180);         // Reload
    delay(220);
    servoReload.write(90);

    servoTensor.write(180);         // Stretch

    delay(300);

    z = 0;
  }
}

