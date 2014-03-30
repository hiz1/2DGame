#include "hzSprite.h"

map<string, ofImage *> imageCaches;

hzSprite::hzSprite()
{
}

hzSprite::hzSprite(string filename, int sw, int sh, int baseXi, int baseYi)
{
  if(imageCaches.count(filename) == 0) {
    imageCaches.insert(map<string, ofImage *>::value_type(filename, new ofImage(filename)));
  }
  image = imageCaches[filename];
  this->sw = sw;
  this->sh = sh;
  this->baseXi = baseXi;
  this->baseYi = baseYi;
}

hzSprite::~hzSprite()
{
  // 画像はキャッシュしているのでimageのdeleteは行わない
}

ofImage *hzSprite::getImage()
{
  return image;
}

void hzSprite::draw(float x, float y, int xi, int yi)
{
  draw(x, y, 0, xi, yi);
}

void hzSprite::draw(float x, float y, float z, int xi, int yi)
{
  image->drawSubsection(x, y, z, sw, sh, (baseXi + xi)* sw, (baseYi + yi) * sh);
}
