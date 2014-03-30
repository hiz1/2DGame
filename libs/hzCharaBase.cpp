#include "hzCharaBase.h"
#include "testApp.h"


hzCharaBase::hzCharaBase(ofPtr<hzSprite> sprite, float x, float y)
{
  this->sprite = sprite;
  this->pos.x = x;
  this->pos.y = y;
  this->pos.z = 0;
  xi = yi = 0;
}

hzCharaBase::~hzCharaBase()
{
}

void hzCharaBase::draw()
{
  this->sprite->draw(this->pos.x, this->pos.y, this->pos.z, this->xi, this->yi);

}

void hzCharaBase::move(float dx, float dy)
{
  if(dy < 0   ) {
      pos += ofPoint(0, dy);
      yi = 3;
  }
  if(dy > 0 ) {
      pos += ofPoint(0,  dy);
      yi = 0;
  }

  if(dx > 0) {
      pos += ofPoint( dx, 0 );
      yi = 2;
  }
  if(dx < 0 ) {
      pos += ofPoint( dx, 0 );
      yi = 1;
  }

}

void hzCharaBase::update()
{
  if(ofGetFrameNum() % 10 == 0)xi ++;
  xi = ofWrap(xi, 0, 2);
}
