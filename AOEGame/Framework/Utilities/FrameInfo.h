#ifndef __FRAMEINFO_H__
#define __FRAMEINFO_H__

#include <string>

/*  PLIST FORMAT
frame: {{x,y},{width,height}} That's the position of the image inside the sprite sheet. 

offset: If you have trimmed sprites, that's the offset between the original sprite and the trimmed one. In your case you could easily ignore it

rotated: If the sprite was rotated or not - guess you can omit that too

sourceColorRect: The part of the original sprite that was taken. only important if trimmed

sourceSize: The original size of the untrimmed sprite

*/
namespace Framework
{
	class FrameInfo
	{
	public:
		FrameInfo();
		FrameInfo(const char* key, int x, int y, int w, int h, int col, int row) { m_keyName = key; m_frameX = x; m_frameY = y; m_frameWidth = w; m_frameHeight = h; m_frameColum = col; m_frameRow = row; };
		~FrameInfo();

	private:
		const char*		m_keyName;
		int				m_frameX;
		int				m_frameY;
		int				m_frameWidth;
		int				m_frameHeight;
		int				m_frameColum;
		int				m_frameRow;
	public:

		const char*		getKeyName() { return m_keyName; }
		void			setKeyName(const char* name) { m_keyName = name; }
		int				getFrameX()	 { return m_frameX; }
		void			setFrameX(int x) { m_frameX = x; }
		int				getFrameY()	 { return m_frameY; }
		void			setFrameY(int y) { m_frameY = y; }
		int				getFrameWidth()	{ return m_frameWidth; }
		void			setFrameWidth(int width) { m_frameWidth = width; }
		int				getFrameHeight() { return m_frameHeight; }
		void			setFrameHeight(int height) { m_frameHeight = height; }
		int				getFrameColumn() { return m_frameColum; }
		void			setFrameColumn(int column) { m_frameColum = column; }
		int				getFrameRow() { return m_frameRow; }
		void			setFrameRow(int row) { m_frameRow = row; }
	};
}
#endif//__FRAMEINFO_H__