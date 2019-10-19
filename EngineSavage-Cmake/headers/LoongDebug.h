#pragma once
#include<cstdio>
#include <cstdarg>
#ifdef _DEBUG
#define LOONG_DEBUG
#define LoongDebug(format,...) LoongDebugLog(format,__VA_ARGS__)
void LoongDebugLog(const char* format, ...);
#else
#define LoongDebug(format,...) ((void)0)
#endif // _DEBUG
