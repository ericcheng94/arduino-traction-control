const int a = 8;
const int b = 9;
const int c = 4;
const int d = 3;
const int e = 2;
const int f = 7;
const int g = 6;
const int dp = 5;
const int sensorPin = 14;
const int headlights = 12;
const int auto_btn = 11;

int lightCal;
int lightVal;

int btnPress;
bool autoMode;

void setup() {
  Serial.begin(9600);
  pinMode(headlights, OUTPUT);
  pinMode(auto_btn, INPUT);
  pinMode(a, OUTPUT);  //A
  pinMode(b, OUTPUT);  //B
  pinMode(c, OUTPUT);  //C
  pinMode(d, OUTPUT);  //D
  pinMode(e, OUTPUT);  //E
  pinMode(f, OUTPUT);  //F
  pinMode(g, OUTPUT);  //G
  pinMode(dp, OUTPUT);  //DP

  lightCal = analogRead(sensorPin);
  autoMode = true;
}

void loop() {

  btnPress = digitalRead(auto_btn);

  if (btnPress == HIGH && autoMode == true)
    autoMode = false;
  else if (btnPress == HIGH && autoMode == false)
    autoMode = true;

  if (autoMode == true)
    auto_lights();
  // else
    // manual_lights();
}

void auto_lights() {
  lightVal = analogRead(sensorPin);
  // Serial.println(lightVal);

  if (lightVal < lightCal - 100) {
    digitalWrite(headlights, HIGH);
  } else {
    digitalWrite(headlights, LOW);
  }

  digitalWrite(a, HIGH);
  delay(100);
  digitalWrite(b, HIGH);
  delay(100);
  digitalWrite(c, HIGH);
  delay(100);
  digitalWrite(e, HIGH);
  delay(100);
  digitalWrite(f, HIGH);
  delay(100);
  digitalWrite(g, HIGH);
}

void manual_lights() {
  digitalWrite(headlights, HIGH);

  digitalWrite(a, LOW);
  digitalWrite(b, LOW);
  digitalWrite(c, LOW);
  digitalWrite(e, LOW);
  digitalWrite(f, LOW);
  digitalWrite(g, LOW);

  digitalWrite(b, HIGH);
  delay(100);
  digitalWrite(c, HIGH);
  delay(100);
  digitalWrite(d, HIGH);
  delay(100);
  digitalWrite(e, HIGH);
  delay(100);
  digitalWrite(f, HIGH);
}
