#ifndef __GAMESTATE_H__
#define __GAMESTATE_H__

#include "../Application/Context.h"

namespace Framework
{
	class GameState
	{
	protected:
		D3DXMATRIX m_transitionMaxtrix;
	public:
		GameState();
		~GameState();

		virtual void Entered() = 0;
		virtual void Leaving() = 0;
		virtual void Obscuring() = 0;
		virtual void Revealed() = 0;
	};
}
#endif