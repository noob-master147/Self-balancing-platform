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
  
  int dx = map(x,0,9,30,150);
  int dy = map(y,0,9,30,150);

  dx = dx + 5 - dx%5;
  dy = dy + 5 - dy%5;
  sx.write(dx);
  delay(5);
  sy.write(dy);
  delay(5);
  Serial.println(dx);
  Serial.println(dy);

  
}
