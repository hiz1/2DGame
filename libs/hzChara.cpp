#include "hzChara.h"
#include "testApp.h"


hzChara::hzChara(ofPtr<hzSprite> sprite, float x, float y, string script, lua_State *L) : hzCharaBase(sprite, x, y)
{
  // スレッドを生成し、グローバルテーブルに積む
  this->L = L;
  lua_settop(L,1);
  lua_getglobal(L, "addThread");
  co = lua_newthread(L);
  lua_call(L, 1, 1);
  threadIdx = lua_tonumber(L, -1);
  lua_settop(L,1);

  ofLogNotice() << "add thread:" << threadIdx;

  lua_getglobal(co, script.c_str());

}

hzChara::~hzChara()
{
  deleteThread();
}

void hzChara::deleteThread()
{
  ofLogNotice() << "delete start thread:" << threadIdx;
  lua_settop(L,1);
  lua_getglobal(L, "removeThread");
  lua_pushnumber(L, threadIdx);
  lua_call(L, 1, 0);
  lua_settop(L,1);
  ofLogNotice() << "delete end   thread:" << threadIdx;
  delete co;

  co = NULL;
}

void hzChara::update()
{
  currentChara = this;
  if(co != NULL) {
    lua_resume(co, NULL, 0);
    if (lua_type(co, -1) == LUA_TNIL) {
      deleteThread();
    }
  }
  hzCharaBase::update();
}
