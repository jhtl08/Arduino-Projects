int digits[10][8]={
// a  b  c  d  e  f  g  .  
  {1, 1, 1, 1, 1, 1, 0, 0}, // 0
  {0, 1, 1, 0, 0, 0, 0, 0}, // 1
  {1, 1, 0, 1, 1, 0, 1, 0}, // 2
  {1, 1, 1, 1, 0, 0, 1, 0}, // 3
  {0, 1, 1, 0, 0, 1, 1, 0}, // 4
  {1, 0, 1, 1, 0, 1, 1, 0}, // 5
  {1, 0, 1, 1, 1, 1, 1, 0}, // 6
  {1, 1, 1, 0, 0, 0, 0, 0}, // 7
  {1, 1, 1, 1, 1, 1, 1, 0}, // 8
  {1, 1, 1, 1, 0, 1, 1, 0}  // 9
};

int current_count = 0;
String count_as_string;

int place_val_pins[3] = {7, 8, 10};

int prev_place_val = 7;

volatile bool count_up = 1;

volatile bool count_paused = 0;

float initial_time, time_duration;

void setup() {
  for(int i=7;i<=18;i++)  pinMode(i,OUTPUT);
  for(int i=2;i<=3;i++)  pinMode(i,OUTPUT);
  attachInterrupt(digitalPinToInterrupt(2), pause_resume, RISING);
  attachInterrupt(digitalPinToInterrupt(3), switch_direction, RISING);
}

void switch_direction(){
  noInterrupts();  // ignore debounce
  count_up = !count_up;
}

void pause_resume(){
  noInterrupts();  /// ignore debounce
  count_paused = !count_paused;
}

void writeOn(int new_place_val){
  digitalWrite(prev_place_val, LOW);
  digitalWrite(new_place_val, HIGH);
  prev_place_val = new_place_val;
}

void displayCount(){
  initial_time = millis();
  time_duration = initial_time;
  while(time_duration-initial_time<200){
    // writes current_count on the 7-segment display
    for(int i=0; i<=2; i++){
      writeOn(place_val_pins[i]); // iterate for on every 7-segment display (7, 8, 10)
      for(int j=0; j<=7; j++){
        digitalWrite(11+j, digits[count_as_string[3-i]-'0'][j]); // activates the right LEDs of 7-segment display
        // count_as_string converted back into integer to access digits as index
      }
      delay(5);
      time_duration = millis();
    }  
  }
}

void loop() {
  if(count_paused){
    displayCount();
    return;  // loop again without doing the code below
  }

  count_as_string = String(1000+current_count);  // convert count to string
  displayCount();

  if (count_up){
    current_count++;
    if (current_count>101)  current_count=0;
  }
  else{
    current_count--;
    if (current_count<0)  current_count=101;
  }
}
