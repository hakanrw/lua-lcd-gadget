-- native modules --
local lcd = require("lcd")
local gpio = require("lcd")
--                --

--    lua files   --
local util = require("util")
local pinout = require("pinout")
--                --

lcd.set_cursor(0, 0)
lcd.string("Booting...")

sleep(1.5)

lcd.clear()
lcd.string("Hello from Lua!")

sleep(1.5)

lcd.clear()
lcd.string(util.greet("World!"))

gpio.init(pinout.led_red)
gpio.init(pinout.led_green)

gpio.set_dir(pinout.led_red, gpio.out)
gpio.set_dir(pinout.led_green, gpio.out)

for i = 1, 10 do
    gpio.put(pinout.led_red, i % 2 == 0 and gpio.high or gpio.low)
    gpio.put(pinout.led_green, i % 2 == 1 and gpio.high or gpio.low)
end
