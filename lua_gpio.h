/*
 * Copyright (c) 2024 Hakan Candar
 * All rights reserved.
 *
 * This source code is licensed under the BSD 2-Clause License found in the
 * LICENSE file in the root directory of this source tree.
 */

#ifndef LUA_GPIO_H
#define LUA_GPIO_H

#include <lua.h>
#include <lauxlib.h>
#include <lualib.h>
#include <pico/stdlib.h>

int lua_gpio_init(lua_State *L);

int lua_gpio_set_dir(lua_State *L);

int lua_gpio_put(lua_State *L);

int lua_gpio_get(lua_State *L);

void register_gpio(lua_State *L);

#endif
