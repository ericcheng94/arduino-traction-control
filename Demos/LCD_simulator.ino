#include <LiquidCrystal.h>

#define rs 7
#define en 6
#define d4 5
#define d5 4
#define d6 3
#define d7 2

LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
int   fwRPM = 0;
int   rwRPM = 0;
float voltage = 11.1;
int   drain = 0;

void setup() {
  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
  lcd.setCursor(10, 0);
  lcd.print("TC:OFF");
  lcd.setCursor(10, 1);
  lcd.print("V:");
}

void updateLCD() {
  // simulate battery drain
  drain++;
  if (drain % 100 == 0)
    voltage -= 0.1;
  if (voltage < 9)
    voltage = 11.1;
  lcd.setCursor(12, 1);
  lcd.print(voltage);

  // demo front wheel RPM
  lcd.setCursor(0, 0);
  lcd.print("fwRPM:");
  fwRPM++;
  if (fwRPM > 500) {
    fwRPM = 0;
    lcd.setCursor(6, 0);
    lcd.print("   ");
  }
  lcd.setCursor(6, 0);
  lcd.print(fwRPM);

  // demo rear wheel RPM
  lcd.setCursor(0, 1);
  lcd.print("rwRPM:");
  rwRPM++;
  if (rwRPM > 500) {
    rwRPM = 0;
    lcd.setCursor(6, 1);
    lcd.print("   ");
  }
  lcd.setCursor(6, 1);
  lcd.print(rwRPM);
}

void loop() {
  updateLCD();
  delay(10);
}
