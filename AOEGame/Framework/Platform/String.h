#ifndef __STRING_H__
#define	__STRING_H__

#include <string>
#include <Windows.h>


namespace Framework
{
	typedef std::string G_String;
	typedef	const char * G_CStr;
	class String
	{
	private:
		G_String		m_string;

	public:
		explicit String();
		explicit String(const char* str);
		
		~String();
		
		int			getLength();
		int			compare(G_String r);
		void		concat(G_String r);
		G_CStr		c_str();

		

	public:
		static LPCWSTR LpWcharFromChar(const char* carr);

		friend int StringCompare(G_String l, G_String r);
		friend G_String& StringCat(G_String l, G_String r);
	};
}


#endif//__STRING_H__