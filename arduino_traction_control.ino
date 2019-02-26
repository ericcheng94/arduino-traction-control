#include <LiquidCrystal.h>

// LCD pins
#define rs 30
#define en 31
#define d4 28
#define d5 29
#define d6 26
#define d7 27

// L298N DC motor controller pins
#define enA 2
#define in1 22
#define in2 23
#define in3 24
#define in4 25
#define enB 3

// Wheel speed sensor pins
#define fLeftWheel  50
#define fRightWheel 51
#define rLeftWheel  52
#define rRightWheel 53

unsigned long start_time  = 0;
unsigned long end_time    = 0;
int fLeftSteps  = 0;
int fRightSteps = 0;
int rLeftSteps  = 0;
int rRightSteps = 0;
int fLeftSteps_old  = 0;
int fRightSteps_old = 0;
int rLeftSteps_old  = 0;
int rRightSteps_old = 0;

int rRight = 0;
int rLeft  = 0;
int fRight = 0;
int fLeft  = 0;

int tempL = 0;
int rpmL = 0;
int tempR = 0;
int rpmR = 0;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

void setup() {
  Serial.begin(9600);
  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
  pinMode(enA, OUTPUT);
  pinMode(enB, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);
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
  lcd.print("whel1:");
  lcd.setCursor(0, 1);
  lcd.print("whel2:");

  start_time = millis();
  end_time = start_time + 1000;

  int wheel1 = rLeftWheel;
  int wheel2 = rRightWheel;

  while(millis() < end_time)
  {
    if(digitalRead(wheel1) == HIGH)
      rLeft = 1;
    else if (rLeft == 1 && digitalRead(wheel1 == LOW)) {
      rLeftSteps++;
      rLeft = 0;
    }
    if(digitalRead(wheel2) == HIGH)
      rRight = 1;
    else if (rRight == 1 && digitalRead(wheel2 == LOW)) {
      rRightSteps++;
      rRight = 0;
    }
    // lcd.setCursor(6,0);
    // lcd.print(rRightSteps);
    // lcd.setCursor(6,1);
    // lcd.print(fRightSteps);

    // Serial.println("Steps " + rRightSteps);
    // lcd.print("   ");
  }
  tempL = rLeftSteps - rLeftSteps_old;
  rLeftSteps_old = rLeftSteps;
  rpmL = ((tempL * 60 / 20));
  lcd.setCursor(6, 0);
  lcd.print(rpmL);
  lcd.print(" ");

  tempR = rRightSteps - rRightSteps_old;
  rRightSteps_old = rRightSteps;
  rpmR = ((tempR * 60 / 20));
  lcd.setCursor(6, 1);
  lcd.print(rpmR);
  lcd.print(" ");

  int analogSpeed = 0;

  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
  analogWrite(enA, analogSpeed);
  analogWrite(enB, analogSpeed);
}

void loop() {
  updateLCD();
  // delay(10);
}
