/*
 * PIR sensor tester
 */
 
int ledPin = 13;                // choose the pin for the LED
int inputPin = 2;               // choose the input pin (for PIR sensor)
int pirState = LOW;             // we start, assuming no motion detected
int val = 0;                    // variable for reading the pin status


unsigned long timeLastTriggered = 0;
unsigned long minTriggerInterval = 10* 1000; // 10 seconds 



void setup() {
  pinMode(ledPin, OUTPUT);      // declare LED as output
  pinMode(inputPin, INPUT);     // declare sensor as input
  timeLastTriggered = 0;
  Serial.begin(9600);
}
 
void loop(){
  val = digitalRead(inputPin);  // read input value
  
  if (val == HIGH) {            // check if the input is HIGH
    
    digitalWrite(ledPin, HIGH);  // turn LED ON
    
    if (pirState == LOW) {
      Serial.println("Motion detected!");
      unsigned long timeSinceLastTriggered = millis() - timeLastTriggered; // Time in ms since last triggered (or current time if not previously triggered
      // We only want to print on the output change, not state
      Serial.print("Time since last triggered ");
      Serial.println((timeSinceLastTriggered/1000));
      if ( timeSinceLastTriggered > minTriggerInterval )
      {
        timeLastTriggered = millis();
        pirState = HIGH;
      }
      else
      {
        Serial.println("Swallowed");
        delay(500);
      }
    }
    
  } else {
    digitalWrite(ledPin, LOW); // turn LED OFF
    if (pirState == HIGH){
      // we have just turned of
      Serial.println("Motion ended!");
      // We only want to print on the output change, not state
      pirState = LOW;
    }
  }
}
