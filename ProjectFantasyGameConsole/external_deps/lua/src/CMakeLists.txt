cmake_minimum_required(VERSION 3.23)
project(FantasyGameConsoleProject)

SET(LUA_LIB_SOURCE
    lapi.c lcode.c lctype.c ldebug.c ldo.c ldump.c 
    lfunc.c lgc.c llex.c lmem.c lobject.c lopcodes.c 
    lparser.c lstate.c lstring.c ltable.c ltm.c lundump.c 
    lvm.c lzio.c lauxlib.c lbaselib.c lcorolib.c ldblib.c 
    liolib.c lmathlib.c loadlib.c loslib.c lstrlib.c 
    ltablib.c lutf8lib.c linit.c)

add_library(lua STATIC ${LUA_LIB_SOURCE})
target_include_directories(lua 
    PUBLIC ../include
    PRIVATE .)
