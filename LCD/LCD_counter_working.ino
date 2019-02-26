#include <LiquidCrystal.h>

#define rs 30
#define en 31
#define d4 28
#define d5 29
#define d6 26
#define d7 27

#define fLeftWheel  50
#define fRightWheel 51
#define rLeftWheel  52
#define rRightWheel 53

unsigned long start_time = 0;
unsigned long end_time = 0;
int   steps = 0;
float steps_old = 0;
float temp = 0;
int rpm = 0;

LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
// int   fwRPM = 0;
// int   rwRPM = 0;
// float voltage = 11.1;
// int   drain = 0;

void setup() {
  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);

  pinMode(fLeftWheel,INPUT_PULLUP);
  pinMode(fRightWheel,INPUT_PULLUP);
  pinMode(rLeftWheel,INPUT_PULLUP);
  pinMode(rRightWheel,INPUT_PULLUP);

  lcd.setCursor(10, 0);
  lcd.print("TC:OFF");
  lcd.setCursor(10, 1);
  lcd.print("V:11.1");
}

void updateLCD() {
  lcd.setCursor(0, 0);
  lcd.print("fwRPM:");
  lcd.setCursor(0, 1);
  lcd.print("rwRPM:");

  int wheel = fRightWheel;

  start_time = millis();
  end_time = start_time + 1000;
  while(millis() < end_time)
  {
    if(digitalRead(wheel))
    {
      steps++;
      while(digitalRead(wheel));
    }
    lcd.setCursor(6,0);
    lcd.print(steps);
    // lcd.print("   ");
  }
  temp = steps - steps_old;
  steps_old = steps;
  rpm = ((temp * 60 / 20));
  lcd.setCursor(6, 1);
  lcd.print(rpm);
  lcd.print(" ");
}

void loop() {
  updateLCD();
  // delay(10);
}
