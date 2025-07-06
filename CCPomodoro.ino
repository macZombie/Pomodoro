

#include "M5Cardputer.h"
#include <M5Unified.h>


int minutes;
int seconds;
int elapsed;
int limit;

bool paused;


int tDelay;
unsigned long tStart;
unsigned long tStop;
int tDelta;

auto cfg = M5.config();


void printTime(int minutes,int seconds){

    int myColour = minutes / 5;

    String outputString = "";

    if ( minutes < 10 ){

        outputString = outputString + " ";

    } 

    outputString = outputString + minutes;

    outputString = outputString + ":";

    if ( seconds < 10 ){

         outputString = outputString + "0";
    
    }

     outputString = outputString + seconds;


      switch(myColour){

      case 0:  M5Cardputer.Display.setTextColor(RED); break;
      case 1:  M5Cardputer.Display.setTextColor(YELLOW); break;
      case 2:  M5Cardputer.Display.setTextColor(BLUE); break;
      case 3:  M5Cardputer.Display.setTextColor(VIOLET); break;
      case 4:  M5Cardputer.Display.setTextColor(MAGENTA); break;

      //default: tft.setTextColor(TFT_WHITE); break;

    }

     //M5Cardputer.Display.clear();

     if ( ( minutes == 0 ) && ( seconds == 0 ) ){

        M5Cardputer.Display.setTextColor(WHITE);
        
     }

     M5Cardputer.Display.drawString(outputString,M5Cardputer.Display.width() / 2,M5Cardputer.Display.height() / 2);



}


void setup() {
   // Serial.begin(115200);
   // Serial.println("CCPomo");

    //auto cfg = M5.config();
    
    M5Cardputer.begin(cfg, true);
    M5Cardputer.Display.setRotation(1);
    M5Cardputer.Display.setTextColor(WHITE);
    M5Cardputer.Display.setTextDatum(middle_center);
    //M5Cardputer.Display.setTextFont(&fonts::FreeSerifBoldItalic18pt7b);
    M5Cardputer.Display.setTextSize(6);

    M5Cardputer.Display.drawString("CCPomo",M5Cardputer.Display.width() / 2,M5Cardputer.Display.height() / 2);

    delay(1000);


    minutes = 24;
    
    seconds = 59;

    M5Cardputer.Display.setTextSize(8);

    paused = false;

    tDelay = 1000;

}



void loop() {

    tStart = millis(); 
    
    M5Cardputer.update();
    
    M5Cardputer.Display.clear();
    
    printTime(minutes,seconds);


    if ( paused == false ){

        seconds--;

    



        if ( seconds < 0 ){

            minutes--;

            seconds = 59;

        }



        if (  ( minutes == 0 ) && ( seconds == 0 )  ){

            paused = true;

            //Serial.println("Done!");
 
            M5Cardputer.Display.clear();
              
            
            
            printTime(0,0);



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


            for ( int loopJ = 0; loopJ < 3; loopJ++){

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

            } // loopJ





        } // minutes and seconds are zero




    } // paused     
    
    
    
    if (M5Cardputer.Keyboard.isChange()) {
        
        if (M5Cardputer.Keyboard.isKeyPressed('p')) {
          
            //Serial.println("p");

            if ( paused == false ){

                paused = true;

            }else{

                paused = false;
            
            }

            delay(100);

        } 
    
        if (M5Cardputer.Keyboard.isKeyPressed(';')) {
          
            //Serial.println("up arrow");

            if ( minutes < 24 ){

                minutes++;

            }

            delay(100);

            paused = false;

        } 

        if (M5Cardputer.Keyboard.isKeyPressed('.')) {
          
            //Serial.println("down arrow");

            if ( minutes > 1 ){

                minutes--;

            }

            delay(100);

            paused = false;


        } 


        if (M5Cardputer.Keyboard.isKeyPressed('r')) {
          
            //Serial.println("r");

            minutes = 0;

            seconds = 5;

            delay(100);

            paused = false;

        } 
    
    
    }

    tStop = millis(); 

    tDelta =  tStop - tStart;

    //Serial.println(tDelta);

    int myDelay = tDelay - tDelta;

    //Serial.println(myDelay);


    delay(myDelay);

} // loop()
