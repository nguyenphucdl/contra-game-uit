#ifndef __CHAPTER6APP_H__
#define __CHAPTER6APP_H__

#include "Framework\Application\Game.h"
#include "Framework\GameState\GameStateManager.h"


using namespace Framework;

class Chapter6App
	: public Game
{
private:

	//GamePlay1 m_testGameTask;
	GameStateManager m_gameStateManager;

public:
	explicit Chapter6App();
	virtual ~Chapter6App();

	virtual bool Initialize();
};

#endif//__CHAPTER6APP_H__