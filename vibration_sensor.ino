const int sensorPin = 0;
const int ledPin = 13;
const int THRESHOLD = 10;

void setup() {
pinMode(ledPin,OUTPUT);  // put your setup code here, to run once:

}

void loop() {
  int val = analogRead(sensorPin);// put your main code here, to run repeatedly:
  if(val >= THRESHOLD)
  {
    digitalWrite(ledPin,HIGH);
    delay(100);
  }
  else
   digitalWrite(ledPin,LOW);
}
