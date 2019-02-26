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

// Ultrasonic sensor pins
#define trigPin 43
#define echoPin 42

#define tcLed 38

long  duration;
int   distanceCm;

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

// Master motor speed control 0 - 255
int motorMaster = 200;
int motorSpeed = motorMaster;

int tcRR = 0;
int tcFR = 0;
int tcGO = 1; // Run motors if 1, halt motors if 0

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
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(tcLed, OUTPUT);
  // lcd.setCursor(10, 0);
  // lcd.print("TC:OFF");
  // lcd.setCursor(10, 1);
  // lcd.print("V:11.1");
  lcd.setCursor(0, 0);
  lcd.print("RR:");
  lcd.setCursor(10, 0);
  lcd.print("RL:");
  lcd.setCursor(0, 1);
  lcd.print("FR:");
  lcd.setCursor(10, 1);
  lcd.print("FL:");
}

void tractionControl() {
  start_time = millis();
  end_time = start_time + 100;

  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distanceCm = duration*0.034/2;
  Serial.println(distanceCm);
  if (distanceCm < 50)
    motorSpeed = 0;
  else
    motorSpeed = motorMaster;

  while(millis() < end_time)
  {
    // Front left wheel step counter
    if(digitalRead(fLeftWheel) == HIGH)
      fLeft = 1;
    else if (fLeft == 1 && digitalRead(fLeftWheel == LOW)) {
      fLeftSteps++;
      fLeft = 0;
      tcGO = 1;
    }
    // Front right wheel step counter
    if(digitalRead(fRightWheel) == HIGH)
      fRight = 1;
    else if (fRight == 1 && digitalRead(fRightWheel == LOW)) {
      fRightSteps++;
      fRight = 0;
      tcFR++;
      tcGO = 1;
    }
    // Rear left wheel step counter
    if(digitalRead(rLeftWheel) == HIGH)
      rLeft = 1;
    else if (rLeft == 1 && digitalRead(rLeftWheel == LOW)) {
      rLeftSteps++;
      rLeft = 0;
    }
    // Rear right wheel step counter
    if(digitalRead(rRightWheel) == HIGH)
      rRight = 1;
    else if (rRight == 1 && digitalRead(rRightWheel == LOW)) {
      rRightSteps++;
      rRight = 0;
      tcRR++;
    }

    if (tcRR > tcFR + 5)
    {
      analogWrite(enA, 0);
      analogWrite(enB, 0);
      digitalWrite(tcLed, HIGH);
      tcFR = 0;
      tcRR = 0;
      tcGO = 0;
      motorSpeed = 150;
    }
    lcd.setCursor(3, 0);
    lcd.print(rRightSteps);
    lcd.setCursor(13, 0);
    lcd.print(tcRR);
    // lcd.print(rLeftSteps);
    lcd.setCursor(3 , 1);
    lcd.print(fRightSteps);
    lcd.setCursor(13, 1);
    lcd.print(tcFR);
    // lcd.print(fLeftSteps);
  }
  // // Front left wheel rpm calculation
  // tempFL = fLeftSteps - fLeftSteps_old;
  // fLeftSteps_old = fLeftSteps;
  // rpmFL = ((tempFL * 240 / 20));
  // lcd.setCursor(13, 1);
  // lcd.print(rpmFL);
  // lcd.print(" ");
  // // Front right wheel rpm calculation
  // tempFR = fRightSteps - fRightSteps_old;
  // fRightSteps_old = fRightSteps;
  // rpmFR = ((tempFR * 240 / 20));
  // lcd.setCursor(3, 1);
  // lcd.print(rpmFR);
  // lcd.print(" ");
  // // Rear left wheel rpm calculation
  // tempRL = rLeftSteps - rLeftSteps_old;
  // rLeftSteps_old = rLeftSteps;
  // rpmRL = ((tempRL * 240 / 20));
  // lcd.setCursor(13, 0);
  // lcd.print(rpmRL);
  // lcd.print(" ");
  // // Rear right wheel rpm calculation
  // tempRR = rRightSteps - rRightSteps_old;
  // rRightSteps_old = rRightSteps;
  // rpmRR = ((tempRR * 240 / 20));
  // lcd.setCursor(3, 0);
  // lcd.print(rpmRR);
  // lcd.print(" ");

  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
  if (tcGO == 1) {
    analogWrite(enA, motorSpeed);
    analogWrite(enB, motorSpeed);
    digitalWrite(tcLed, LOW);
  }
  tcRR = 0;
  tcFR = 0;
  Serial.println(motorSpeed);
}

void loop() {
  tractionControl();
}
