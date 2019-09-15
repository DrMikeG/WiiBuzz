/*
  Example for different sending methods
  
  https://github.com/sui77/rc-switch/
  
*/

#include <RCSwitch.h>

RCSwitch mySwitch = RCSwitch();

void setup() {

  Serial.begin(9600);
  delay(200);  
  // Transmitter is connected to Arduino Pin #10  
  mySwitch.enableTransmit(10);
  Serial.print("transmitting pin ");
  Serial.println(10);
  // Optional set pulse length.
  mySwitch.setPulseLength(310);
  
  // Optional set protocol (default is 1, will work for most outlets)
  mySwitch.setProtocol(1);
  
  // Optional set number of transmission repetitions.
   mySwitch.setRepeatTransmit(1); // 1 is not enough to get a successful programming, but 15 is
   // still can't get it to switch though
  
}

void loop() {

 Serial.println("Loop...");

  /* Same switch as above, but using decimal code */
  //Serial.println("Switch 1 on...");
  //mySwitch.send(6520320, 24);
   /* Same switch as above, but using binary code */
  //mySwitch.send(6520398,24);
  //mySwitch.send("011000110000000000000000");
  //delay(1500);  
  //Serial.println("Switch 1 off...");
  //mySwitch.send(6520390, 24);
  //mySwitch.send("011000110111111001000011");
  for (int i=0; i < 15; i++)
  {
    mySwitch.send("011000110000000000000000");
    delay(40);  
  }
  
  delay(1500);  
 
}
