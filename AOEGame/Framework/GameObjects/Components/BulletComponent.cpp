#include "BulletComponent.h"
#include "SpriteComponent.h"
#include "TransformComponent.h"
#include "LifeTimeComponent.h"
#include "../../Utilities/Timer.h"

namespace Framework
{
	BulletComponent::BulletComponent(GameObject* pOwner)
		: Component(pOwner)
		, m_bullets()
		, m_bulletFiring()
		, m_elapse(2.0f)
		, m_delay(0)
		, m_velocity(0.0f, 0.0f, 0.0f)
		, m_spawnOffset(0.0f, 0.0f, 0.0f)
	{
		m_bullets.reserve(10);
		m_bulletFiring.reserve(10);
	}

	BulletComponent::~BulletComponent()
	{

	}

	void BulletComponent::Initialize()
	{
		Framework::AttachEvent(Events::UPDATE_EVENT, *this);

		for (m_bulletIterator = m_bullets.begin(); m_bulletIterator != m_bullets.end(); m_bulletIterator++)
		{
			GameObject* bullet = *m_bulletIterator;

			SpriteComponent* pBulletSpriteComponent = component_cast<SpriteComponent>(bullet);
			assert(pBulletSpriteComponent);
			if (pBulletSpriteComponent)
			{
				pBulletSpriteComponent->Hide();
			}
		}

		m_delay = 0.25f;
	}

	void BulletComponent::AddBullet(GameObject* bullet)
	{
		m_bullets.push_back(bullet);
	}

	void BulletComponent::Fire()
	{
		for (m_bulletIterator = m_bullets.begin(); m_bulletIterator != m_bullets.end(); m_bulletIterator++)
		{
			GameObject* bullet = *m_bulletIterator;
			if (!bullet->IsFeature())
			{
				bullet->SetFeature(true);

				SpriteComponent* pBulletSpriteComponent = component_cast<SpriteComponent>(bullet);
				assert(pBulletSpriteComponent);
				SpriteComponent* pOwnerSpriteComponent = component_cast<SpriteComponent>(GetOwner());
				assert(pOwnerSpriteComponent);
				if (pBulletSpriteComponent && pOwnerSpriteComponent)
				{
					TransformComponent* pOwnerTransformComponent = component_cast<TransformComponent>(GetOwner());
					assert(pOwnerTransformComponent);
					TransformComponent* pBulletTransformComponent = component_cast<TransformComponent>(bullet);
					assert(pBulletTransformComponent);
					LifeTimeComponent* pLifeTimeComponent = component_cast<LifeTimeComponent>(bullet);
					assert(pLifeTimeComponent);
					if (pOwnerTransformComponent && pBulletTransformComponent && pLifeTimeComponent)
					{
						Vector3 trans = pOwnerTransformComponent->GetTranslatiton();
						Vector3 center = pOwnerSpriteComponent->GetCenter();
						center.m_y *= -1;
						Vector3 offset = m_spawnOffset;
						trans.Add(center);
						if (pOwnerSpriteComponent->GetCurrentDirection() == SpriteDirections::LEFT)
							offset.m_x *= -1;
						trans.Add(offset);
						
						pBulletTransformComponent->GetTransform()->SetTranslation(trans);
						pLifeTimeComponent->Start();
					}

					pBulletSpriteComponent->Show(true);
					pBulletSpriteComponent->SetDefaultDirection(pOwnerSpriteComponent->GetCurrentDirection());
				}

				break;
			}
		}
	}

	void BulletComponent::Reload()
	{
		/*for (m_bulletIterator = m_bulletFiring.begin(); m_bulletIterator != m_bulletFiring.end(); m_bulletIterator++)
		{
			GameObject* bullet = *m_bulletIterator;
			bullet->SetFeature(false);
		}*/
		m_bulletFiring.clear();
	}

	void BulletComponent::UpdateBullets()
	{		
		for (m_bulletIterator = m_bullets.begin(); m_bulletIterator != m_bullets.end(); m_bulletIterator++)
		{
			GameObject* bullet = *m_bulletIterator;
			if (bullet->IsFeature())
			{
				TransformComponent* pBulletTransformComponent = component_cast<TransformComponent>(bullet);
				assert(pBulletTransformComponent);
				SpriteComponent* pBulletSpriteComponent = component_cast<SpriteComponent>(bullet);
				assert(pBulletSpriteComponent);
				LifeTimeComponent* pLifeTimeComponent = component_cast<LifeTimeComponent>(bullet);
				assert(pLifeTimeComponent);

				if (pBulletTransformComponent && pBulletSpriteComponent && pLifeTimeComponent)
				{
					if (pBulletSpriteComponent->GetCurrentDirection() == SpriteDirections::RIGHT)
						m_velocity.m_x = (m_velocity.m_x > 0) ? m_velocity.m_x : -m_velocity.m_x;
					else
						m_velocity.m_x = (m_velocity.m_x < 0) ? m_velocity.m_x : -m_velocity.m_x;



					Vector3 position = pBulletTransformComponent->GetTranslatiton();
					Vector3 translation = m_velocity;
					translation.Multiply(Timer::GetSingletonPtr()->GetTimeSim());
					position.Add(translation);

					pBulletTransformComponent->SetTranslation(&position);

					if (pLifeTimeComponent->IsDead())
					{
						bullet->SetFeature(false);
						pBulletSpriteComponent->Hide();
					}
				}
			}
		}
	}

	void BulletComponent::HandleEvent(Event* pEvent)
	{
		switch (pEvent->GetID())
		{
		case Events::UPDATE_EVENT:
		{
			m_elapse += Timer::GetSingletonPtr()->GetTimeSim();

			SpriteComponent* pOwnerSpriteComponent = component_cast<SpriteComponent>(GetOwner());
			assert(pOwnerSpriteComponent);
			if (pOwnerSpriteComponent)
			{
				if (pOwnerSpriteComponent->GetCurrentState() % 100 == 50)
				{
					if (m_elapse > m_delay)
					{
						Fire();
						m_elapse = 0;
					}
				}

			}

			UpdateBullets();
		}
			break;
		}
	}
}