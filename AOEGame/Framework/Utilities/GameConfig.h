#ifndef __GAME_CONFIG_H__
#define __GAME_CONFIG_H__
#define WIN32_LEAN_AND_MEAN 

#include <map>
#include "Singleton.h"
#include <string>
#include <algorithm>

namespace Framework
{
	typedef std::string		config_str;
	class GameConfig : public Singleton<GameConfig>
	{
	public:
		
		typedef std::map<config_str, config_str>		ConfigDictionary;
		typedef std::pair<config_str, config_str>		ConfigDictionaryPair;
		typedef	ConfigDictionary::iterator				ConfigDictionaryIterator;
	private:
		ConfigDictionary			m_configDict;


	public:
		explicit GameConfig();
		explicit GameConfig(const char* file);
		virtual ~GameConfig();

		bool				TryGetInt(config_str key, int &value);					// Try parse the value to int
		bool				TryGetFloat(config_str key, float &value);				// Try parse the value to float
		bool				TryGetString(config_str key, config_str &value);		// Try parse the value to string
		bool				TryGetBool(config_str key, bool &value);			// Try parse the value to bool	

		int					GetInt(config_str key);
		float				GetFloat(config_str key);
		bool				GetBool(config_str key);
		config_str			Get(config_str key);									// Get value of specified key
		bool				IsExist(config_str key);								// Check if an specified key exist ?
		

	public:
		static void LoadConfig();
		static void LoadConfig(const char* xmlFile);
	};
}
#endif