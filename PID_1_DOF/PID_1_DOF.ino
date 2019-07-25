#include <Wire.h>
#include <Servo.h>

const int numReadings = 5;
int readings[numReadings];
int readIndex = 0;                  // the index of the current reading
int readtotal = 0;                  // the running total
int readaverage = 0;

const int trigPin = 5;
const int echoPin = 7;
long duration;
float distance = 0.0;

int Analog_in = A0;
Servo myservo;  


float elapsedTime, time, timePrev;        
float distance_previous_error, distance_error;
int period = 50;                                                                   //Refresh rate


float kp=8; 
float ki=0.2; 
float kd=3100; 
float distance_setpoint = 17;                                                      //distance from sensor to the middle of the bar
float PID_p, PID_i, PID_d, PID_total;



void setup() {
 
  Serial.begin(9600);  
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  myservo.attach(9); 
  pinMode(Analog_in,INPUT);  
  for (int thisReading = 0; thisReading < numReadings; thisReading++) {
    readings[thisReading] = 0;
  }
  myservo.write(170);
  delay(5000);
  time = millis();
}

void loop() {
  if (millis() > time+period)
  {
    time = millis();    
    distance = constrain(get_dist(),5,30);   
    distance_error = distance_setpoint - distance;   
    PID_p = kp * distance_error;
    float dist_diference = distance_error - distance_previous_error;     
    PID_d = kd*((distance_error - distance_previous_error)/period);
      
    if(-3 < distance_error && distance_error < 3)
    {
      PID_i = PID_i + (ki * distance_error);
    }
    else
    {
      PID_i = 0;
    }
  
    PID_total = PID_p + PID_i + PID_d;  
    PID_total = map(PID_total, -150, 150, 0, 150);
  
    if(PID_total < 20){PID_total = 20;}
    if(PID_total > 160) {PID_total = 160; } 
  
    myservo.write(PID_total + 30);  
    distance_previous_error = distance_error;
  }
}




float get_dist()
{
  readtotal = readtotal - readings[readIndex];
  
  digitalWrite(trigPin, LOW);
  delayMicroseconds(10);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  float duration = pulseIn(echoPin, HIGH);
  readings[readIndex] = duration*0.034/2;
  readtotal = readtotal + readings[readIndex];
  readIndex = readIndex + 1;

  if (readIndex >= numReadings) {
    readIndex = 0;
  }

  readaverage = readtotal / numReadings;
  delay(1);        
  Serial.println(readaverage); 
  return(readaverage);
}
