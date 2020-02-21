https://github.com/debsahu/TwitterWebAPI

Installed libraries as suggested, and butchered example code to make EspTwitterPoster.ino

This just posted 00:00:16 to twitter using DrMikeGibbens creds

That's a start.

Adding to git without cred (I hope)

# 2019_10_03 

Still having issues with 3.3V vs 5v supply to sensor. It acts erratically on 3.3V, which is to say on the esp8266, however I've not been able to try it on the esp with 5v.

I found a hack where you can backpower the PIR sensor from the jumper pin, pushing 3.3V in on the low side of the regulator.
http://techgurka.blogspot.com/2013/05/cheap-pyroelectric-infrared-pir-motion.html

I also need to be clear:

GPIO 0, pin 0, is the blue on-board LED 
GPIO 2 I am using as input, when using RX for serial.

It's still behaving erratically.
Need to try with a voltage divider.


When I put the 3.3V out from the PIR into RX pin, the esp light goes off, but it doesn't crash?
This is so infuriating.
The sketch is now setup to loop, gently pulsing the LED on GPIO2.
If the digital read is high, then it should pull the LED to on for 2 seconds.

I've tried using the TX and RX pins. Without a pulldown resistor, the pin is high and the pulsing never happens.
With a pulldown resistor, we see the pulse, so we have the right pin.

If I connect the pin to 3.3V then the LED should come on - but it doesn't, it does off.
The ESP hasn't powered off or crashed, because when you remove the 3.3V it resumes pulsing (rather than reconnect to the network etc...)

I don't know why the LED is going off. Is it working? But you can't have the LED on whilst taking input on TX? Seems unlikely.
I tried adding series resistors in case the current is too high.
A 500ohm resistor makes no difference.
A 1k resistor, the pin no longer registers 3.3V.
