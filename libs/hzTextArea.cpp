#include "hzTextArea.h"

hzTextArea::hzTextArea(ofxTrueTypeFontUC *font, string areatext)
{
  rect = font->getStringBoundingBox(areatext, 0, 0);
  dy = -rect.y;
  dx = -rect.x;
  this->font = font;
  this->text = "";
}

hzTextArea::~hzTextArea()
{
  //dtor
}

void hzTextArea::setPosition(ofPoint pos) {
  this->pos = pos;
  this->rect.x = pos.x;
  this->rect.y = pos.y;
  this->pos.x += dx;
  this->pos.y += dy;

}

void hzTextArea::setText(string text)
{
  this->text = text;
}

void hzTextArea::draw()
{
  if(text.size() == 0) return;
  int radius = 15;
  ofSetColor(255,255,255, 255);
  ofFill();
  ofRectRounded(rect.x-radius, rect.y-radius, rect.width+radius*2,rect.height+radius*2, radius);
  ofSetColor(0,0,0, 255);
  ofNoFill();
  ofRectRounded(rect.x-radius, rect.y-radius, rect.width+radius*2,rect.height+radius*2, radius);
  ofSetColor(0, 0, 0);
  font->drawString(text, pos.x, pos.y);
}

