#include "hzPlayer.h"


hzPlayer::hzPlayer(ofPtr<hzSprite> sprite, float x, float y, hzCursor *cursor) : hzCharaBase(sprite, x, y)
{
  this->cursor = cursor;

}

hzPlayer::~hzPlayer()
{
}

void hzPlayer::update(bool eventRunning)
{
  hzCharaBase::update(eventRunning);
  if(eventRunning) return;

  if(cursor->isUp()   ) {
      move(0, -5);
  }
  if(cursor->isDown() ) {
      move(0, 5);
  }

  if(cursor->isRight()) {
      move(5, 0);
  }
  if(cursor->isLeft() ) {
      move(-5, 0);
  }


}
