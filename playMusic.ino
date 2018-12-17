#include <pcmConfig.h>
#include <pcmRF.h>
#include <TMRpcm.h>
#include <SD.h>
#include <SPI.h>

/*
Arduino Based Music Player. Originally written by Aswinth Raj, heavily modified
for CS 320: Tangible User Interfaces MusicBox project by Christina Chen.

 The circuit:
 * three push Buttons on pins 5, 6, 7
 * Audio Out - pin 9
 * SD card attached to SPI bus as follows:
 ** MOSI - pin 11
 ** MISO - pin 12
 ** CLK - pin 13
 ** CS - pin 4 

 */

#define SD_ChipSelectPin 4 //Chip select is pin number 4
TMRpcm music; //Lib object is named "music"

int volPin = A0; //slide potentiometer to control volume

void setup(){
  
music.speakerPin = 9; //Audio out on pin 9

Serial.begin(9600); //Serial Com for debugging 

if (!SD.begin(SD_ChipSelectPin)) {
  Serial.println("SD fail");
  }else{
    Serial.println("SD card successfully read");
  }

music.quality(1);        //  Set 1 for 2x oversampling Set 0 for normal

pinMode(7, INPUT_PULLUP); //classy button
pinMode(6, INPUT_PULLUP); //funky button
pinMode(5, INPUT_PULLUP); // techno button

}

void loop()
{  

  volume();
  
  if (digitalRead(7) == HIGH){
    Serial.println("classy button pressed");
    music.play("classy.wav");
 }

 if (digitalRead(6) == HIGH){
    Serial.println("funky button pressed");
    music.play("funky.wav");
 }

  if (digitalRead(5) == HIGH){
    Serial.println("techno button pressed");
    music.play("techno.wav");
 }
   
}

int rawValue;

void volume(){ //reads value from slider potentiometer and changes volume accordingly
  
  rawValue = analogRead(volPin);
  //Serial.println(rawValue);
  //delay(500);
  
  if (rawValue < 128){
    music.setVolume(0);
  } else if ((rawValue >= 90) & (rawValue < 180)) {
    music.setVolume(1);
  }else if ((rawValue >= 180) & (rawValue < 270)){ 
    music.setVolume(2);
  }else if ((rawValue >= 270) & (rawValue < 360)){
    music.setVolume(3);
  }else if ((rawValue >= 360) & (rawValue < 500)){
    music.setVolume(4);
  }else if ((rawValue >= 500) & (rawValue < 580)){
    music.setVolume(5);
  }else if ((rawValue >= 600) & (rawValue < 630)){
    music.setVolume(6);
  }
}
