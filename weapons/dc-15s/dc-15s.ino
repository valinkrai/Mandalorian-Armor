/*
 * Play wave audio files with Arduino.
 * This is a free software with NO WARRANTY.
 * https://simple-circuit.com/
 */
 
#include <SPI.h>     // include Arduino SPI library
#include <SD.h>      // include Arduino SD library
#include "TMRpcm.h"  // include TMRpcm library
 
#define trigger     2
#define rumble   3
#define muzzle_led   4 
#define buffSize 128 //must be an even number
//#define SD_FULLSPEED
#define HANDLE_TAGS
#define DISABLE_SPEAKER2
//#define USE_TIMER2
#define debug

TMRpcm audio;
 
File root;
int triggerCount;
int triggerState;
 
void setup(void) {
  triggerCount = 0;
  triggerState = 0;
  Serial.begin(9600);
  pinMode(trigger,   INPUT_PULLUP);
 
  Serial.print("Initializing SD card...");
  if (!SD.begin()) {
    Serial.println("failed!");
    while(true);  // stay here.
  }
  Serial.println("OK!");
 
  audio.speakerPin = 9;  // set speaker output to pin 9
 
  root = SD.open("/");      // open SD card main root
  printDirectory(root, 0);  // print all files names and sizes
 
  audio.setVolume(6);    //   0 to 7. Set volume level
  audio.quality(0);      //  Set 1 for 2x oversampling Set 0 for normal
       File fireSound =  SD.open("/silence.wav");  // open next file
       delay(100);
       audio.play( fireSound.name() );      // play the audio 
  pinMode(muzzle_led, OUTPUT);    // sets the digital pin 13 as output
  pinMode(rumble, OUTPUT);    // sets the digital pin 13 as output
  digitalWrite(muzzle_led, LOW); // sets the digital pin 13 on
  digitalWrite(rumble, HIGH);  // sets the digital pin 13 off
 
}
 
// main loop
void loop() {
  /*
  int Value = digitalRead(trigger);
  Serial.println(Value*10000);
  delay(10);
  */
  /*
  if ( !audio.isPlaying() ) {
    // no audio file is playing
    File entry =  SD.open("/fire.wav");  // open next file
    audio.play( entry.name() );      // play the audio file

  }*/
  if ( digitalRead(trigger) && triggerState) {
      while( !digitalRead(trigger) || audio.isPlaying()) {
        delay(10);
      }
      
      triggerState = 0;
  }
  if ( !digitalRead(trigger) && !triggerState) {
    if (triggerCount >= 8) {
       File fireSound =  SD.open("/empty.wav");  // open next file
       audio.play( fireSound.name() );      // play the audio file
       
       delay(441);
      
       audio.disable();
       triggerCount = 0;
       software_reboot();
      
    }
    // 'next' button is pressed
      triggerState = 1;
      // no audio file is playing
  
      Serial.print("Fire: ");
      Serial.println(++triggerCount);
      File fireSound =  SD.open("/fire.wav");  // open next file
      audio.play( fireSound.name() );      // play the audio file
      
      digitalWrite(muzzle_led, HIGH); // sets the digital pin 13 on
      digitalWrite(rumble, LOW); // sets the digital pin 13 on
      delay(125);
      digitalWrite(muzzle_led, LOW); // sets the digital pin 13 on
      
      delay(200);
      digitalWrite(rumble, HIGH);  // sets the digital pin 13 off
      
      

  }
  
}
 
// a small function for buttons debounce
bool debounce (int bt)
{
  byte count = 0;
  for(byte i = 0; i < 5; i++)
  {
    if ( !digitalRead(bt) )
      count++;
    delay(10);
  }
 
  if(count > 2)  return 1;
  else           return 0;
}
 
void printDirectory(File dir, int numTabs) {
  while (true) {
 
    File entry =  dir.openNextFile();
    if (! entry) {
      // no more files
      break;
    }
    for (uint8_t i = 0; i < numTabs; i++) {
      Serial.print('\t');
    }
    Serial.print(entry.name());
    if (entry.isDirectory()) {
      Serial.println("/");
      printDirectory(entry, numTabs + 1);
    } else {
      // files have sizes, directories do not
      Serial.print("\t\t");
      Serial.println(entry.size(), DEC);
    }
    entry.close();
  }
}
 void software_reboot()
{
asm volatile (" jmp 0");
}
// end of code.
