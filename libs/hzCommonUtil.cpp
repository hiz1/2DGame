//
//  CommonUtil.cpp
//  Menu
//
//  Created by 成田 輝久 on 2013/11/03.
//
//

#include "hzCommonUtil.h"


// 文字列の長さを全角文字数で数える
int utf8len(const string &s)
{
    size_t i = 0;
    size_t len = 0;
    size_t s_size = s.size();
    unsigned char c;
    while(i < s_size){
        c = s[i];
        if(c == 0x00) i += 0;
        else if(c < 0x80) i += 1;
        else if(c < 0xC2) throw logic_error("error");
        else if(c < 0xE0) i += 2;
        else if(c < 0xF0) i += 3;
        else if(c < 0xF8) i += 4;
        else if(c < 0xFC) i += 5;
        else if(c < 0xFE) i += 6;
        else i += 1;
        len++;
    }
    return len;
}

// 文字列の長さを半角文字数で数える
int utf8HWlen(const string &s)
{
    size_t i = 0;
    size_t len = 0;
    size_t s_size = s.size();
    unsigned char c;
    while(i < s_size){
        c = s[i];
        if(c == 0x00) i += 0;
        else if(c < 0x80) {
            i += 1;
            len ++;
            continue;
        }
        else if(c < 0xC2) throw logic_error("error");
        else if(c < 0xE0) i += 2;
        else if(c < 0xF0) i += 3;
        else if(c < 0xF8) i += 4;
        else if(c < 0xFC) i += 5;
        else if(c < 0xFE) i += 6;
        else i += 1;
        len+=2;
    }
    return len;
}

// n番目の全角文字のインデックスを返す
int utf8index(const string &s, int widx) {
    if(widx == 0)return 0;

    size_t i = 0;
    size_t len = 0;
    size_t s_size = s.size();
    unsigned char c;
    while(i < s_size){
        c = s[i];
        if(c == 0x00) i += 0;
        else if(c < 0x80) i += 1;
        else if(c < 0xC2) throw logic_error("error");
        else if(c < 0xE0) i += 2;
        else if(c < 0xF0) i += 3;
        else if(c < 0xF8) i += 4;
        else if(c < 0xFC) i += 5;
        else if(c < 0xFE) i += 6;
        else i += 1;
        len++;
        if(len == widx) return i;
    }
    return -1;
}

// 半角文字で数えてn番目の文字のインデックスを返す
int utf8HBindex(const string &s, int hwidx) {
    if(hwidx == 0)return 0;

    size_t i = 0;
    size_t len = 0;
    size_t s_size = s.size();
    unsigned char c;
    while(i < s_size){
        c = s[i];
        if(c == 0x00) i += 0;
        else if(c < 0x80) {
            i += 1;
            len ++;
            if(len == hwidx) return i;
            continue;
        }
        else if(c < 0xC2) throw logic_error("error");
        else if(c < 0xE0) i += 2;
        else if(c < 0xF0) i += 3;
        else if(c < 0xF8) i += 4;
        else if(c < 0xFC) i += 5;
        else if(c < 0xFE) i += 6;
        else i += 1;
        len+=2;
        if(len >= hwidx) return i;
    }
    return -1;
}

// stringのbegin番目の全角文字からbegin+length-1番目の全角文字までのsubstringを返す
std::string utf8substr(const string &s, int begin, int length) {
    int beginIndex = utf8index(s, begin);
    int endIndex   = utf8index(s, begin+length);
    if(beginIndex >= s.length() || beginIndex == -1)return "";
    if(endIndex   >  s.length() || endIndex   == -1)endIndex = s.length();
    return s.substr(beginIndex, endIndex-beginIndex);
}

// stringのbegin番目の全角文字からbegin+length-1番目の全角文字までのsubstringを返す
std::string utf8HWsubstr(const string &s, int begin, int length) {
    int beginIndex = utf8HBindex(s, begin);
    int endIndex   = utf8HBindex(s, begin+length);
    if(beginIndex >= s.length() || beginIndex == -1)return "";
    if(endIndex   >  s.length() || endIndex   == -1)endIndex = s.length();
    return s.substr(beginIndex, endIndex-beginIndex);
}

// 文字列を１行col文字のrow行の文字列に変換する
std::string createParagraph(const string &s, int col, int row) {
    string paragraph;
    vector<string> rows = ofSplitString(s, "\n");

    int rowNum = 0;
    for(int idx=0;idx<rows.size();idx++) {
        int rowLength = utf8HWlen(rows[idx]);

        int colIdx = 0;
        while(colIdx * col < rowLength) {
            paragraph += utf8HWsubstr(rows[idx], colIdx * col, col) + "\n";
            rowNum ++;
            colIdx ++;
            if(rowNum >= row)return paragraph;
        }
    }
    return paragraph;
}

// 文字列をareaに収まる文字列に変換する
std::string createParagraphByArea(const string &s, const ofPoint &fontSize, const ofPoint &area) {
    return createParagraph(s, area.x / fontSize.x * 2, area.y / fontSize.y);
}

// メッシュに法線ベクトルを自動追加する（TRIANGLESを想定）
void setNormals(ofMesh &mesh) {
    int nV = mesh.getNumVertices();
    int nT = mesh.getNumIndices() / 3;
    vector<ofPoint> norm(nV);

    for(int t=0;t<nT;t++) {
        int i1 = mesh.getIndex(3 * t );
        int i2 = mesh.getIndex(3 * t + 1);
        int i3 = mesh.getIndex(3 * t + 2);

        const ofPoint &v1 = mesh.getVertex(i1);
        const ofPoint &v2 = mesh.getVertex(i2);
        const ofPoint &v3 = mesh.getVertex(i3);

        ofPoint dir = ((v2 - v1)).crossed(v3 - v1).normalized();

        norm[i1] += dir;
        norm[i2] += dir;
        norm[i3] += dir;
    }

    for(int i=0;i<nV;i++) {
        norm[i].normalize();
    }
    mesh.clearNormals();
    mesh.addNormals(norm);
}

// Luaのスレッドを作成し、スレッドINDEXを返す
int addLuaThread(lua_State *L, lua_State **co, string script)
{
    lua_settop(L,1);
    lua_getglobal(L, "addThread");
    *co = lua_newthread(L);
    lua_call(L, 1, 1);
    int eventThreadIdx = lua_tonumber(L, -1);
    lua_settop(L,1);
    ofLogNotice() << "add thread:" << eventThreadIdx;
    lua_getglobal(*co, script.c_str());
    return eventThreadIdx;
}

void deleteLuaThread(lua_State *L, lua_State **co,int threadIdx)
{
  lua_settop(L,1);
  lua_getglobal(L, "removeThread");
  lua_pushnumber(L, threadIdx);
  lua_call(L, 1, 0);
  lua_settop(L,1);
  delete *co;
  *co = NULL;
  ofLogNotice() << "delete thread :" << threadIdx;
}

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
