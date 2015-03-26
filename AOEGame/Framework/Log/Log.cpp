#include "Log.h"
#include "../Utilities/GameConfig.h"
#include "../GameObjects/Components/RenderableComponent.h"//TEST
#include "../GameObjects/Components/TransformComponent.h"
#include "../GameObjects/Components/CameraComponent.h"
#include "../GameObjects/Components/SpriteComponent.h"
#include "../GameObjects/Components/TileMapComponent.h"
#include "../GameObjects/Components/StaticComponent.h"

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

	void Log::printComponentIDs()
	{
		if (Log::isDebug())
		{
			string logPath = LogConfig::outPath;

			std::filebuf fb;
			fb.open(logPath, std::ios::out);
			std::ostream os(&fb);
			os << "<ComponentIDs>" << endl;
			os << "RenderableComponent(" << RenderableComponent::GetId() << ") TransformComponent(" << TransformComponent::GetId() << ") ";
			os << "TileMapComponent(" << TileMapComponent::GetId() << ") CameraComponent(" << CameraComponent::GetId() << ") ";
			os << "SpriteComponent(" << SpriteComponent::GetId() << ") StaticComponent(" << StaticComponent::GetId() << ") ";
			os << endl << "</ComponentIDs>";
			fb.close();
		}
	}
	bool Log::isDebug()
	{
		bool isDebug = LogConfig::outToFile;

		return isDebug;
	}

}