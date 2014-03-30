#ifndef HZPLAYER_H
#define HZPLAYER_H

#include "hzCharaBase.h"
#include "hzCursor.h"

class hzPlayer : public hzCharaBase
{
  public:
    hzPlayer(ofPtr<hzSprite> sprite, float x, float y, hzCursor *cursor);
    virtual ~hzPlayer();
    virtual void update();
  protected:
  private:
    hzCursor *cursor;
};
#endif // HZPLAYER_H
