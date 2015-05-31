#include "QuadtreeLoader.h"
#include <unordered_map>

using namespace std;
using namespace rapidxml;

namespace Framework
{
	QuadtreeLoader::QuadtreeLoader(std::string file)
		: m_file(file)
		, m_quadtree(NULL)
		, m_mapScaleRatio(1.0f)
	{
	}

	QuadtreeLoader::~QuadtreeLoader()
	{
	}

	Quadtree* QuadtreeLoader::GetQuadTree()
	{
		return m_quadtree;
	}

	bool QuadtreeLoader::Load()
	{
		// check file valids
		// Read the xml file into a vector
		ifstream theFile(m_file.c_str());
		if (theFile.fail())
			return false;
		vector<char> buffer((istreambuf_iterator<char>(theFile)), istreambuf_iterator<char>());
		buffer.push_back('\0');
		// Parse the buffer using the xml file parsing library into doc 
		m_doc.parse<0>(&buffer[0]);
		m_rootNode = m_doc.first_node("map");
		xml_node<>* quadtreeNode = m_rootNode->first_node("quadtree");
		if (quadtreeNode == NULL)
		{
			Log::error("Cannot load quadtree node!");
			exit(0);
		}
			

		int x = atoi(quadtreeNode->first_attribute("x")->value());
		int y = atoi(quadtreeNode->first_attribute("y")->value());
		int width = atoi(quadtreeNode->first_attribute("width")->value());
		int height = atoi(quadtreeNode->first_attribute("height")->value());

		Quadtree* quadtree = new Quadtree(0, Rect(x, y, width * m_mapScaleRatio, height * m_mapScaleRatio));

		//Parse quadtree elements
		xml_node<> *data = quadtreeNode->first_node("data");
		xml_node<> *node, *objectDataNode;
		int id, parent_id, level;
		char* dataString = NULL;
		char* matchStrtok = NULL;
		std::vector<int>* objectDatas = NULL;
		Quadtree* currentNode = quadtree;

		for (node = data->first_node("node"); node; node = node->next_sibling())
		{
			id = atoi(node->first_attribute("id")->value());
			parent_id = atoi(node->first_attribute("parent")->value());
			level = atoi(node->first_attribute("level")->value());

			objectDataNode = node->first_node("objects");
			objectDatas = NULL;
			if (objectDataNode != NULL)
			{
				objectDatas = new std::vector<int>();
				dataString = objectDataNode->first_attribute("data")->value();
				matchStrtok = strtok(dataString, ",");
				while(matchStrtok != NULL)
				{
					objectDatas->push_back(atoi(matchStrtok));
					matchStrtok = strtok(NULL, ",");
				}
			}
			currentNode = currentNode->InitNodeData(id, parent_id, level, objectDatas);
		}
		while (currentNode != NULL)
		{
			m_quadtree = currentNode;
			currentNode = currentNode->GetParent();
		}
		
		return true;
	}
}