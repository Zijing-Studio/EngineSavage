#include "LoongDebug.h"

void LoongDebugLog(const char* format, ...)
{
	va_list va;
	va_start(va, format);
#ifdef _MSC_VER
		vprintf_s(format, va);
#else
		vprintf(format, va);
#endif
	printf("\n");
}
