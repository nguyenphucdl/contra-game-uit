#include "CameraComponent.h"
#include "../GameObject.h"

namespace Framework
{
	CameraComponent::CameraComponent(GameObject* pOwner)
		: Component(pOwner)
	{
		m_position = Vector3(0.0f, 0.0f, 10.0f);
		m_updir = Vector3(0.0f, 1.0f, 0.0f);

		//hard coded to 1.3333 by default
		double ratio = 640.0f / 480.0f;
		SetFrustum(3.14159f/4, ratio, 1.0f, 2000.0f);
	}

	void CameraComponent::SetFrustum(const float fov, const float aspectRatio, const float nearRange, const float farRange)
	{
		this->setFOV(fov);
		this->setAspectRatio(aspectRatio);
		this->setNearRange(nearRange);
		this->setFarRange(farRange);
	}

	CameraComponent::~CameraComponent()
	{
	}

	void CameraComponent::UpdateMatrix()
	{
		// set the camera's perspective matrix
		D3DXMATRIX& matrixProj = m_matrixProj.GetD3DMatrix();
		D3DXMatrixPerspectiveFovLH(&matrixProj, (float)this->m_fov, 
			(float)this->m_aspectRatio, (float)this->m_nearRange, (float)this->m_farRange);
		m_matrixProj.SetD3DMatrix(matrixProj);

		// set the camera's view matrix
		D3DXMATRIX& matrixView = m_matrixView.GetD3DMatrix();
		D3DXMatrixLookAtLH(&matrixView, &this->m_position.GetD3DVector(), &this->m_target.GetD3DVector(), &this->m_updir.GetD3DVector());
		m_matrixView.SetD3DMatrix(matrixView);
	}

	void CameraComponent::Initialize()
	{
	}

	void CameraComponent::HandleEvent(Event* pEvent)
	{
		assert(pEvent);
		if(pEvent->GetID() == POSTUPDATE_EVENT)
		{
			UpdateMatrix();
			Renderer::GetSingleton().SetProjectionMatrix(this->m_matrixProj);
			Renderer::GetSingleton().SetViewMatrix(this->m_matrixView);
			/*assert(Renderer::GetSingletonPtr());
			Renderer::GetSingleton().AddRenderable(&m_renderable);*/
		}
	}
}