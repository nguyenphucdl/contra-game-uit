#include "GameObject.h"
#include"../Log/Log.h"

namespace Framework
{
	GameObject::GameObject(ObjectId id)
		: m_feature(false)
		, m_id(id)
		, m_type(-1)
		, m_components(10)
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

	Component* GameObject::GetComponent(unsigned int id)
	{
		Component* pComponent = NULL;
		try {
			pComponent = m_components.at(id);
		}
		catch (const std::out_of_range& oor) {
			Log::error("Try to get component with id out of range (%d) reson (%s)", id, oor.what());
		}
		return pComponent;
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