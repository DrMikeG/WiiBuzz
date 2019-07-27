#include <CapacitiveSensor.h>
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>

const char* ssid = "ManCaveIOT";
const char* password = "z8gGpcvqjhpk";

CapacitiveSensor   cs_4_2 = CapacitiveSensor(0,2);        // 10M resistor between pins 4 & 2, pin 2 is sensor pin, add a wire and or foil if desired

void setup_wifi() {
 Serial.begin(115200);
  delay(100);
 
  // We start by connecting to a WiFi network
 
  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
  
  WiFi.begin(ssid, password);
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
 
  Serial.println("");
  Serial.println("WiFi connected");  
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
 
}

void setup()                    
{
    
  setup_wifi(); 
  //pinMode(SwitchedPin, OUTPUT);
  //digitalWrite(SwitchedPin, LOW);
  
}

void triggerFlash()
{
  
  HTTPClient http;  //Declare an object of class HTTPClient
  http.begin("http://192.168.0.45/flash");  //Specify request destination
  //http.begin("http://mancave.local/0/on");  // mDNS does not seem to be supported
  int httpCode = http.GET();                                                                  //Send the request
  if (httpCode > 0) { //Check the returning code
    String payload = http.getString();   //Get the request response payload
    Serial.println(payload);                     //Print the response payload
  }
  http.end();   //Close connection
}

void loop()                    
{
    long start = millis();
    long total1 =  cs_4_2.capacitiveSensor(30);
    digitalWrite(LED_BUILTIN, LOW);    // turn the LED off by making the voltage LOW
    //Serial.print(millis() - start);        // check on performance in milliseconds
    //Serial.print("\n");                    // tab character for debug windown spacing

    Serial.print(total1);                  // print sensor output 1
    Serial.print("\n");
    if (total1 > 1000)
    {
      triggerFlash();
      delay(2000);                       // wait for a second
    }
    
    delay(50);                             // arbitrary delay to limit data to serial port 
}
