#include <Servo.h>

Servo sx; //servo for x axis roll
Servo sy; //servo for y axis roll


int len=0;


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
  while(Serial.available()==0)
  {}
    String a=Serial.readString();
    int b = a.toInt();
    Serial.println(b+12);

    //int dx = map(x,-1*len,len,0,180);
    //int dy = map(y, -1*len,len,0,180);

  
}
