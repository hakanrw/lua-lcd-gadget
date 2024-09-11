#ifndef LUA_LCD_H
#define LUA_LCD_H

#include <lua.h>
#include <lauxlib.h>
#include <lualib.h>
#include "lcd.h"

int lua_lcd_clear(lua_State *L);

int lua_lcd_set_cursor(lua_State *L);

int lua_lcd_string(lua_State *L);

int lua_lcd_init(lua_State *L);

//LUALIB_API int luaopen_lcd(lua_State *L);

void register_lcd(lua_State *L);

#endif
