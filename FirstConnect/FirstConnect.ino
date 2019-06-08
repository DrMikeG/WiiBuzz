#include <ESP8266WiFi.h>

// Update these with values suitable for your network.
const char* ssid = "VM4826469";
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
}
 
void loop()
{
  
}
