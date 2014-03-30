#include "hzCursor.h"

hzCursor::hzCursor()
{
  left = right = up = down = false;
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
}

void hzCursor::keyReleased(int key) {
  if(key == OF_KEY_UP        ) up    = false;
  else if(key == OF_KEY_DOWN ) down  = false;

  if(key == OF_KEY_RIGHT     ) right = false;
  else if(key == OF_KEY_LEFT ) left  = false;
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
