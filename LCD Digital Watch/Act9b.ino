#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);

int time_before, time_after;
int seconds = 0;
int minutes = 0;
int hour = 12;
int lcd_refresh_rate = 100;
String period = "AM";

void setup() {
  lcd.init();
  lcd.backlight();
  lcd.print("Jason Lorenzo");
  time_before = millis();
  attachInterrupt(digitalPinToInterrupt(2), increment_hour, RISING);
  attachInterrupt(digitalPinToInterrupt(3), increment_minutes, RISING);
}

void increment_hour(){
  noInterrupts();
  check_period();
  hour++;
  check_hour();
}

void increment_minutes(){
  noInterrupts();
  minutes++;
  check_minutes();
  check_hour();
}

void loop() {
  time_after = millis();
  if (time_after-time_before >= 1000){
    seconds++;
    if (seconds >= 60){
      seconds = 0;
      minutes++;
    }
    check_minutes();
    check_hour();
    time_before = time_after;
  }
  lcd.setCursor(0,1);
  if (hour < 10) lcd.print("0");
  lcd.print(hour);
  lcd.print(":");
  if (minutes < 10) lcd.print("0");
  lcd.print(minutes);
  lcd.print(":");
  if (seconds < 10) lcd.print("0");
  lcd.print(seconds);
  lcd.print(" ");
  lcd.print(period);
  delay(lcd_refresh_rate);
}

void check_minutes(){
  if (minutes >= 60){
    minutes = 0;
    check_period();
    hour++;
  }
}

void check_hour(){
  if (hour >= 13){
    hour = 1;
  }
}

void check_period(){
  if (hour == 11){
    if (period == "AM")
      period = "PM";
    else if (period == "PM")
      period = "AM";
  }
}
