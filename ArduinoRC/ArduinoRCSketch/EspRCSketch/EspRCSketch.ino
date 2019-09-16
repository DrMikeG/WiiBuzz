#include <RCSwitch.h>
#include <ESP8266WiFi.h>
#include <ESP8266mDNS.h>        // Include the mDNS library

const char* ssid = "VM4826469";
const char* password = "z8gGpcvqjhpk";


WiFiServer server(80);
RCSwitch mySwitch = RCSwitch();
// Variable to store the HTTP request
String header;

// Auxiliar variables to store the current output state
String output2State = "off";
String output0State = "on";

// Assign output variables to GPIO pins
const int output0 = 0;
const int output2 = 2;

//IPAddress local_IP(192,168,0,45);
//IPAddress gateway(192,168,0,9);
//IPAddress subnet(255,255,255,0);

void setup() {

  //Serial.begin(115200);
  delay(200);  
  // Transmitter is connected to Esp Pin #GPIO0  
  mySwitch.enableTransmit(3);
  //Serial.print("transmitting pin ");
  //Serial.println(10);
  // Optional set pulse length.
  mySwitch.setPulseLength(310);
  
  // Optional set protocol (default is 1, will work for most outlets)
  mySwitch.setProtocol(1);
  
  // Optional set number of transmission repetitions.
   mySwitch.setRepeatTransmit(15); // 1 is not enough to get a successful programming, but 15 is
   // still can't get it to switch though

  pinMode(output2, OUTPUT);
  pinMode(output0, OUTPUT);
  // Set outputs to LOW
  digitalWrite(output2, LOW);
  digitalWrite(output0, HIGH);
  // Connect to Wi-Fi network with SSID and password
  //Serial.print("Connecting to ");
  //Serial.println(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
  //  Serial.print(".");
  }
  /*Serial.println("");
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
  */
  if (!MDNS.begin("lvlights")) {             // Start the mDNS responder for esp8266.local
    //Serial.println("Error setting up MDNS responder!");
  }
  //Serial.println("mDNS responder started");
  server.begin();
  //Serial.println("HTTP server started");
  digitalWrite(output2, HIGH);
  
}

void loop() {

WiFiClient client = server.available();   // Listen for incoming clients

  if (client) {                             // If a new client connects,
    //Serial.println("New Client.");          // print a message out in the serial port
    String currentLine = "";                // make a String to hold incoming data from the client
    while (client.connected()) {            // loop while the client's connected
      if (client.available()) {             // if there's bytes to read from the client,
        char c = client.read();             // read a byte, then
        //Serial.write(c);                    // print it out the serial monitor
        header += c;
        if (c == '\n') {                    // if the byte is a newline character
          // if the current line is blank, you got two newline characters in a row.
          // that's the end of the client HTTP request, so send a response:
          if (currentLine.length() == 0) {
            // HTTP headers always start with a response code (e.g. HTTP/1.1 200 OK)
            // and a content-type so the client knows what's coming, then a blank line:
            client.println("HTTP/1.1 200 OK");
            client.println("Content-type:text/html");
            client.println("Connection: close");
            client.println();
            
            // turns the GPIOs on and off
            if (header.indexOf("GET /lights/on") >= 0) {
              Serial.println("GPIO 2 on");
              output2State = "on";
              //digitalWrite(output2, HIGH);
              mySwitch.send("0110001101111110010011110");
              //delay(1500);  
            } else if (header.indexOf("GET /lights/off") >= 0) {
              //Serial.println("GPIO 2 off");
              output2State = "off";
              //digitalWrite(output2, LOW);
              mySwitch.send("0110001101111110010001110");
              //delay(1500);  
            } else if (header.indexOf("GET /0/on") >= 0) {
              //Serial.println("GPIO 0 on");
              output0State = "on";
              digitalWrite(output2, HIGH);
            } else if (header.indexOf("GET /0/off") >= 0) {
              //Serial.println("GPIO 0 off");
              output0State = "off";
              digitalWrite(output2, LOW);
            }
            
            // Display the HTML web page
            client.println("<!DOCTYPE html><html>");
            client.println("<head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">");
            client.println("<link rel=\"icon\" href=\"data:,\">");
            // CSS to style the on/off buttons 
            // Feel free to change the background-color and font-size attributes to fit your preferences
            client.println("<style>html { font-family: Helvetica; display: inline-block; margin: 0px auto; text-align: center;}");
            client.println(".button { background-color: #195B6A; border: none; color: white; padding: 16px 40px;");
            client.println("text-decoration: none; font-size: 30px; margin: 2px; cursor: pointer;}");
            client.println(".button2 {background-color: #77878A;}</style></head>");
            
            // Web Page Heading
            client.println("<body><h1>Status socket controls</h1>");
            
            // Display current state, and ON/OFF buttons for GPIO 2  
            client.println("<p>Lights are " + output2State + "</p>");
            // If the output2State is off, it displays the ON button       
            if (output2State=="off") {
              client.println("<p><a href=\"/lights/on\"><button class=\"button\">ON</button></a></p>");
            } else {
              client.println("<p><a href=\"/lights/off\"><button class=\"button button2\">OFF</button></a></p>");
            } 
               
            

            client.println("</body></html>");
            
            // The HTTP response ends with another blank line
            client.println();
            // Break out of the while loop
            break;
          } else { // if you got a newline, then clear currentLine
            currentLine = "";
          }
        } else if (c != '\r') {  // if you got anything else but a carriage return character,
          currentLine += c;      // add it to the end of the currentLine
        }
      }
    }
    // Clear the header variable
    header = "";
    // Close the connection
    client.stop();
    //Serial.println("Client disconnected.");
    //Serial.println("");
  }

  
 
}