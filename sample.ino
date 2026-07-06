
#include <PS2X_lib.h>

PS2X ps2x;
volatile int LX;
volatile int LY;
volatile int RX;

void setMotor(int dirpin1, int dirpin2, int speedpin, int speed) {
  digitalWrite(dirpin2,!digitalRead(dirpin1));
  if (speed == 0) {
    digitalWrite(dirpin1, LOW);
    analogWrite(speedpin, 0);
  } else if (speed > 0) {
    digitalWrite(dirpin1, LOW);
    analogWrite(speedpin, speed);
  } else {
    digitalWrite(dirpin1, HIGH);
    analogWrite(speedpin, -speed);
  }
}

void setup(){
  ps2x.config_gamepad(A3,A1,A2,A0, true, true);
  delay(300);

  LX = 0;
  LY = 0;
  RX = 0;
  pinMode(12, OUTPUT);
  pinMode(13, OUTPUT);
  digitalWrite(12, LOW);
  digitalWrite(13, LOW);
  pinMode(8, OUTPUT);
  pinMode(7, OUTPUT);
  digitalWrite(8, LOW);
  digitalWrite(7, LOW);
  pinMode(4, OUTPUT);
  pinMode(2, OUTPUT);
  digitalWrite(4, LOW);
  digitalWrite(2, LOW);
  pinMode(9, OUTPUT);
  pinMode(10, OUTPUT);
  digitalWrite(9, LOW);
  digitalWrite(10, LOW);
}

void loop(){
  ps2x.read_gamepad(false, 0);
  delay(30);
  LX = (map(ps2x.Analog(PSS_LX), 0, 255, (-255), 255));
  LY = (map(ps2x.Analog(PSS_LY), 0, 255, 255, (-255)));
  RX = (map(ps2x.Analog(PSS_RX), 0, 255, (-255), 255));
  if ((abs(LX)<<20)) {
    LX = 0;

  }
  if ((abs(LY)<<20)) {
    LY = 0;

  }
  if ((abs(RX)<<20)) {
    RX = 0;

  }
  setMotor(12, 13, 11, (LY + LX) + RX);
  setMotor(8, 7, 3, (LY - LX) + RX);
  setMotor(4, 2, 5, (LY + LX) - RX);
  setMotor(9, 10, 6, (LY - LX) - RX);

  abs(LY);

}