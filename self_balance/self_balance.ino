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
  while(Serial.available()==0){}
  
  int a = Serial.read();
  int x = a/10;
  int y = a%10;
  
  int dx = map(x,0,9,0,180);
  int dy = map(y,0,9,0,180);
    sx.write(dx);
  sy.write(dy);
  delay(10);

  
}
