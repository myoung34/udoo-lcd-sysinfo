udoo-lcd-sysinfo
================

This is an example project for outputting system information from the i.mx6 processor of the UDOO to the sam3x via Serial.

## Parts Needed ##

 * [This TFT LCD](http://www.adafruit.com/products/376). It's worth noting they've made a newer revision, but it shouldn't be any different.
 * [A 10k Ohm resistor](http://www.radioshack.com/product/index.jsp?productId=2062347)
 * [A Jumper kit and board](http://www.radioshack.com/product/index.jsp?productId=18761926) or an [arduino shield](http://www.adafruit.com/products/51)
 * [A breadboard button](http://bit.ly/1eONbBk)

## Setup ##

 * Get these arduino libraries
    * [Adafuit_GFX library](https://github.com/adafruit/Adafruit-GFX-Library)
    * [Adafuit TFT LCD library](https://github.com/adafruit/TFTLCD-Library)
 * Wire up the button exactly the same as the [arduino tutorial](http://www.arduino.cc/en/Tutorial/Switch#.UxVG7PldUkA) to digital 2.
 * [Modify your LCD to use Digital 3 to control the backlight](http://learn.adafruit.com/2-8-tft-touch-shield/controlling-the-backlight).
 * Set up the ``ttymxc3`` device in linux for Serial on 9600 baud.

        sudo stty -F /dev/ttymxc3 cs8 9600 ignbrk -brkint -icrnl -imaxbel \
        -opost -onlcr -isig -icanon -iexten -echo -echoe -echok -echoctl -echoke noflsh -ixon -crtscts

    * Add that command to ``/etc/rc.local`` to make it permanent.

 * Add [this bash script](https://github.com/myoung34/udoo-lcd-sysinfo/blob/master/script/udoo.sh) to ``/usr/local/bin``.
    * Set it for startup by adding ``sh /usr/local/bin/udoo.sh | cat > /dev/ttymxc3`` to ``/etc/rc.local``.
    * Add a cron to update it every minute by adding this to ``/etc/crontab``

            * * * * * root sh /usr/local/bin/udoo.sh | cat > /dev/ttymxc3

 * Remove the ``J18`` jumper from the UDOO.
 * Set up arduino [to work with the UDOO](http://www.udoo.org/downloads/).
 * Load [this sketch](https://github.com/myoung34/udoo-lcd-sysinfo/blob/master/sketch/udoo.ino) to your Arduino.
 * Reboot the arduino via the ``RST`` switch, or by a full power reboot. 
 * Replace the ``J18`` jumper so that the chips can communicate.

## Files ##

 * ``sketch/udoo.ino`` This is the Arduino sketch. Remember to use Arduino 1.5.4 IDE for UDOO compatibility
 * ``script/udoo.sh`` This is the bash script which collects some system data to output to the UDOO. Pipe to cat to help buffering.
