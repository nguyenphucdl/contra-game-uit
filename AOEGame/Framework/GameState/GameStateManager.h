#ifndef __GAMESTATE_MANAGER_H__
#define __GAMESTATE_MANAGER_H__

#include "../Application/Context.h"
#include "../Kernel/Task.h"
#include "../EventManager/EventHandler.h"
#include "../GamePlay/GamePlay.h"



namespace Framework
{
	class GameStateManager
		: public Task
		, public EventHandler

	{
	private:
		GamePlay*	m_currentGamePlay;
		bool		m_paused;
		//std::stack<GameState*>	m_currentStates;
		//std::vector<Drawable*>	m_activeDrawables;
		//std::vector<Updateable*> m_activeUpdateables;
	public:
		GameStateManager(const unsigned int priority);
		~GameStateManager();

		
		void			Switch(GameState* state);
		GameState*		Pop();
		void			Push(GameState* state);
		GameState*		Peek();

		// From Task
		virtual bool	Start();
		virtual void	OnSuspend();
		virtual void	Update();
		virtual void	OnResume();
		virtual void	Stop();

		virtual void HandleEvent(Event* pEvent);
	};
}
#endif