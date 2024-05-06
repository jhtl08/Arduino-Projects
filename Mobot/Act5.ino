int rightDIR = 8;
int leftDIR = 11;
int rightRUN = 9;
int leftRUN = 10;

//adjust PWM depending on how strong 
// motors are relative to each other
int leftPWM = 250;
int rightPWM = 180;


//adjust time delay to ensure 90 degree turn
int delay90deg = 450;
int delay45deg = delay90deg/2;

void goForward(int delayT){
  digitalWrite(rightDIR, HIGH);
  digitalWrite(leftDIR, HIGH);
  analogWrite(rightRUN, rightPWM);
  analogWrite(leftRUN, leftPWM);
  delay(delayT);
  for(int i=8; i<=11; i++)
    digitalWrite(i, LOW);
}

void goBackward(int delayT){
  digitalWrite(rightDIR, LOW);
  digitalWrite(leftDIR, LOW);
  analogWrite(rightRUN, rightPWM);
  analogWrite(leftRUN, leftPWM);
  delay(delayT);
  for(int i=8; i<=11; i++)
    digitalWrite(i, LOW);
}

void turnRight(int delayT){
  digitalWrite(rightDIR, LOW);
  digitalWrite(leftDIR, HIGH);
  analogWrite(rightRUN, rightPWM);
  analogWrite(leftRUN, leftPWM);
  delay(delayT);
  for(int i=8; i<=11; i++)
    digitalWrite(i, LOW);
}

void turnLeft(int delayT){
  digitalWrite(rightDIR, HIGH);
  digitalWrite(leftDIR, LOW);
  analogWrite(rightRUN, rightPWM);
  analogWrite(leftRUN, leftPWM);
  delay(delayT);
  for(int i=8; i<=11; i++)
    digitalWrite(i, LOW);
}

void setup() {
  for(int i=8; i<=11; i++)
    pinMode(i, OUTPUT);

}

void loop() {
  //drawing pattern 6 (letter Z)
  //first step
  goForward(750);

  //second step
  turnRight(delay90deg);
  goForward(3000);

  //third step
  turnLeft(delay45deg);
  goBackward(3700);

  //fourth step
  turnRight(delay45deg);
  goForward(3000);

  while(1);
}
