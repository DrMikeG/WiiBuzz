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

# 2019_06_16 

The 'server' can switch an LED that it is directly powering, but I need to switch the power or ground to the LED matrix.

The LED matrix can pull 60ma (surprised it is this low) - so I am going to power this separately.

Need either and NPN or PNP transitors, depending on if I am switching the ground of the power of the circuit.
What is best for the ESP?

https://electronics.stackexchange.com/questions/211579/npn-transistor-is-always-on?rq=1
NPN transistor switching the ground out of the maxtrix...
The downside of this is that it means the matrix is always on...


I should be able to use a PNP transistor to switch the power rather than the ground...
https://www.electronics-tutorials.ws/transistor/tran_4.html

Need to be careful, as will be sinking some of the current when turned we pull the PNP base pin to ground.
Voltage divider (43Ko v 620o) ensures current flows through LED.
Resistor is between LED - and ground...


PN2222 - Type - NPN
Collector-Emitter Voltage: 30 V
Collector-Base Voltage: 60 V
Emitter-Base Voltage: 5 V
Collector Current: 0.6 A
Collector Dissipation - 0.625 W
DC Current Gain (hfe) - 100 to 300
Transition Frequency - 300 MHz
Operating and Storage Junction Temperature Range -55 to +150 °C
Package - TO-92

https://www.el-component.com/bipolar-transistors/pn2222

In stock I seem to have

TR3906 https://solarbotics.com/product/tr3906/ https://cdn.solarbotics.com/products/datasheets/2n3906.pdf (100ma)
TR3904 https://cdn.solarbotics.com/products/datasheets/2n3904.pdf (100ma)
TR2907 https://cdn.solarbotics.com/products/datasheets/pn2907a.pdf (500ma)


With flat side up, left to right is EBC


There are two ways to bypass the resistor. One way is to lower the input voltage. If you are able to run your complete circuit with the same voltage as forward voltage of the LED, perfect. No resistor needed.

There is a 3V Vf = LED forward voltage drop in Volts (found in the LED datasheet) for the matrix.

I suspect you are trying to drive the PNP base with a 3.3V logic signal while controlling 5V to the buzzer. That just isn't going to work. To turn the transistor off (non-conducting) you need to raise the voltage on the base to be close to the emitter voltage, or about 5V. You can't do that with a 3.3V logic signal. You make a PNP transistor conduct by lowering the base voltage about 0.7V below the emitter voltage, not by setting the base voltage to 0.7V above ground.

You might be able to add a pullup resistor from the base itself to 5V to turn the transistor off when the logic output is 3.3V. Select resistor values so that when the 3.3V signal is low the voltage at the base is less than 4.3V. You would also have to select resistor values that limit the current that will flow back into the 3.3V logic output when that output signal is high. This is all just speculation, you haven't provided a datasheet for the device that is driving the base.

https://forum.arduino.cc/index.php?topic=602676.0

https://learn.sparkfun.com/tutorials/transistors/all

So, I have 3.3V pushing into the Collector of the PNP transistor.
If base is connected directly to ground, all that current would rush through.
The voltage drop across that path to base is 0.7V
So (3.3 - 0.7 = 2.4V) V=IR
I want to put just 30ma (0.03A) because according to the data sheet that should give 100ma Ic
The means the transistor has a multiplier of x2.

I'm running 45ma through base, using a resistor 50 ohm resistor

Using a 100ohm resistor, base current is 60ma, Ie is 20ma
Using a 50o, Ie is 50ma

2.4 = 50 * 0.05 (50ma)
At 50ma, DC current gain is 60
2.4 = 100 * 0.025 (25ma)

Current applification should be between x60 and x100.

# 2019_06_20 

I now have 10 x PN2907A PNP tranistors.
https://cdn-shop.adafruit.com/product-files/3598/PN2907A-D.PDF

(IC = -0.1 mAdc, VCE = -10 Vdc) = 75
(IC = -1.0 mAdc, VCE = -10 Vdc) = 100

2.4 = 100 * 0.05 (100ma)


I have 44ma flowing through the base
I have 46ma flowing through the emitter.

Should have 73ma.

22 through base = 50 through emitter
1000ohm 10 throuh em
300ohm = 25
60 thro 40base em 50 ohm


# 2019_06_23 
Having had no more luck with drawing more than 60ma though LED, switched back to NPN transistor.
2n2222

led drawing 60ma 2.96v 
V = I R
2.96 = 0.06 * R = 49ohm

Bypassing transistor, led draws 82


Base @ 40ma 50o - 74.6ma
Base @ ? 54o = 74
Base 40 ? 62o = 73
Base @ ? 75o = 72


Base @ 23m 100o - 67ma
Base @ ?m 112o - 63ma
Base @ 17 150o - 52ma
Base @ ? 330o - 64ma

32 and 78ma
67.8o made from 5 x 330o

I think I cooked my first esp