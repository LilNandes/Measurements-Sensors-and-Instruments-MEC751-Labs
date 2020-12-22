#include <PID_v1.h>
double Setpoint, Input, Output;
double Kp=10, Ki=25, Kd=0;
PID myPID(&Input, &Output, &Setpoint, Kp, Ki, Kd, DIRECT);

int motorpin1 = 5;
int motorpin2 = 6;
int a;

#define ThermistorPin A0
int Vo;
float R1 = 10000;
float logR2, R2, T, Tf, Tc;
float c1 = 1.009249522e-03, c2 = 2.378405444e-04, c3 = 2.019202697e-07;


void setup() {
  // put your setup code here, to run once:
  pinMode(motorpin1,OUTPUT);
  pinMode(motorpin2,OUTPUT);
  Serial.begin(9600);
  Serial.println("Temperature Setpoint");
  Setpoint=35.00;
  myPID.SetMode(AUTOMATIC);
}

void loop() {
  Vo = analogRead(ThermistorPin);
  R2 = R1 * (1023.0 / (float)Vo - 1.0);
  logR2 = log(R2);
  T = (1.0 / (c1 + c2*logR2 + c3*logR2*logR2*logR2));
  Tc = T - 273.15;
  Tf = (Tc * 9.0)/ 5.0 + 32.0; 

  //Serial.print("Temperature: "); 
//  Serial.print(Tf);
//  Serial.print(" F; ");
  Serial.print(Tc);
  //Serial.print(" C");   

  delay(500);
  Input=Tc;
  myPID.Compute();
  Serial.print(",");
  Serial.println(Setpoint);
  a=map((Output),0,255,-255,0);
 

  if(Tc>Setpoint)
  {
  analogWrite(motorpin1, -1*a);
  }

  if(Tc<Setpoint)
  {
  analogWrite(motorpin1, 0);
  }


//     digitalWrite(motorpin1,LOW);
//     digitalWrite(motorpin2,HIGH);
//     delay(5000);
//     digitalWrite(motorpin1,HIGH);
//     digitalWrite(motorpin2,LOW);
//     delay(10000);
}
