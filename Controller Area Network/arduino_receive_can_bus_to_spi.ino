#include <SPI.h>
#include "mcp_can.h"

// Chip Select pin for SPI communication
#define spi_CS_pin 10;

#define led_pin 11;
bool ledON = 1;

MCP_CAN CAN(spi_CS_pin);

void setup() {
  Serial.begin(115200);
  pinMode(led_pin, OUTPUT);

  while (CAN_OK != CAN.begin(CAN_500KBPS)) {
    Serial.println("CAN BUS init failed");
    delay(100);
  }
  Serial.println("CAN BUS Sheild init OK!");
}

void loop() {
  unsigned char len = 0;
  unsigned char buf[8];

  if (CAN_MSGAVAIL == CAN.checkReceive()) {
    CAN.readMsgBuf(&len, buf);

    unsigned long canId = CAN.getCanId();

    Serial.println("------------------------");
    Serial.print("Data from ID: 0x");
    Serial.println(canId, HEX);

    for (int i = 0; i < len; i++) {
      Serial.print(buf[i]);
      Serial.print("\t");
      if (ledON && i == 0) {
        digitalWrite(led_pin, buf[i]);
        ledON = 0;
        delay(500);
      } else if (!(ledON) && i == 4) {
        digitalWrite(led_pin, buf[i]);
        ledON = 1;
      }
    }
    Serial.println();
  }
}
