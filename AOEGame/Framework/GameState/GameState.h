#ifndef __GAMESTATE_H__
#define __GAMESTATE_H__

namespace Framework
{
	class GameState
	{
	private:

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