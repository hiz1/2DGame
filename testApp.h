#pragma once

#include "ofMain.h"
#include "libs/hzCursor.h"
#include "libs/hzSprite.h"
#include "libs/hzChara.h"
#include "libs/hzPlayer.h"
#include "libs/hzCommonUtil.h"
#include "libs/hzTextArea.h"
#include "ofxTrueTypeFontUC.h"
#include "ofxJSONElement.h"

#include <stdio.h>
#include "lua.hpp"

extern hzChara *currentChara;

void dumpStack(lua_State* L);

class testApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);

  private:
    hzCursor cursor;
    ofxTrueTypeFontUC font;
    lua_State* L;
    lua_State* event;
    int eventThreadIdx;
    bool eventRunning;
};
