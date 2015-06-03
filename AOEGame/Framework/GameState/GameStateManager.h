#ifndef __GAMESTATE_MANAGER_H__
#define __GAMESTATE_MANAGER_H__

#include "../Application/Context.h"
#include "../Kernel/Task.h"
#include "GameState.h"


namespace Framework
{
	class GameStateManager
		: public Task
	{
	private:
		//std::stack<GameState*>	m_currentStates;
		//std::vector<Drawable*>	m_activeDrawables;
		//std::vector<Updateable*> m_activeUpdateables;
	public:
		GameStateManager();
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
	};
}
#endif