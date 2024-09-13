/*
 * Copyright (c) 2024 Hakan Candar
 * All rights reserved.
 *
 * This source code is licensed under the BSD 2-Clause License found in the
 * LICENSE file in the root directory of this source tree.
 */

#include "modules.h"
#include "lua_lcd.h"

#include "map.h"

#include "incbin.h"

#define INCLUA(x) INCTXT(x, #x ".lua");

MAP(INCLUA, LUA_FILES)

#define REGISTER(x) register_module(L, #x, luaopen_##x);
#define LUAOPEN(x) int luaopen_##x(lua_State *L) { return lopen(L, g_##x##_data); }

int lopen(lua_State* L, const char* lua_script) {
    lua_pop(L, lua_gettop(L));
    printf("before lua stack size: %d\n", lua_gettop(L));
    if (luaL_dostring(L, lua_script) == LUA_OK) {
        printf("after lua stack size: %d\n", lua_gettop(L));
        if (lua_istable(L, -1)) {
            return 1;
        }
        else {
            printf("returned stack bad, stack size: %d\n", lua_gettop(L));
            lua_pop(L, lua_gettop(L));
        }
    } else {
        const char *error_msg = lua_tostring(L, -1);
        printf("Error: %s\n", error_msg);
        lua_pop(L, lua_gettop(L));
    }

    return 0;
}

MAP(LUAOPEN, LUA_FILES)

void register_module(lua_State *L, const char* modname, int (*funcptr)(lua_State *L)) {
    luaL_getsubtable(L, LUA_REGISTRYINDEX, LUA_PRELOAD_TABLE);
    lua_pushcfunction(L, funcptr);
    lua_setfield(L, -2, modname);
    lua_pop(L, 1);  // remove PRELOAD table
}

void modules_preregister(lua_State *L) {
    register_lcd(L);
    MAP(REGISTER, LUA_FILES)
    printf("lua stack size: %d\n", lua_gettop(L));
}
