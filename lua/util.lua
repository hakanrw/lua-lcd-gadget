---- utility functions container ----

local util = {}

local gpio = require("gpio")

function util.greet(name)
    return "Hello, " .. name
end

function util.add(a, b)
    return a + b
end

function util.init_all(...)
    local args = {...}
    for i, v in ipairs(args) do
        gpio.init(v)
    end
end

return util
