#include "CResCache.h"

#include <direct.h>

// 0x8FB928
CString CResCache::DEFAULT_CACHE_DIRECTORY("hd0:\\cache\\");

// #binary-identical
// 0x78BF50
CResCache::CResCache()
{
    getcwd(workingDirectory, sizeof(workingDirectory));
    field_108 = DEFAULT_CACHE_DIRECTORY;
    field_110 = 0;
    field_11C = 175000000;
    field_120 = 175000000;
    field_114 = 0;
    field_118 = 0;
    field_124 = 0;
    field_0 = 0;
    InitializeCriticalSection(&criticalSection);
}

// 0x78C020
CResCache::~CResCache()
{
    EnterCriticalSection(&criticalSection);

    // TODO: Incomplete.

    LeaveCriticalSection(&criticalSection);
    DeleteCriticalSection(&criticalSection);
}
