#include <SPI.h>
#include <mcp_can.h>

// Ultrasonic sensor pins
#define trigPin 6
#define echoPin 9

// CS pin for SPI communication
#define spi_CS_pin 10;

int   ledHIGH   = 1;
int   ledLOW    = 0;
bool  crashImminent = false;

MCP_CAN CAN(spi_CS_pin);

void setup() {
  Serial.begin(115200);

  while (CAN_OK != CAN.begin(CAN_500KBPS)) {
    Serial.println("CAN BUS init failed");
    delay(100);
  }
  Serial.println("CAN BUS Sheild init OK!");
}

unsigned char stmp[8] = {ledHIGH, 1, 2, 3, ledLOW, 5, 6, 7};

void loop() {
  Serial.println("In loop");
  CAN.sendMsgBuf(0x43, 0, 8, stmp);
  // delay(1000);

  // Sends out ultrasonic signal and checks rebounding signal for distance
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distanceCm = duration*0.034/2;
  // Serial.println(distanceCm);
  if (distanceCm < 50) {
    // Send interrupt signal to Arduino Mega of impending doom
    crashImminent = true;

  }


}
