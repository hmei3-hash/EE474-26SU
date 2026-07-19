#define ledPin 19  //assign the pin 
void setup() {
  // put your setup code here, to run once:
  pinMode(ledPin,OUTPUT); //setup the pin to ouput mode
  digitalWrite(ledPin,LOW); //initiate the pin to low 
}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(ledPin,HIGH); //turn on
  delay(1000); //wait for 1s
  digitalWrite(ledPin,LOW); // turn off
  delay(1000); // wait for 1s
}
