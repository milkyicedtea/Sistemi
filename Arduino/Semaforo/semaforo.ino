int led1 = 8;
int led2 = 9;
int	button1 = 7;
int button2 = 6;

void setup()
{
    pinMode(led1, OUTPUT);
    pinMode(button1, INPUT);
    pinMode(led2, OUTPUT);
    pinMode(button2, INPUT);
}

void loop() {
    digitalWrite(led1, LOW);
    digitalWrite(led2, LOW);

    if (digitalRead(button1) == HIGH)
    {
        digitalWrite(led1, HIGH);
    }
    else if (digitalRead(button1) == LOW)
    {
        digitalWrite(led1, LOW);
    }
    if (digitalRead(button2) == HIGH)
    {
        digitalWrite(led2, HIGH);
    }
    else if (digitalRead(button2) == LOW)
    {
        digitalWrite(led2, LOW);
    }
    if (digitalRead(button1) == HIGH && digitalRead(button2) == HIGH)
    {
        digitalWrite(led1, LOW);
        digitalWrite(led2, LOW);
        delay(1000);
        digitalWrite(led1, HIGH);
        digitalWrite(led2, HIGH);
        delay(1000);
        }
        delay(1000);
}

//add inputs on arduino
https://arduino.stackexchange.com/questions/17154/how-to-add-more-inputs-on-arduino#


// 8 * 3 pedoni 

// 4 * 3 segnali sbarre

// 12 * 3 led macchine