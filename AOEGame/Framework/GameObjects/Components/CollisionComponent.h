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

		Vector3		m_min;
		Vector3		m_max;
		bool		m_isAttached;

		typedef std::vector<CollisionListener*>		CollisionListenerVector;
		typedef CollisionListenerVector::iterator	CollisionListenerVectorIterator;

		CollisionListenerVector		m_eventListeners;

	public:
		static unsigned int GetId() { return s_id; }

		explicit CollisionComponent(GameObject* pOwner);
		virtual ~CollisionComponent();

		virtual void Initialize();

		void SetMin(const Vector3& point) { m_min = point; }
		void SetMax(const Vector3& point) { m_max = point; }

		const Vector3& GetMin();
		const Vector3& GetMax();

		bool Intersects(CollisionComponent& target);

		virtual void HandleEvent(Event* pEvent);

		void AttachRenderable(Renderable* renderable) { m_isAttached = true; m_renderable = renderable; }
		void AddEventListener(CollisionListener* pListener) { m_eventListeners.push_back(pListener); }
	};
}
#endif