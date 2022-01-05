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

int startTime = 28800000;
int homeTime = 59400000;  //Changed to 11PM for testing

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
  FastLED.setBrightness(255);

  totalTimeMS = getRemainingTime();
  Serial.println("Time back from GRT");
  Serial.println(totalTimeMS);


  //If Time is in the envelope of the School Day
  if ((totalTimeMS > startTime) && (totalTimeMS < homeTime)) {
    Serial.println("In the main");
    totalTimeMS = homeTime - totalTimeMS;
    delayCounter = totalTimeMS / NUM_LEDS;
    Serial.println("Counting down to home time!");

    resetter();
    Serial.println("Time per each led");
    Serial.println(delayCounter);
    countDown(delayCounter);

  } else {
    Serial.println("Not in the main");
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
  for (int d = NUM_LEDS - 1; d > -1; d--) {
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
