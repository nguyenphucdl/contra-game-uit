#include "SceneBase.h"
#include "../Utilities/TmxLoader.h"
#include "../Quadtree/QuadtreeLoader.h"

namespace Framework
{
	SceneBase::SceneBase()
	{
		
	}

	SceneBase::~SceneBase()
	{
	}

	bool SceneBase::LoadSceneFromFile(std::string file)
	{
		TmxLoader *tmxLoader = new TmxLoader(file);
		bool res = tmxLoader->Load();

		if (!res)
			return false;

		m_tileMap = tmxLoader->GetTileMap();
		m_tileMap->Init();

		float mapScale = tmxLoader->GetScaleRatio();

		QuadtreeLoader* quadtreeLoader = new QuadtreeLoader(file);
		quadtreeLoader->SetScaleRatio(mapScale);
		res = quadtreeLoader->Load();

		m_objectTable = tmxLoader->GetObjectHashTable();
	}
}