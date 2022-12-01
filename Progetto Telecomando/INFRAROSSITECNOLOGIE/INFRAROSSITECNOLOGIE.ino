#include <IRremote.h>



  
   
int RECV_PIN = 11;     
  
IRrecv irrecv(RECV_PIN);     
decode_results results;     
void setup(){     
 Serial.begin(9600);     
 irrecv.enableIRIn();     
 pinMode(13, OUTPUT);     
      
}     
void loop(){   
  Serial.println(irrecv.decode(&results));
   if (irrecv.decode(&results)){     
int value = results.value;     
Serial.println(value); 
     
       switch(value){     
         case 26775: //Keypad button "1"     
         //accendo led quando premo 1     
         digitalWrite(13, HIGH);     
              
         }     
       switch(value){     
         case -26521: //Keypad button "2"     
         //spengo led quando premo 2     
         digitalWrite(13, LOW); 
         }
       irrecv.resume();      
       
} }     
