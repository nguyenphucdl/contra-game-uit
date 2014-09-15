#ifndef __LOG_H__
#define __LOG_H__

#include <stdarg.h>
#include <stdio.h>
#include <string>

namespace Framework
{
	class Log
	{
	public:
		typedef const const char*	Log_Str;

		static int LOG_LEVEL_MIN;
		static int LOG_LEVEL_MAX;
	public:
		const static int LOG_LEVEL_ROOT;
		const static int LOG_LEVEL_SUPER;
		const static int LOG_LEVEL_HIGHT;
		const static int LOG_LEVEL_MEDIUM;
		const static int LOG_LEVEL_LOW;
		const static int LOG_LEVEL_NORMAL;

	public:
		static void error(Log_Str pMessage, ...);
		static void warn(int level, Log_Str pMessage, ...);
		static void info(int level, Log_Str pMessage, ...);
		static void debug(int level, Log_Str pMessage, ...);
	};
}

#endif //__LOG_H__