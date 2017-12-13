#include "stdafx.h"
#include "Data.h"

Data::~Data()
{
}

Data & Data::Instance()
{
    static Data instance;
    return instance;
}