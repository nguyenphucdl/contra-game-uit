#ifndef __GAMEOBJECT_H__
#define	__GAMEOBJECT_H__

#include <vector>
#include "Component.h"

namespace Framework
{
	typedef unsigned int ObjectId;
	class GameObject
	{
		template<class T>
		friend T* component_cast(GameObject& object);

		template<class T>
		friend T* component_cast(GameObject* object);
		
	private:
		typedef std::vector<Component*>								ComponentVector;
		typedef ComponentVector::iterator							ComponentVectorIterator;

		ComponentVector					m_components;
		bool							m_feature;
		int								m_type;
		ObjectId						m_id;

		template<class T>
		T* GetComponent()	{ return static_cast<T*>(GetComponent(T::GetId())); }

		Component* GetComponent(unsigned int id);

	public:
		GameObject(ObjectId id);
		~GameObject();

		template <class T>
		bool AddComponent();
		void SetFeature(bool val) { m_feature = val; }
		bool IsFeature() { return m_feature; }
		void SetType(int type) { m_type = type; }
		int	 GetType()		   { return m_type; }
		ObjectId GetId() { return m_id; }
		void InitializeComponents();
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

		Component* pNewComponent = m_components[T::GetId()];
		if (pNewComponent == NULL)
		{
			pNewComponent = new T(this);
			m_components[T::GetId()] = pNewComponent;
			added = true;
		}
		return added;
	}
}

#endif//__GAMEOBJECT_H__