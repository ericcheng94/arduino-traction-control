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

int fLeft  = 0;
int fRight = 0;
int rLeft  = 0;
int rRight = 0;

int tempFL = 0;
int tempFR = 0;
int tempRL = 0;
int tempRR = 0;

int rpmFL = 0;
int rpmFR = 0;
int rpmRL = 0;
int rpmRR = 0;

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
  pinMode(fLeftWheel, INPUT_PULLUP);
  pinMode(fRightWheel, INPUT_PULLUP);
  pinMode(rLeftWheel, INPUT_PULLUP);
  pinMode(rRightWheel, INPUT_PULLUP);

  lcd.setCursor(10, 0);
  lcd.print("TC:OFF");
  lcd.setCursor(10, 1);
  lcd.print("V:11.1");
}

void tractionControl() {
  lcd.setCursor(0, 0);
  lcd.print("lwRPM:");
  lcd.setCursor(0, 1);
  lcd.print("rwRPM:");

  start_time = millis();
  end_time = start_time + 1000;

  while(millis() < end_time)
  {
    if(digitalRead(fLeftWheel) == HIGH)
      fLeft = 1;
    else if (fLeft == 1 && digitalRead(fLeftWheel == LOW)) {
      fLeftSteps++;
      fLeft = 0;
    }
    if(digitalRead(fRightWheel) == HIGH)
      fRight = 1;
    else if (fRight == 1 && digitalRead(fRightWheel == LOW)) {
      fRightSteps++;
      fRight = 0;
    }
    if(digitalRead(rLeftWheel) == HIGH)
      rLeft = 1;
    else if (rLeft == 1 && digitalRead(rLeftWheel == LOW)) {
      rLeftSteps++;
      rLeft = 0;
    }
    if(digitalRead(rRightWheel) == HIGH)
      rRight = 1;
    else if (rRight == 1 && digitalRead(rRightWheel == LOW)) {
      rRightSteps++;
      rRight = 0;
    }
  }

  tempRL = rLeftSteps - rLeftSteps_old;
  rLeftSteps_old = rLeftSteps;
  rpmRL = ((tempRL * 60 / 20));
  lcd.setCursor(6, 0);
  lcd.print(rpmRL);
  lcd.print(" ");

  tempRR = rRightSteps - rRightSteps_old;
  rRightSteps_old = rRightSteps;
  rpmRR = ((tempRR * 60 / 20));
  lcd.setCursor(6, 1);
  lcd.print(rpmRR);
  lcd.print(" ");

  int motorSpeed = 0; // 0 - 255

  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
  analogWrite(enA, motorSpeed);
  analogWrite(enB, motorSpeed);
}

void loop() {
  tractionControl();
}
