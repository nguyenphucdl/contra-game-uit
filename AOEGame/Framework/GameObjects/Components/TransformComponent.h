#ifndef __TRANSFORMCOMPONENT_H__
#define	__TRANSFROMCOMPONENT_H__

#include "../Component.h"
#include "../../Renderer/Renderer.h"
#include "../../GameObjects/Components/RenderableComponent.h"
#include "../../Math/Transform.h"

namespace Framework
{
	class TransformComponent
		: public Component
	{
	protected:
		static const unsigned int	s_id = ComponentIDs::TransformComponentId;

		Transform*	m_transform;

	public:
		static unsigned int GetId() { return s_id; }

		explicit TransformComponent(GameObject* pOwner);
		virtual ~TransformComponent();

		virtual void Initialize();
		bool	AttachRenderableTransform(RenderableComponent* pRenderableComponent);


		Transform*	 GetTransform()								{ return m_transform; }
		void		 SetTransform(Transform* trans)				{ m_transform = trans; }
		void		 SetTranslation(Vector3* translate)			{ m_transform->SetTranslation(*translate); }
		Vector3		 GetTranslatiton()							{ return m_transform->GetTranslation(); }
	};

}
#endif//__TRANSFROMCOMPONENT_H__