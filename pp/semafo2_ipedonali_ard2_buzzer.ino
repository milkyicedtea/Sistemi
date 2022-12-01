int speaker = 14;
int contped = 13;
int c2 = 0;// fase 3 macchine include Pedonale 2
int c4 = 0;// fase 4 macchine include Pedonale 4
int b1 = 0;
int ledState = LOW;             // ledState used to set the LED
int ledRosso = LOW; 
unsigned long t1, t2, t3, t4, t5, dt1, dt2, dt3, dt4;  
  
#define VERDE 0
#define ROSSO 1
#define ped1 0
#define ped2 1
#define ped3 2
#define ped4 3

int b1counter = 0;

int lastb1 = 0;
int stato = 0;
int val = 1;
int c = 0;// stato standby ( giallo lampeggiante)
int T = 0; // test led
int semaforo1[] = {5, 6};
int semaforo2[] = {7, 8};
int semaforo3[] = {9, 10};
int semaforo4[] = {11,12};
//int chiamate1[] = {14,14,14,14};vettore da settare con Mega


void setup()
{
  pinMode(3, INPUT);// chiamata a semaforo 1P da Arduino1
  pinMode(2, INPUT);// chiamata a semaforo 4P da Arduino1
  pinMode(13, OUTPUT);// uscita verso Ard1 per pedoni


  for (int i = 0; i <2; i++)
  {
    pinMode(semaforo1[i], OUTPUT);
    pinMode(semaforo2[i], OUTPUT);
    pinMode(semaforo3[i], OUTPUT);
    pinMode(semaforo4[i], OUTPUT);
  } 
    
//  for (int i = 0; i <5; i++)
//  { 
//  pinMode(chiamate1[i], OUTPUT);
// } 
  pinMode(speaker, OUTPUT);
  pinMode(contped, OUTPUT);
}


void loop()
{
  int soglia = 25;
  int v = analogRead(A5);
  c2 = digitalRead(2);// uscita arduino 1 
  c4 = digitalRead(3);// uscita arduino 1
  Serial.begin(9600);
  Serial.println("valorev");
  Serial.println(v);
  Serial.println("stato");
  Serial.println(stato);
  Serial.println("contped");
  Serial.println(contped);
  Serial.println("c2");
  Serial.println(c2);
  Serial.println("c4");
  Serial.println(c4);
  Serial.println("b1");
  Serial.println(b1);
  Serial.println("c");
  Serial.println(c);
  delay(500);

  // SEMAFORI PEDONALI IN STAND BY
  if ((t11blink(500)) && (b1==0) && (c==0) )
  {
    digitalWrite (semaforo1[1],ledRosso);
    digitalWrite (semaforo2[1],ledRosso);
    digitalWrite (semaforo3[1],ledRosso);
    digitalWrite (semaforo4[1],ledRosso);
    if (millis() - t1 > 10000)
    {
      c = 1;
      t1 = millis();
    }
  }

  // CICLO MACCHINA 
  if (( (v>= 0) && (v<100) ) &&(c==1))
  {
    b1=0;
    cambiaStato(semaforo1,ROSSO);
    cambiaStato(semaforo2,ROSSO);
    cambiaStato(semaforo3,ROSSO);
    cambiaStato(semaforo4,ROSSO);
    if (millis() - t1 > 2000)
    {
      c=2;
      t1= millis();
    }
  }
 



  //  CHIAMATA DA ARD1 2P
  if (((c2 == HIGH) && (b1 == 0)) && (c == 2))
  {
    c=21;
    b1=2;
    stato=1;
    
    if ((millis() - t1 > 3000))
    {
      digitalWrite (semaforo2[0], stato);
      digitalWrite (semaforo2[1], !stato);
    }
   
  for(int i = 0; i < 4; i++)
  { // suono lungo 
    tone(speaker,1000,200);
    delay(1000);
    noTone(speaker);
  }

  for(int i = 0; i < 8; i++)
  { // suono veloce 
    tone(speaker,1000,200);
    delay(500);
    noTone(speaker);
  }
  lastb1 = b1;}
  if ((stato == 1 ) && (c == 21) && (millis() - t1 > 6000))
  {
    stato = 0;
    c = 1;   
    t1 = millis();
  }

  // CHIAMATA DA ARD1 4P
  if (((c4 == HIGH) && (b1 == 0)) && (c == 2))
  {
    c=41;
    b1=4;
    stato=1;
    
    if ((millis()-t1 >3000))
    {
      digitalWrite (semaforo4[0], stato);
      digitalWrite (semaforo4[1], !stato);
    }

    for(int i=0; i < 4; i++)
    { // suono lungo 
      tone(speaker, 1000, 200);
      delay(1000);
      noTone(speaker);
    }

    for(int i = 0; i < 8; i++)
    { // suono veloce 
      tone(speaker, 1000, 200);
      delay(500);
      noTone(speaker);
    }
    lastb1 = b1;
  }

  if ((stato == 1 )&&(c==41)&&(millis()-t1 >7000))
  {
    stato=0;
    c=1;
    contped=0;
    digitalWrite (semaforo4[0],stato);
    digitalWrite (semaforo4[1],!stato);
    b1=0;
    t1= millis();
  }

 // CHIAMATA PEDONALE SEMAFORO 4p
 
  if ( (v> 180 -soglia) && (v<180+soglia) && (c==2))
  {
    b1=4;
    stato=1;
    contped=1; 
    digitalWrite(13,HIGH); 
    if ((millis()-t1 >4000))
    {
      digitalWrite (semaforo4[0],stato);
      digitalWrite (semaforo4[1],!stato); 
    }
  
    for(int i = 0; i < 4; i++)
    {
      /* suono lungo */
      tone(speaker,1000,200);
      delay(1000);
      noTone(speaker);
    }

    for(int i = 0; i < 8; i++)
    { 
      /* suono veloce */
      tone(speaker,1000,200);
      delay(500);
      noTone(speaker);
    }
    lastb1 = b1;
  } 

  if ((stato == 1 ) && (b1 = 4) && (millis() - t1 > 7000))
  {
    stato=0;
    c=1;
    contped=0;
    b1=0;
    digitalWrite(13,LOW);
    t1= millis();
  }
    
    
   
 // CHIAMATA PEDONALE SEMAFORO 3p
  if (( (v > 362 - soglia) && (v < 362 + soglia)) && (c == 2))
  {
    b1=3;
    stato=1;
    digitalWrite(13,HIGH);   
    if ((millis()-t1 >4000))
    {
      digitalWrite (semaforo3[0],stato);
      digitalWrite (semaforo3[1],!stato);
    }

    for(int i = 0;i<4;i++)
    { // suono lungo
      tone(speaker,1000,200);
      delay(1000);
      noTone(speaker);
    }

    for(int i = 0; i < 8; i++)
    { 
      // suono veloce
      tone(speaker,1000,200);
      delay(500);
      noTone(speaker);
    }
    lastb1 = b1;
  }

  if ((stato == 1 ) && (b1 = 3) && (millis() - t1 > 7000))
  {
    stato = 0;
    c=1;
    digitalWrite(13, LOW); 
    t1 = millis();
  }
  

  // CHIAMATA PEDONALE SEMAFORO 2p
  if (((v > 546 - soglia) && (v < 546 + soglia)) && (c == 2))
  {
    b1=2;
    stato=1;
    digitalWrite(13,HIGH);

    if ((millis()-t1 >4000))
    { 
      digitalWrite (semaforo2[0],stato);
      digitalWrite (semaforo2[1],!stato);  
    }

    for(int i = 0; i < 4; i++)
    { 
      /* suono lungo */
      tone(speaker,1000,200);
      delay(1000);
      noTone(speaker);
    }

    for(int i = 0;i<8;i++)\
    { 
      /* suono veloce */
      tone(speaker,1000,200);
      delay(500);
      noTone(speaker);
    }
    lastb1 = b1;
  }

  if ((stato == 1 ) && (b1 = 2) && (millis() - t1 > 7000))
  {
    stato=0;
    c=1;
    digitalWrite(13, LOW);
    t1= millis();
  }
  // CHIAMATA PEDONALE SEMAFORO 1p 
  if (( (v > 840 - 10) && (v < 840 + 10)) && (c == 2))
  {
    b1=1;
    stato=1;
    digitalWrite(13, HIGH); 
    if ((millis()-t1 >4000))
    {
      digitalWrite (semaforo1[0], stato);
      digitalWrite (semaforo1[1], !stato);
    }

    for(int i = 0; i < 4; i++)\
    {
      /* suono lungo */
      tone(speaker,1000,200);
      delay(1000);
      noTone(speaker);
    }

    for(int i = 0; i < 8; i++)
    {
      /* suono veloce */
      tone(speaker, 1000, 200);
      delay(500);
      noTone(speaker);
    }
    lastb1 = b1;
  }
  if ((stato == 1 ) && (b1 = 1) && (millis() - t1 > 7000))
  {
    stato = 0;
    c = 1;
    digitalWrite(13, LOW); 
    t1 = millis();
  }
  
  // CHIAMATA PEDONALE contemporanea 1p + 2p va semaforo 1
  if (((v > 765 - soglia) && (v < 765 + soglia)) && (c == 2))
  {
    b1=5;
    stato=1;
    digitalWrite(13, HIGH);   
    if ((millis() - t1 > 4000))
    {
      digitalWrite (semaforo1[0], stato);
      digitalWrite (semaforo1[1], !stato);
    }
   
   digitalWrite (semaforo1[0], stato);
   digitalWrite (semaforo1[1], !stato);

    for(int i = 0; i < 4; i++)
    {
      /* suono lungo */
      tone(speaker, 1000, 200);
      delay(1000);
      noTone(speaker);
    }

    for(int i = 0; i < 8; i++)
    {
      /* suono veloce */
      tone(speaker, 1000, 200);
      delay(500);
      noTone(speaker);
    }
    lastb1 = b1;
  }

  if ((stato == 1 ) && (b1 = 5) && (millis() - t1 > 7000))
  {
    stato=0;
    c=1;
    digitalWrite(13, LOW);
    t1= millis();
  } 
  // CHIAMATA PEDONALE contemporanea 1p + 3p va semaforo 1 e 3
  if (((v > 680 - soglia) && (v < 680 + soglia)) && (c == 2))
  {
    b1 = 6;
    stato = 1;
    digitalWrite(13, HIGH);   
    if ((millis() - t1 > 4000))
    {
      digitalWrite (semaforo3[0], stato);
      digitalWrite (semaforo3[1], !stato);
      digitalWrite (semaforo1[0], stato);
      digitalWrite (semaforo1[1], !stato);
    }

    for(int i = 0; i < 4; i++){ /* suono lungo */
    tone(speaker,1000,200);
    delay(1000);
    noTone(speaker);
    }
    for(int i = 0; i < 8; i++)
    {
      /* suono veloce */
      tone(speaker,1000,200);
      delay(500);
      noTone(speaker);
    }
    lastb1 = b1;
  }
  if ((stato == 1 )&&(b1=5)&&(millis()-t1 >7000))
  {
    stato=0;
    c=1;
    digitalWrite(13,LOW);
    t1= millis();
  }
  // CHIAMATA PEDONALE contemporanea 2p + 3p va semaforo 2 e 3
  if (((v > 443 - soglia) && (v < 443 + soglia)) && (c == 2))
  {
    b1=8;
    stato=1;
    digitalWrite(13,HIGH);   
    if ((millis()-t1 >4000))
    {
      digitalWrite (semaforo2[0],stato);
      digitalWrite (semaforo2[1],!stato);
      digitalWrite (semaforo3[0],stato);
      digitalWrite (semaforo3[1],!stato);
    }
    for(int i = 0; i < 4; i++)
    {
      /* suono lungo */
      tone(speaker,1000,200);
      delay(1000);
      noTone(speaker);
    }
    for(int i = 0; i < 8; i++)
    {
      /* suono veloce */
      tone(speaker,1000,200);
      delay(500);
      noTone(speaker);
    }
    lastb1 = b1;
  } 

  if ((stato == 1 )&&(b1=5)&&(millis()-t1 >7000))
  {
    stato=0;
    c=1;
    digitalWrite(13,LOW);
    t1= millis();
  }

  // CHIAMATA PEDONALE contemporanea 1p + 4p va semaforo 1 e 4
    if (((v > 507 - soglia) && (v < 507 + soglia)) && (c == 2))
    {
      b1=7;
      stato=1;
      digitalWrite(13,HIGH);   
      if ((millis()-t1 >4000))
      {
        digitalWrite (semaforo4[0],stato);
        digitalWrite (semaforo4[1],!stato);
        digitalWrite (semaforo1[0],stato);
       digitalWrite (semaforo1[1],!stato);
      }

    for(int i = 0; i < 4; i++)
    {
      /* suono lungo */
      tone(speaker,1000,200);
      delay(1000);
      noTone(speaker);
    }

    for(int i = 0; i < 8; i++)
    {
      /* suono veloce */
      tone(speaker,1000,200);
      delay(500);
      noTone(speaker);
    }
    lastb1 = b1;
  }

    if ((stato == 1 )&&(b1=5)&&(millis()-t1 >7000))
    {
      stato=0;
      c=1;
      digitalWrite(13,LOW);
      t1= millis();
    }
// CHIAMATA PEDONALE contemporanea 2p + 4p va semaforo 2 e 4
  if (((v > 280 - soglia) && (v < 280 + soglia)) && (c == 2))
  {
    b1=9;
    stato=1;
    digitalWrite(13,HIGH);   
    if ((millis()-t1 >4000))
    {
      digitalWrite (semaforo2[0],stato);
      digitalWrite (semaforo2[1],!stato);
      digitalWrite (semaforo4[0],stato);
      digitalWrite (semaforo4[1],!stato);
    }

    for(int i = 0;i<4;i++)
    {
      /* suono lungo */
      tone(speaker,1000,200);
      delay(1000);
      noTone(speaker);
    }

    for(int i = 0; i < 8; i++)
    {
      /* suono veloce */
      tone(speaker,1000,200);
      delay(500);
      noTone(speaker);
    }
    lastb1 = b1;
  }
  if ((stato == 1 ) && (b1 = 5) && (millis() - t1 > 7000))
  {
    stato=0;
    c=1;
    digitalWrite(13, LOW);
    t1= millis();
  }
  // CHIAMATA PEDONALE contemporanea 3p + 4p va semaforo 2 e 4
  if (((v > 220 - soglia) && (v < 220 + soglia)) && (c == 2)) 
  {
    b1=10;
    stato=1;
    digitalWrite(13,HIGH);   
    if ((millis()-t1 >4000))
    {
      digitalWrite (semaforo3[0],stato);
      digitalWrite (semaforo3[1],!stato);
      digitalWrite (semaforo4[0],stato);
      digitalWrite (semaforo4[1],!stato);
    }

    for(int i = 0;i<4;i++)
    { /* suono lungo */
      tone(speaker,1000,200);
      delay(1000);
      noTone(speaker);
    }

    for(int i = 0; i < 8; i++)
    { /* suono veloce */
      tone(speaker,1000,200);
      delay(500);
      noTone(speaker);
    }
    lastb1 = b1;
  }
  if ((stato == 1 ) && (b1 = 5) && (millis() - t1 > 7000))
  {
    stato=0;
    c=1;
    digitalWrite(13,LOW);
    t1= millis();
  }
}

void cambiaStato(int semaforo[], int luce)
{ 
  for (int i = 0; i < 3; i++)
  {
    if(i == luce)
    {
      digitalWrite(semaforo[i], HIGH);
    }
    else 
    {
      digitalWrite(semaforo[i], LOW);
    }
  }
}

void cambiaped(int chiamate1[], int luce)
{ 
  for (int i = 0; i < 4; i++)
  {
    if(i == luce)
    {
      digitalWrite(chiamate1[i], HIGH);
    }
    else 
    {
      digitalWrite(chiamate1[i], LOW);
    }
  }
}

void cambiab1(int chiamate1[], int luce)
{ 
  for (int i = 0; i < 5; i++)
  {
    if(i == luce)
    {
      digitalWrite(chiamate1[i], HIGH);
    }
    else
    {
      digitalWrite(chiamate1[i], LOW);
    }
  }
}

int t11blink (int timer11)
{
  static unsigned long t11, dt11;
  int ret = 0;
  dt11 = millis() - t11;
  if ((dt11 >= 500) && (c == 0))
  {
    t11= millis();
    if (ledRosso == LOW)
    {
      ledRosso = HIGH;
    } 
    else
    {
      ledRosso = LOW;
    }
  ret = 1;
  }
  return ret;
}

int t12 (int timer12)
{
  static unsigned long t12, dt12;
  int ret = 0;
  dt12 = millis() - t12;
  if ((dt12 >= 10000) && (c == 0))
  {
    t12= millis();
    ret = 1;
  }
  return ret;
}