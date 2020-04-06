# include <SoftwareSerial.h>
#include <ESP8266WiFi.h>
#include <TinyGPS.h>
#include <DHT.h>        // including the library of DHT11 temperature and humidity sensor
#define DHTTYPE DHT11   // DHT 11 #define dht_dpin 0
# define dht_dpin 0
char auth[] = "YourAuthToken";
char ssid[] = "YourNetworkName";
char pass[] = "YourPassword";
float lat ,lon ; // create variable for latitude and longitude object
SoftwareSerial gpsSerial(3,4);//rx,tx
TinyGPS gps; // create gps object
int flamePin = 11;
int Flame = LOW;
int flag1=0;
int flag2=0;
// for gas
int redLed=12;
int greenLed=11;
int smokeA0=A0;
//Threshold value
int sensorThres=400;
// for dht11
DHT dht(dht_dpin, DHTTYPE);

void setup()

{
    Serial.begin(9600);
    pinMode(flamePin, INPUT);
    pinMode(redLed,OUTPUT);
    pinMode(greenLed,OUTPUT);
    pinMode(smokeA0,INPUT);
    dht.begin(); 
    
    Serial.println("Humidity and temperature\n\n");
    
    Serial.println("The GPS Received Signal:");
    //gpsSerial.begin(9600); // connect gps sensor

    delay(900);
   
}
void loop()
{
Flame = digitalRead(flamePin);
if (Flame== HIGH && flag1==0){
Serial.println("Fire!!!");
flag1 = 1;
} 
else{
Serial.println("No worries!");
flag1=0;
}
// for gas
int analogSensor=analogRead(smokeA0);
Serial.print("Pin A0:");
Serial.println(analogSensor);
//check the value and compare with threshold value
if(analogSensor>sensorThres)
{
  digitalWrite(redLed,HIGH);
  digitalWrite(greenLed,LOW);
  flag2=2;
}
else
{
  digitalWrite(redLed,LOW);
  digitalWrite(greenLed,HIGH);
  flag2=0;
}
delay(100);
// for dht11
float th = 50;    
float h = dht.readHumidity();    
float t = dht.readTemperature();
Serial.print("Current humidity = ");
Serial.print(h);
Serial.print("%  ");
Serial.print("temperature = "); 
Serial.print(t);   
Serial.println("C");
if(t>th){
    Serial.print("Worries");
}
delay(900);
//Serial.println("Flame is")
while(gpsSerial.available()){ // check for gps data
if(gps.encode(gpsSerial.read()))// encode gps data
{
gps.f_get_position(&lat,&lon); // get latitude and longitude
// display position


Serial.print(lat);
Serial.print(" ");
Serial.print(lon);
Serial.print(" ");


}
}

String latitude = String(lat,6);
String longitude = String(lon,6);
Serial.println(latitude+";"+longitude);
delay(1000);

}
