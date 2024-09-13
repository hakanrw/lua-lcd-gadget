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
    PROPERTIES OBJECT_DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/lua/main.lua"
)

file(GLOB LUA_FILES "${CMAKE_CURRENT_SOURCE_DIR}/lua/*.lua")

# Create a list to store Lua file names without the extension
set(LUA_FILES_WITHOUT_EXT "")

# Loop through the Lua files and remove the extension
foreach(LUA_FILE ${LUA_FILES})
    # Get the filename without the directory and extension
    get_filename_component(LUA_FILE_WE ${LUA_FILE} NAME_WE)
    # Append the filename without extension to the list
    list(APPEND LUA_FILES_WITHOUT_EXT ${LUA_FILE_WE})
endforeach()

# Convert the list to a semicolon-separated string
string(REPLACE ";" ", " LUA_FILES_STR "${LUA_FILES_WITHOUT_EXT}")

set_source_files_properties(modules.c
    PROPERTIES OBJECT_DEPENDS "${LUA_FILES}"
)

# Pass the list of Lua files without extension to the compiler as a definition
add_definitions(-DLUA_FILES=${LUA_FILES_STR})

# Print the collected filenames without extension
message(STATUS "Lua files (without extension): ${LUA_FILES_STR}")

# rest of your project
add_executable(lua_gadget
    gadget.c
    lcd.c
    stubs.c
    lua_lcd.c
    modules.c
)

# Add pico_stdlib library which aggregates commonly used features
target_link_libraries(lua_gadget pico_stdlib pico_stdio hardware_i2c lua)
target_include_directories(lua_gadget PUBLIC .)

pico_add_extra_outputs(lua_gadget)
pico_enable_stdio_usb(lua_gadget 1)
