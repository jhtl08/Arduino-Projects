const int left[4] = {10, 11, 12, 13};
const int right[4] = {9, 8, 7, 6};
const int delayT = 150;

void setup() {
  for(int i=17; i<=19; i++)
    pinMode(i, INPUT_PULLUP);
  for(int i=6; i<=13; i++)
    pinMode(i, OUTPUT);
}

void allOn(int * lights){
  for(int i=0; i<=3; i++)
    digitalWrite(lights[i], HIGH);
}

void allOff(int * lights){
  for(int i=0; i<=3; i++)
    digitalWrite(lights[i], LOW);
}

void cascade(int * lights){
  allOn(lights);
  for(int i=0; i<=3; i++){
    delay(delayT);
    digitalWrite(lights[i], LOW);
  }
  delay(delayT);
}

void cascadeBoth(int * lights1, int * lights2){
  allOn(lights1);
  allOn(lights2);
  for(int i=0; i<=3; i++){
    delay(delayT);
    digitalWrite(lights1[i], LOW);
    digitalWrite(lights2[i], LOW);
  }
  delay(delayT);
}

void loop() {
  bool A = digitalRead(19);
  bool B = digitalRead(18);
  bool C = digitalRead(17);

  if(A==1){
    if(B==1){
      if(C==1){
        allOff(left);
        allOff(right);
      }
      else{
        allOff(left);
        cascade(right);
      }
    }
    else{
      if(C==1){
        cascade(left);
        allOff(right);
      }
      else{
        cascadeBoth(left, right);
      }
    }
  }
  else
    if(B==1){
      if(C==1){
        allOn(left);
        allOn(right);
      }
      else{
        allOn(left);
        cascade(right);
      }
    }
    else{
      if(C==1){
        cascade(left);
        allOn(right);
      }
      else{
        cascadeBoth(left, right);
      }
    }
}

