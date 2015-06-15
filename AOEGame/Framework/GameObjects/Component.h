#ifndef __COMPONENT_H__
#define __COMPONENT_H__

namespace Framework
{
	class GameObject;

	class Component
	{
	private:
		GameObject*			m_pOwner;

		virtual void Initialize() = 0;

	public:
		explicit Component(GameObject* pOwner)
			: m_pOwner(pOwner)
		{
		}

		virtual ~Component() { }

		GameObject* GetOwner() { return m_pOwner; }

		friend class GameObject;
	};
}
#endif//__COMPONENT_H__