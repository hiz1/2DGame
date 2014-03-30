#ifndef HZTEXTAREA_H
#define HZTEXTAREA_H

#include "ofMain.h"
#include "ofxTrueTypeFontUC.h"

class hzTextArea
{
  public:
    hzTextArea(ofxTrueTypeFontUC *font, string areatext);
    virtual ~hzTextArea();
    void setPosition(ofPoint pos);
    void setText(string text);
    void draw();
  protected:
  private:
    float dx, dy;
    ofxTrueTypeFontUC *font;
    ofPoint pos;
    ofRectangle rect;
    string text;
};

#endif // HZTEXTAREA_H
