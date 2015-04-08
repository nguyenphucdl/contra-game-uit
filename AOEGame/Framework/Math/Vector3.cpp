#include "Vector3.h"

namespace Framework
{
	Vector3::Vector3()
		: m_x(0.0f), m_y(0.0f), m_z(0.0f)
		, m_d3dvector(0.0f, 0.0f, 0.0f) // DirectX
	{
		
	}

	Vector3::Vector3(const float x, const float y, const float z)
		: m_x(x), m_y(y), m_z(z)
		, m_d3dvector(x, y, z) // DirectX
	{

	}

	Vector3::Vector3(const Vector3& in)
		: m_x(in.m_x), m_y(in.m_y), m_z(in.m_z)
		, m_d3dvector(in.m_x, in.m_y, in.m_z)

	{
	}

	Vector3::~Vector3()
	{
	}

	void Vector3::Set(const float x, const float y, const float z)
	{
		m_x = x;
		m_y = y;
		m_z = z;
	}

	void Vector3::Set(const Vector3& in)
	{
		Set(in.m_x, in.m_y, in.m_z);
	}

	void Vector3::Multiply(const float scalar)
	{
		m_x *= scalar;
		m_y *= scalar;
		m_z *= scalar;
	}

	void Vector3::Divide(const float scalar)
	{
		float divisor = 1.0f / scalar;
		m_x *= divisor;
		m_y *= divisor;
		m_z *= divisor;
	}

	void Vector3::Add(const Vector3& in)
	{
		m_x += in.m_x;
		m_y += in.m_y;
		m_z += in.m_z;
	}

	void Vector3::Subtract(const Vector3& in)
	{
		m_x -= in.m_x;
		m_y -= in.m_y;
		m_z -= in.m_z;
	}

	Vector3 Vector3::GetInverse()
	{
		//m_x = -m_x; m_y = -m_y; m_z = -m_z;
		return Vector3(-m_x, -m_y, -m_z);
	}

	Vector3 Vector3::GetInverseX()
	{
		return Vector3(-m_x, m_y, m_z);
	}

	Vector3 Vector3::GetInverseY()
	{
		return Vector3(m_x, -m_y, m_z);
	}

	Vector3& Vector3::operator=(const Vector3& in)
	{
		m_x = in.m_x; m_y = in.m_y; m_z = in.m_z;
		return *this;
	}

	float Vector3::Length() const
	{
		return sqrt((m_x*m_x) + (m_y*m_y) + (m_z*m_z));
	}

	float Vector3::LengthSquared() const
	{
		return (m_x*m_x) + (m_y*m_y) + (m_z*m_z);
	}

	float Vector3::Distance2(const Vector3& in)
	{
		return sqrt((in.m_x - m_x)*(in.m_x - m_x) + (in.m_y - m_y)*(in.m_y - m_y));
	}

	void Vector3::Normalize()
	{
		Divide(Length());
	}

	void Vector3::GetNormal(Vector3& normal)
	{
		normal = *this;
		normal.Normalize();
	}

	float Vector3::Dot(const Vector3& in) const
	{
		return (m_x * in.m_x) + (m_y * in.m_y) + (m_z * in.m_z);
	}

	Vector3 Vector3::Cross(const Vector3& in) const
	{
		return Vector3(
			(m_y * in.m_z) - (m_z * in.m_y),
			(m_z * in.m_x) - (m_x * in.m_z),
			(m_x * in.m_y) - (m_y * in.m_x));
	}

	// DirectX
	void Vector3::_updateD3D()
	{
		m_d3dvector.x = m_x; m_d3dvector.y = m_y; m_d3dvector.z = m_z;
	}

	GVECTOR3& Vector3::GetD3DVector()
	{
		_updateD3D();
		return m_d3dvector;
	}

	void Vector3::SetD3DVector(GVECTOR3& vector)
	{
		m_x = vector.x; m_y = vector.y; m_z = vector.z;
		m_d3dvector = vector;
	}

	void Vector3::operator+=(const Vector3& in)
	{
		m_x += in.m_x; m_y += in.m_y; m_z += in.m_z;
	}

	void Vector3::operator-=(const Vector3& in)
	{
		m_x -= in.m_x; m_y -= in.m_y; m_z -= in.m_z;
	}

	void Vector3::operator*=(const Vector3& in)
	{
		m_x *= in.m_x; m_y *= in.m_y; m_z *= in.m_z;
	}

	void Vector3::operator/=(const Vector3& in)
	{
		m_x /= in.m_x; m_y /= in.m_y; m_z /= in.m_z;
	}

	//equality operator comparison includes double rounding
	bool Vector3::operator==(const Vector3& in) const
	{
		float ep = 0.0001f;
		return (
			(((in.m_x - ep) < m_x) && (m_x < (in.m_x + ep))) &&
			(((in.m_y - ep) < m_y) && (m_y < (in.m_y + ep))) &&
			(((in.m_z - ep) < m_z) && (m_z < (in.m_z + ep))) );
	}

	bool Vector3::operator!=(const Vector3& in) const
	{
		return (!(*this == in));
	}
}