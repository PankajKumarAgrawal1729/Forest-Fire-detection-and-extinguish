int flamePin = 11;
int Flame = HIGH;
int flag=0;
void setup()

{
   Serial.begin(9600);
   pinMode(flamePin, INPUT);
}
void loop()
{
Flame = digitalRead(flamePin);
if (Flame== LOW && flag==0){
Serial.println("Fire!!!");

flag = 1;
} 
else{
Serial.println("No worries!");
}
flag=0;
}
