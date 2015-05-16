#include "AnimCache.h"
#include <set>
#include "Utils.h"
#include "../Renderer/Texture/TextureManager.h"
#include "../Log/Log.h"

namespace Framework
{
	AnimCache::AnimCache(std::string file)
		: m_file(file)
	{
		m_propList = map<string, FrameInfo*>();
		m_basePath = Utils::getPathOfFile(file);
	}

	AnimCache::~AnimCache()
	{
		
	}

	bool AnimCache::Load()
	{
		//check file valid

		//Read the xml file into a vector
		ifstream theFile(m_file.c_str());
		if (theFile.fail())
		{
			Log::error("[Property][Load] Error to load file [%s]!", m_file.c_str());
			return false;
		}

		vector<char> buffer((istreambuf_iterator<char>(theFile)), istreambuf_iterator<char>());
		buffer.push_back('\0');
		// Parse the buffer using the xml file parsing library into doc 
		xml_document<> m_doc;
		m_doc.parse<0>(&buffer[0]);
		xml_node<>* m_rootNode = m_doc.first_node("plist");
		if (m_rootNode == NULL)
			return false;

		// FRAMES DICT
		xml_node<>* root_dict = m_rootNode->first_node("dict")->first_node("dict");

		char* keyName;
		int f_x, f_y, f_width, f_height, f_column = 0;
		for (xml_node<> *node = root_dict->first_node(); node; node = node->next_sibling())
		{
			char* nodeName = node->name();
			if (strcmp(nodeName, "key") == 0)
			{
				keyName = node->value();
			}
			else//node dict
			{
				char* subKeyName;
				int f_x, f_y, f_width, f_height, f_column = 0, f_row = 0;
				for (xml_node<>* sub_node = node->first_node(); sub_node; sub_node = sub_node->next_sibling())
				{
					char* subNodeName = sub_node->name();
					if (strcmp(sub_node->name(), "key") == 0)
					{
						subKeyName = sub_node->value();
					}
					else//string node
					{
						if (strcmp(subKeyName, "frame") == 0)//string value of key frame
						{
							char* frameValue = sub_node->value();
							char* match;
							match = strtok(frameValue, "{},");
							int valueArr[4] = {-1, -1, -1, -1};
							int idx = 0;
							if (match != NULL)
							{
								valueArr[idx] = stoi(match);
								while (match = strtok(NULL, "{},"))
								{
									idx++;
									valueArr[idx] = stoi(match);
								}
							}
							if (idx != 3)//Error
							{
								Log::error("[Property][Load] Error to parse node value[%s] from [%s] of [%s]!", sub_node->name(), subKeyName ,keyName);
								return false;
							}

							f_x = valueArr[0];
							f_y = valueArr[1];
							f_width = valueArr[2];
							f_height = valueArr[3];
						}//end if node string of frame
						else if (strcmp(subKeyName, "column") == 0){
							f_column = stoi(sub_node->value());
						}
						else if (strcmp(subKeyName, "row") == 0) {
							f_row = stoi(sub_node->value());
						}
						else if (strcmp(subKeyName, "rotated") == 0){

						}//...
					}
				}//end node value of dict
				FrameInfo *fr = new FrameInfo(keyName, f_x, f_y, f_width, f_height, f_column, f_row);
				m_propList[keyName] = fr;
			}
		}//end for traverse node
		
		//Register texture
		m_sheetName = Utils::getNameWithoutExt(m_file) + ".png";
		std::string textureFile = m_basePath + "\\" + m_sheetName;
		RegisterTexture(textureFile);
		//Texture* sheet = GetTexture("texture.png");
		//int i = 3;
		//m_it = m_propList.find("Rockman-Running.png");
		//std::string key = m_it->first;
		//FrameInfo* val = m_it->second;

	}

	FrameInfo* AnimCache::getFrameInfo(std::string state)
	{
		m_it = m_propList.find(state);
		if (m_it != m_propList.end())
		{
			return m_it->second;
		}
		return NULL;
	}
}