#include "Arduino.h"

class Pen {
  public:
    Pen(uint32_t frameHeight, uint32_t frameWidth);
    ~Pen();

    typedef enum {
      UP,
      DOWN,
      LEFT,
      RIGHT
    } eDir_t;

    typedef enum {
      WRITING,
      MOVING,
      ERASING
    } eMode_t;

    uint32_t frameWidth, frameHeight;

    void clear(void);
    uint8_t** getFrame(void);
    void move(eDir_t dir);
    void getPos(uint32_t &x, uint32_t&y);
    size_t getIdx();
    void setMode(eMode_t mode);
    void printFrame();

  private:
    uint8_t *pFrameHolder;
    uint8_t **ppFrame;
    uint32_t pos_x{0};
    uint32_t pos_y{0};
    eMode_t curr_mode{MOVING};
    void update();

};