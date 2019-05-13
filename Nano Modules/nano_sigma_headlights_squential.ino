#define led1 2
#define led2 3
#define led3 4
#define led4 5
#define led5 6
#define led6 7
#define led7 8
#define led8 9
#define led9 10

void setup()
{
  pinMode(led1, OUTPUT);  //       # #
  pinMode(led2, OUTPUT);  // # # #
  pinMode(led3, OUTPUT);  //  #
  pinMode(led4, OUTPUT);  //   #
  pinMode(led5, OUTPUT);  //    #
  pinMode(led6, OUTPUT);  //    #
  pinMode(led7, OUTPUT);  //   #
  pinMode(led8, OUTPUT);  //  #
  pinMode(led9, OUTPUT);  // # # # #
}

void loop()
{
  digitalWrite(led1, HIGH);
  delay(120);
  digitalWrite(led2, HIGH);
  delay(60);
  digitalWrite(led3, HIGH);
  delay(60);
  digitalWrite(led4, HIGH);
  delay(60);
  digitalWrite(led5, HIGH);
  delay(60);
  digitalWrite(led6, HIGH);
  delay(60);
  digitalWrite(led7, HIGH);
  delay(60);
  digitalWrite(led8, HIGH);
  delay(60);
  digitalWrite(led9), HIGH);

  delay(2000);

  digitalWrite(led1, LOW);
  delay(200);
  digitalWrite(led2, LOW);
  delay(200);
  digitalWrite(led3, LOW);
  delay(200);
  digitalWrite(led4, LOW);
  delay(200);
  digitalWrite(led5, LOW);
  delay(200);
  digitalWrite(led6, LOW);
  delay(200);
  digitalWrite(led7, LOW);
  delay(200);
  digitalWrite(led8, LOW);
  delay(200);
  digitalWrite(led9, LOW);

  delay(1000);
}
