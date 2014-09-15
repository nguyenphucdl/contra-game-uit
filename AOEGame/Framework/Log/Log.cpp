#include "Log.h"


namespace Framework
{
	const int Log::LOG_LEVEL_ROOT = 10;
	const int Log::LOG_LEVEL_SUPER = 50;
	const int Log::LOG_LEVEL_HIGHT = 100;
	const int Log::LOG_LEVEL_MEDIUM = 300;
	const int Log::LOG_LEVEL_LOW = 600;
	const int Log::LOG_LEVEL_NORMAL = 1000;

	// User log level
	int Log::LOG_LEVEL_MIN = Log::LOG_LEVEL_MEDIUM;
	int Log::LOG_LEVEL_MAX = Log::LOG_LEVEL_ROOT;

	void Log::error(Log_Str pMessage, ...)
	{
		char buffer[256];
		va_list lVarArgs;
		va_start(lVarArgs, pMessage);
		vsprintf_s ( buffer, 256, pMessage, lVarArgs );
		fputs(buffer, stdout);
		va_end(lVarArgs);
	}

	void Log::info(int level, Log_Str pMessage, ...)
	{
		if(level < Log::LOG_LEVEL_MAX || level > LOG_LEVEL_MIN)
			return;		

		char farr[25];
		sprintf(farr, "L%d", level);
		std::string format = std::string(pMessage);
		format.insert(0, std::string(farr));

		char buffer[256];
		va_list lVarArgs;
		va_start(lVarArgs, pMessage);
		/*sprintf_s ( buffer, 256, format, lVarArgs );*/
		vsprintf_s(buffer, 256, format.c_str(), lVarArgs );
		fputs ( buffer, stdout );
		va_end(lVarArgs);

	}

	void Log::warn(int level, Log_Str pMessage, ...)
	{
		char buffer[256];
		va_list lVarArgs;
		va_start(lVarArgs, pMessage);
		vsprintf_s ( buffer, 256, pMessage, lVarArgs );
		fputs ( buffer, stdout );
		va_end(lVarArgs);
	}
	
	void Log::debug(int level, Log_Str pMessage, ...)
	{
		char buffer[256];
		va_list lVarArgs;
		va_start(lVarArgs, pMessage);
		vsprintf_s ( buffer, 256, pMessage, lVarArgs );
		fputs ( buffer, stdout );
		va_end(lVarArgs);
	}
}