#ifndef COLLISIONCOMPONENT_H_
#define COLLISIONCOMPONENT_H_

#include <vector>
#include "../Component.h"
#include "../../Renderer/Renderable.h"
#include "../../EventManager/EventHandler.h"
#include "../../Math/Vector3.h"
#include "../../Utilities/Enums.h"
#include "../../Collision/CollisionListener.h"

namespace Framework
{
	class CollisionComponent
		: public Component
		, public EventHandler
	{
	private:
		static const unsigned int s_id = ComponentIDs::CollisionComponentId;

		typedef std::vector<CollisionListener*>		CollisionListenerVector;
		typedef CollisionListenerVector::iterator	CollisionListenerVectorIterator;

		CollisionListenerVector		m_eventListeners;
		Renderable*	m_renderable;

		bool		m_isAttached;
		bool		m_active;
		Vector3		m_lastAABBMin;
		Vector3		m_lastAABBMax;
		Vector3		m_AABBMin;
		Vector3		m_AABBMax;

		virtual void Initialize();
	public:
		static unsigned int GetId() { return s_id; }

		explicit CollisionComponent(GameObject* pOwner);
		virtual ~CollisionComponent();

		const Vector3& GetAABBMin();
		const Vector3& GetAABBMax();
		const Vector3& GetBoundMax() const { return m_renderable->GetBoundMax(); }
		const Vector3& GetBoundMin() const { return m_renderable->GetBoundMin(); }
		bool IsActive() { return m_active; }
		void SetActive(bool val) { m_active = val; }

		bool Intersects(CollisionComponent& target);
		bool SweptAABB(CollisionComponent& target);

		virtual void HandleEvent(Event* pEvent);

		void AttachRenderable(Renderable* renderable);
		void AddEventListener(CollisionListener* pListener);
	};

	inline void CollisionComponent::AddEventListener(CollisionListener* pListener)
	{ 
		m_eventListeners.push_back(pListener); 
	}

	inline void CollisionComponent::AttachRenderable(Renderable* renderable)
	{ 
		m_isAttached = true;
		m_renderable = renderable; 
		Vector3 boundMin = m_renderable->GetBoundMin();
		Transform::Vector3Transform(&boundMin, &boundMin, &m_renderable->GetTransform());
		m_AABBMin.Set(boundMin.m_x, boundMin.m_y - m_renderable->GetBoundMax().m_y, 1.0f);
		m_AABBMax.Set(boundMin.m_x + m_renderable->GetBoundMax().m_x, boundMin.m_y, 1.0f);
		m_lastAABBMin.Set(m_AABBMin);
		m_lastAABBMax.Set(m_AABBMax);
	}

	inline const Vector3& CollisionComponent::GetAABBMin()
	{
		return m_AABBMin;
	}

	inline const Vector3& CollisionComponent::GetAABBMax()
	{
		return m_AABBMax;
	}
}
#endif