#include <CapacitiveSensor.h>

/*
 * CapitiveSense Library Demo Sketch
 * Paul Badger 2008
 * Uses a high value resistor e.g. 10M between send pin and receive pin
 * Resistor effects sensitivity, experiment with values, 50K - 50M. Larger resistor values yield larger sensor values.
 * Receive pin is the sensor pin - try different amounts of foil/metal on this pin
 */


CapacitiveSensor   cs_4_2 = CapacitiveSensor(4,2);        // 10M resistor between pins 4 & 2, pin 2 is sensor pin, add a wire and or foil if desired

void setup()                    
{
   Serial.begin(9600);
    // initialize digital pin LED_BUILTIN as an output.
  pinMode(LED_BUILTIN, OUTPUT);
}

void loop()                    
{
    long start = millis();
    long total1 =  cs_4_2.capacitiveSensor(30);
    digitalWrite(LED_BUILTIN, LOW);    // turn the LED off by making the voltage LOW
    //Serial.print(millis() - start);        // check on performance in milliseconds
    //Serial.print("\n");                    // tab character for debug windown spacing

    //Serial.print(total1);                  // print sensor output 1
    //Serial.print("\n");
    if (total1 > 1000)
    {
      digitalWrite(LED_BUILTIN, HIGH);   // turn the LED on (HIGH is the voltage level)
      delay(200);                       // wait for a second
    }
    
    delay(50);                             // arbitrary delay to limit data to serial port 
}
