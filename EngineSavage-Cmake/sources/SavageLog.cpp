#include "SavageLog.h"

#define SAVAGE_LOGMODE_CONSOLE 1

uint g_savage_log_mode = SAVAGE_LOGMODE_CONSOLE;

void SetLogMode(uint mode)
{
	g_savage_log_mode = mode;
}

uint GetLogMode()
{
	return g_savage_log_mode;
}

void SavageLog(const char* format, ...)
{
	va_list va;
	va_start(va, format);
	if (g_savage_log_mode & SAVAGE_LOGMODE_CONSOLE)
#ifdef _WIN32
		vprintf_s(format, va);
#else
		vprintf(format, va);
#endif
}
