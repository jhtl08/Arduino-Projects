// state names for better readabilty
const int IDLE = 0;
const int FILL = 1;
const int WASH = 2;
const int DRAIN1 = 3;
const int REFILL = 4;
const int RINSE = 5;
const int DRAIN2 = 6;
const int PAUSE = 7;

int countT = 5;

volatile int state = IDLE;
volatile int T = 1;
int washDuration = 5;

volatile int activeLED = 10; 

// checkpoint variables for going back from PAUSE
volatile int state_holder;

bool SHIFT_MODE;

void setup() {
  pinMode(A5, INPUT_PULLUP);
  for (int i = 4; i <= 13; i++)
    pinMode(i, OUTPUT);
  digitalWrite(12, HIGH);  // Normal Mode initially
  attachInterrupt(0, start_pause, FALLING);
  attachInterrupt(1, reset, FALLING);
}

void start_pause() {
  if (state == IDLE) {
    state = FILL;
    digitalWrite(activeLED, LOW);
    T = 0;
  } else if (state == PAUSE) {
    state = state_holder;
    digitalWrite(activeLED, LOW);
  } else {
    state = PAUSE;
    digitalWrite(activeLED, LOW);
  }
}

void reset() {
  state = IDLE;
  digitalWrite(activeLED, LOW);
}

void loop() {
  SHIFT_MODE = !digitalRead(A5);

  switch (state) {
    case IDLE:
      activeLED = 10;
      digitalWrite(activeLED, HIGH);  // show current state
      if (SHIFT_MODE) {  // A5
        if (washDuration == 3) {
          washDuration = 5;
          digitalWrite(11, LOW);
          digitalWrite(12, HIGH);
        } else if (washDuration == 5) {
          washDuration = 8;
          digitalWrite(12, LOW);
          digitalWrite(13, HIGH);
        } else if (washDuration == 8) {
          washDuration = 3;
          digitalWrite(13, LOW);
          digitalWrite(11, HIGH);
        }
      }
      break;

    case FILL:
      activeLED = 9;
      digitalWrite(activeLED, HIGH);  // show current state
      state_holder = state;
      if (T == countT) {
        state = WASH;
        digitalWrite(9, LOW);
        T = 0;
      }
      break;

    case WASH:
      activeLED = 8;
      digitalWrite(activeLED, HIGH);  // show current state
      state_holder = state;
      if (T == washDuration) {
        state = DRAIN1;
        digitalWrite(8, LOW);
        T = 0;
      }
      break;

    case DRAIN1:
      activeLED = 7;
      digitalWrite(activeLED, HIGH);  // show current state
      state_holder = state;
      if (T == countT) {
        state = REFILL;
        digitalWrite(7, LOW);
        T = 0;
      }
      break;

    case REFILL:
      activeLED = 6;
      digitalWrite(activeLED, HIGH);  // show current state
      state_holder = state;
      if (T == countT) {
        state = RINSE;
        digitalWrite(6, LOW);
        T = 0;
      }
      break;

    case RINSE:
      activeLED = 5;
      digitalWrite(activeLED, HIGH);  // show current state
      state_holder = state;
      if (T == countT) {
        state = DRAIN2;
        digitalWrite(5, LOW);
        T = 0;
      }
      break;

    case DRAIN2:
      activeLED = 4;
      digitalWrite(activeLED, HIGH);  // show current state
      state_holder = state;
      if (T == countT) {
        state = IDLE;
        digitalWrite(4, LOW);
        T = 0;
      }
      break;

    case PAUSE:
      activeLED = 14;
      digitalWrite(activeLED, HIGH);  // show current state
      T--;  // Ensures current duration remains
      break;
  }
  T++;
  delay(500);
  digitalWrite(3, LOW);  // to blink when on PAUSE
  delay(500);
}
