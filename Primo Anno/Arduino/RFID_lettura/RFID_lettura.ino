/*   
PINOUT:
RC522 MODULE    Uno/Nano    
SDA             D10
SCK             D13
MOSI            D11
MISO            D12
IRQ             N/A
GND             GND
RST             D9
3.3V            3.3V

*/




#include <MFRC522.h>

MFRC522 mfrc522(10, 9);
String mycode="codice";

void setup(){
  pinMode(2, OUTPUT);
  Serial.begin(9600);
  SPI.begin();
 mfrc522.PCD_Init();
}



void loop()
{
  if(!mfrc522.PICC_IsNewCardPresent()){
    return ;
  }
  if(!mfrc522.PICC_ReadCardSerial()){
    return ;
  }
  String content = " ";
  Serial.println("UID tag:");
for(int i = 0; i<mfrc522.uid.size; i++){
  byte b =mfrc522.uid.uidByte[i];
  Serial.print (b < 0x10 ? " 0" : " ");
  Serial.print (b, DEC);
  digitalWrite (2,HIGH);
  delay(300);
  digitalWrite (2,LOW);
  
}
  
  Serial.println();
  delay(500);
}
