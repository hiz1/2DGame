#ifndef CURSOR_H
#define CURSOR_H

#include "ofMain.h"


class hzCursor
{
  public:
    hzCursor();
    virtual ~hzCursor();
    void keyPressed(int key);
    void keyReleased(int key);
    bool isUp();
    bool isDown();
    bool isLeft();
    bool isRight();
    bool isBtn1();
    bool isBtn2();
    bool isBtn3();
  protected:
  private:
    bool up, down, left, right;
    bool btn1, btn2, btn3;
};

#endif // CURSOR_H
