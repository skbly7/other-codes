char yaad[1500];
int motor1[] = {9,8};
int motor2[] = {3,2};
int d[] = {7,6,5,4};
int cur=0;
long start;
void setup() {
  pinMode(motor1[0], OUTPUT);
  pinMode(motor1[1], OUTPUT);
  pinMode(motor2[0], OUTPUT);
  pinMode(motor2[1], OUTPUT);
  pinMode(d[0], INPUT);
  pinMode(d[1], INPUT);
  pinMode(d[2], INPUT);
  pinMode(d[3], INPUT);
  start=millis();
}
void swap_pin()
{
motor1[0]=2;
motor1[0]=3;
motor2[0]=8;
motor2[0]=9;
}
void traceback()
{
  int input;
  swap_pin();
  while(1)
  {
   input=yaad[--cur];
   if(input==0)
     forward();
   if(input==1)
     backward();
   if(input==2)
     right();
   if(input==3)
     left(); 
   if(input==4)
     stopr(); 
     delay(10);
     if(cur==0)
     break;
  }
}
void give_response(int y){
 yaad[cur++]=y;
}
void loop() {
    int input[4];
    int i;
  int y=-1;
  // put your main code here, to run repeatedly:
  for(i=0;i<4;i++)
   input[i]=digitalRead(d[i]);
 if(input[0] == LOW && input[1] == HIGH && input[2] == LOW && input[3] == LOW)
 {
   y=0;
   forward();
 }
 if(input[0] == HIGH && input[1] == LOW && input[2] == HIGH && input[3] == LOW)
  {
    y=1;
    backward();
  }
 if(input[0] == LOW && input[1] == LOW && input[2] == HIGH && input[3] == LOW)
 {
   y=2; 
   right();
 }
 if(input[0] == HIGH && input[1] == LOW && input[2] == LOW && input[3] == LOW)
 {
    y=3;
    left();
 }
 if(input[0] == LOW && input[1] == LOW && input[2] == LOW && input[3] == LOW)
 {
    y=4;
    stopr();
 }
 if(input[0] == HIGH && input[1] == HIGH && input[2] == HIGH && input[3] == HIGH)
   traceback();
  if(millis()>start+10)
  {
   give_response(y);
   start=millis();
  }
}

void stopr()
{
  Serial.println("STOP");
  digitalWrite(motor1[0], LOW);
  digitalWrite(motor1[1], LOW);
  digitalWrite(motor2[0], LOW);
  digitalWrite(motor2[1], LOW);
}

void forward()
{
  Serial.println("FORWARD");
  digitalWrite(motor1[0], HIGH);
  digitalWrite(motor1[1], LOW);
  digitalWrite(motor2[0], HIGH);
  digitalWrite(motor2[1], LOW);
}

void backward()
{
  
  Serial.println("BACK");
  digitalWrite(motor1[0], LOW);
  digitalWrite(motor1[1], HIGH);
  digitalWrite(motor2[0], LOW);
  digitalWrite(motor2[1], HIGH);
}

void left()
{
  
  Serial.println("LEFT");
  digitalWrite(motor1[0], HIGH);
  digitalWrite(motor1[1], LOW);
  digitalWrite(motor2[0], LOW);
  digitalWrite(motor2[1], LOW);
}

void right()
{
  Serial.println("RIGHT");
  digitalWrite(motor1[0], LOW);
  digitalWrite(motor1[1], LOW);
  digitalWrite(motor2[0], HIGH);
  digitalWrite(motor2[1], LOW);
}
