#include "hzChara.h"
#include "testApp.h"
#include "libs/hzCommonUtil.h"

hzChara::hzChara(ofPtr<hzSprite> sprite, float x, float y, string script, string eventScript, lua_State *L) : hzCharaBase(sprite, x, y)
{
  // スレッドを生成し、グローバルテーブルに積む
  this->L = L;
  threadIdx = addLuaThread(this->L, &co, script);
  this->eventScript = eventScript;
}

hzChara::~hzChara()
{
  deleteLuaThread(L, &co, threadIdx);
}



void hzChara::update(bool eventRunning)
{
  hzCharaBase::update(eventRunning);
  if(eventRunning) return;

  currentChara = this;
  if(co != NULL) {
    lua_resume(co, NULL, 0);
    if (lua_type(co, -1) == LUA_TSTRING) {
      deleteLuaThread(L, &co, threadIdx);
    }
  }

}

string hzChara::getEventScript()
{
  return eventScript;
}
