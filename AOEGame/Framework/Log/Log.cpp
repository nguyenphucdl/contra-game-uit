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

		string __trace_file = LogConfig::outPath;

		FILE *f = stderr;
		if (fopen_s(&f, __trace_file.c_str(), "a") != 0)
		{
			fprintf(stderr, "WARNING: Failed to open trace file '%s' for writing!\n", __trace_file);
			return;
		}

		if (Log::isDebug())
		{
			fprintf_s(f, "<Error>");
			fprintf_s(f, buffer);
			fprintf_s(f, "</Error>\n");
		}

		if (__trace_file.c_str() != NULL)
			fclose(f);
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

	void Log::start()
	{
		string __trace_file = LogConfig::outPath;

		FILE *f = stderr;
		if (fopen_s(&f, __trace_file.c_str(), "w") != 0)
		{
			fprintf(stderr, "WARNING: Failed to open trace file '%s' for writing!\n", __trace_file);
			return;
		}

		if (__trace_file.c_str() != NULL)
			fclose(f);
	}

	void Log::printComponentIDs()
	{
		string __trace_file = LogConfig::outPath;

		FILE *f = stderr;
		if (fopen_s(&f, __trace_file.c_str(), "a") != 0)
		{
			fprintf(stderr, "WARNING: Failed to open trace file '%s' for writing!\n", __trace_file);
			return;
		}

		if (Log::isDebug())
		{
			fprintf_s(f, "<ComponentIDs>\n");
			fprintf_s(f, "   <RenderableComponent id=%d />\n   <TransformComponent id=%d />\n", RenderableComponent::GetId(), TransformComponent::GetId());
			fprintf_s(f, "   <TileMapComponent id=%d />\n   <CameraComponent id=%d />\n", TileMapComponent::GetId(), CameraComponent::GetId());
			fprintf_s(f, "   <SpriteComponent id=%d />\n   <StaticComponent id=%d />\n", SpriteComponent::GetId(), StaticComponent::GetId());
			fprintf_s(f, "</ComponentIDs>\n");
		}

		if (__trace_file.c_str() != NULL) 
			fclose(f);
	}

	void Log::printMapEvents()
	{
		/*string __trace_file = LogConfig::outPath;

		FILE *f = stderr;
		if (fopen_s(&f, __trace_file.c_str(), "a") != 0)
		{
			fprintf(stderr, "WARNING: Failed to open trace file '%s' for writing!\n", __trace_file);
			return;
		}

		string eventName[20] = { };
		eventName[Events::KEY_DOWN_EVENT] = "KEY_DOWN_EVENT";
		eventName[Events::KEY_UP_EVENT] = "KEY_UP_EVENT";
		eventName[Events::POST_RENDER_EVENT] = "POST_RENDER_EVENT";
		eventName[Events::POST_UPDATE_EVENT] = "POST_UPDATE_EVENT";
		eventName[Events::PRE_RENDER_EVENT] = "PRE_RENDER_EVENT";
		eventName[Events::PRE_UPDATE_EVENT] = "PRE_UPDATE_EVENT";
		eventName[Events::RENDER_EVENT] = "RENDER_EVENT";
		eventName[Events::UPDATE_EVENT] = "UPDATE_EVENT";
		eventName[Events::PLAYER_JUMP_EVENT] = "PLAYER_JUMP_EVENT";
		eventName[Events::COLLISION_EVENT] = "COLLISION_EVENT";


		if (Log::isDebug())
		{
			

			//fprintf_s(f, "<EventMap>\n");
			//EventManager::EventMap* eventMap = &EventManager::GetSingletonPtr()->m_eventMap;
			//for (EventManager::EventMapIterator iter = eventMap->begin(); iter != eventMap->end(); ++iter)
			//{
				//Event* pEvent = iter->second;
				
				//fprintf_s(f, "	<Event id=%d name=%s reference=%d />\n", pEvent->GetID(), eventName[pEvent->GetID()].c_str(), pEvent->m_listeners.size());
				
			//}
			//fprintf_s(f, "<EventMap>\n");
			
		}

		if (__trace_file.c_str() != NULL)
			fclose(f);*/
	}

	bool Log::isDebug()
	{
		bool isDebug = LogConfig::outToFile;

		return isDebug;
	}

}