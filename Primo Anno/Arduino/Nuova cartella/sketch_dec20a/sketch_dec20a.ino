/*
LOW = valore di tensione = 0
HIGH = valore di tensione = 1
*/



void setup()
{
// initialize pin
pinMode(13, OUTPUT);
}

void loop()
{
digitalWrite(13, HIGH); //accendi 5V su porta 13
delay(15);
digitalWrite(13, LOW); //spegni 5V su porta 13
delay(15);
digitalWrite(13, HIGH);
}
