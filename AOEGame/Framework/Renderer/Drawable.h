#ifndef __IDRAW_H__
#define __IDRAW_H__

#include <d3d9.h>
#include <d3dx9.h>

namespace Framework
{

	class Drawable 
	{
		friend class Renderer;
	protected:
		virtual void Draw(LPD3DXSPRITE spriteHandler) = 0;
	};
}


#endif