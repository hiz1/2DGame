#ifndef HZCHARA_H
#define HZCHARA_H


#include "hzCharaBase.h"
#include "lua.hpp"

class hzChara : public hzCharaBase
{
  public:
    hzChara(ofPtr<hzSprite> sprite, float x, float y, string script, lua_State *L);
    virtual ~hzChara();
    void deleteThread();
    void update();
  protected:
  private:
    lua_State *L;
    lua_State *co;
    lua_State *event;
    int threadIdx;
};

#endif // HZCHARA_H
