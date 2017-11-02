#include "stdafx.h"
#include "int3.h"


int3::int3() : x(0), y(0), z(0)
{ }

int3::int3(int value) : x(value), y(value), z(value)
{ }

int3::int3(int x, int y, int z) : x(x), y(y), z(z)
{ }

int3::~int3()
{ }
