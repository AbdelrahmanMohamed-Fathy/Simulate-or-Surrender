#pragma once
#include <cstdlib>
#include <time.h>

static int GenerateNumber(int min=0, int max=100)
{
    return min + (rand() % (max - min + 1));
}