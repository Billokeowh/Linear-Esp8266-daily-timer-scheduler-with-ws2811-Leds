# Linear-Esp8266-daily-timer-scheduler-with-ws2811-Leds
This is a linear countdown timer which displays remaining time to chosen set points in a visual format. 

This is a very simple visual countdown timer for use with the ESP 8266 and some WS2811 Leds. Once you decide what times that you would like to count down to, the esp8266 gets the current time from an NTP server and counts down using the Leds. All Leds will be used regardless of time until next setpoint as the remaining time is divided proportionally across the number of Leds declared at the start of the program. 

This linear scheduler is designed to be a simple and easy to use tool to give a visual representation of time until various points throughout the day. I use this tool daily in the classroom to allow children of all ages to understand the time they have until the next lesson.  The amount of time is then divided out evenly over the given number of Leds. This means that whether you are counting down from 1 hour or 1 minute, the entire strip of Leds will be used. If you want to change the set points you can easily do so in the code section marked - Set-points. To calculate your setpoints in the correct format just multiple the hour you want by 360000. e.g. 4pm = 16 x 360000 = 57600000. Use decimals for half, quarter hours etc.... Although I am using this in a education setting, it would be just as effective anywhere where understanding the passage of time/parsing information from analogue or digal clocks is difficult - retirement home, Special education setting etc...

I have yet to create a nice looking enclosure but will add photos as soon as I have done so. 




