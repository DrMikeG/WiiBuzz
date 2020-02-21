#include <RCSwitch.h>
#include <ESP8266WiFi.h>
#include <ESP8266mDNS.h> // Include the mDNS library

const char *ssid = "VM4826469";
const char *password = "z8gGpcvqjhpk";

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

// At the serial lines are commented out
// because I have the circuit set up to use pin 3 (rx pin on ESP8266-01 Pinout)
// to control rc board input
// I am still seeing a connection reset error, but I think I've solved at least one 
// of the hangs by removing the while(true) infinte loop

void setup()
{

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

  //Serial.println("HTTP server started");
  digitalWrite(output2, HIGH);
}

bool wifiIsConnected()
{
  return WiFi.status() == WL_CONNECTED;
}

void setup_wifi()
{
  //Serial.println("setup_wifi()");
  digitalWrite(output2, LOW);
  // Connect to Wi-Fi network with SSID and password
  //Serial.print("Connecting to ");
  //Serial.println(ssid);
  WiFi.begin(ssid, password);
  for (int i = 0; i < 30; i++)
  {
    if (WiFi.status() == WL_CONNECTED)
    {
      break;
    }
    digitalWrite(output2, HIGH);
    delay(250);
    digitalWrite(output2, LOW);
    delay(250);
    //Serial.print(".");
  }

  if (WiFi.status() == WL_CONNECTED)
  {
    digitalWrite(output2, HIGH);
    //Serial.println("");
    //Serial.print("Connected to ");
    //Serial.println(ssid);
    //Serial.print("IP address: ");
    //Serial.println(WiFi.localIP());

    //if (!MDNS.begin("lvlights")) {             // Start the mDNS responder for esp8266.local
    //  //Serial.println("Error setting up MDNS responder!");
    //}
    ////Serial.println("mDNS responder started");
    server.begin();
  }
}

// prepare a web page to be send to a client (web browser)
String prepareHtmlPage()
{
  /*String htmlPage =
      String("HTTP/1.1 200 OK\r\n") +
      "Content-Type: text/html\r\n" +
      "Connection: close\r\n" + // the connection will be closed after completion of the response
      "Refresh: 5\r\n" +        // refresh the page automatically every 5 sec
      "\r\n" +
      "<!DOCTYPE HTML>" +
      "<html>" +
      "Analog input:  " +
      "</html>" +
      "\r\n";*/
      // HTTP headers always start with a response code (e.g. HTTP/1.1 200 OK)
      // and a content-type so the client knows what's coming, then a blank line:
      String htmlPage1 =
      String("HTTP/1.1 200 OK\n")+
      String("Content-type:text/html\n")+
      String("Connection: close\n\n")+
      // Display the HTML web page
      String("<!DOCTYPE html><html>\n")+
      String("<head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">\n")+
      String("<link rel=\"icon\" href=\"data:,\">\n")+
      // CSS to style the on/off buttons
      // Feel free to change the background-color and font-size attributes to fit your preferences
      String("<style>html { font-family: Helvetica; display: inline-block; margin: 0px auto; text-align: center;}\n")+
      String(".button { background-color: #195B6A; border: none; color: white; padding: 16px 40px;\n")+
      String("text-decoration: none; font-size: 30px; margin: 2px; cursor: pointer;}\n")+
      String(".button2 {background-color: #77878A;}</style></head>\n")+
      // Web Page Heading
      String("<body><h1>Status socket controls</h1>\n")+
      // Display current state, and ON/OFF buttons for GPIO 2
      String("<p>Lights are " + output2State + "</p>\n");

      // If the output2State is off, it displays the ON button
      if (output2State == "off")
      {
        htmlPage1 += String("<p><a href=\"/lights/on\"><button class=\"button\">ON</button></a></p>\n");
      }
      else
      {
        htmlPage1 += String("<p><a href=\"/lights/off\"><button class=\"button button2\">OFF</button></a></p>\n");
      }
      htmlPage1 += String("</body></html>\n\n");
      // The HTTP response ends with another blank line
  return htmlPage1;
}

void handleClientRequest(WiFiClient client)
{
  //Serial.println("\n[Client connected]");

  if (client.connected())
  {
    bool clientLightOnFound = false;
    bool clientLightOffFound = false;
    
    digitalWrite(output2, LOW);
    for (int i = 0; i < 1000; i++) // Do not use infinite loop - too many edge cases that will lock system
    {
      ////Serial.print("Client read ");
      ////Serial.println(i);
      if (!client.connected())
      {
        break;
      }

      // read line by line what the client (web browser) is requesting
      if (client.available())
      {
        String line = client.readStringUntil('\r');
        //Serial.println(line);

        if (line.indexOf("GET /lights/on") >= 0)
        {
          //Serial.println("Lights on");
          output2State = "on";
          mySwitch.send("0110001101111110010011110");          
        }

        if (line.indexOf("GET /lights/off") >= 0)
        {
           //Serial.println("Lights off");
           output2State = "off";
           mySwitch.send("0110001101111110010001110");           
        }
        
        // wait for end of client's request, that is marked with an empty line
        if (line.length() == 1 && line[0] == '\n')
        {
          //Serial.println("\nPrepareHTMLPage()");
          client.println(prepareHtmlPage());
          break;
        }
      }
    }

    delay(1000); // give the web browser time to receive the data

    // close the connection:
    client.stop();
    digitalWrite(output2, HIGH);
    //Serial.println("[Client disconnected]");
  } // do not disconnect a non-connected client
}

void checkIfNewClientAvailable()
{
  WiFiClient client = server.available(); // Listen for incoming clients
  if (client)
  {
    // we have a new client sending some request
    handleClientRequest(client);
  }
}

void loop()
{

  if (!wifiIsConnected())
  {
    setup_wifi();
  }
  else
  {
    checkIfNewClientAvailable();
  }
}
