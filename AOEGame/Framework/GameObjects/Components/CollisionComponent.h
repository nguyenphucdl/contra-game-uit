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

		Renderable*	m_renderable;

		bool		m_isAttached;

		typedef std::vector<CollisionListener*>		CollisionListenerVector;
		typedef CollisionListenerVector::iterator	CollisionListenerVectorIterator;

		CollisionListenerVector		m_eventListeners;

		virtual void Initialize();
	public:
		static unsigned int GetId() { return s_id; }

		explicit CollisionComponent(GameObject* pOwner);
		virtual ~CollisionComponent();

		const Vector3 GetAABBMin();
		const Vector3 GetAABBMax();
		const Vector3& GetBoundMax() const { return m_renderable->GetBoundMax(); }
		const Vector3& GetBoundMin() const { return m_renderable->GetBoundMin(); }
 
		bool Intersects(CollisionComponent& target);

		virtual void HandleEvent(Event* pEvent);

		void AttachRenderable(Renderable* renderable) { m_isAttached = true; m_renderable = renderable; }
		void AddEventListener(CollisionListener* pListener) { m_eventListeners.push_back(pListener); }
	};
}
#endif