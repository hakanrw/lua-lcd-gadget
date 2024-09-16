-------  native modules  --------
local lcd = require("lcd")
local gpio = require("gpio")
---------------------------------

----------  lua files  ----------
local util = require("util")
local pinout = require("pinout")
---------------------------------

lcd.set_cursor(0, 0)
lcd.string("Booting...")

sleep(1.5)

lcd.clear()
lcd.string("Hello from Lua!")

-- gpio.init(pinout.led_red)
-- gpio.init(pinout.led_green)
-- gpio.init(pinout.button_b)

util.init_all(
    pinout.led_red, 
    pinout.led_green, 
    pinout.button_b
)

gpio.set_dir(pinout.led_red, gpio.out)
gpio.set_dir(pinout.led_green, gpio.out)
gpio.set_dir(pinout.button_b, gpio.inp)

local i = 0
while true do
    gpio.put(pinout.led_red, i == 0 and gpio.high or gpio.low)
    gpio.put(pinout.led_green, i == 1 and gpio.high or gpio.low)
    sleep(0.5)
    i = 1 - i

    print(gpio.get(pinout.button_b))
    if gpio.get(pinout.button_b) == gpio.high then break end
end

lcd.clear()
lcd.string("Handover to C!")

gpio.put(pinout.led_red, gpio.low)
gpio.put(pinout.led_green, gpio.low)

sleep(1.5)
