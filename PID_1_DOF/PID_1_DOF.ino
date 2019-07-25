#include <Wire.h>
#include <Servo.h>


const int trigPin = 2;
const int echoPin = 3;
long duration;
float distance = 0.0;

int Analog_in = A0;
Servo myservo;  // create servo object to control a servo, later attatched to D9



float elapsedTime, time, timePrev;        //Variables for time control
float distance_previous_error, distance_error;
int period = 50;  //Refresh rate period of the loop is 50ms

//ye kp, ki, kd constant set hoten hai. isko change kar kar ke dekhna
float kp=8; //Mine was 8
float ki=0.2; //Mine was 0.2
float kd=3100; //Mine was 3100
float distance_setpoint = 15;           //Should be the distance from sensor to the middle of the bar in mm
float PID_p, PID_i, PID_d, PID_total;



void setup() {
  //analogReference(EXTERNAL);
  Serial.begin(9600);  
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  myservo.attach(9); 
  myservo.write(125); 
  pinMode(Analog_in,INPUT);  
  time = millis();
}

void loop() {
  if (millis() > time+period)
  {
    time = millis();    
    distance = get_dist();   
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
  
    myservo.write(PID_total+30);  
    distance_previous_error = distance_error;
  }
}




float get_dist()
{
  digitalWrite(trigPin, LOW);
  delayMicroseconds(10);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  float duration = pulseIn(echoPin, HIGH);
  float distance= duration*0.034/2;
  Serial.print("Distance: "); 
  return(distance);
}
