int digitalVolt;
float analogVolt;

void setup() {
  for(int i=4; i<=13; i++)
    pinMode(i, OUTPUT);
  pinMode(A0, INPUT);
}

void loop() {
  digitalVolt = analogRead(A0);
  analogVolt = (5./1023.)*digitalVolt;

  for(float i=0.5; i<analogVolt; i+=0.5){
    digitalWrite((2*i+3), HIGH);
  }

  if(analogVolt>4.9)
    digitalWrite(13, HIGH);

  delay(200);

  for(int i=4; i<=13; i++)
    digitalWrite(i, LOW);

  delay(100);
}
