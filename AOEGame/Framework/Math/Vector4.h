#ifndef __VECTOR4_H__
#define __VECTOR4_H__

namespace Framework
{
	class Vector4
	{
	public:
		float m_x;
		float m_y;
		float m_z;
		float m_w;

		Vector4();
		Vector4(const float x, const float y, const float z, const float w);
		virtual ~Vector4();

		void Set(Vector4& in);
		void Multiply(float scalar);
		void Divide(float scalar);
		void Add(Vector4& in);
		void Subtract(Vector4& in);

		Vector4& operator=(const Vector4& in);
	};
}
#endif//__VECTOR4_H__