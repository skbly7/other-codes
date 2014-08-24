int sensorPin[] = {A0, A1, A2};   
int totalpin=3;   
const int ledPin = 9;    
int sensorMin[] = {1023, 1023, 1023, 1023, 1023};
int sensorMax[] = {0, 0, 0, 0, 0};
float sensorAvg[] = {0.0, 0.0, 0.0, 0.0, 0.0};

void calib()
{
  int i,l,temp;
  for (l=0;l<1000;l++) 
  {  
    for(i=0;i<totalpin;i++)
    {
      temp = analogRead(sensorPin[i]);
      if (temp > sensorMax[i]) {
        sensorMax[i] = temp;
      }
      if (temp < sensorMin[i]) {
        sensorMin[i] = temp;
      }
    }
	delay(10);
  }
  // delay of 10ms and loop 1000 tyms, thus 10000ms i.e. 10s.. :)
  for(i=0;i<totalpin;i++)
  {
   sensorAvg[i] = (sensorMax[i]+sensorMin[i])/2;
  }
}

void setup() {
  for(i=0;i<totalpin;i++)
  {
   pinMode(sensorPin[i], INPUT);
  }
  pinMode(13, OUTPUT);
  digitalWrite(13, HIGH);
  calib();
  digitalWrite(13, LOW);
  Serial.begin(9600);
}
void loop() {

// baaki ka khud karna h.. :P
// All the best..!

}