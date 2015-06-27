#ifndef __GAMEOBJECT_H__
#define	__GAMEOBJECT_H__

#include <vector>
#include "Component.h"
#include"../Log/Log.h"

namespace Framework
{
	typedef unsigned int ObjectId;
	typedef unsigned int ResourceId;
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
		std::string						m_tag;
		ObjectId						m_id;
		ResourceId						m_resId;

		template<class T>
		T* GetComponent()	{ return static_cast<T*>(GetComponent(T::GetId())); }

		Component* GetComponent(unsigned int id);
		Component* SafeGetComponent(unsigned int id);

	public:
		GameObject(ObjectId id);
		~GameObject();

		template <class T>
		bool AddComponent();
		void SetFeature(bool val) { m_feature = val; }
		bool IsFeature() { return m_feature; }
		void SetType(int type) { m_type = type; }
		int	 GetType()		   { return m_type; }
		void SetResId(int resId) { m_resId = resId; }
		int	 GetResId()			{ return m_resId; }

		void SetTag(std::string tag) { m_tag = tag; }
		std::string GetTag()		 { return m_tag; }
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

	inline Component* GameObject::GetComponent(unsigned int id)
	{
		return m_components[id];
	}

	inline Component* GameObject::SafeGetComponent(unsigned int id)
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
}

#endif//__GAMEOBJECT_H__