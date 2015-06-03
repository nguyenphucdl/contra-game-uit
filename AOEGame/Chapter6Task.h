#ifndef __CHAPTER6TASK_H__
#define __CHAPTER6TASK_H__

#include "Framework\Kernel\Task.h"
#include "Framework\Utilities\Timer.h"
#include "Framework\Renderer\Texture\TextureManager.h"
#include "Framework\EventManager\EventManager.h"
#include "Framework\GameObjects\GameObject.h"
#include "Framework\GameObjects\Components\RenderableComponent.h"
#include "Framework\GameObjects\Components\CameraComponent.h"
#include "Framework\GameObjects\Components\TileMapComponent.h"
#include "Framework\GameObjects\Actions\Animation.h"
#include "PlayerMovementComponent.h"

using namespace Framework;

class Chapter6Task
	: public Task
	, public EventExecutorAware
	, public EventHandler
{
private:
	Framework::GameObject	m_playerObject;
	Framework::GameObject	m_tileMapObject;
	Framework::GameObject	m_cameraObject;
	Framework::GameObject	m_contraObject;
	Framework::GameObject	m_contraFinalObject;
public:
	Chapter6Task(const unsigned int priority);
	virtual ~Chapter6Task();

	virtual void HandleEvent(Event* pEvent);

	// From Task
	virtual bool	Start();
	virtual void	OnSuspend();
	virtual void	Update();
	virtual void	OnResume();
	virtual void	Stop();
};

#endif//__CHAPTER6TASK_H__