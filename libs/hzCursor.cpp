#include "hzCursor.h"

hzCursor::hzCursor()
{
  left = right = up = down = false;
  btn1 = btn2 = btn3 = false;
}

hzCursor::~hzCursor()
{
  //dtor
}


void hzCursor::keyPressed(int key) {
  if(key == OF_KEY_UP        ) up    = true;
  else if(key == OF_KEY_DOWN ) down  = true;

  if(key == OF_KEY_RIGHT     ) right = true;
  else if(key == OF_KEY_LEFT ) left  = true;

  if(key == 'z' || key == 'Z') btn1  = true;
  if(key == 'x' || key == 'X') btn2  = true;
  if(key == 'c' || key == 'C') btn3  = true;
}

void hzCursor::keyReleased(int key) {
  if(key == OF_KEY_UP        ) up    = false;
  else if(key == OF_KEY_DOWN ) down  = false;

  if(key == OF_KEY_RIGHT     ) right = false;
  else if(key == OF_KEY_LEFT ) left  = false;

  if(key == 'z' || key == 'Z') btn1  = false;
  if(key == 'x' || key == 'X') btn2  = false;
  if(key == 'c' || key == 'C') btn3  = false;
}

bool hzCursor::isUp() {
  return up;
}
bool hzCursor::isDown() {
  return down;
}
bool hzCursor::isLeft() {
  return left;
}
bool hzCursor::isRight() {
  return right;
}

bool hzCursor::isBtn1() {
  return btn1;
}
bool hzCursor::isBtn2() {
  return btn2;
}
bool hzCursor::isBtn3() {
  return btn3;
}
