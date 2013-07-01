
#ifndef __LUA_CTRLBOARD_H_
#define __LUA_CTRLBOARD_H_

extern "C"
{
    #include "lua.h"
    #include "lualib.h"
    #include "lauxlib.h"
}

#ifndef DECLSPEC
    #define DECLSPEC
#endif

extern "C" int DECLSPEC luaopen_luactrlboard( lua_State * L );


#endif

