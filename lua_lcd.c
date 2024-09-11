#include "lua_lcd.h"

int lua_lcd_clear(lua_State *L) {
    printf("clear from within lua\n");
    lcd_clear();

    return 0;
}

int lua_lcd_set_cursor(lua_State *L) {
    int row = luaL_checknumber(L, 1);
    int col = luaL_checknumber(L, 2);

    lcd_set_cursor(row, col);

    return 0;
}

int lua_lcd_string(lua_State *L) {
    const char* str = luaL_checkstring(L, 1);

    lcd_string(str);

    return 0;
}

int lua_lcd_init(lua_State *L) {
    printf("init from within lua\n");
    lcd_init();

    return 0;
}

// Create the module and register functions
int luaopen_lcd(lua_State *L) {
    printf("exampl\n");

    // Create a new table for the `lcd` module
    lua_newtable(L);

    lua_pushcfunction(L, lua_lcd_string);
    lua_setfield(L, -2, "string");

    lua_pushcfunction(L, lua_lcd_clear);
    lua_setfield(L, -2, "clear");

    lua_pushcfunction(L, lua_lcd_init);
    lua_setfield(L, -2, "init");

    lua_pushcfunction(L, lua_lcd_set_cursor);
    lua_setfield(L, -2, "set_cursor");

    // Return the table as the result of require("lcd")
    return 1;
}

void register_lcd(lua_State *L) {
    luaL_getsubtable(L, LUA_REGISTRYINDEX, LUA_PRELOAD_TABLE);
    lua_pushcfunction(L, luaopen_lcd);
    lua_setfield(L, -2, "lcd");
    lua_pop(L, 1);  // remove PRELOAD table
}
