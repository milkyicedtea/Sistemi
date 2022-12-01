




int ledState = LOW;             // ledState used to set the LED
int ledGiallo = LOW; 

unsigned long t1,t2,t3,t4,t5,dt1,dt2,dt3,dt4;  

 
#define VERDE 0
#define GIALLO 1
#define ROSSO 2
#define ped1 0
#define ped2 1
#define ped3 2
#define ped4 3
int s=0;
int standby=0;
int pedone =0;
int b1counter = 0;
int b1 = 0;
int lastb1= 0;
int State= LOW;
int val=0;
int v=0;
int c=0;// stato standby ( giallo lampeggiante)
int T=0; // test led
int lastc=0;// serve a riprendere il ciclo dopo chiamata da dove stava 
int semaforo1[] = {13, 12, 11 };//dritto-destra 4
int semaforo2[] = {13, 12, 11 };//dritto-destra 2
int semaforo3[] = {7, 6, 5 };//dritto-sinistra 1
int semaforo4[] = {4, 3, 2 };//dritto-sinistra 3
int semaforo5[] = {10, 9, 8 };//destra semaforo 1
int semaforo6[] = {10, 9, 8 };//destra semaforo 3
int semaforo7[] = {10, 9, 8  }; // sinistra semaforo 2 
int semaforo8[] = {10, 9, 8 };//sinistra semaforo 4
int x = 200;// ritardo cambio stato semafori
int ritardo = 1000;
int contped = 0;// premuta pulsante chiamata pedoni
int rp =LOW;// rosso effettivo su pedoni
int rm =LOW;// rosso effettivo su pedoni
int lastcontped = LOW;


void setup() {
  

Serial.begin(9600);

for (int i = 0; i <3; i++) {
    pinMode(semaforo1[i], OUTPUT);
    pinMode(semaforo2[i], OUTPUT);
    pinMode(semaforo3[i], OUTPUT);
    pinMode(semaforo4[i], OUTPUT);
    pinMode(semaforo5[i], OUTPUT);
    pinMode(semaforo6[i], OUTPUT);
    pinMode(semaforo7[i], OUTPUT);
    pinMode(semaforo8[i], OUTPUT);}
pinMode(14, OUTPUT); //verso2 per ciclo pedonale P2
pinMode(15, OUTPUT); //verso2 per ciclo pedonale P4
pinMode(18, INPUT);  // da arduino 2 (alto con chiamata pulsante)
pinMode(17, INPUT);  // da arduino 2 (alto con tutti i semafori rossi)
pinMode(19, OUTPUT); //verso ard2 per rosso fine ciclo macchine
}

void loop() {
rm=digitalRead(19);  
contped=digitalRead(18);//da output ard2 su premuta pulsante pedonale  
rp=digitalRead(17);// da output ard2 tutti i semafori rossi
T=1;
standby=1;
int v = analogRead(A2);
int soglia =20;

if ( digitalRead(14)==0 && digitalRead(15)==0 && contped==0) {
  s=1;}
  else s=0;// nessun ciclo macchina che riguarda pedoni, nessuna chiamata pedoni con s=1

// condizione di chiamata semaforo pedonale 
// rosso sul ciclo attivo
// contped =1 quando c'è un pedonale verde per ciclo pedonale
/*if (contped != lastcontped && contped == HIGH){
   State = !State;
  if (State == HIGH){
  digitalWrite(contped, HIGH);
 }
else{ 
digitalWrite(contped, LOW);
}
}
lastcontped = contped;*/




   


    
// FUNZIONAMENTO BASE
    // stand by
    
if (t11blink(500)&& (T==1)&& standby==1){

digitalWrite (semaforo1[1],ledGiallo);
digitalWrite (semaforo2[1],ledGiallo);
digitalWrite (semaforo3[1],ledGiallo);
digitalWrite (semaforo4[1],ledGiallo);
digitalWrite (semaforo5[1],ledGiallo);
digitalWrite (semaforo6[1],ledGiallo);
digitalWrite (semaforo7[1],ledGiallo);
digitalWrite (semaforo8[1],ledGiallo);
if (millis()-t1 >7000){
c=1;
lastc=0;
standby=0;
 t1= millis();

 }}

// FASE 1 TUTTI ROSSI
if (((c==1)&&(millis()-t1 >1000)) ){
  lastc=1;

 if (millis()-t1 >1000){
cambiaStato(semaforo1,ROSSO);
cambiaStato(semaforo2,ROSSO);
cambiaStato(semaforo3,ROSSO);
cambiaStato(semaforo4,ROSSO);
cambiaStato(semaforo5,ROSSO);
cambiaStato(semaforo6,ROSSO);
cambiaStato(semaforo7,ROSSO);
cambiaStato(semaforo8,ROSSO);
digitalWrite (19,HIGH);
if ((millis()-t1 >2000)){

t1= millis();
c=2;}}
}
 

// FASE 2 PRIMO CICLO SEMAFORO 
 if (((c==2) )&&(millis()-t1 >5000)){
lastc=2;

if (((millis()-t3 >4000)&&(contped ==0))&& rp==1 && rm==1){
digitalWrite (19,LOW);
cambiaStato(semaforo1,VERDE);
cambiaStato(semaforo2,VERDE);
t3=millis();}

if (millis()-t1 >7000){
cambiaStato(semaforo1,GIALLO);
cambiaStato(semaforo2,GIALLO);

if  (millis()-t1 >9000) {
cambiaStato(semaforo1,ROSSO);
cambiaStato(semaforo2,ROSSO);
digitalWrite (19,HIGH);
t1= millis();
c=3;}}
if ((millis()-t1>7000) && (rp==0)){
cambiaStato(semaforo1,GIALLO);
cambiaStato(semaforo2,GIALLO);
if  ((millis()-t1>9000) && (rp==0))  {
cambiaStato(semaforo1,ROSSO);
cambiaStato(semaforo2,ROSSO);
digitalWrite (19,HIGH);
t1= millis();
c=3;
}}
if ((contped ==1)&&(millis()-t1 >7000)){
cambiaStato(semaforo1,GIALLO);
cambiaStato(semaforo2,GIALLO);
if ((contped ==1)&&(millis()-t1 >9000))  {
cambiaStato(semaforo1,ROSSO);
cambiaStato(semaforo2,ROSSO);
digitalWrite (19,HIGH);
t1= millis();
c=3;
}}
}

//FASE 3 SECONDO CICLO SEMAFORO
if ((c==3)&&(millis()-t1 >5000)){
lastc=c;

if (((millis()-t3 >4000)&&(contped ==0))&& rp==1 && rm==1){
digitalWrite (19,LOW);
cambiaStato(semaforo5,VERDE);
cambiaStato(semaforo6,VERDE);
cambiaStato(semaforo7,VERDE);
cambiaStato(semaforo8,VERDE);
t3=millis();}
if (millis()-t1 >7000){
cambiaStato(semaforo5,GIALLO);
cambiaStato(semaforo6,GIALLO);
cambiaStato(semaforo7,GIALLO);
cambiaStato(semaforo8,GIALLO);
if  (millis()-t1 >9000) {
cambiaStato(semaforo5,ROSSO);
cambiaStato(semaforo6,ROSSO);
cambiaStato(semaforo7,ROSSO);
cambiaStato(semaforo8,ROSSO);
digitalWrite (19,HIGH);
t1= millis();
c=4;}}
if ((millis()-t1>7000) && (rp==0)){
cambiaStato(semaforo5,GIALLO);
cambiaStato(semaforo6,GIALLO);
cambiaStato(semaforo7,GIALLO);
cambiaStato(semaforo8,GIALLO);
if  ((millis()-t1>9000) && (rp==0))  {
cambiaStato(semaforo5,ROSSO);
cambiaStato(semaforo6,ROSSO);
cambiaStato(semaforo7,ROSSO);
cambiaStato(semaforo8,ROSSO);
digitalWrite (19,HIGH);
t1= millis();
t1= millis();
c=4;}}
if ((contped ==1)&&(millis()-t1 >7000)){
cambiaStato(semaforo5,GIALLO);
cambiaStato(semaforo6,GIALLO);
cambiaStato(semaforo7,GIALLO);
cambiaStato(semaforo8,GIALLO);
if ((contped ==1)&&(millis()-t1 >9000))  {
cambiaStato(semaforo5,ROSSO);
cambiaStato(semaforo6,ROSSO);
cambiaStato(semaforo7,ROSSO);
cambiaStato(semaforo8,ROSSO);
digitalWrite (19,HIGH);
t1= millis();
c=4;}}
}
//FASE 4 TERZO CICLO SEMAFORO

if ((c==4)&&(millis()-t1 >5000)&& (contped == 0)&& rp==1 ){
lastc=c;

digitalWrite (15,HIGH);
cambiaStato(semaforo3,VERDE);
digitalWrite (19,LOW);
if ((millis()-t1 >7000)){
cambiaStato(semaforo3,GIALLO);
if ((millis()-t1 >9000)){
digitalWrite (15,LOW);
cambiaStato(semaforo3,ROSSO);
digitalWrite (19,HIGH);

t1= millis();
c=5;}}

}
//FASE 5 QUARTO CICLO SEMAFORO
if (((c==5)&& (contped == 0))&&(millis()-t1 >5000)&& rp==1  ){
lastc=c;
digitalWrite (19,LOW);
digitalWrite (14,HIGH);
cambiaStato(semaforo4,VERDE);
if ((millis()-t1 >7000)){
cambiaStato(semaforo4,GIALLO);
if ((millis()-t1 >9000)){
cambiaStato(semaforo4,ROSSO);
digitalWrite (14,LOW);
digitalWrite (19,HIGH);
t1= millis();
c=2;
}}

}
Serial.println("c");
Serial.println(c); 
Serial.println("State");
Serial.println(State); 
Serial.println("s");
Serial.println(s); 
Serial.println("contped");
Serial.println(contped);   
Serial.println("rp");
Serial.println(rp);
Serial.println("rm");
Serial.println(rm);
Serial.println(v);
Serial.println(val);
//Serial.println("pedone"); 
//Serial.println(pedone);


 delay(500);
 
 }

void cambiaStato(int semaforo[], int luce){ 
for (int i = 0; i < 3; i++){
  if(i == luce){
    digitalWrite(semaforo[i], HIGH);
  }else {
    digitalWrite(semaforo[i], LOW);
  }
  }
}
void cambiaped(int chiamate1[], int luce){ 
for (int i = 0; i < 4; i++){
  if(i == luce){
    digitalWrite(chiamate1[i], HIGH);
  }else {
    digitalWrite(chiamate1[i], LOW);
  }
  }
}





 int t11blink (int timer11){
  static unsigned long t11,dt11;
  int ret= 0;
  dt11 = millis()- t11;
  if ((dt11>=500)&&(c==0)){
  t11= millis();
  if (ledGiallo == LOW) {
      ledGiallo = HIGH;
    } else {
      ledGiallo = LOW;
    }
  ret = 1;
  }
  return ret;
  } 
 int t12 (int timer12){
  static unsigned long t12,dt12;
  int ret = 0;
  dt12 = millis()- t12;
  if ((dt12>=10000)&& (c==0)){
  t12= millis();
  
  ret = 1;
  }
  return ret;
  }  
  
