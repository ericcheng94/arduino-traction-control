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
// #define fLeftWheelInterrupt  50
// #define fRightWheelInterrupt 51
// #define rLeftWheelInterrupt  52
// #define rRightWheelInterrupt 53
// Ultrasonic sensor pins
#define trigPin 43
#define echoPin 42
// Traction Control Indicator Light
#define tcLed 38

const byte fLeftWheelInterrupt = 20;
const byte fRightWheelInterrupt = 21;
const byte rLeftWheelInterrupt = 18;
const byte rRightWheelInterrupt = 19;

long  duration;
int   distanceCm;

unsigned long start_time  = 0;
unsigned long end_time    = 0;

// Set as volatile for use in ISR
volatile byte fLeftSteps  = LOW;
volatile byte fRightSteps = LOW;
volatile byte rLeftSteps  = LOW;
volatile byte rRightSteps = LOW;

volatile int tcRR = 0;
volatile int tcFR = 0;
volatile int tcGO = 1; // Run motors if 1, halt motors if 0

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
int motorMaster = 150;
int motorSpeed = motorMaster;

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
  pinMode(fLeftWheelInterrupt,  INPUT_PULLUP);
  pinMode(fRightWheelInterrupt, INPUT_PULLUP);
  pinMode(rLeftWheelInterrupt,  INPUT_PULLUP);
  pinMode(rRightWheelInterrupt, INPUT_PULLUP);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(tcLed, OUTPUT);

  attachInterrupt(digitalPinToInterrupt(fLeftWheelInterrupt), frontLeftWheelInterrupted, RISING);
  attachInterrupt(digitalPinToInterrupt(fRightWheelInterrupt), frontRightWheelInterrupted, RISING);
  attachInterrupt(digitalPinToInterrupt(rLeftWheelInterrupt), rearLeftWheelInterrupted, RISING);
  attachInterrupt(digitalPinToInterrupt(rRightWheelInterrupt), rearRightWheelInterrupted, RISING);
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

// // Pin Change Interrupt Request 0
// ISR (PCINT0_vect) {
//   // handle pin change interrupt for selected pins
//
// }
//
// // Pin Change Interrupt Request 1
// ISR (PCINT1_vect) {
//   // handle pin change interrupt for selected pins
// }
//
// // Pin Change Interrupt Request 2
// ISR (PCINT2_vect) {
//   // handle pin change interrupt for selected pins
// }

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
  // Serial.println(distanceCm);
  if (distanceCm < 50)
    motorSpeed = 0;
  else
    motorSpeed = motorMaster;

  while(millis() < end_time)
  {
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
    // lcd.print(tcRR);
    lcd.print(rLeftSteps);
    lcd.setCursor(3 , 1);
    lcd.print(fRightSteps);
    lcd.setCursor(13, 1);
    // lcd.print(tcFR);
    lcd.print(fLeftSteps);
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
  // Serial.println(motorSpeed);
}

void loop() {
  tractionControl();
}

// External ISR triggered by a change in the front left wheel sensor pin state
void frontLeftWheelInterrupted() {
  fLeftSteps++;
  // Serial.println("FLINT");
  tcGO = 1;
}
// External ISR triggered by a change in the front right wheel sensor pin state
void frontRightWheelInterrupted() {
  fRightSteps++;
  tcFR++;
  tcGO = 1;
}
// External ISR triggered by a change in the rear left wheel sensor pin state
void rearLeftWheelInterrupted() {
  rLeftSteps++;
}
// External ISR triggered by a change in the rear right wheel sensor pin state
void rearRightWheelInterrupted() {
  rRightSteps++;
  tcRR++;
}
