int stato = LOW;
int led = 13;
int button = 2;


void setup() {
  pinMode(led, OUTPUT);
  pinMode(button, INPUT);
}

void loop() {
  
  if (digitalRead(button) == HIGH)
  {
    stato = !stato;
  	delay(200);
  }
  
  if (stato == HIGH)
  {
    digitalWrite(led, HIGH);
  }
  else
  {
    digitalWrite(led, LOW);
  }
}
