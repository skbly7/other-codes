//2,3 left motor
//4,5 right motor

int yaad[1000];
long last;
int cur;
void setup()
{
cur=0;
pinMode(2,OUTPUT);
pinMode(3,OUTPUT);
pinMode(4,OUTPUT);
pinMode(5,OUTPUT);
pinMode(8,INPUT);
pinMode(9,INPUT);
pinMode(10,INPUT);
pinMode(11,INPUT);
Serial.begin(9600);
last=millis();
}
void stopr()
{
yaad[cur++]=3;
Serial.println("Stop");
digitalWrite(2,LOW);
analogWrite(3,0);
digitalWrite(4,LOW);
analogWrite(5,0);
}
void loop()
{
  int d0=digitalRead(8);
  int d1=digitalRead(9);
  int d2=digitalRead(10);
  int d3=digitalRead(11);
  //Serial.print(d0);
  //Serial.print(d1);
  //Serial.print(d2);
  //Serial.println(d3);
  //straight();
  
  if(last+10<millis())
  {
    if(d0==1)
    {
      straight();
    }
    else if(d1==1)
    {
      left();
    }
    else if(d2==1)
    {
      right();
    }
    else
    stopr();
  }
}
void straight()
{
yaad[cur++]=0;
Serial.println("Stright");
digitalWrite(2,LOW);
analogWrite(3,100);
digitalWrite(4,LOW);
analogWrite(5,100);
}
void left()
{
yaad[cur++]=1;
Serial.println("Left");
digitalWrite(2,LOW);
analogWrite(3,0);
digitalWrite(4,LOW);
analogWrite(5,100);
}
void right()
{
yaad[cur++]=2;
Serial.println("Right");
digitalWrite(2,LOW);
analogWrite(3,100);
digitalWrite(4,LOW);
analogWrite(5,0);
}
