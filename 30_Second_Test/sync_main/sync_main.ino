void setup() {
  // put your setup code here, to run once:
  pinMode(7, OUTPUT);
  delay(2000);
}

void loop() {
  // put your main code here, to run repeatedly:
  for (int i = 0; i < 15; i++) {
    digitalWrite(7, LOW);
    delay(1994);
    digitalWrite(7, HIGH);
    delay(5);
  }
  while (true){
    delay(10000);
  }
}
