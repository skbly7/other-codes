char yaad[1500]; 
int motor1[] = {2,3};
int motor2[] = {4,5};
int d[] = {8,9,10,11};
int cur=0;
long start;
void setup() 
{
  Serial.begin(9600);
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
  motor2[0]=3;
  motor2[1]=2;
  motor1[0]=5;
  motor1[1]=4;
}
void traceback()
{
  int input;
  swap_pin();
  cur=cur-2;
  while(1)
  {
   input=yaad[--cur];
   if(input==0)
     forward_2();
   if(input==1)
     left_2(); 
   if(input==2)
     right_2();
     delay(20);
   if(cur==0)
   break;
  }
}
void traceback2()
{
  int input;
  rotate();
  while(1)
  {
   input=yaad[--cur];
   if(input==0)
     forward_2();
   if(input==1)
     left_2(); 
   if(input==2)
     right_2();
     delay(20);
   if(cur==0)
   break;
  }
}
void give_response(int y){
  if(cur<1400)
 yaad[cur++]=y;
}
void loop() {
    int input[4];
    int i;
  int y=-1;
  // put your main code here, to run repeatedly:

if(millis()>start+20)
{
   for(i=0;i<4;i++)
   input[i]=digitalRead(d[i]);
 if(input[0] == HIGH)
 {
   y=0;
   forward();
 }
 else if(input[1] == HIGH)
 {
    y=1;
    left();
 }
 else if(input[2] == HIGH)
 {
   y=2; 
   right();
 }
 else if(input[3] == HIGH)
 {
    traceback();
 }
 else
 stopr();
 give_response(y);
 start=millis();
}
}

void stopr()
{
  Serial.println("stop");
  digitalWrite(motor1[0], LOW);
  digitalWrite(motor1[1], LOW);
  digitalWrite(motor2[0], LOW);
  digitalWrite(motor2[1], LOW);
}

void forward()
{
  Serial.println("forward");
  digitalWrite(motor1[0], HIGH);
  analogWrite(motor1[1], 156);
  digitalWrite(motor2[0], HIGH);
  analogWrite(motor2[1], 156);
}

void backward()
{
  Serial.println("back");
  digitalWrite(motor1[0], LOW);
  analogWrite(motor1[1], 100);
  digitalWrite(motor2[0], LOW);
  analogWrite(motor2[1], 100);
}

void left()
{
  Serial.println("left");
  digitalWrite(motor1[0], HIGH);
  analogWrite(motor1[1], 156);
  digitalWrite(motor2[0], LOW);
  analogWrite(motor2[1], 100);
}

void right()
{
  Serial.println("right");
  digitalWrite(motor1[0], LOW);
  analogWrite(motor1[1], 100);
  digitalWrite(motor2[0], HIGH);
  analogWrite(motor2[1], 156);
}
void stopr_2()
{
  Serial.println("stop");
  digitalWrite(motor1[0], LOW);
  digitalWrite(motor1[1], LOW);
  digitalWrite(motor2[0], LOW);
  digitalWrite(motor2[1], LOW);
}

void forward_2()
{
  Serial.println("forward");
  analogWrite(motor1[0], 100);
  digitalWrite(motor1[1], LOW);
  analogWrite(motor2[0], 100);
  digitalWrite(motor2[1], LOW);
}

void backward_2()
{
  Serial.println("back");
  analogWrite(motor1[0], 156);
  digitalWrite(motor1[1], HIGH);
  analogWrite(motor2[0], 156);
  digitalWrite(motor2[1], HIGH);
}

void right_2()
{
  Serial.println("left");
  analogWrite(motor1[0], 100);
  digitalWrite(motor1[1], LOW);
  analogWrite(motor2[0], 156);
  digitalWrite(motor2[1], HIGH);
}

void left_2()
{
  Serial.println("right");
  analogWrite(motor1[0], 156);
  digitalWrite(motor1[1], HIGH);
  analogWrite(motor2[0], 100);
  digitalWrite(motor2[1], LOW);
}
