#include <LiquidCrystal.h>

#define rs 7
#define en 6
#define d4 5
#define d5 4
#define d6 3
#define d7 2

#define fWheel 8
#define rWheel 9

unsigned long start_time = 0;
unsigned long end_time = 0;
int   steps = 0;
float steps_old = 0;
float temp = 0;
int rpm = 0;

LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
int   fwRPM = 0;
int   rwRPM = 0;
float voltage = 11.1;
int   drain = 0;

void setup() {
  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);

  pinMode(fWheel,INPUT_PULLUP);
  pinMode(rWheel,INPUT_PULLUP);

  lcd.setCursor(10, 0);
  lcd.print("TC:OFF");
  lcd.setCursor(10, 1);
  lcd.print("V:");
}

void updateLCD() {
  drain++;
  if (drain % 100 == 0)
    voltage -= 0.1;
  if (voltage < 9)
    voltage = 11.1;
  lcd.setCursor(12, 1);
  lcd.print(voltage);

  lcd.setCursor(0, 0);
  lcd.print("fwRPM:");
  lcd.setCursor(0, 1);
  lcd.print("rwRPM:");

  // unsigned long start_time = 0;
  // unsigned long end_time = 0;
  // int   steps = 0;
  // float steps_old = 0;
  // float temp = 0;
  // int rpm = 0;

  start_time = millis();
  end_time = start_time + 1000;
  while(millis() < end_time)
  {
    if(digitalRead(fWheel))
    {
      steps++;
      while(digitalRead(fWheel));
    }
    lcd.setCursor(6,0);
    lcd.print(steps);
    // lcd.print("   ");
  }
  temp = steps - steps_old;
  steps_old = steps;
  rpm = ((temp * 60) / 20);
  lcd.setCursor(6, 1);
  lcd.print(rpm);
  lcd.print(" ");

  // OLD LCD CODE
  // lcd.setCursor(0, 0);
  // lcd.print("fwRPM:");
  // fwRPM++;
  // if (fwRPM > 500) {
  //   fwRPM = 0;
  //   lcd.setCursor(6, 0);
  //   lcd.print("   ");
  // }
  // lcd.setCursor(6, 0);
  // lcd.print(fwRPM);
  //
  //
  //
  // lcd.setCursor(0, 1);
  // lcd.print("rwRPM:");
  // rwRPM++;
  // if (rwRPM > 500) {
  //   rwRPM = 0;
  //   lcd.setCursor(6, 1);
  //   lcd.print("   ");
  // }
  // lcd.setCursor(6, 1);
  // lcd.print(rwRPM);
}

void loop() {
  updateLCD();
  // delay(10);
}
