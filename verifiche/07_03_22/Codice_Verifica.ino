int led1 = 8;	// rosso
int led2 = 9;	// verde
int	button1 = 6;	// sinistro
int button2 = 7;	// destro

void setup()
{
  pinMode(led1, OUTPUT);
  pinMode(button1, INPUT);
  pinMode(led2, OUTPUT);
  pinMode(button2, INPUT);
}

void loop()
{
  digitalWrite(led1, LOW);
  digitalWrite(led2, LOW);
  
  // Solo button1 premuto
  if (digitalRead(button1) == HIGH && digitalRead(button2) == LOW)
  {
    for(int i = 0; i < 10; i++)
    {
  		digitalWrite(led1, LOW);
      	digitalWrite(led2, HIGH);
      	delay(500);
      	digitalWrite(led2, LOW); 
    	digitalWrite(led1, HIGH);
    	delay(500);
    }
  }
  
  // Solo button2 premuto
  if (digitalRead(button2) == HIGH && digitalRead(button1) == LOW)
  {
    for(int i = 0; i < 10; i++)
    {
  		digitalWrite(led2, LOW);
      	digitalWrite(led1, HIGH);
      	delay(500);
      	digitalWrite(led1, LOW); 
    	digitalWrite(led2, HIGH);
    	delay(500);
    }
  }
  
  // Entrambi i pulsanti
  if (digitalRead(button1) == HIGH && digitalRead(button2) == HIGH)
  {
   	for(int i = 0; i < 10; i++)
    {
    	digitalWrite(led1, LOW);
    	digitalWrite(led2, LOW);
  		delay(500);
    	digitalWrite(led1, HIGH);
    	digitalWrite(led2, HIGH);
    	delay(500);
  
    }
  }
  delay(500);
}