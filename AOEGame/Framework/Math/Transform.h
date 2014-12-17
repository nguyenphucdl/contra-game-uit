#ifndef __TRANSFORM_H__
#define __TRANSFORM_H__

#include "Matrix3.h"
#include "Matrix4.h"
#include "Vector3.h"

namespace Framework
{
	class Transform
	{
	private:
		Matrix3		m_rotation;
		Vector3		m_translation;
		float		m_scale;
		Matrix4		m_matrix;

	public:
		Transform();
		virtual ~Transform();

		void			Clone(const Transform& transform);

		void			SetRotation(const Matrix3& rotation);
		const Matrix3&	GetRotation() const;

		void			SetTranslation(const Vector3& translation);
		Vector3&	GetTranslation();

		void			SetScale(const float scale);
		const float		GetScale() const;

		void			ApplyForward(const Vector3& in, Vector3& out) const;
		void			ApplyInverse(const Vector3& in, Vector3& out) const;

		void			UpdateMatrix();

		const Matrix4&	GetMatrix();
		void			GetInverseMatrix(Matrix4& out) const;
		void			GetInverseTransform(Transform& out) const;
		void			GetInverseTransposeMatrix(Matrix4& out) const;
		void			GetInverseTransposeMatrix(Matrix3& out) const;

		Transform		Multiply(Transform& input) const;

	public:
		static void Vector3Transform(_In_ Vector3* pIn, _Out_ Vector3 *pOut, _In_ Transform* pTransform);
		static D3DXVECTOR3 GetVector3FromWorldView(_In_ D3DXVECTOR3& posIn, _In_ D3DXMATRIX& matrixWorldView);
	};
}

#endif//__TRANSFROM_H__