#include <SPI.h>
#include <RH_RF95.h>

const byte ledPin = LED_BUILTIN;
const byte interruptPin = EXTERNAL_INT_2;
volatile byte state = LOW;
unsigned long incr = 24782;
unsigned long offset = 24782;
int num = 0;
int super_num = 0;

RH_RF95 rf95(8, 3); 

void setup() {
  if (!rf95.init())
    while(true) {
      delay(500);
    }
  rf95.setTxPower(23, false);
  rf95.setSpreadingFactor(12);                //   <-- SF
  rf95.setTxPower(23);
  rf95.setFrequency(915);
  rf95.setSignalBandwidth(250000);
  
  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, LOW);

  pinMode(A3, INPUT_PULLUP);
  attachInterrupt(A3, blink, RISING);
}

void loop() {
  if(state == HIGH) {
    delayMicroseconds(0);                  //   <-- replace incr with 0 for the constant offset node
    digitalWrite(ledPin, HIGH);
    uint8_t data[] = "Hello";
    rf95.send(data, sizeof(data));
    rf95.waitPacketSent();
    state = LOW;
    digitalWrite(ledPin, LOW);
    num++;
    super_num++;
    if (num == 10) {
      incr = incr + offset;
      num = 0;
    }
    if (super_num == 110) {
      delay(10000);
    }
  }
}

void blink() {
  state = HIGH;
}
