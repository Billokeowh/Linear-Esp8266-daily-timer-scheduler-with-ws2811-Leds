#include <FastLED.h>
#define NUM_LEDS 29
#define DATA_PIN 2 // check the pin out of the board you're using, this can cause a lot of frustration!
#define CLOCK_PIN 13
//END OF CLOCK DEFINITIONS

#include <NTPClient.h>
#include <ESP8266WiFi.h>
#include <WiFiUdp.h>

const char *ssid     = "XXX"; // Your SSID
const char *password = "XXX";  //Your WiFi pw

// END OF NPT DEFINITIONS
int delayCounter = 0;
int timeLeft = 0;
int hoursInMS = 0;
int minsInMS = 0;
int secsInMS = 0;
int totalTimeMS = 0;



//Set-points
// Timetable of what to countdown towards
//To get the time you need you multiple the hour you want by 360000. e.g. 4pm = 16 x 360000 = 57600000. Use decimals for half, quarter hours etc...

int startTime = 32400000; 
int t1 = 34200000;
int t2 = 36000000;
int t3 = 37800000;
int breakTime = 39600000;
int t4 = 40500000;
int t5 = 42300000;
int t6 = 44400000;
int lunchTime = 46800000;
int t7 = 48600000;
int t8 = 50400000;
int homeTime = 5220000;  //Changed to 11PM for testing

CRGB leds[NUM_LEDS];

WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, "ie.pool.ntp.org", 0, 60000); // Chose what NTP server you want to use. Also choose your offset for daylight savings etc... It's 0 here. 

void setup() {

  FastLED.addLeds<NEOPIXEL, DATA_PIN>(leds, NUM_LEDS);  // Check what strips you're using with the FastLed Library. 
  FastLED.setBrightness(255); // 0-255
  Serial.begin(9600);

  WiFi.begin(ssid, password);


//Blink led 10 every 200 ms until connected. 
  while ( WiFi.status() != WL_CONNECTED ) {
    leds[10] = CRGB::Blue;
    FastLED.show();
    delay ( 100 );
    Serial.print ( "." );
    leds[10] = CRGB::Black;
    FastLED.show();
    delay ( 100 );
  }

  timeClient.begin();

}

void loop() {
  FastLED.setBrightness(155);

  totalTimeMS = getRemainingTime();

  //If Time is in the envelope of the School Day
  if ((totalTimeMS > startTime) && (totalTimeMS < homeTime)) {

    //to 9:30
    if ((totalTimeMS > startTime) && (totalTimeMS < t1)) {
      totalTimeMS = t1 - totalTimeMS;
      delayCounter = totalTimeMS / NUM_LEDS;
      Serial.println("-> t1 - 1.1");
    }
    //to 10:00
    if ((totalTimeMS > t1) && (totalTimeMS < t2)) {
      totalTimeMS = t2 - totalTimeMS;
      delayCounter = totalTimeMS / NUM_LEDS;
      Serial.println("-> t2 - 1.2");
    }
    //to 10:30
    if ((totalTimeMS > t2) && (totalTimeMS < t3)) {
      totalTimeMS = t3 - totalTimeMS;
      delayCounter = totalTimeMS / NUM_LEDS;
      Serial.println("-> t3 - 1.3");
    }
    //to 11:00
    if ((totalTimeMS > t3) && (totalTimeMS < breakTime)) {
      totalTimeMS = breakTime - totalTimeMS;
      delayCounter = totalTimeMS / NUM_LEDS;
      Serial.println("-> Breaktime - 1.4");
    }
    //to 11:15
    if ((totalTimeMS > breakTime) && (totalTimeMS < t4)) {
      totalTimeMS = t4 - totalTimeMS;
      delayCounter = totalTimeMS / NUM_LEDS;
      Serial.println("-> y4 - 2.1");
    }
    //to 11:45
    if ((totalTimeMS > t4) && (totalTimeMS < t5)) {
      totalTimeMS = t5 - totalTimeMS;
      delayCounter = totalTimeMS / NUM_LEDS;
      Serial.println("-> t5 - 2.2");
    }
    //to 12:20
    if ((totalTimeMS > t5) && (totalTimeMS < t5)) {
      totalTimeMS = t5 - totalTimeMS;
      delayCounter = totalTimeMS / NUM_LEDS;
      Serial.println("-> t6 - 2.3");
    }
    //to 13:00
    if ((totalTimeMS > t6) && (totalTimeMS < lunchTime)) {
      totalTimeMS = lunchTime - totalTimeMS;
      delayCounter = totalTimeMS / NUM_LEDS;
      Serial.println("-> Lunch - 2.5 ");
    }
    //to 13:30
    if ((totalTimeMS > lunchTime) && (totalTimeMS < t7)) {
      totalTimeMS = t7 - totalTimeMS;
      delayCounter = totalTimeMS / NUM_LEDS;
      Serial.println("-> t7 - 3.1");
    }
    //to 14:00
    if ((totalTimeMS > t7) && (totalTimeMS < t8)) {
      totalTimeMS = t8 - totalTimeMS;
      delayCounter = totalTimeMS / NUM_LEDS;
      Serial.println("-> t8 - 3.2");
    }
    //to 14:30
    if ((totalTimeMS > t8) && (totalTimeMS < homeTime)) {
      totalTimeMS = homeTime - totalTimeMS;
      delayCounter = totalTimeMS / NUM_LEDS;
      Serial.println("-> Hometime - 3.3");
    }


  
 
  

  resetter();
  Serial.println("Time per each led");
  Serial.println(delayCounter);
  countDown(delayCounter);

  }else{
    // If we're not in the window of the school day then blink, delay 60 seconds and check again. 
    for (int u = 0; u < NUM_LEDS; u++) {
    leds[u] = CRGB::Black;
    FastLED.show();
    delay(10);
  }
   delay(60000);
}

}

// reset the strip to green
void resetter() {
  Serial.println("Resetting");
  for (int u = 0; u < NUM_LEDS; u++) {
    leds[u] = CRGB::Green;
    FastLED.show();
    delay(10);
  }
}


// Pass the delaycounter value from above and calculate a delay time per led. Then run through each. 
void countDown(int delayCounter) {
  FastLED.setBrightness(255);
  Serial.println("Counting Down");
  for (int d = NUM_LEDS-1; d > -1; d--) {
    Serial.println(d);
    Serial.println(delayCounter / 256);


    // blink the top led to show program is working. 
    for (int f = 0; f < 128; f++) {

      leds[d] = CRGB::Red;
      FastLED.show();
      delay(delayCounter / 256);
      leds[d] = CRGB::Black;
      FastLED.show();
      delay(delayCounter / 256);




      //Standard with No Blink
      //leds[i] = CRGB::Black;
      //FastLED.show();
      //delay(delayCounter);
    }
  }
}


//Query the NTP server and calculate current time in MS. 
int getRemainingTime() {
  timeClient.update();
  Serial.println(timeClient.getFormattedTime());
  //Getting current time in MS
  hoursInMS = (timeClient.getHours() * 3600000);
  minsInMS = (timeClient.getMinutes() * 60000);
  secsInMS = (timeClient.getSeconds() * 1000);

  totalTimeMS = (hoursInMS + minsInMS + secsInMS);
  Serial.println("Total time in MS");
  Serial.println(totalTimeMS);

  return (totalTimeMS);

}
