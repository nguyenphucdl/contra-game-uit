#ifndef __GAMEPLAY1_H__
#define __GAMEPLAY1_H__

#include "Framework\Kernel\Task.h"
#include "Framework\Utilities\Timer.h"
#include "Framework\Renderer\Texture\TextureManager.h"
#include "Framework\EventManager\EventManager.h"
#include "Framework\GameObjects\GameObject.h"
#include "Framework\GameObjects\Components\RenderableComponent.h"
#include "Framework\GameObjects\Components\CameraComponent.h"
#include "Framework\GameObjects\Components\TileMapComponent.h"
#include "Framework\GameObjects\Actions\Animation.h"
#include "Framework\GameObjects\Components\CollisionComponent.h"


class GamePlay1
	: public Framework::Task
	, public Framework::EventHandler
{
private:
	Framework::GameObject	m_playerObject;
	Framework::GameObject	m_npc1;

	Framework::GameObject	m_tileMapObject;
	Framework::GameObject	m_cameraObject;
	Framework::GameObject	m_contraObject;
	Framework::GameObject	m_contraFinalObject;

	vector<Framework::GameObject*>*	m_objects;
	vector<Framework::GameObject*>::iterator m_objIt;

	Framework::CollisionComponent*		m_pPlayerCollisionComponent;
	Framework::CollisionComponent*		m_npc1CollisionComponent;
public:
	GamePlay1(const unsigned int priority);
	virtual ~GamePlay1();

	virtual void HandleEvent(Framework::Event* pEvent);

	// From Task
	virtual bool	Start();
	virtual void	OnSuspend();
	virtual void	Update();
	virtual void	OnResume();
	virtual void	Stop();
};

#endif//__GAMEPLAY1_H__