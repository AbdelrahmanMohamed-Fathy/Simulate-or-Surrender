#include <cstdlib>
#include <time.h>

int GenerateNumber(int min=0, int max=100)
{
    return min + ( rand() % (max-min+1) );
}