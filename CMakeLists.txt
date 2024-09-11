cmake_minimum_required(VERSION 3.13)

# initialize the SDK directly
set(PICO_BOARD pico_w)
include($ENV{PICO_SDK_PATH}/pico_sdk_init.cmake)

project(lua_gadget C CXX ASM)

# debuginfo
#set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -g3")

# initialize the Raspberry Pi Pico SDK
pico_sdk_init()

# add lua
add_subdirectory(lua)

# gadget.c depends on example.lua
set_source_files_properties(gadget.c
    PROPERTIES OBJECT_DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/example.lua"
)

# rest of your project
add_executable(lua_gadget
    gadget.c
    lcd.c
    stubs.c
    lua_lcd.c
)

# Add pico_stdlib library which aggregates commonly used features
target_link_libraries(lua_gadget pico_stdlib pico_stdio hardware_i2c lua)
target_include_directories(lua_gadget PUBLIC .)

pico_add_extra_outputs(lua_gadget)
pico_enable_stdio_usb(lua_gadget 1)
