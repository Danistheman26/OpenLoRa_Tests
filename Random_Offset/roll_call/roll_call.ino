#include <SPI.h>
#include <RH_RF95.h>

//RH_RF95 rf95(8, 3); // Adafruit Feather M0 with RFM95
RH_RF95 rf95;

int SF_hold = 8;
uint8_t SF[] = "8";                      // <= SF

int BW_hold = 250000;
uint8_t BW[] = "250000";              // <= BW

uint8_t buf[RH_RF95_MAX_MESSAGE_LEN];
uint8_t len = sizeof(buf);

void setup() 
{
    Serial.begin(9600);
    
    if (!rf95.init())
      Serial.println("init failed");
      
    pinMode(LED_BUILTIN, OUTPUT);

    // Default, config messages sent using SF = 8 and BW = 250000
    rf95.setTxPower(23, false);
    rf95.setSpreadingFactor(8);
    rf95.setTxPower(23);
    rf95.setFrequency(915);
    rf95.setSignalBandwidth(250000);
    
    Serial.println("Sending to rf95_server");
    delay(5000);
}

void loop()
{
  
  for (int i = 0; i < 22; i++) {
    delay(150);
    digitalWrite(LED_BUILTIN, HIGH);
    uint8_t data3[] = {(i >> 8), (i & 0xFF)};                    // <= Beacon
    rf95.send(data3, sizeof(data3));
    rf95.waitPacketSent();
    digitalWrite(LED_BUILTIN, LOW);
    //Serial.println(i);

    delay(0);
    if (rf95.available()) {
      if (rf95.recv(buf, &len)) {
        String rx_m = (char*)buf;
        Serial.println(buf[1]);
      }
    }
  }
  delay(1500);
  uint8_t data4[] = "Rst";                      // <= Reset Beacon
  rf95.send(data4, sizeof(data4));
  rf95.waitPacketSent();
  delay(100);
  rf95.send(data4, sizeof(data4));              // <= Make sure all nodes reset
  rf95.waitPacketSent();
  delay(100);
  rf95.send(data4, sizeof(data4));              // <= Really make sure all nodes reset
  rf95.waitPacketSent();
  while (true)
    delay(1000);
}
