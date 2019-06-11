#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>

// Update these with values suitable for your network.
const char* ssid = "ManCaveIOT";
const char* password = "z8gGpcvqjhpk";

WiFiClient espClient;
int SwitchedPin = 0;

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
  
  HTTPClient http;  //Declare an object of class HTTPClient
  http.begin("http://192.168.0.45/0/on");  //Specify request destination
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
  
}
