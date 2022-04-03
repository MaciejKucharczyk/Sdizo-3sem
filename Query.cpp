#include <iostream>
#include <iomanip>
#include <windows.h>

long long int read_QPC() // funkcja mierzaca czas algorytmu
{
    LARGE_INTEGER count;
    QueryPerformanceCounter(&count);
    return((long long int)count.QuadPart);
}

long long int frequency, start, elapsed;