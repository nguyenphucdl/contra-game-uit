#ifndef __GAMEPLAY_H__
#define __GAMEPLAY_H__

#include "../Application/Context.h"
#include "../EventManager/EventExecutor.h"
#include "../GameState/GameState.h"
#include "../GameObjects/GameObject.h"
#include "SceneBase.h"
#include "TileMapScene.h"

namespace Framework
{
	class GamePlay
		: public GameState
	{
	private:
		std::stack<SceneBase*>  m_scenes;



		TileMapScene* m_tileMapScene;//Test
		TileMapScene* m_scene2;
	public:
		GamePlay();
		~GamePlay();

		void Init();
		void Update();
		void Draw();
		void Pause();
		void Resume();

		void Entered();
		void Leaving();
		void Obscuring();
		void Revealed();
	};
}
#endif 