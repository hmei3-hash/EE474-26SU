#define ledPin 19  //assign led pin
#define button 20 //assign button pin

void setup() {
  // put your setup code here, to run once:
  pinMode(button, INPUT_PULLUP); //setup with internal pullup so that by default high
  pinMode(ledPin,OUTPUT);// setup output mode
  digitalWrite(ledPin,LOW); //initiate led pin as low 

}

void loop() {
  // put your main code here, to run repeatedly:
  if (digitalRead(button)==LOW){ //if reads low(button pushed)
    digitalWrite(ledPin,HIGH); //turn up 
  }
  else{
    digitalWrite(ledPin,LOW); //if not turn off
  }
}
