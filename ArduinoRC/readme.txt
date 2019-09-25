#Arduino switch for radio remote sockets

Starting with my fav. nano - then porting to esp8266

Starting Arduino sketch in \ArduinoRCSketch


Using

File > Examples > RC_Switch > ReceiveDemo_Advanced

Only compiles in examples folder...

5
Off:
17:08:41.869 -> Decimal: 6520392 (24Bit) Binary: 011000110111111001001000 Tri-State: not applicable PulseLength: 310 microseconds Protocol: 1
17:08:41.977 -> Raw data: 9628,300,916,908,308,904,308,304,912,304,912,304,916,908,304,912,308,300,912,908,312,904,312,904,308,912,304,912,304,908,308,300,916,300,920,904,308,300,916,296,920,904,312,304,912,28,40,48,16,
17:08:42.193 -> 

1 On:
17:06:11.589 -> Decimal: 6520320 (24Bit) Binary: 011000110111111000000000 Tri-State: not applicable PulseLength: 310 microseconds Protocol: 1
17:06:11.692 -> Raw data: 9632,296,920,904,312,904,308,304,912,304,912,304,916,912,300,912,308,296,916,908,312,904,312,904,312,908,304,908,308,908,312,296,920,296,920,904,312,296,920,296,920,904,312,908,308,912,304,908,364,
17:06:11.946 -> 

1 Off:
17:06:58.283 -> Decimal: 6520391 (24Bit) Binary: 011000110111111001000111 Tri-State: not applicable PulseLength: 310 microseconds Protocol: 1
17:06:58.356 -> Raw data: 9632,300,920,904,312,908,308,300,916,300,920,296,916,908,308,908,308,296,924,900,312,904,312,908,308,908,308,908,312,904,308,300,916,300,920,904,308,304,916,300,916,300,916,916,300,908,308,908,352,
17:06:58.605 -> 

2 On:
17:07:33.376 -> Decimal: 6488064 (24Bit) Binary: 011000110000000000000000 Tri-State: not applicable PulseLength: 310 microseconds Protocol: 1
17:07:33.481 -> Raw data: 9628,300,920,904,308,908,304,308,908,308,908,308,912,912,300,912,308,300,912,912,308,904,312,904,312,908,304,908,308,912,304,300,916,300,920,904,308,20,244,20,432,32,72,20,52,24,68,84,28,
17:07:33.702 -> 

2:Off:
17:07:43.304 -> Decimal: 6520387 (24Bit) Binary: 011000110111111001000011 Tri-State: not applicable PulseLength: 310 microseconds Protocol: 1
17:07:43.414 -> Raw data: 9628,300,920,904,312,908,308,300,916,300,916,300,912,912,304,912,308,300,916,908,308,904,312,912,304,912,304,908,312,904,308,300,916,300,920,904,308,304,912,304,912,304,912,304,916,44,100,48,72,
17:07:43.631 -> 

3 On:
17:07:53.588 -> Decimal: 6520397 (24Bit) Binary: 011000110111111001001101 Tri-State: not applicable PulseLength: 310 microseconds Protocol: 1
17:07:53.694 -> Raw data: 9628,300,920,912,300,912,308,300,916,296,920,300,912,908,308,908,308,300,920,904,308,904,312,908,308,908,308,908,312,900,312,296,920,296,924,900,316,296,916,300,916,908,308,908,312,296,916,908,352,
17:07:53.909 -> 

3:Off:
17:08:05.833 -> Decimal: 6520389 (24Bit) Binary: 011000110111111001000101 Tri-State: not applicable PulseLength: 310 microseconds Protocol: 1
17:08:05.946 -> Raw data: 9628,304,916,904,312,904,308,304,912,304,912,304,916,908,304,912,308,300,912,912,308,908,308,908,308,912,304,908,308,908,308,300,916,300,920,904,308,300,916,300,916,300,920,904,308,48,268,28,144,
17:08:06.165 -> 

4 On:
17:08:14.403 -> Decimal: 6520398 (24Bit) Binary: 011000110111111001001110 Tri-State: not applicable PulseLength: 310 microseconds Protocol: 1
17:08:14.510 -> Raw data: 9628,296,920,908,308,908,308,300,916,300,916,300,916,908,304,912,308,300,916,908,308,904,312,908,308,908,304,912,312,908,304,296,920,296,920,904,308,304,48,28,916,908,64,20,48,24,96,20,92,
17:08:14.765 -> 

4:Off:
17:08:24.760 -> Decimal: 6520390 (24Bit) Binary: 011000110111111001000110 Tri-State: not applicable PulseLength: 310 microseconds Protocol: 1
17:08:24.834 -> Raw data: 9628,300,916,908,308,908,304,308,908,308,908,308,912,912,304,908,308,300,916,908,312,904,312,904,308,912,304,908,308,912,308,296,920,296,920,904,308,16,524,32,1008,20,36,96,24,44,40,288,80,
17:08:25.082 -> 


https://www.instructables.com/id/Using-an-ESP8266-to-Control-Mains-Sockets-Using-43/

# 2019_09_15

Notes on Pi socket controllers.

pi@raspbmc:~$ hostname
raspbmc
pi@raspbmc:~$ pwd
/home/pi
pi@raspbmc:~$ ls
lightsoff.sh  lightson.sh  log.txt  run.sh
pi@raspbmc:~$ cat lightson.sh
#!/bin/sh
# My first script
#echo "Hello World!" >> /home/pi/log.txt

sudo /usr/sbin/pihat --brand=5 --repeats=50 --id=407524 --channel=7 --state=1
pi@raspbmc:~$ cat lightsoff.sh
#!/bin/sh
# My first script
#echo "Hello World!" >> /home/pi/log.txt
# button 1  is channel 7
# button 2 is channel 3
sudo /usr/sbin/pihat --brand=5 --repeats=50 --id=407524 --channel=7 --state=0
pi@raspbmc:~$


https://github.com/s7mx1/pihat I know the code in this project generates the correct signal for my remotes.
The code in the RC-switch generates something close to the correct signal, but not close enough?

I've compiled the piHat code to just print the values:

channel 7 state 1 0110001101111110010011110
channel 7 state 0 0110001101111110010001110


Created working ESP8266 sketch using 3.3V power for transmitter and pin 3 (RX pin)
Cannot program when connected, but once programmed can connected to RX pin (not supporting serial output any more though)

Lets write a web server...

Boom! Working!

I've been working on a few art projects recently, which were too touch-and-go for me to make videos of.

This is just a short video, because this was just a two evening project - and it's electronically functional, but not finished - because I need to make a case.

This is based heavily on (in fact using spare parts from) the esp8266 silent alerter I showed in a previous video. The one with the brass poppy sculpture as a capacitive switch.

I have a raspberry pi model 1, setup as a media server - which is rarely used. Its secondary function - which has become its primary function is a remote control for the living room lamps.
I have some 'status' brand 433mhz mains switches, synchronised to turn a number of lamps on or off.
There is a physical remote control, or you can access a URL on the pi, and it broadcasts the relevant control signal from a 433mhz tx module.


I've always been reluctant to upgrade the pi media server, because it means messing with the light controls which are used daily.

We have the same LM-triple-1 7 power supply, an esp8266 and a 433mhz module.
I'm using the RC-switch arduino library (which can transmit, but cannot decode this brand of socket)

Hosting a website the send the 'switch on' or 'switch off' radio signal when on is URL accessed.
This needs a case, but will work as an independent device allowing me to upgrade the media server.

Today I learned that if you are willing to go without serial output, you can reuse the RX pin as GPIO on an ESP8266
This is good, because pins 0 and 2 (which I had been using) have pull-up restrictions - which I have previously worked around.

I could have avoided parts on previous projects, if I have known this.

# 2019_09_25 

Adapting EspRCSketch.ini code to auto-reconnect to wifi not connected.

When the power goes off here, which happens a lot for a first world country, these esp devices I'm building come back up faster the my router.
So, they fail to connect to the wifi, because it's not there to connect too.

So, I'm changing the running loop on this one to check for a wifi connection - and if one is not found then it attempts to connect.
I'm not sure about the final line which is  server.begin(); - it feels like this won't do what I expect.

I'll wait for the next brown out and check how this copes.