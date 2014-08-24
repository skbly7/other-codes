void setup() {
  // put your setup code here, to run once:
pinMode(A0,INPUT);
pinMode(A1,INPUT);
pinMode(A2,INPUT);
pinMode(2,INPUT);
pinMode(3,INPUT);
Serial.begin(9600);
}

void loop() {
Serial.print(analogRead(A0));
Serial.print("    ");
Serial.print(analogRead(A1));
Serial.print("    ");
Serial.print(analogRead(A2));
Serial.print("    ");
Serial.print(digitalRead(2));
Serial.print("    ");
Serial.print(digitalRead(3));
Serial.print("    ");
Serial.println();
delay(500);
}
