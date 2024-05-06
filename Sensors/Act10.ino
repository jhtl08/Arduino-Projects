#include <DHT.h>

const int TOUCH_PIN = 2;
const int ECHO_PIN = 11;
const int TRIG_PIN = 12;
const int TEMP_PIN = 3;

DHT dht(TEMP_PIN, DHT11);

void setup() {
  Serial.begin(9600);
  dht.begin();
  pinMode(TOUCH_PIN, INPUT);
  pinMode(ECHO_PIN, INPUT);
  pinMode(TRIG_PIN, OUTPUT);
}

void loop() {
  int TOUCH_STATE = digitalRead(TOUCH_PIN);

  if (TOUCH_STATE){
    digitalWrite(TRIG_PIN, LOW);
    delayMicroseconds(2);
    digitalWrite(TRIG_PIN, HIGH);
    delayMicroseconds(10);
    digitalWrite(TRIG_PIN, LOW);

    long duration = pulseIn(ECHO_PIN, HIGH);
    
    float Tc = dht.readTemperature(); 
    long v_sound = 0.6*Tc + 331.5;;
    float cm = ((0.6*Tc + 331.5)*duration)/20000;

    Serial.print("temperature: ");
    Serial.print(Tc);
    Serial.print(" C ");
    Serial.print("speed of sound: ");
    Serial.print(v_sound);
    Serial.print("m/s ");
    Serial.print("distance: ");
    Serial.print(cm);
    Serial.println("cm");
    while(TOUCH_STATE){
      TOUCH_STATE = digitalRead(TOUCH_PIN);
    }
  }
}
