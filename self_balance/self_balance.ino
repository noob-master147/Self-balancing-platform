#include <Servo.h>

Servo sx; //servo for x axis roll
Servo sy; //servo for y axis roll

float x=0;
float y=0;
int len=0;
int serialdata=0;

void setup() {
  Serial.begin(9600);
  sx.attach(8);
  sy.attach(9);
  sx.write(90);
  sy.write(90);
  pinMode(8,OUTPUT);
  pinMode(9,OUTPUT);

}

void loop() {
  if(Serial.available()>0)
  x = Serial.read();
  y = Serial.read();
  

  int dx = map(x,-1*len,len,0,180);
  int dy = map(y, -1*len,len,0,180);

  sx.write(dx);
  sy.write(dy);
  delay(5);

}
