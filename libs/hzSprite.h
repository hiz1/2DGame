#ifndef SPRITE_H
#define SPRITE_H

#include "ofMain.h"

class hzSprite
{
  public:
    hzSprite();
    hzSprite(string filename, int sw, int sh, int baseXi = 0, int baseYi = 0);
    virtual ~hzSprite();
    ofImage *getImage();
    void draw(float x, float y, int xi, int yi);
    void draw(float x, float y, float z, int xi, int yi);
  protected:
  private:
    ofImage *image;
    int sw, sh;
    int baseXi, baseYi;
};

#endif // SPRITE_H
