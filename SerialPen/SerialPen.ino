/*
  SerialPen

  Paints on Arduino Uno R4 WiFi LED matrix based on commands from Serial input.
  A serial terminal like PuTTY or picocom can be used to interact with the Arduino.

  The circuit:
  - none

*/
#include <Arduino_LED_Matrix.h>
#include "Pen.h"

#define ROWS 8
#define COLUMNS 12

ArduinoLEDMatrix matrix;

Pen myPen(ROWS, COLUMNS);

int key = -1;
int keyUp = 'w';
int keyDown = 's';
int keyRight = 'd';
int keyLeft = 'a';
int keyWrite = 'u';
int keyMove = 'i';
int keyErase = 'o';
int keyPrintSerial = 'p';


int getKey(){
  int userInput = 0;
  size_t currentPos = myPen.getIdx();

  while (!Serial.available()) {
    // while waiting for input switch on and off pointer LED to make it less bright
    delay(50);
    matrix.on(currentPos);
    delay(50);
    matrix.off(currentPos);
  }

  // use only last char
  while (Serial.available()>0) {
    userInput = Serial.read();
  }

  return userInput;
}

void printConfig(){
  Serial.println("Configuration:");
  Serial.print("key UP: ");
  Serial.println((char)keyUp);
  Serial.print("key DOWN: ");
  Serial.println((char)keyDown);
  Serial.print("key RIGHT: ");
  Serial.println((char)keyRight);
  Serial.print("key LEFT: ");
  Serial.println((char)keyLeft);
  Serial.print("key WRITE mode: ");
  Serial.println((char)keyWrite);
  Serial.print("key MOVE mode: ");
  Serial.println((char)keyMove);
  Serial.print("key ERASE mode: ");
  Serial.println((char)keyErase);
  Serial.print("key Print to Serial: ");
  Serial.println((char)keyPrintSerial);
}


void printFrameToSerial(){
  uint8_t **frame = myPen.getFrame();

  Serial.print("uint8_t frame[");
  Serial.print(myPen.frameHeight);
  Serial.print("][");
  Serial.print(myPen.frameWidth);
  Serial.println("] = {");

  for(uint32_t r=0; r<myPen.frameHeight; r++) {
    Serial.print("\t{");
    for(uint32_t c=0; c<myPen.frameWidth; c++) {
      Serial.print(frame[r][c]);
      if((c+1) < myPen.frameWidth) Serial.print(",");
    }
    Serial.println("},");
  }
  Serial.println("};");
}


void setup() {
  // initialize serial communications at 9600 bps:
  Serial.begin(9600);

  // set pen initial mode
  myPen.setMode(Pen::MOVING);

  // clear frame data
  myPen.clear();

  // start LED matrix
  matrix.begin();

  // Start Setup
  Serial.println("Do you want to change default keys (y/n):\n");
  key = getKey();

  if (key == 'y' || key == 'Y'){
    Serial.println("Press key to be used for UP movement:\n");
    keyUp = getKey();
    Serial.println("Press key to be used for DOWN movement:\n");
    keyDown = getKey();
    Serial.println("Press key to be used for RIGHT movement:\n");
    keyRight = getKey();
    Serial.println("Press key to be used for LEFT movement:\n");
    keyLeft = getKey();

    Serial.println("Press key to be used for WRITE mode:\n");
    keyWrite = getKey();
    Serial.println("Press key to be used for MOVE mode:\n");
    keyMove = getKey();
    Serial.println("Press key to be used for ERASE mode:\n");
    keyErase = getKey();

    Serial.println("Press key to be used for printing frame to Serial:\n");
    keyPrintSerial = getKey();
  }

  // print configuration
  printConfig();
  
  Serial.println("Starting pen..\n");

}


void loop() {

  key = getKey();

  if (key == keyUp){
    myPen.move(Pen::UP);
  }
  else if (key == keyDown){
    myPen.move(Pen::DOWN);
  }
  else if (key == keyRight){
    myPen.move(Pen::RIGHT);
  }
  else if (key == keyLeft){
    myPen.move(Pen::LEFT);
  }
  else if (key == keyMove){
    myPen.setMode(Pen::MOVING);
  }
  else if (key == keyWrite){
    myPen.setMode(Pen::WRITING);
  }
  else if (key == keyErase){
    myPen.setMode(Pen::ERASING);
  }
  else if (key == keyPrintSerial){
    printFrameToSerial();
  }

  matrix.renderBitmap(myPen.getFrame(), ROWS, COLUMNS);

}
