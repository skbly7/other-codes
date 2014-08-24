int sensorPin[] = {A0, A1, A2, A3, A4};    //check before run
int motor_left[] = {7, 6};
int motor_right[] = {8, 9};
int totalpin = 5;  //check before run
const int ledPin = 9;     //check before run
int blocksensor = 4;
int voidsensor = 5;

int sensorValue[] = {0, 0, 0, 0, 0};
int sensorMin[] = {1023, 1023, 1023, 1023, 1023};
int sensorMax[] = {0, 0, 0, 0, 0};
float sensorAvg[] = {0.0, 0.0, 0.0, 0.0, 0.0};
/*
calib part over here..!! :D  :P
lets tell bot where it is... :) 
it is his right..!!!!
*/
int present[5];
void present_situation()
{
  int i;
  for (i = 0; i < totalpin; i++)
  {
      present[i] = input_a(sensorPin[i], sensorAvg[i]);
  }
}
/*
but ohh no..! more work.. :/
execution part begins.. :P
*/

int count;
int problems[10];
int wtd;    //Tells us What To Do.. i.e. wtd.. :P weird.. :D
int temp_inputs[10];
char temp_inputs_sk[10];
int input_a(int sensor, int avg)
{
  int i;
  i = analogRead(sensor);
  if (i > avg)
    return 0;
  return 1;
}

int input_d(int sensor)
{
  return (digitalRead(sensor));
}
int present2[10];
void present_situation2()
{
  int i;
  for (i = 0; i < totalpin; i++)
  {
    if (input_a(sensorPin[i], sensorAvg[i]) == 1)
      present2[i] = '0';
    else
      present2[i] = '1';
  }
}
void left_forward(int s = 255)
{
  digitalWrite(motor_left[0], HIGH);
  analogWrite(motor_left[1], 255 - s);
}
void right_forward(int s = 255)
{
  digitalWrite(motor_right[0], HIGH);
  analogWrite(motor_right[1], 255 - s);
}
void left_backward(int s = 255)
{
  digitalWrite(motor_left[0], LOW);
  analogWrite(motor_left[1], s);
}
void right_backward(int s = 255)
{
  digitalWrite(motor_right[0], LOW);
  analogWrite(motor_right[1], s);
}
void left_stop()
{
  digitalWrite(motor_left[0], LOW);
  analogWrite(motor_left[1], 0);
}
void right_stop()
{
  digitalWrite(motor_right[0], LOW);
  analogWrite(motor_right[1], 0);
}

void start_bot(int s = 255)
{
  left_forward(s);
  right_forward(s);
}
void stop_bot()
{
  left_stop();
  right_stop();
}
//not_true return 1 till condition don't come, and 0 when it satisfy the condition.....!!!! :DD
//shit...!! have to check it.. :/
int not_true()
{
  int temp_value[10];
  int i, flag = 1;
  for (i = 0; i < totalpin; i++)
  {
    temp_value[i] = input_a(sensorPin[i], sensorAvg[i]);
    if (temp_value[i] != problems[i])
    {
      flag = 0;
    }
  }
  if (flag)
    return 0;
  else return 1;
}
/*
Lets move bot now.. .;)
*/
void rotate_left_90()
{
  int flag, we_got;
  int temp_value[10], i;
  start_bot(180);
  while(1)
  {
    present_situation();
   if (!(present[0] == 1 &&present[1] == 1 &&present[2] == 1 && present[3] == 1 && present[4] == 1))
    break;
  }
  for (i = 0; i < totalpin; i++)
  {
      temp_value[i] = input_a(sensorPin[i], sensorAvg[i]);
  }
  left_backward(100);
  right_forward(100);
  while (1) {
    flag = 1;
    for (i = 0; i < totalpin; i++)
    {
        we_got = input_a(sensorPin[i], sensorAvg[i]);
      if (we_got != temp_value[i])
        flag = 0;
    }
    if (flag == 0)
      break;
  }
//true till here..
 while (1) {
    flag = 2;
    for (i = 0; i < totalpin; i++)
    {
        we_got = input_a(sensorPin[i], sensorAvg[i]);
     
      if (we_got != temp_value[i])
        flag--;
    }
    if (flag!=0)
      break;
  }
  left_stop();
  right_stop();
}
void rotate_right(int s = 255)
{
  left_forward(s);
  right_backward(s);
}
void rotate_left(int s = 255)
{
  left_backward(s);
  right_forward(s);
}
void rotate_right_90()
{
  int temp_value[10], i;
  for (i = 0; i < totalpin; i++)
  {
    problems[i] = input_a(sensorPin[i], sensorAvg[i]);
  }
  left_forward();
  right_backward();
  delay(50);
  while (not_true());
}
void rotate_180()
{
  rotate_right_90();
  rotate_right_90();
}
void calib()
{
  int i;
  while (millis() < 8000) {  //Check initial delay, it is 5s, i.e. 3s + 5s for calibiration
    for (i = 0; i < totalpin; i++)
    {
      sensorValue[i] = analogRead(sensorPin[i]);
      if (sensorValue[i] > sensorMax[i]) {
        sensorMax[i] = sensorValue[i];
      }
      if (sensorValue[i] < sensorMin[i]) {
        sensorMin[i] = sensorValue[i];
      }
    }
  }
  for (i = 0; i < totalpin; i++)
  {
    sensorAvg[i] = (sensorMax[i] + sensorMin[i]) / 2;
  }
}
int tell_duniya()
{
  if (digitalRead(blocksensor) == HIGH)
    return 5;
  if (digitalRead(voidsensor) == HIGH)
    return 6;
  if (temp_inputs_sk == "01110")
    return 1;
  else   if (temp_inputs_sk == "11111")
    return 2;
  else   if (temp_inputs_sk == "11110")
    return 3;
  else   if (temp_inputs_sk == "01111")
    return 4;
}

void setup() {
  delay(3000);
  pinMode(motor_left[0], OUTPUT);
  pinMode(motor_left[1], OUTPUT);
  pinMode(motor_right[0], OUTPUT);
  pinMode(motor_right[1], OUTPUT);
  pinMode(13, OUTPUT);
  digitalWrite(13, HIGH);
  calib();
  digitalWrite(13, LOW);
  Serial.begin(9600);
  count = 0;
}
/* remove from node jaldi se....

while(1)
    {
      present_situation();
      if(!(present[1] == 1 && present[3] == 1 && present[4] == 1))
      break;
    }
    
*/

void loop() {
  //3 0 1 2 4
//  Serial.print(present[0]);
//  Serial.print(present[1]);
//  Serial.print(present[2]);
//  Serial.print(present[3]);
//  Serial.print(present[4]);
//  Serial.println();
//  
  present_situation();
  if (present[0] == 1 &&present[1] == 1 &&present[2] == 1 && present[3] == 1 && present[4] == 1)
  {
    rotate_left_90();
    count++;
    Serial.print("Found a new node. It's number is : ");
    Serial.println(count);
  }
  else if (present[1] == 1)
  {
    start_bot(180);
  }
  else if (present[2] == 1)
  {
    rotate_right(50);
  }
  else if (present[0] == 1)
  {
    rotate_left(50);
  }
  else if (present[4] == 1)
  {
    rotate_right(50);
  }
  else if (present[3] == 1)
  {
    rotate_left(50);
  }
}

