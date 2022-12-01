int buzzerPin = 0;
unsigned long previousMillis1 = 0; //will store last time LED was updated
unsigned long interval1 = 100;  //interval at which to blink (milliseconds)

unsigned long interval2 = 1000;
unsigned int counter = 0;
//
void setup()
{
  DDRB = B111111;
  DDRD = B11111111;
  DDRC = B111110;
}

void loop()
{
 PORTB = B010010;
 PORTD = B01111100;
 PORTC = B010000;
 tone (0, 1000, 500);
  delay(1000); // mezzo secondo
  PORTB = B000000;
  PORTD = B00000000;
  PORTC = B000000;
  noTone(0);
  delay(1000); // Wait for 1000 millisecond(s)
}
void blinkLed() {
  //
  if (millis() - previousMillis1 > interval1) {
    previousMillis1 = millis(); //save the last time I blinked the LED
    PORTB = B111111;
  PORTD = B1111111;
  PORTC = B111110;}
  
}