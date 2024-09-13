/*
 * Copyright (c) 2024 Hakan Candar
 * All rights reserved.
 *
 * This source code is licensed under the BSD 2-Clause License found in the
 * LICENSE file in the root directory of this source tree.
 */

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

void register_lcd(lua_State *L);

#endif
