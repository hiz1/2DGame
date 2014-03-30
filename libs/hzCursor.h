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
  protected:
  private:
    bool up, down, left, right;
};

#endif // CURSOR_H
