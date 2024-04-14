#if (defined(ESP32))
//MCP41010
#define  MCP41x1_SCK   18 // Define SCK pin for MCP4131 or MCP41010
#define  MCP41x1_MOSI  23 // Define MOSI pin for MCP4131 or MCP41010
#define  MCP41x1_MISO  19 // Define MISO pin for MCP4131 or MCP41010
#define  MCP41x1_CS     5 // Define chipselect pin for MCP41010 (CS for Volume)
#define  MCP41x1_ALC   17 // Define chipselect pin for MCP41010 (CS for ALC)
#endif

#include <SPI.h>
#include <MCP4xxxx.h>     // https://github.com/UA6EM/MCP4xxxx

MCP4xxxx Potentiometer(MCP41x1_CS, MCP41x1_MOSI, MCP41x1_SCK, 250000UL, SPI_MODE0);
MCP4xxxx Alc(MCP41x1_ALC, MCP41x1_MOSI, MCP41x1_SCK, 500000UL, SPI_MODE0);
int d_resis;

void testMCP41010() {
  
  d_resis = 255;
  Serial.println("START Test MCP41010");
  for (int i = 0; i < d_resis; i++) {
    Potentiometer.writeValue(i);
    delay(100);
    Serial.print("MCP41010 = ");
    Serial.println(i);
  }
  for (int j = d_resis; j >= 1; --j) {
    Potentiometer.writeValue(j);
    delay(100);
    Serial.print("MCP41010 = ");
    Serial.println(j);
  }
  Serial.println("STOP Test MCP41010");

  d_resis = 255;
  Serial.println("START Test ALC");
  for (int i = 0; i < d_resis; i++) {
    Alc.writeValue(i);
    delay(100);
    Serial.print("ALC = ");
    Serial.println(i);
  }
  for (int j = d_resis; j >= 1; --j) {
    Alc.writeValue(j);
    delay(100);
    Serial.print("ALC = ");
    Serial.println(j);
  }
  Serial.println("STOP Test ALC");
}


void setup() {
  Serial.begin(115200);
  Potentiometer.begin();
  Alc.begin();
  testMCP41010();
}

void loop() {

}
