#pragma once

#define DELETED 0
#define NORMAL 1
#define LOCK 2

struct Point
{
	int x = 0;				
	int y = 0;				
	int status = NORMAL;
	int poke = 0;
};