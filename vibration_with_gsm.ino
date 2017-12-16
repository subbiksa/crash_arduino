#include <SoftwareSerial.h>
String pilih;
SoftwareSerial mySerial(9, 10);
const int ledPin = 13;      // led connected to digital pin 13
const int knockSensor = A0; // the piezo is connected to analog pin 0
const int threshold = 500;  // threshold value to decide when the detected sound is a knock or not
int sensorReading = 0;      // variable to store the value read from the sensor pin
int ledState = LOW;         // variable used to store the last LED status, to toggle the light
void setup() {
  pinMode(ledPin, OUTPUT); 
mySerial.begin(9600); // Setting the baud rate of GSM Module
Serial.begin(9600); // Setting the baud rate of Serial Monitor (Arduino)
RecieveMessage();
delay(100);
}
void loop() {
  // read the sensor and store it in the variable sensorReading:
  sensorReading = analogRead(knockSensor);

  // if the sensor reading is greater than the threshold:
  if (sensorReading >= threshold) {
    // toggle the status of the ledPin:
    ledState = !ledState;
    // update the LED pin itself:
    digitalWrite(ledPin, ledState);
    // send the string "Knock!" back to the computer, followed by newline
    Serial.println("System Vibrating.....");
    delay(1000);
  }
  if (Serial.available()>0)
switch(Serial.read())
{
case 's':
SendMessage();
break;
case 'r':
RecieveMessage();
break;
}
if (mySerial.available()>0)
{ Serial.write(mySerial.read());
pilih = mySerial.read();}
}
void SendMessage()
{
mySerial.println("AT+CMGF=1"); //Sets the GSM Module in Text Mode
delay(1000); // Delay of 1000 milli seconds or 1 second
mySerial.println("AT+CMGS=\"+918056155080\"\r"); // Replace x with mobile number
delay(1000);
mySerial.println("ACCIDENT ALERT!");// The SMS text you want to send
mySerial.println("LATITUDE: 11.1018 NORTH");// The SMS text you want to send
mySerial.println("LONGITUDE: 76.9665 EAST");// The SMS text you want to send
mySerial.println(pilih);
delay(100);
mySerial.println((char)26);// ASCII code of CTRL+Z
delay(1000);
}
void RecieveMessage()
{
mySerial.println("AT+CNMI=2,2,0,0,0"); // AT Command to recieve a live SMS
delay(1000);
}



