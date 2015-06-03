#ifndef __SCENE_BASE_H__
#define __SCENE_BASE_H__

#include "../Application/Context.h"
#include "../Quadtree/Quadtree.h"
#include "../TileMap/TileMap.h"

namespace Framework
{
	class SceneBase
	{
	public:
		typedef std::unordered_map<int, GameObject*> ObjectHashTable;
		typedef ObjectHashTable::iterator			 ObjectHashTableIterator;

		SceneBase();
		~SceneBase();

	private:
		ObjectHashTable*	m_objectTable;
		Quadtree*			m_quadtree;
		TileMap*			m_tileMap;

		
	public:
		bool LoadSceneFromFile(std::string file);

		virtual void Init() = 0;
		virtual void Update() = 0;
		virtual void Draw() = 0;
		virtual void Pause() = 0;
		virtual void Resume() = 0;
	};
}
#endif