#include "Pen.h"

#define DECR_POS(pos, size) ( (pos > 0) ? (pos - 1) : (size - 1) )
#define INCR_POS(pos, size) ( (pos + 1) % size )


Pen::Pen(uint32_t frameHeight, uint32_t frameWidth) {
  this->frameWidth = frameWidth;
  this->frameHeight = frameHeight;

  pFrameHolder = new uint8_t[frameHeight * frameWidth];
  ppFrame = new uint8_t *[frameHeight];

  for (int r = 0; r < frameHeight; r++) ppFrame[r] = pFrameHolder + r * frameWidth;
};

Pen::~Pen(){
  delete pFrameHolder;
  delete ppFrame;
}

uint8_t** Pen::getFrame(void){
  return ppFrame;
}

void Pen::getPos(uint32_t &x, uint32_t&y){
  x = pos_x;
  y = pos_y;
}

size_t Pen::getIdx(){
  return pos_x + (frameWidth * pos_y);
}

void Pen::setMode(eMode_t mode){
  curr_mode = mode;
  this->update();
}

void Pen::clear(){
  for (int r=0; r<frameHeight; r++){
    for (int c=0; c<frameWidth; c++){
      ppFrame[r][c] = 0;
    }
  }
}

void Pen::update(){
  switch (curr_mode) {
    case WRITING:
      ppFrame[pos_y][pos_x] = 1;
      break;
    case MOVING:
      break;
    case ERASING:
      ppFrame[pos_y][pos_x] = 0;
      break;
  }
}


void Pen::move(eDir_t dir){

  switch (dir) {
    case UP:
      pos_y = DECR_POS(pos_y, frameHeight);
      break;
    case DOWN:
      pos_y = INCR_POS(pos_y, frameHeight);
      break;
    case RIGHT:
      pos_x = INCR_POS(pos_x, frameWidth);
      break;
    case LEFT:
      pos_x = DECR_POS(pos_x, frameWidth);
      break;
  }

  this->update();
}