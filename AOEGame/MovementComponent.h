#ifndef __MOVEMENTCOMPONENT_H__
#define __MOVEMENTCOMPONENT_H__

#include "Framework\Application\Context.h"
#include "Framework\Renderer\Renderer.h"
#include "Framework\GameObjects\Components\RenderableComponent.h"
#include "Framework\Math\Vector3.h"
#include "Framework\GameObjects\GameObject.h"
#include "Framework\GameObjects\Component.h"
#include "Framework\EventManager\EventHandler.h"
#include "Framework\Collision\CollisionListener.h"


class MovementComponent
	:	public	Framework::Component
	,   public	Framework::EventHandler
	,   public  Framework::CollisionListener
{
private:
	static const unsigned int s_id = Framework::ComponentIDs::MovementComponentId;

	Framework::Transform*	m_transform;

	Framework::SpriteStates		m_currentState;
	Framework::SpriteDirections	m_currentDirection;

	Framework::Vector3			m_velocity;
	Framework::Vector3			m_acceleration;

	float				m_floor;
	bool				m_isSupported;
	float				m_offset[4];
	Framework::Vector3				m_vectorOffset;

public:
	static unsigned int GetId() { return s_id; }

	explicit MovementComponent(Framework::GameObject* pOwner);
	virtual ~MovementComponent();

	bool	AttachRenderableTransform(Framework::RenderableComponent* pRenderableComponent);

	Framework::Transform*	 GetTransform()								{ return m_transform; }
	void		 SetTransform(Framework::Transform* trans)				{ m_transform = trans; }
	void		 SetTranslation(Framework::Vector3* translate)			{ m_transform->SetTranslation(*translate); }
	Framework::Vector3		 GetTranslatiton()						{ return m_transform->GetTranslation(); }

	virtual void Initialize();


private:
	virtual void HandleEvent(Framework::Event* pEvent);
	virtual void HandleCollision(Framework::CollisionEventData* pData);

	void UpdateGame();
	void SetIsSupported(bool isSupported, float floor = 0.0f) { m_isSupported = isSupported; m_floor = floor; }
};
#endif