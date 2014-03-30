#ifndef HZCHARA_H
#define HZCHARA_H


#include "hzCharaBase.h"
#include "lua.hpp"

class hzChara : public hzCharaBase
{
  public:
    hzChara(ofPtr<hzSprite> sprite, float x, float y, string script, string eventScript, lua_State *L);
    virtual ~hzChara();
    void update(bool eventRunning);
    string getEventScript();
  protected:
  private:
    lua_State *L;
    lua_State *co;
    string eventScript;
    int threadIdx;
};

#endif // HZCHARA_H
