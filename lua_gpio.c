/*
 * Copyright (c) 2024 Hakan Candar
 * All rights reserved.
 *
 * This source code is licensed under the BSD 2-Clause License found in the
 * LICENSE file in the root directory of this source tree.
 */

#include "lua_gpio.h"

int lua_gpio_init(lua_State *L) {
    int pin = luaL_checkinteger(L, 1);
    gpio_init(pin);
    return 0;
}

int lua_gpio_set_dir(lua_State *L) {
    int pin = luaL_checkinteger(L, 1);
    bool dir = luaL_checkinteger(L, 2);

    gpio_set_dir(pin, dir);
    return 0;
}

int lua_gpio_get_dir(lua_State *L) {
    int pin = luaL_checkinteger(L, 1);

    bool dir = gpio_get_dir(pin);
    lua_pushboolean(L, dir);
    return 1;
}

int lua_gpio_put(lua_State *L) {
    int pin = luaL_checkinteger(L, 1);
    bool val = luaL_checkinteger(L, 2);

    gpio_put(pin, val);
    return 0;
}

int lua_gpio_get(lua_State *L) {
    int pin = luaL_checkinteger(L, 1);

    bool val = gpio_get(pin);
    lua_pushboolean(L, val);
    return 1;
}

// Create the module and register functions
int luaopen_gpio(lua_State *L) {
    // Create a new table for the `lcd` module
    lua_newtable(L);

    lua_pushcfunction(L, lua_gpio_init);
    lua_setfield(L, -2, "init");

    lua_pushcfunction(L, lua_gpio_set_dir);
    lua_setfield(L, -2, "set_dir");

    lua_pushcfunction(L, lua_gpio_get_dir);
    lua_setfield(L, -2, "get_dir");

    lua_pushcfunction(L, lua_gpio_put);
    lua_setfield(L, -2, "put");

    lua_pushcfunction(L, lua_gpio_get);
    lua_setfield(L, -2, "get");

    lua_pushinteger(L, GPIO_IN);
    lua_setfield(L, -2, "in");

    lua_pushinteger(L, GPIO_OUT);
    lua_setfield(L, -2, "out");

    lua_pushinteger(L, 1);
    lua_setfield(L, -2, "high");

    lua_pushinteger(L, 0);
    lua_setfield(L, -2, "low");

    // Return the table as the result of require("lcd")
    return 1;
}

void register_gpio(lua_State *L) {
    luaL_getsubtable(L, LUA_REGISTRYINDEX, LUA_PRELOAD_TABLE);
    lua_pushcfunction(L, luaopen_gpio);
    lua_setfield(L, -2, "gpio");
    lua_pop(L, 1);  // remove PRELOAD table
}
