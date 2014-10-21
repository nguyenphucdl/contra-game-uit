#ifndef __VECTOR3_H__
#define __VECTOR3_H__

#include <d3d9.h>
#include <d3dx9.h>
#include <cmath>

namespace Framework
{
	typedef	D3DXVECTOR3 GVECTOR3;
	class Vector3
	{
	public:
		float		m_x;
		float		m_y;
		float		m_z;
		// DirectX
		GVECTOR3	m_d3dvector;
	public:
		Vector3();
		Vector3(const Vector3& in);
		Vector3(const float x, const float y, const float z);
		virtual ~Vector3();

		void	Set(const float x, const float y, const float z);
		void	Set(const Vector3& in);
		void	Multiply(const float scalar);
		void	Divide(const float scalar);
		void	Add(const Vector3& in);
		void	Subtract(const Vector3& in);
		void	Negate();
		float	Length() const;
		float	LengthSquared() const;
		float	Distance2(const Vector3& in);
		
		float	Dot(const Vector3& in) const;
		Vector3	Cross(const Vector3& in) const;
		void	Normalize();
		void	GetNormal(Vector3& normal);
		
		Vector3& operator=(const Vector3& in);
		//Vector3& operator=(const Vector4& in);
		void operator+=(const Vector3& in);
		void operator-=(const Vector3& in);
		void operator*=(const Vector3& in);
		void operator/=(const Vector3& in);
		bool operator==(const Vector3& in ) const;
		bool operator!=(const Vector3& in ) const;

		// DirectX
		GVECTOR3& GetD3DVector();
		void	SetD3DVector(GVECTOR3& vector);
	private:
		void	_updateD3D();
	};
}

#endif//__VECTOR3_H__