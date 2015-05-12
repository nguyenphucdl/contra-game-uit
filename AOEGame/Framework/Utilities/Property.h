#ifndef __PROPERTY_H__
#define __PROPERTY_H__

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
	class Property
	{
	public:
		Property(std::string file);
		~Property();

		bool Load();

	private:
		std::string			m_file;
		std::string			m_basePath;
		xml_document<>		m_doc;
		xml_node<>*			m_rootNode;

		
		map<string, FrameInfo*> m_propList;
	};
}
#endif//__GAMEPLAY1_H__