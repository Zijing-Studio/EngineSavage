#include "LoongDebug.h"

void LoongDebugLog(const char* format, ...)
{
	va_list va;
	va_start(va, format);
#ifdef _WIN32
		vprintf_s(format, va);
#else
		vprintf(format, va);
#endif
	printf("\n");
}
