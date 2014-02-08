#include <EEPROM.h>
#include <SimpleSDAudio.h>
#include <SPI.h>
#define SD_ChipSelectPin 10

#define CHAPTER_C  0
#define SHOULD_RESET 1
#define LAST_TRACK 136
#define SPEAKER_PIN 9
#define VOICES 4

unsigned int counter;
long voice;

void play_track()
{
  char buf[15];
  
  sprintf(buf, "%i-%i.wav", counter, voice);
  Serial.println("Playing: " + String(buf)); 
  if(!SdPlay.setFile(buf)) {
    Serial.println(F(" not found on card! Error code: "));
    Serial.println(SdPlay.getLastError());
  } else
    SdPlay.play();
}

void setup()
{
  Serial.begin(115200);
  Serial.println("Hello!");
  SdPlay.setSDCSPin(SD_ChipSelectPin);
  
  counter = EEPROM.read(CHAPTER_C);
  if (counter == 0xff) {
    EEPROM.write(CHAPTER_C, 0);
    counter = 1;
  }
  
  if(EEPROM.read(SHOULD_RESET)) {
    counter = 1;
    Serial.println("Reseting counter");
  } else {
    EEPROM.write(SHOULD_RESET, 1);
  }
  
  randomSeed(analogRead(2));
  
  voice = random(1, VOICES);

  if (!SdPlay.init(SSDA_MODE_FULLRATE | SSDA_MODE_MONO | SSDA_MODE_AUTOWORKER)) {
    Serial.print(F("Error code: "));
    Serial.println(SdPlay.getLastError());
    while(1);
  } else {
   Serial.println(F("Wiring is correct and a card is present.")); 
  }
  
  play_track();
}


void loop()
{  
  if(SdPlay.isStopped()) {
    Serial.println("Play ended");
    counter++;    
    if(counter > LAST_TRACK)
      counter = 1;
    play_track();
    EEPROM.write(SHOULD_RESET, 0);
    EEPROM.write(CHAPTER_C, counter);
  }
}
