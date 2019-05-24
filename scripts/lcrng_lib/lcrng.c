#include <stdio.h>
#include <stdint.h>

#include <lua.h>                          
#include <lauxlib.h>                           
#include <lualib.h>   

static uint32_t _lcrng(uint32_t seed){
	return (uint32_t)(0x41C64E6DULL*((uint64_t)seed) + 0x00006073ULL);
}

static int lcrng(lua_State* L){
	uint32_t seed = (uint32_t)lua_tointeger(L, 1);
	lua_pushnumber(L, _lcrng(seed));
	return 1;
}

int luaopen_lcrng(lua_State *L){
	lua_register(L, "lcrng", lcrng);
	
	return 0;
}