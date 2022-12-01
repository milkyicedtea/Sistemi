int ledport = 13;
int buttonport = 7;
int val = 0;

void setup()
{
  pinMode(ledport, OUTPUT);
  pinMode(buttonport, INPUT);
}

void loop()
{
  val = digitalRead(buttonport); // reading button value
  if (val == 1)
  {
    digitalWrite(ledport, HIGH);
    delay(1000);
    digitalWrite(ledport, LOW);
    delay(1000);
    digitalWrite(ledport, HIGH);  
  }
  else{
    digitalWrite(ledport, LOW);
  }
}
