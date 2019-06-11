# WiiBuzz

https://crazysqueak.wordpress.com/2015/12/17/hack-wimote-raspberry-pi/

https://pimylifeup.com/raspberry-pi-wiimote-controllers/

https://www.instructables.com/id/Wiimote-Controller-Configuration-for-Raspberry-Pi-/

https://www.raspberrypi.org/forums/viewtopic.php?t=32039

https://youtu.be/9QZkCQSHnko

ESP8266

https://youtu.be/bl1T4iG5QKY

https://youtu.be/zKeLOp91mmU


Notes on torch I've pulled apart.

Single LED draws 30ma @ 3.5V
matrix of 3x6 draws 60ma @ 3.5V
Three parallel tracks of 0.5V LEDs?


Three pads at the bottom of the matrix

GND MATRIX VCC SINGLE VCC


I'm now trying to setup a soft access point following example here:
https://arduino-esp8266.readthedocs.io/en/latest/esp8266wifi/soft-access-point-examples.html

Might be best if my IOT network was independent of our home wifi?

This actually seems to work, which is pretty amazing!

Plan.

Button indoors which connects to wifi.
Server outdoor which connects to wifi

Push button is detected by server. Light flashes.

Broken torch provides light.

Torch runs at 3.5V.

12 LEDs to flash.
Constant draw was 60ma at 3.5V
Could I half this with PWM?

Planning to use ESP8266 ESP01's as transmitter and reciever.

Should test reception in mancave as first test.

Power? How do you power one?
I have a power supply, 3.5V and plenty of 5V?
https://www.youtube.com/watch?v=j21CMZ6Lrfc
Sucks a lot of power.

20 - 250ma!



    x   x   x   x
    
    x   x   x   x


Light to show connection - Can I use onboard LED?


I've had a lot of luck with my programming tonight.
I've had three examples working:

1) Connect to home wifi (FirstConnect.ino)
2) Act as a SoftAP and allow phone to connect to isolated IOT wifi (SoftAP)
3) Serve a webpage toggling GPIO pin with LED on - (WebPage.ino)

I think I want a combination of these - but I need to know more about the SoftAP

I want a transistor to power the LEDs.

The programming board is providing a really handy power supply. Perhaps I should got another?


Read and digest these pages: https://tttapa.github.io/ESP8266/Chap02%20-%20Hardware.html

Before you begin ...
There's a few things you have to look out for when using an ESP8266: The most important thing is that it runs at 3.3V, so if you connect it to a 5V power supply, you'll kill it. Unlike some 3.3V Arduino or Teensy boards, the ESP8266's I/O pins are not 5V tolerant, so if you use a 5V USB-to-Serial converter, or 5V sensors etc. you'll blow it up.
A second thing to keep in mind is that the ESP8266 can only source or sink 12mA per output pin, compared to 20-40mA for most Arduinos.

mDNS - lets have DNS on our IOT

I have ordered 10x LT1117 5V to 3.3V regulators.
Capable up to 950ma
These need pairing with two 10uF capacitors.

Next I need a transistor I can use to control 60ma @ 3V...

# 2019_06_11 

Trying new working log by data in README.md

I have one ESP8266 setup as a access point (SoftAP.ino)
I took this outside to the workshop and the range / signal strength seems great.

I thought I had combined webserver / Access point code, but no evidence I did this yet.

Going to do some reading about sleep modes before I decide how to switch my ESP8266.
https://www.losant.com/blog/making-the-esp8266-low-powered-with-deep-sleep
I could possibly battery power the switch if I did this?


WebPageAP combines webserver and access point with mDNS (possibly)
Android doesn't support mDNS at all.

Now I'm writing the switch client, and programming a second board.
https://techtutorialsx.com/2016/07/17/esp8266-http-get-requests/

SwitchClient.ino connects to IOT wireless and uses the url
"http://192.168.0.45/0/on" to switch the light on on the server
doesn't seem to support mDNS lookup?

Still waiting for power.
Going to use USB to get 5V. For server, this needs splitting into two 3.3V supplies.
Build in LED is on Pin 2
Not sure about design of switch yet...