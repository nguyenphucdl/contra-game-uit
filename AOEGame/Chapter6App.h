#ifndef __CHAPTER6APP_H__
#define __CHAPTER6APP_H__

#include "Framework\Application\Game.h"
#include "Chapter6Task.h"
#include "GamePlay1.h"

using namespace Framework;

class Chapter6App
	: public Game
{
private:
	//Chapter6Task	m_testGameTask;
	GamePlay1 m_testGameTask;

public:
	explicit Chapter6App();
	virtual ~Chapter6App();

	virtual bool Initialize();
};

#endif//__CHAPTER6APP_H__