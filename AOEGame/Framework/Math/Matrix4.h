#ifndef __MATRIX4_H__
#define	__MATRIX4_H__

#include <d3d9.h>
#include <d3dx9.h>

namespace Framework
{
	class Vector3;
	class Vector4;
	class Matrix3;

	typedef	D3DXMATRIX GMATRIX;
	class Matrix4
	{
	public:
		float		m_m[16];
		// DirectX
		GMATRIX		m_d3dmatrix;

		enum Rows
		{
			X, Y, Z, W, NUM_ROWS
		};
		Matrix4();
		virtual ~Matrix4();
		
		void	Identify();
		Vector3	Transform(const Vector3& in) const;
		Vector3 TransformTranspose(const Vector3& in) const;
		Vector4 Multiply(const Vector4& in) const;
		void	RotateAroundX(float radians);
		void	RotateAroundY(float radians);
		void	RotateAroundZ(float radians);
		void	Multiply(const Matrix4& in, Matrix4& out) const;

		Matrix4 Transpose() const;

		Matrix4& operator=(const Matrix3& in);
		Matrix4& operator=(const Matrix4& in);

		Vector4	GetRow(const Rows row) const;

		// DirectX
		GMATRIX& GetD3DMatrix();
		void	 SetD3DMatrix(GMATRIX& matrix);
	private:
		void _updateD3D();
	};
}
#endif//__MATRIX4_H__