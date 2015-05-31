#ifndef __GAMEOBJECT_H__
#define	__GAMEOBJECT_H__

#include <unordered_map>
#include "Component.h"

namespace Framework
{
	class GameObject
	{
		template<class T>
		friend T* component_cast(GameObject& object);

		template<class T>
		friend T* component_cast(GameObject* object);
		
	private:
		typedef std::tr1::unordered_map<unsigned int, Component*>	ComponentUnorderedMap;
		typedef ComponentUnorderedMap::iterator						ComponentUnorderedMapIterator;

		ComponentUnorderedMap			m_components;
		bool							m_feature;
		int								m_type;

		template<class T>
		T* GetComponent()	{ return static_cast<T*>(GetComponent(T::GetId())); }

		Component* GetComponent(unsigned int id);

	public:
		GameObject();
		~GameObject();

		template <class T>
		bool AddComponent();
		void SetFeature(bool val) { m_feature = val; }
		bool IsFeature() { return m_feature; }
		void SetType(int type) { m_type = type; }
		int	 GetType()		   { return m_type; }
	};

	template <class T>
	T* component_cast(GameObject& object)
	{
		return object.GetComponent<T>();
	}

	template <class T>
	T* component_cast(GameObject* pObject)
	{
		T* pComponent = NULL;
		if(pObject)
		{
			pComponent = pObject->GetComponent<T>();
		}

		return pComponent;
	}

	template <class T>
	bool GameObject::AddComponent()
	{
		bool added = false;

		ComponentUnorderedMapIterator result = m_components.find(T::GetId());
		if(result == m_components.end())
		{
			T* pNewComponent = new T(this);

			//pNewComponent->Initialize();//test

			if(pNewComponent)
			{
				std::pair<unsigned int, Component*> newComponent(T::GetId(), pNewComponent);
				std::pair<ComponentUnorderedMapIterator, bool> addedIter = m_components.insert(newComponent);
				added = addedIter.second;
			}
		}
		return added;
	}
}

#endif//__GAMEOBJECT_H__