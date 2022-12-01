//わあああああああああああああああああああああああああああああああああ

// Select which protocol should be used. If none are selected, all will be used
//#define DECODE_DENON        // Includes Sharp
//#define DECODE_JVC
//#define DECODE_KASEIKYO
//#define DECODE_PANASONIC    // Same as DECODE_KASEIKYO
//#define DECODE_LG
//#define DECODE_NEC          // Includes Apple and Onkyo
//#define DECODE_SAMSUNG
//#define DECODE_SONY
//#define DECODE_RC5
//#define DECODE_RC6

//#define DECODE_BOSEWAVE
//#define DECODE_LEGO_PF
//#define DECODE_MAGIQUEST
//#define DECODE_WHYNTER

//#define DECODE_DISTANCE     // universal decoder for pulse width or pulse distance protocols
//#define DECODE_HASH         // special decoder for all protocols

#define DEBUG               // Activate this for debug output from the decoders
//#define INFO                // To see valuable informations from universal decoder for pulse width or pulse distance protocols

#include <Arduino.h>

#include <IRremote.hpp>

// Define macros for input and output pin etc.

// #include "PinDefinitionsAndMore.h"

#define IR_RECEIVE_PIN A2

#if !defined(STR_HELPER)
#define STR_HELPER(x) #x
#define STR(x) STR_HELPER(x)
#endif

int blue_led = 4;

void setup()
{
    Serial.begin(9600);
    
    // Initialize LED (Not utilized)
     pinMode(blue_led, OUTPUT);

    //pinMode(2, INPUT);

    // Start the receiver and if not 3 parameter specified, take LED_BUILTIN pin from the internal boards definition as default feedback LED
    // IR_RECEIVE_PIN is defined in PinDefinitionsAndMore (PIN 2)
    IrReceiver.begin(IR_RECEIVE_PIN, ENABLE_LED_FEEDBACK, blue_led);
    // IrReceiver.start();
    
    //Prints all the active protocols + PIN to place the reciver at
    Serial.print(F("Ready to receive IR signals of protocols: "));
    printActiveIRProtocols(&Serial);
    Serial.println(F("at pin " STR(IR_RECEIVE_PIN)));
}

void loop()
{

     IrReceiver.start();
     // Decoded result is in the IrReceiver.decodedIRData structure.
     
     // command is in IrReceiver.decodedIRData.command
     // address is in command is in IrReceiver.decodedIRData.address
     // up to 32 bit raw data is in IrReceiver.decodedIRData.decodedRawData

    //Check if received data is available and if yes, try to decode it.

    // Serial.println(IrReceiver.available()); // prints 0 if no receiver is available (prints 0)
    // Serial.println(IrReceiver.isIdle()); // prints 1 if no reception is going on (prints 1)
    // Serial.println(IrReceiver.decode()); // prints 0 if no data is available (prints 0)
    // Serial.println(IrReceiver.decodedIRData.command);
    IrReceiver.printIRResultAsCVariables.decodedIRData.command(&Serial);
     delay(400);
    if (IrReceiver.decode())
    {

        // Print a short summary of received data if the protocol is NOT UNKNOWN (it is)
        IrReceiver.printIRResultShort(&Serial);
        if (IrReceiver.decodedIRData.protocol == UNKNOWN)
        {
            // Our protocol is UNKNOWN, print some info?
            // Serial.println("IrReceiver.decodedIRData.command: ");
            // Serial.println(IrReceiver.decodedIRData.command); // Prints received command
        }

        //Enable comunication back since it stopped when it received
        IrReceiver.resume();

        // Check what received data was and do something
        if (IrReceiver.decodedIRData.command == 0x10)
        {
            Serial.println("Hex = 0x10");
        }
        else if (IrReceiver.decodedIRData.command == 0x11)
        {
            Serial.println("Hex = 0x11");
        }
    }
}
