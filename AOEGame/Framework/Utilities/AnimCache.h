#ifndef __ANIM_CACHE_H__
#define __ANIM_CACHE_H__

#include <string>
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <map>
#include "../Lib/rapidxml-1.13/rapidxml.hpp"
#include "FrameInfo.h"

using namespace rapidxml;
using namespace std;

namespace Framework
{
	class AnimCache
	{
	public:
		AnimCache(std::string file);
		~AnimCache();

		bool Load();

	private:
		std::string			m_file;
		std::string			m_basePath;
		std::string			m_sheetName;
		//xml_document<>		m_doc;
		//xml_node<>*			m_rootNode;

		
		map<string, FrameInfo*> m_propList;
		map<string, FrameInfo*>::iterator m_it;

	public:
		FrameInfo* getFrameInfo(std::string state);

		std::string getSheetName() { return m_sheetName; }
	};
}
#endif