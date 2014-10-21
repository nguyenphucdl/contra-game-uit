#include "GameConfig.h"
#include "Constants.h"
namespace Framework
{
	

	GameConfig::GameConfig() 
	{
		m_configDict.insert(ConfigDictionaryPair("TestFloat1", "2.3f"));
		m_configDict.insert(ConfigDictionaryPair("TestFloat2", "2.3"));		
		m_configDict.insert(ConfigDictionaryPair(ConfigKey::GAME_WIDTH, "640"));
		m_configDict.insert(ConfigDictionaryPair(ConfigKey::GAME_HEIGHT, "480"));
		m_configDict.insert(ConfigDictionaryPair(ConfigKey::FULLSCREEN, "0"));
		m_configDict.insert(ConfigDictionaryPair(ConfigKey::CLASS_NAME, "Spacewar"));
		m_configDict.insert(ConfigDictionaryPair(ConfigKey::GAME_TITLE, "Spacewar"));
	}
	
	GameConfig::GameConfig(const char* file)
	{
	}

	GameConfig::~GameConfig() 
	{
	}

	void GameConfig::LoadConfig()
	{
		new GameConfig();
	}

	void GameConfig::LoadConfig(const char* xmlFile)
	{
		new GameConfig(xmlFile);
	}

	bool GameConfig::IsExist(config_str key)
	{
		ConfigDictionaryIterator result =  m_configDict.find(key);
		if(result != m_configDict.end())
			return true;
		return false;
	}

	bool GameConfig::TryGetInt(config_str key, int &value)
	{
		ConfigDictionaryIterator result =  m_configDict.find(key);
		if(result == m_configDict.end())
			return false;
		if(strcmp(result->second.c_str(), "") == 0)
		{
			value = 0;
		}
		else
		{
			int check = atoi(result->second.c_str());
			if(check == 0)
				return false;
			value = check;
		}
		return true;
	}

	bool GameConfig::TryGetFloat(config_str key,float &value)
	{
		ConfigDictionaryIterator result =  m_configDict.find(key);
		if(result == m_configDict.end())
			return false;
		if(strcmp(result->second.c_str(), "0.0") == 0)
		{
			value = 0.0;
		}
		else
		{
			float check = atof(result->second.c_str());
			if(check == 0.0)
				return false;
			value = check;
		}
		return true;
	}

	bool GameConfig::TryGetBool(config_str key, bool &value)
	{
		ConfigDictionaryIterator result = m_configDict.find(key);
		if(result == m_configDict.end())
			return false;
		config_str val = result->second;
		std::transform(val.begin(), val.end(), val.begin(), ::tolower);
		if((val.compare("true") == 0) || val.compare("1") == 0)
		{
			value = true;
			return true;
		}
		else if((val.compare("false") == 0) || (val.compare("0") == 0))
		{
			value = false;
			return true;
		}
		// Else
		return false;
	}

	bool GameConfig::TryGetString(config_str key,config_str &value)
	{
		ConfigDictionaryIterator result =  m_configDict.find(key);
		if(result == m_configDict.end())
			return false;
		value = result->second;
		return true;
	}

	int GameConfig::GetInt(config_str key)
	{
		int val;
		if(TryGetInt(key, val))
		{
			return val;
		}
		return -999;
	}

	float GameConfig::GetFloat(config_str key)
	{
		float val;
		if(TryGetFloat(key, val))
		{
			return val;
		}
		return -999.9f;
	}

	config_str GameConfig::Get(config_str key)
	{
		config_str val;
		if(TryGetString(key, val))
		{
			return val;
		}
		return "";
	}

	bool GameConfig::GetBool(config_str key)
	{
		bool val;
		if(TryGetBool(key, val))
		{
			return val;
		}
		return false;
	}
}