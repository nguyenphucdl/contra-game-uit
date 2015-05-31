#ifndef __QUADTREE_LOADER_H__
#define	__QUADTREE_LOADER_H__

#include <string>
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include "../Lib/rapidxml-1.13/rapidxml.hpp"
#include "Quadtree.h"

namespace Framework
{
	class QuadtreeLoader
	{
	public:
		QuadtreeLoader(std::string file);
		~QuadtreeLoader();

		bool		Load();
		Quadtree*	GetQuadTree();

		void		SetScaleRatio(float scale)	{ m_mapScaleRatio = scale; }
		float		GetScaleRatio()				{ return m_mapScaleRatio; }
	private:
		std::string			m_file;
		rapidxml::xml_document<>		m_doc;
		rapidxml::xml_node<> *			m_rootNode;
		float							m_mapScaleRatio;

		Quadtree*	m_quadtree;
	};
}
#endif
