#include "stdafx.h"
#include "lua_bit.h"

 
int AndL(int luaL_checkintegerf, int luaL_checkintegers)
{
	unsigned int first = luaL_checkintegerf;
	unsigned int second = luaL_checkintegers;
    return first & second;
}
int OrL(int luaL_checkintegerf, int luaL_checkintegers)
{
	unsigned int first = luaL_checkintegerf;
	unsigned int second = luaL_checkintegers;
	return first | second;
}

int RShiftL(int luaL_checkintegerf, int luaL_checkintegers)
{
	unsigned int first = luaL_checkintegerf;
	unsigned int second = luaL_checkintegers;
	return first >> second;
}

int LShiftL(int luaL_checkintegerf, int luaL_checkintegers)
{
	unsigned int first = luaL_checkintegerf;
	unsigned int second = luaL_checkintegers;
	return first << second;
}
