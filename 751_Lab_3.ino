#include "Stepper.h"
#define STEPS  32 
Stepper small_stepper(STEPS, 8, 10, 9, 11);

const int sensorPin = A0;  
int sensorValue = 0;       
float Vin = 5;             
float Vout = 0;            
float Rref = 999;         
float R = 0;              
volatile int state = 0;
int Meter, Angle; 

void setup ()
{
  Serial.begin(9600);      
  pinMode(2, INPUT_PULLUP);
  pinMode(3, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(2), Reset, FALLING);
  attachInterrupt(digitalPinToInterrupt(3), Start, FALLING);
  small_stepper.setSpeed(500);
}

void loop ()
{
  sensorValue = analogRead(sensorPin);  
  Vout = (Vin * sensorValue) / 1023;    
  R = Rref * (1 / ((Vin / Vout) - 1)); 
  Serial.print("R: ");                  
  Serial.println(R);                    
  delay(1000);                        

  Meter=map((R),0,10000,0,2048);
  //Angle=map((Meter),0,60,0,2048);
  
  if (state==2)
  {
    small_stepper.step(Angle);
  }

  if (state==1)
  {
   small_stepper.step(-Angle); 
  }
   state=0;
}

void Reset()
{
  if(digitalRead(2)==LOW)
  {
    state=1;
    Angle=Angle;  
  }
  else
  {
    state=0;
  }
}

void Start()
{
    if(digitalRead(3)==LOW)
  {
    state=2;
    Angle=Meter;  
  }
  else
  {
    state=0;
  }
}
