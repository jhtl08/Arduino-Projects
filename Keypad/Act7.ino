int RGBvalues[4][4][3]={
{{255,0,0}, {255,128,0}, {255,255,0}, {128,255,0}},
{{0,255,0}, {0,255,128}, {0,255,255}, {0,128,255}},
{{0,0,255}, {127,0,255}, {255,0,255}, {255,0,127}},
{{102,15,15}, {15,102,15}, {15,15,102}, {255,255,255}}};

void setup() {
  for(int i=2;i<=5;i++) pinMode(i, OUTPUT);
  for(int i=14;i<=17;i++) pinMode(i, INPUT_PULLUP);
  for(int i=9;i<=11; i++) pinMode(i, OUTPUT);
}

void color(int row, int column){
  for (int i=9; i<=11; i++){
    analogWrite(i, RGBvalues[row][column][i-9]);
  }
}

void loop() {
  for (int i=2; i<=5; i++){
    digitalWrite(i, HIGH);
  }
  for (int i=2; i<=5; i++){
    digitalWrite(i, LOW);
    if(!digitalRead(14)){
      color(i-2,0);
      break;
      }
    else if (!digitalRead(15)){
      color(i-2, 1);
      break;
      }
    else if (!digitalRead(16)){
      color(i-2, 2);
      break;
      }
    else if (!digitalRead(17)){
      color(i-2, 3);
      break;
      }
  }
}
