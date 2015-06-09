#include <string>
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include "../Lib/rapidxml-1.13/rapidxml.hpp"
#include "../TileMap/TileMap.h"
#include "../TileMap/TileSet.h"
#include "../GamePlay/SceneBase.h"

using namespace rapidxml;
using namespace std;

namespace Framework
{
	class TmxLoader 
	{
	public:
		TmxLoader(std::string& file);
		~TmxLoader();

		bool Load();
		TileMap* GetTileMap();
		float	 GetScaleRatio();

	private:
		bool _checkValid();
		bool _parseMap();
	
		

	private:
		std::string			m_file;
		std::string			m_basePath;
		float				m_scaleRatio;
		TileMap *			m_tileMap;
		vector<TileSet*>*	m_tileSets;
		xml_document<>		m_doc;
		xml_node<> *		m_rootNode;
		
		
	};
}