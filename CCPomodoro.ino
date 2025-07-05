#include <M5Unified.h>
#include <M5GFX.h>


M5GFX tft;

unsigned long total = 0;

unsigned long tn = 0;

unsigned long start;

unsigned long finish;

unsigned long elapsed;

int minutes;

int seconds;



String outputString;


void setup() {
  Serial.begin(115200);
  //Serial.println(""); Serial.println("");
 // Serial.println("CCPomodoro"); 
 
  tft.init();

  tft.startWrite();


  start = 0;
  
  finish = 25 * 60 ;
 
  elapsed = 0;

  minutes = 24;
  
  seconds = 60;

  outputString = "";

  int del = 1000;
  
  int thisDel = 0;
  



    while ( elapsed < finish){

       unsigned long tStart = millis();

        seconds--;

        if ( seconds < 0 ){

            minutes--;

            seconds = 59;

        }

        elapsed++;

        delay(1000);

      

        outputString = "";

        if ( minutes < 10 ){

          outputString = outputString + " ";

        }

        outputString = outputString + String(minutes);

        outputString = outputString + ":";

        if ( seconds < 10 ){

          outputString = outputString + "0";

        }

        outputString = outputString + String(seconds);

        //Serial.println(outputString);

        printMe(outputString,minutes);
  
        unsigned tStop = millis();

        unsigned tDuration = tStop - tStart;

        //Serial.println(tDuration);

        thisDel = del - tDuration;

        //Serial.println(thisDel);

        //delay(thisDel);

        


    }

    Serial.println("Done");

    auto cfg = M5.config();

  M5.begin(cfg);

  M5.Speaker.begin();


  /// The setVolume function can be set the master volume in the range of 0-255. (default : 64)
  M5.Speaker.setVolume(64);

  /// The setAllChannelVolume function can be set the all virtual channel volume in the range of 0-255. (default : 255)
  M5.Speaker.setAllChannelVolume(255);

  /// The setChannelVolume function can be set the specified virtual channel volume in the range of 0-255. (default : 255)
  M5.Speaker.setChannelVolume(0, 255);


  /// tone data (8bit unsigned wav)
  const uint8_t wavdata[64] = { 132,138,143,154,151,139,138,140,144,147,147,147,151,159,184,194,203,222,228,227,210,202,197,181,172,169,177,178,172,151,141,131,107,96,87,77,73,66,42,28,17,10,15,25,55,68,76,82,80,74,61,66,79,107,109,103,81,73,86,94,99,112,121,129 };

  const float note[8] = { 261.63 ,293.66, 329.63, 349.23, 392.00, 440.00, 493.88 , 523.25 };




    for ( int loopy = 7; loopy >= 0 ; loopy--){

      float freq = note[loopy];

      int dur = 200;

      M5.Speaker.tone(freq, dur, 1, true, wavdata, sizeof(wavdata));
      M5.delay(100);
     
      M5.Speaker.tone(freq * 2, dur, 2, true, wavdata, sizeof(wavdata));
      M5.delay(100);
     
      M5.Speaker.tone(freq * 4, dur, 3, true, wavdata, sizeof(wavdata));
      M5.delay(100);

      while (M5.Speaker.isPlaying()) { M5.delay(1); } // Wait for the output to finish.

    } // loopy



}




void loop(void){

}

 






void printMe(String myString , int minutes){

    int myColour = minutes / 5;

    tft.fillScreen(TFT_BLACK);
    
    tft.setCursor(15,40); // x , y 
    
    //tft.setTextColor(TFT_GREEN,TFT_BLACK);

    switch(myColour){

      case 0: tft.setTextColor(TFT_RED); break;
      case 1: tft.setTextColor(TFT_YELLOW); break;
      case 2: tft.setTextColor(TFT_BLUE); break;
      case 3: tft.setTextColor(TFT_VIOLET); break;
      case 4: tft.setTextColor(TFT_MAGENTA); break;

      //default: tft.setTextColor(TFT_WHITE); break;

    }

    //tft.setTextColor(TFT_VIOLET);
    
    tft.setTextSize(7);
    
    tft.println(myString);
    
    tft.println();

}


