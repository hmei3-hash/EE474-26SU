#define ledPin 19
#define readPin 1
uint32_t curr; 
void setup() {
  // put your setup code here, to run once:
  ledcAttach(ledPin,512,12);

}

void loop() {
  // put your main code here, to run repeatedly:
    curr = analogRead(readPin);
 ledcWrite(ledPin, curr);
 
}
