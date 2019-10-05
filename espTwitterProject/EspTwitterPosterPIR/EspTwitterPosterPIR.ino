#include <ESP8266WiFi.h>
#include <WiFiClientSecure.h>
#include <NTPClient.h>
#include <WiFiUdp.h>
#include <TimeLib.h>
#include <TwitterWebAPI.h>

const char* ssid = "VM4826469";           // WiFi SSID
const char* password = "z8gGpcvqjhpk";   // WiFi Password

static char const consumer_key[]    = "";
static char const consumer_sec[]    = "";
static char const accesstoken[]     = "-REI0k7pimbxDNA1kR6kMkVAOrKwRq8f";
static char const accesstoken_sec[] = "";

//The TX pin can be accessed from the sketch as GPIO1 and RX is GPIO3

int ledPin = 2;                // choose the pin for the LED - pin 3, GPIO 3?
int inputPin = 3;               // choose the input pin (for PIR sensor) - RX
int pirState = LOW;             // we start, assuming no motion detected
int val = 0;                    // variable for reading the pin status
unsigned long timeLastTriggered = 0;
unsigned long minTriggerInterval = 10* 1000; // 10 seconds 

WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, "europe.pool.ntp.org", 0, 60000);  // NTP server pool, offset (in seconds), update interval (in milliseconds)
TwitterClient tcr(timeClient, consumer_key, consumer_sec, accesstoken, accesstoken_sec);

bool usingSerial = false;

long dutyCycle;

void Println(String s)
{
  if (usingSerial)
  {
    Serial.println(s);
  }
}
void Println(int i)
{
  if (usingSerial)
  {
    Serial.println(i);
  }
}

unsigned long loopCount = 0;
unsigned long loopMax = 5000;

void setup(void){

  if (usingSerial)
  {
    //Begin Serial
    Serial.begin(115200);
    inputPin = 0; // Use GPIO 0 (RX 3 used for serial)
  }
  // WiFi Connection
  WiFi.begin(ssid, password);

  
  Println("\nConnecting to ");
  Println(ssid);
  // Wait for connection
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Println(".");
  }
  Println("Connected. yay!");
  Println("IP address: ");
  Println(WiFi.localIP().toString());
  delay(100);
  // Connect to NTP and force-update time
  tcr.startNTP();
  Println("NTP Synced");
  delay(100);
  // Setup internal LED
  pinMode(ledPin, OUTPUT);
  //if (twi_update_interval < 5) api_mtbs = 5000; // Cant update faster than 5s.
  digitalWrite(ledPin, LOW);
  
  
  timeClient.update();
  delay(5000);
  
  Println(timeClient.getFormattedTime());
  
  std::string twitter_post_msg =timeClient.getFormattedTime().c_str();
  
  //tcr.tweet(twitter_post_msg);
  //digitalWrite(ledPin, HIGH);

  //pinMode(ledPin, OUTPUT);      // declare LED as output
  pinMode(inputPin, INPUT);     // declare sensor as input
  timeLastTriggered = 0;

  digitalWrite(ledPin, LOW); // turn LED OFF

  dutyCycle = 2; // Start at 2 going up...
}

/*void extractJSON(String tmsg) {
  const char* msg2 = const_cast <char*> (tmsg.c_str());
  DynamicJsonBuffer jsonBuffer;
  JsonObject& response = jsonBuffer.parseObject(msg2);
  
  if (!response.success()) {
    Serial.println("Failed to parse JSON!");
    Serial.println(msg2);
//    jsonBuffer.clear();
    return;
  }
  
  if (response.containsKey("statuses")) {
    String usert = response["statuses"][0]["user"]["screen_name"];
    String text = response["statuses"][0]["text"];
    if (text != "") {
      text = "@" + usert + " says " + text;
      search_msg = std::string(text.c_str(), text.length());
    }
  } else if(response.containsKey("errors")) {
    String err = response["errors"][0];
    search_msg = std::string(err.c_str(), err.length());
  } else {
    Serial.println("No useful data");
  }
  
  jsonBuffer.clear();
  delete [] msg2;
}
*/

void fadeDutyCycle()
{
  analogWrite(ledPin, dutyCycle);
  delay(1);
  // dutyCycle starts at 2
  // As we go around this loop, we want dutyCycle to decrease by 2 if odd
  // and increase by 2 if even
  // if dutyCycle > 1022 then duty cycle = 1021 (start odds going down)
  // if dutyCycle < 3 then duty cycle = 2 (start evens going up)
  if (dutyCycle > 1022)
    dutyCycle = 1021;
  if (dutyCycle < 3)
    dutyCycle = 2;
    
  if (dutyCycle % 2 == 0)
  {
    dutyCycl++;
  }
  else
  {
    dutyCycl--;
  }
}

void loop(void){

  //Loop Fade
  fadeDutyCycle();

  if (false)
  {
    // Fade
    // increase the LED brightness
    for(int dutyCycle = 0; (val == LOW) && dutyCycle < 1023; dutyCycle++){   
      // changing the LED brightness with PWM
      val = digitalRead(inputPin);  // read input value
      analogWrite(ledPin, dutyCycle);
      delay(1);
    }
  }

  // decrease the LED brightness
  for(int dutyCycle = 1023; (val == LOW) && dutyCycle > 0; dutyCycle--){
    // changing the LED brightness with PWM
    val = digitalRead(inputPin);  // read input value
    analogWrite(ledPin, dutyCycle);
    delay(1);
  }
  
  if (val == HIGH)
  {
    digitalWrite(ledPin, HIGH); // turn LED ON
    delay(5000);
  }
  
  if (false)
  {
    //Flash
    for (int i = 0; i < 5; i++)
      {
      digitalWrite(ledPin, HIGH);   // turn the LED on (HIGH is the voltage level)
      delay(200);                       // wait for a second
       digitalWrite(ledPin, LOW);    // turn the LED off by making the voltage LOW
       delay(100);                       // wait for a second
    }
  }

  if (false)
  {
    for (int j = 0; j < 10; j++)
    {
    val = digitalRead(inputPin);  // read input value
  
    //digitalWrite(ledPin, LOW); // turn LED OFF
    
    if (val == HIGH) {            // check if the input is HIGH
      digitalWrite(ledPin, HIGH); // turn LED ON
      delay(5000);
    /*
      //for (int i = 0; i < 5; i++)
      //{
      //  digitalWrite(ledPin, LOW);  // turn LED ON
      //  delay(500);
      //} 
      if (pirState == LOW) {
      
        Println("Motion detected!");
        unsigned long timeSinceLastTriggered = millis() - timeLastTriggered; // Time in ms since last triggered (or current time if not previously triggered
        // We only want to print on the output change, not state
        Println("Time since last triggered ");
        Println((timeSinceLastTriggered/1000));
        if ( timeSinceLastTriggered > minTriggerInterval )
        {
          Println("Timer has expired, take action!");
          digitalWrite(ledPin, HIGH); // turn LED ON
          timeLastTriggered = millis();
          pirState = HIGH;
        }
        else
        {
          Println("Swallowed");
          delay(500);
        }
      }
      */
    } else {
      digitalWrite(ledPin, HIGH); // turn LED OFF
      /*
      if (pirState == HIGH){
        // we have just turned of
        Println("Motion ended!");
        digitalWrite(ledPin, LOW); // turn LED ON
        // We only want to print on the output change, not state
        pirState = LOW;
      }*/
    }
    }
  }
}
