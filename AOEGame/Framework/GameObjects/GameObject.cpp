#include "GameObject.h"

namespace Framework
{
	GameObject::GameObject(ObjectId id)
		: m_feature(false)
		, m_id(id)
		, m_type(-1)
		, m_components(20)
	{
	}

	GameObject::~GameObject()
	{
		for (ComponentVectorIterator iter = m_components.begin(); iter != m_components.end(); iter++)
		{
			Component*pComponent = *iter;
			if (pComponent)
			{
				delete pComponent;
				pComponent = NULL;
			}
		}
	}

	void GameObject::InitializeComponents()
	{
		for (ComponentVectorIterator iter = m_components.begin(); iter != m_components.end(); iter++)
		{
			Component*pComponent = *iter;
			if (pComponent)
			{
				pComponent->Initialize();
			}
		}
	}
}