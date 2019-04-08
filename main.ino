#include <Arduino.h>
#include <WMHead.h>
#include <WMBoard.h>
#define ECHOPIN 4
#define TRIGPIN 3

int get_distance(){
  digitalWrite(TRIGPIN, LOW);                    // Set chan Trig xuong muc thap 2uS: ~~__
  delayMicroseconds(2);
  digitalWrite(TRIGPIN, HIGH);                   //Gui mot xung 10uS muc cao vao chan Trig ~~__----------
  delayMicroseconds(10);
  digitalWrite(TRIGPIN, LOW);                    // Gui lai muc thap vao chan Trig         ~~__----------____
  int distance = pulseIn(ECHOPIN, HIGH);        // Đếm thời gian (đơn vị us) cho tới khi chân ECHOPIN có sườn lên
  distance= distance/58;                        // Qui đổi thời gian ra khoảng cách
  delay(100);
  return distance;
}


void setup() {
  Serial.begin(9600);
  pinMode(ECHOPIN, INPUT);
  pinMode(TRIGPIN, OUTPUT);
}

void loop() {
  Serial.println(get_distance());
}

