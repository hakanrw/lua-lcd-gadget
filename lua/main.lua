local lcd = require("lcd")
local util = require("util")
local example = require("example")

lcd.set_cursor(0, 0)
lcd.string("Booting...")

sleep(1.5)

lcd.clear()
lcd.string("Hello from Lua!")

sleep(1.5)

lcd.clear()
lcd.string(util.greet("World!"))
