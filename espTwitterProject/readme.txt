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