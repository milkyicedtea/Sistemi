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
  
  digitalWrite(led, stato);
}
