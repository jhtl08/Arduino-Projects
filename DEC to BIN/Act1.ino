int bit_level[] = {512, 256, 128, 64, 32, 16, 8, 4, 2, 1}; 

void setup() {
  for(int i=2; i<=11; i++)
    pinMode(i, OUTPUT);
}

void dectobin(int dec){
  for(int i=0; i<10; i++){
    if(dec==0){
      digitalWrite(i, LOW);
    }
    else if(dec>=bit_level[i]){
      digitalWrite(11-i, HIGH);
      dec-=bit_level[i];
    }
    else{
      digitalWrite(11-i, LOW);
    }
  }
}

void loop() {
  for (int i=0; i<=1023; i++){ //generates the decimal numbers 0 to 1023
    dectobin(i); //converts generated decimal to binary
    delay(50);
  }
}
