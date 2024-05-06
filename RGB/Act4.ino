String number = "";
int digitalVolt;

void setup() {
  for(int i=9; i<=11; i++)
    pinMode(i, OUTPUT);
  pinMode(A0, OUTPUT);
  Serial.begin(9600);
}

void setColor(int r, int g, int b){
  analogWrite(11, r);
  analogWrite(10, g);
  analogWrite(9, b);
}

void loop() {
  digitalVolt=analogRead(A0);
  Serial.print("Digital Value: ");
  Serial.println(digitalVolt);
  number = String(digitalVolt+10000);

  for(int i=1; i<=4; i++){
    switch(number[i]){
      case '0': //white
        setColor(255, 255, 255);
        break;
      case '1': //red
        setColor(255, 0, 0);
        break;
      case '2': //orange
        setColor(255, 125, 0);
        break;
      case '3': //yellow
        setColor(255, 255, 0);
        break;
      case '4': //green
        setColor(0, 255, 0);
        break;
      case '5': //blue
        setColor(0, 0, 255);
        break;
      case '6': //indigo
        setColor(63, 0, 255);
        break;
      case '7': //violet
        setColor(125, 0, 255);
        break;
      case '8': //ocean
        setColor(0, 84, 147);
        break;
      case '9': //raspberry
        setColor(255, 0, 125);
        break;
    }
    delay(1000);
    setColor(0, 0, 0);
    delay(500);
  }
}
