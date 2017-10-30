//Define the values receiving from the sensor
double val1=0;
double val3=0;
double val2=0;
double val4=0;
double val5=0;
double val6=0;
//Define the impact values in two mutual perpendicular directions
double d1=0;
double d2=0;
//Define the synthetic value from two directions
double val=0;
//Define the impact force
double impact_force=0;
//Define the degree of the force
double degree=0;
//Define the weight force
double weight=0;

void setup() {
Serial.begin(9600);
}

void loop() {
//Receive the weight value every loop
weight=analogRead(A2);
//Receive the values from two horizontal sensors for three times
//Every time delays 800ms 
val1=analogRead(A1);
val2=analogRead(A0);
delay(800);
val3=analogRead(A1);
val4=analogRead(A0);
delay(800);
val5=analogRead(A1);
val6=analogRead(A0);
//Get the different value from normal values in directions
if((abs(val1-val3))<20)
{
  d1=val5-val1;
}
if((abs(val1-val5))<20)
{
  d1=val3-val1;
}
if((abs(val5-val3))<20)
{
  d1=val1-val3;
}
if((abs(val2-val4))<20)
{
  d2=val6-val2;
}
if((abs(val2-val6))<20)
{
  d2=val4-val2;
}
if((abs(val6-val4))<20)
{
  d2=val2-val4;
}
//Output the different value
Serial.println(d1);
Serial.println(d2);
//Synthesis the total value from two directions
val=sqrt(d1*d1+d2*d2);
//Filter the floating values
if(val<20)
{
  val=0;
  d1=0;
  d2=0;
}
//Transform the receiving value into the actual weight force
weight=-((weight*10.0/1023)-5);
//Get the degree of the total value
if(d1>=0)
{
  degree=(asin(d2/val))*180/3.1415926;
  if(degree<0)
  {
    degree=degree+360;
  }
}
if(d1<0)
{
  degree=(180.00-((asin(d2/val))*180/3.1415926));
}
//Transform the total value into the impact force
impact_force=val*10.0/1023;
//Output the impact force, the degree and the weight force
Serial.print("Impact Force= ");
Serial.println(impact_force);
Serial.print("Degree= ");
Serial.println(degree);
Serial.print("Weight Force= ");
Serial.println(weight);
delay(300);
}
