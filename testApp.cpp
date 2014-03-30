#include "testApp.h"


vector<ofPtr<hzChara> > charas;
hzChara *currentChara;

hzPlayer *player;
hzTextArea *textArea;

void dumpStack(lua_State* L)
{
    int i;
    //スタックに積まれている数を取得する
    int stackSize = lua_gettop(L);
    for( i = stackSize; i >= 1; i-- ) {
        int type = lua_type(L, i);
        printf("Stack[%2d-%10s] : ", i, lua_typename(L,type) );

        switch( type ) {
        case LUA_TNUMBER:
            //number型
            printf("%f", lua_tonumber(L, i) );
            break;
        case LUA_TBOOLEAN:
            //boolean型
            if( lua_toboolean(L, i) ) {
                printf("true");
            }else{
                printf("false");
            }
            break;
        case LUA_TSTRING:
            //string型
            printf("%s", lua_tostring(L, i) );
            break;
        case LUA_TNIL:
            //nil
            break;
        default:
            //その他の型
            printf("%s", lua_typename(L, type));
            break;
        }
        printf("\n");
    }
    printf("\n");
}

int move(lua_State* L)
{
  int dx = luaL_checkint(L, -2);
  int dy = luaL_checkint(L, -1);

  currentChara->move(dx, dy);

  return 0; //戻り値の数を指定
}

int say(lua_State* L)
{
  string text = luaL_checkstring(L, -1);
  textArea->setText(text);
}


//--------------------------------------------------------------
void testApp::setup(){
  ofSetFrameRate(60);


  font.loadFont("togoshi-mono.ttf", 12);

  ofLog() << "getLineHeight:" << font.getLineHeight() << endl;
  ofLog() << "getSpaceSize:" << font.getSpaceSize() << endl;

  // Luaを開く
    L = luaL_newstate();

    // Lua標準関数を使う
    luaL_openlibs(L);

    // Luaファイルを読み込む
    if(luaL_loadfile(L, "data\\base.lua") || lua_pcall(L, 0, 0, 0)) {
        perror(lua_tostring(L, -1));
    }

    if(luaL_loadfile(L, "data\\moves.lua") || lua_pcall(L, 0, 0, 0)) {
        perror(lua_tostring(L, -1));
    }
    //move関数をcmove関数としてLuaに登録
    lua_register(L, "cmove", move);

    lua_register(L, "csay", say);


  // キャラ情報読み込み
  ofxJSONElement json;
  json.open("charas.json");

  for(int i=0;i<json.size();i++) {
    string charachip = json[i]["graphic"]["charachip"].asString();
    int    width     = json[i]["graphic"].isMember("width")  ? json[i]["graphic"]["width"].asInt()  : 32;
    int    height    = json[i]["graphic"].isMember("height") ? json[i]["graphic"]["height"].asInt() : 48;
    int    xi        = json[i]["graphic"]["xi"].asInt() * 3;
    int    yi        = json[i]["graphic"]["yi"].asInt() * 4;
    int    x         = json[i]["x"].asInt();
    int    y         = json[i]["y"].asInt();
    string moveScript    = json[i]["move"].asString();
    string eventScript    = json[i]["event"].asString();

    ofPtr<hzSprite> sprite(new hzSprite(charachip, width, height, xi, yi));
    ofPtr<hzChara> chara(new hzChara(sprite,x, y, moveScript, L));
    charas.push_back(chara);
  }

  json.open("player.json");
  string charachip = json["graphic"]["charachip"].asString();
  int    width     = json["graphic"].isMember("width")  ? json["graphic"]["width"].asInt()  : 32;
  int    height    = json["graphic"].isMember("height") ? json["graphic"]["height"].asInt() : 48;
  int    xi        = json["graphic"]["xi"].asInt() * 3;
  int    yi        = json["graphic"]["yi"].asInt() * 4;
  int    x         = json["x"].asInt();
  int    y         = json["y"].asInt();

  ofPtr<hzSprite> sprite(new hzSprite(charachip, width, height, xi, yi));
  player = new hzPlayer(sprite,x, y, &cursor);

  currentChara = charas[0].get();;

  textArea = new hzTextArea(&font, "○○○○○○○○○○\n○○○○○○○○○○\n○○○○○○○○○○\n○○○○○○○○○○");
  textArea->setPosition(ofPoint(200,200,0));
}

//--------------------------------------------------------------
void testApp::update(){
  // リサイズ無効化
  int w = ofGetWidth();
	int h = ofGetHeight();
	if(w != 640 || h != 480) ofSetWindowShape(640, 480);

  player->update();

  for(ofPtr<hzChara> chara : charas) {
    chara->update();
  }

}

//--------------------------------------------------------------
void testApp::draw(){
  ofBackground(100,100,100);

  // グリッド描画
  for(int y = 0; y < ofGetHeight(); y+= 10) {
      if(y % 100 == 0)ofSetColor(255, 255, 255);
      else ofSetColor(150, 150, 150);
    ofLine(0, y, ofGetWidth(), y);
  }
  for(int x = 0; x < ofGetWidth(); x+= 10) {
    if(x % 100 == 0)ofSetColor(255, 255, 255);
    else ofSetColor(150, 150, 150);
    ofLine(x, 0, x, ofGetHeight());
  }


//  ofSetColor(255,255,255);
//  ofRectRounded(190, 190, 120, 120, 20);

//  font.drawString(createParagraphByArea("私のゲームです。さあ遊びなさい。", ofPoint(14, 14), ofPoint(80, 94, 0)), 200,220);

  textArea->draw();
//  ofRectangle rect = font.getStringBoundingBox(serif, 200, 200);
//  float sy = rect.y;
//  rect.y += 200 - sy;
////  rect.y += font.getLineHeight();
//  ofSetColor(255,255,255, 50);
//  ofRect(rect);
//  ofSetColor(255,255,255);
//  font.drawString(serif, 200,200 + (200 - sy));

  ofSetColor(255,255,255);
  player->draw();
  for(ofPtr<hzChara> chara : charas) {
    chara->draw();
  }


//  chara.drawSubsection(pos.x, pos.y, 32, 48,xi * 32, yi * 48);
}

//--------------------------------------------------------------
void testApp::keyPressed(int key){
  cursor.keyPressed(key);

  /*
  if(key == OF_KEY_UP        ) up    = true;
  else if(key == OF_KEY_DOWN ) down  = true;

  if(key == OF_KEY_RIGHT     ) right = true;
  else if(key == OF_KEY_LEFT ) left  = true;
    */
}

//--------------------------------------------------------------
void testApp::keyReleased(int key){
  cursor.keyReleased(key);
  /*
  if(key == OF_KEY_UP        ) up    = false;
  else if(key == OF_KEY_DOWN ) down  = false;

  if(key == OF_KEY_RIGHT     ) right = false;
  else if(key == OF_KEY_LEFT ) left  = false;
    */
}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void testApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void testApp::dragEvent(ofDragInfo dragInfo){

}
