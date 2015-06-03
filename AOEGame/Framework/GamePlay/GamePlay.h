#ifndef __GAMEPLAY_H__
#define __GAMEPLAY_H__

#include "../Application/Context.h"
#include "../EventManager/EventExecutor.h"
#include "../GameState/GameState.h"
#include "SceneBase.h"

namespace Framework
{
	class GamePlay
		: public GameState
	{
	public:
		GamePlay();
		~GamePlay();

	private:
		std::stack<SceneBase*>  m_scenes;

		virtual void Entered();
		virtual void Leaving();
		virtual void Obscuring();
		virtual void Revealed();
	};
}
#endif 