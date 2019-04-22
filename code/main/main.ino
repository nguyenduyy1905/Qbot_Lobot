#include <Arduino.h>
#include <WMHead.h>
#include <WMBoard.h>
#define ECHOPIN 4
#define TRIGPIN 3

double angle_rad = PI / 180.0;
double angle_deg = 180.0 / PI;
double distance;
WMRGBLed rgbLED(0, 4);
WMDCMotor motor1(8);
WMDCMotor motor2(7);

WMLineFollower lineFollower2(A4, A5);
WMMatrixLed matrixLed(5);

int oldDistance;

int get_distance() {
  digitalWrite(TRIGPIN, LOW);                    // Set chan Trig xuong muc thap 2uS: ~~__
  delayMicroseconds(2);
  digitalWrite(TRIGPIN, HIGH);                   //Gui mot xung 10uS muc cao vao chan Trig ~~__----------
  delayMicroseconds(10);
  digitalWrite(TRIGPIN, LOW);                    // Gui lai muc thap vao chan Trig         ~~__----------____
  int distance = pulseIn(ECHOPIN, HIGH);        // Đếm thời gian (đơn vị us) cho tới khi chân ECHOPIN có sườn lên
  distance = distance / 58;                     // Qui đổi thời gian ra khoảng cách
  delay(100);
  return distance;
}


void setup() {
  Serial.begin(9600);
  pinMode(ECHOPIN, INPUT);
  pinMode(TRIGPIN, OUTPUT);
  oldDistance = get_distance();
}

void loop() {
  int temp = get_distance();
  int delta = temp - oldDistance;
  if (temp < 100 & temp > -100)
  {
    distance = temp;
  }
  else
  {
    return; 
  }

  matrixLed.showNum(0, distance);

  if (distance > 5 & distance < 50)
  {
    if (distance > 30 ) {
      motor1.reverseRun(28);
      motor2.reverseRun(30);
      rgbLED.setColor(0, 255, 0, 0);
      rgbLED.show();
    } else {
      motor1.reverseRun(-28);
      motor2.reverseRun(-30);
      rgbLED.setColor(0, 0, 255, 0);
      rgbLED.show();
    }
  }
  else
  {
    if (distance > 50 & distance < 100)
    {
      motor1.reverseRun(15);
      motor2.reverseRun(-15);
      delay(500);
    }
    else
    {
      motor1.reverseRun(0);
      motor2.reverseRun(0);
      rgbLED.setColor(0, 0, 0, 0);
      rgbLED.show();
    }

  }
}
