int led = 13;
int button = 2;


void setup() {
  pinMode(led, OUTPUT);
  pinMode(button, INPUT);
}

void loop() {
  digitalWrite(led, LOW);
  
  int value = digitalRead(button);
  
  digitalWrite(led, value);
}
