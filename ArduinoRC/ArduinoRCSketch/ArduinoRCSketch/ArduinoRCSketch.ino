/*
  Example for different sending methods
  
  https://github.com/sui77/rc-switch/
  
*/

#include <RCSwitch.h>

RCSwitch mySwitch = RCSwitch();

void setup() {

  Serial.begin(9600);
  
  // Transmitter is connected to Arduino Pin #10  
  mySwitch.enableTransmit(2);

  // Optional set pulse length.
  mySwitch.setPulseLength(310);
  
  // Optional set protocol (default is 1, will work for most outlets)
  mySwitch.setProtocol(1);
  
  // Optional set number of transmission repetitions.
   mySwitch.setRepeatTransmit(3);
  
}

void loop() {

 Serial.println("Loop...");

  /* Same switch as above, but using decimal code */
  Serial.println("Switch 1 on...");
  //mySwitch.send(6520320, 24);
   /* Same switch as above, but using binary code */
  mySwitch.send("011000110111111000000000");
  delay(3000);  
  Serial.println("Switch 1 off...");
  //mySwitch.send(6520391, 24);
  mySwitch.send("011000110111111001000111");
  delay(3000);  
 
}
