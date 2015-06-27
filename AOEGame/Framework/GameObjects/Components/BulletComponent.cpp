#include "BulletComponent.h"
#include "SpriteComponent.h"
#include "TransformComponent.h"
#include "LifeTimeComponent.h"
#include "StaticComponent.h"
#include "../../Utilities/Timer.h"

namespace Framework
{
	BulletComponent::BulletComponent(GameObject* pOwner)
		: Component(pOwner)
		, m_bullets()
		, m_bulletFiring()
		, m_elapse(2.0f)
		, m_delay(0.25f)
		, m_velocity(0.0f, 0.0f, 0.0f)
		, m_spawnOffset(0.0f, 0.0f, 0.0f)
		, m_diePosition(-9999, -9999, -9999)
	{
		m_bullets.reserve(10);
		m_bulletFiring.reserve(10);
	}

	BulletComponent::~BulletComponent()
	{

	}

	void BulletComponent::Initialize()
	{
		//Framework::AttachEvent(Events::SCE_UPDATE_EVENT, *this);
		Framework::AttachComponentEvent(Events::COM_UPDATE_EVENT, GetOwner(), *this);
		Framework::AttachComponentEvent(Events::COM_POST_UPDATE_EVENT, GetOwner(), *this);
		Framework::AttachComponentEvent(Events::COM_RENDER_EVENT, GetOwner(), *this);

		for (m_bulletIterator = m_bullets.begin(); m_bulletIterator != m_bullets.end(); m_bulletIterator++)
		{
			GameObject* bullet = *m_bulletIterator;
			bullet->InitializeComponents();

			SpriteComponent* pBulletSpriteComponent = component_cast<SpriteComponent>(bullet);
			assert(pBulletSpriteComponent);
			if (pBulletSpriteComponent)
			{
				//pBulletSpriteComponent->Hide();
				pBulletSpriteComponent->SetTranslation(m_diePosition);
			}
		}
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

				if (GetOwner()->GetResId() == SystemObjectTypes::PLAYER_OBJECT)
				{
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
							//Vector3 velocity = pBulletSpriteComponent->GetVelocity();
							//velocity.Multiply(Timer::GetSingletonPtr()->GetTimeSim());

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
				}
				else
				{
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
							Vector3 velocity = pBulletSpriteComponent->GetVelocity();
							velocity.Multiply(Timer::GetSingletonPtr()->GetTimeSim());

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
					if (GetOwner()->GetResId() == SystemObjectTypes::PLAYER_OBJECT)
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
					}
					else
					{
						Vector3 position = pBulletTransformComponent->GetTranslatiton();
						Vector3 translation = pBulletSpriteComponent->GetVelocity();
						translation.Multiply(Timer::GetSingletonPtr()->GetTimeSim());
						position.Add(translation);
						pBulletTransformComponent->SetTranslation(&position);
					}
					


					

					

					if (pLifeTimeComponent->IsDead())
					{
						bullet->SetFeature(false);
						pBulletSpriteComponent->SetTranslation(m_diePosition);
						//pBulletSpriteComponent->Hide();
					}
				}
			}
		}
	}

	void BulletComponent::FireAll()
	{
		int i = 0;
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
						//Vector3 velocity = pBulletSpriteComponent->GetVelocity();
						//velocity.Multiply(Timer::GetSingletonPtr()->GetTimeSim());

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
			}
			i++;
			if (i > 10)
				break;
		}
	}

	void BulletComponent::HandleEvent(Event* pEvent)
	{
		switch (pEvent->GetID())
		{
			case Events::COM_UPDATE_EVENT:
			{
				//Update sprite bullet object child
				Framework::BroadcastComponentEvent(Events::COM_UPDATE_EVENT, &m_bullets, NULL);

				m_elapse += Timer::GetSingletonPtr()->GetTimeSim();

				SpriteComponent* pOwnerSpriteComponent = component_cast<SpriteComponent>(GetOwner());
				assert(pOwnerSpriteComponent);
				if (pOwnerSpriteComponent)
				{
					if (pOwnerSpriteComponent->GetCurrentState() % 100 == 50 || pOwnerSpriteComponent->GetCurrentState() == SpriteStates::FIRING)
					{
						if (m_elapse > m_delay)
						{
							if (GetOwner()->GetResId() == SystemObjectTypes::PLAYER_OBJECT)
							{
								Fire();
								m_elapse = 0;
							}
							else
							{
								FireAll();
								m_elapse = 0;
							}
							
						}
					}
					

				}

				UpdateBullets();
			}
			break;
			case Events::COM_POST_UPDATE_EVENT:
			{
				Framework::BroadcastComponentEvent(Events::COM_POST_UPDATE_EVENT, &m_bullets, NULL);
			}
			break;
			case Events::COM_RENDER_EVENT :
			{
				Framework::BroadcastComponentEvent(Events::COM_RENDER_EVENT, &m_bullets, NULL);
			}
		}
	}

	void BulletComponent::HandleCollision(CollisionEventData* pData)
	{
		if (pData->m_pCollider->GetResId() == SystemObjectTypes::PLAYER_BULLET 
			|| pData->m_pCollider->GetResId() == SystemObjectTypes::PLAYER_OBJECT)
			return;
		

		//Bullet die
		GameObject* collider = pData->m_pCollider;
		GameObject* source = pData->m_pSource;

		if (source && collider)
		{
			SpriteComponent* pBulletSpriteComponent = component_cast<SpriteComponent>(source);
			StaticComponent* pStaticComponent = component_cast<StaticComponent>(collider);
			LifeTimeComponent* pLifeTimeComponent = component_cast<LifeTimeComponent>(source);
			SpriteComponent* pTestSpriteComponent = component_cast<SpriteComponent>(collider);
			if (pStaticComponent)
			{
				if (pStaticComponent->GetStaticObjectType() == ObjectTypes::RANGE_OF_MOMENT)
					return;
				if (pBulletSpriteComponent && pLifeTimeComponent)
				{
					pLifeTimeComponent->Reset();
					pData->m_pSource->SetFeature(false);
					pBulletSpriteComponent->SetTranslation(m_diePosition);
					//pBulletSpriteComponent->Hide();
				}
			}

			if (pTestSpriteComponent)
			{
				pLifeTimeComponent->Reset();
				pData->m_pSource->SetFeature(false);
				pBulletSpriteComponent->SetTranslation(m_diePosition);
			}
		}
		
		
	}
}