#ifndef hzCharaBaseBASE_H
#define hzCharaBaseBASE_H


#include "ofMain.h"
#include "hzSprite.h"
#include "lua.hpp"

class hzCharaBase
{
  public:
    hzCharaBase(ofPtr<hzSprite> sprite, float x, float y);
    virtual ~hzCharaBase();
    virtual void draw();
    virtual void move(float dx, float dy);
    virtual void update();
  protected:
    ofPtr<hzSprite> sprite;
    ofPoint pos;
    int xi, yi;
  private:

};

#endif // hzCharaBaseBASE_H
