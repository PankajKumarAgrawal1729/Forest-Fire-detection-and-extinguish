int redLed=12;
int greenLed=11;
int smokeA0=A0;
//Threshold value
int sensorThres=400;
void setup() {
  // put your setup code here, to run once:
Serial.begin(9600);
pinMode(redLed,OUTPUT);
pinMode(greenLed,OUTPUT);
pinMode(smokeA0,INPUT);

}

void loop() {
  // put your main code here, to run repeatedly:
int analogSensor=analogRead(smokeA0);
Serial.print("Pin A0:");
Serial.println(analogSensor);
//check the value and compare with threshold value
if(analogSensor>sensorThres)
{
  digitalWrite(redLed,HIGH);
  digitalWrite(greenLed,LOW);
}
else
{
  digitalWrite(redLed,LOW);
  digitalWrite(greenLed,HIGH);
}
delay(100);
}
