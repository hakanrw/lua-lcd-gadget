/*
 * Copyright (c) 2024 Hakan Candar
 * All rights reserved.
 *
 * This source code is licensed under the BSD 2-Clause License found in the
 * LICENSE file in the root directory of this source tree.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <pico/stdlib.h>
#include <pico/time.h>

#include "lua.h"
#include "lauxlib.h"
#include "lualib.h"

#include "gadget.h"
#include "modules.h"
#include "lcd.h"

#include "incbin.h"

INCTXT(luacode, "lua/main.lua");

void pins_setup() {
    gpio_init(LED_RED);
    gpio_init(LED_GREEN);
    gpio_set_dir(LED_RED, GPIO_OUT);
    gpio_set_dir(LED_GREEN, GPIO_OUT);

    gpio_init(BUTTON_A);
    gpio_init(BUTTON_B);
    gpio_set_dir(BUTTON_A, GPIO_IN);
    gpio_set_dir(BUTTON_B, GPIO_IN);

    i2c_init(i2c0, 100 * 1000);
    gpio_set_function(LCD_SDA, GPIO_FUNC_I2C);
    gpio_set_function(LCD_SCL, GPIO_FUNC_I2C);
    gpio_pull_up(LCD_SDA);
    gpio_pull_up(LCD_SCL);

    lcd_init();
}

int lua_sleep(lua_State* L) {
    float sec = luaL_checknumber(L, 1);
    sleep_ms((int) (sec * 1000));
    return 0;
}

void lua_setup() {
    printf("about to luaL_newstate()\n");
    lua_State *L = luaL_newstate();  // Create a new Lua state
    if (L == NULL) {
        printf("Failed to create Lua state\n");
        return;
    } else {
        printf("Successfuly created Lua state\n");
    }

    luaL_openlibs(L);
    modules_preregister(L);

    lua_pushcfunction(L, lua_sleep);
    lua_setglobal(L, "sleep");

    printf("lua stack size: %d\n", lua_gettop(L));

    if (luaL_dostring(L, g_luacode_data) != LUA_OK) {
        printf("Error: %s\n", lua_tostring(L, -1));
        lua_close(L);
        return;
    }
}

void board_loop() {
    sleep_ms(100);
    printf(".");
    fflush(stdout);
}

int main() {
    stdio_init_all();
    sleep_ms(3000);
    printf("starting raspberry pico");

    pins_setup();
    lua_setup();
    while (true) board_loop();
    return 0;
}
