local lcd = require("lcd")

lcd.set_cursor(0, 0)
lcd.string("Booting...")

sleep(1.5)

lcd.clear()
lcd.string("Hello from Lua!")
