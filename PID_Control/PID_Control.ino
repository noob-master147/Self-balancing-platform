double sensed_output, setpoint, control_signal;
double kp, ki, kd;
int T =50;
unsigned long last_time;
double total_error, last_error;



void setup() {
  // put your setup code here, to run once:

}

void loop() {
  PID_Control();

}

void PID_Control()
{

  unsigned long current_time =millis();
  int delta_time = current_time - last_time;
  
  if(delta_time>T)
  {

    double error = setpoint - sensed_output;
    total_error +=error;
    if(total_error>=255) total_error = 255;
    else if(total_error<=0) total_error = 0;
    double delta_error = error -last_error;

    control_signal = kp*error +ki*T*total_error +(kd/T)*delta_error;
    if(total_error>=255) total_error = 255;
    else if(total_error<=0) total_error = 0;
    
    last_error = error;
    last_time = current_time;
  }
}
