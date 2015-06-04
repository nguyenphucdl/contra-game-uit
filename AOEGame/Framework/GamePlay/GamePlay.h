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

		GameObject*	m_pPlayerObject;
		GameObject* m_pCameraObject;

		TileMapScene* m_tileMapScene;//Test
	public:
		GamePlay();
		~GamePlay();

		void Load();
		void Initialize();

		void Entered();
		void Leaving();
		void Obscuring();
		void Revealed();
	};
}
#endif 