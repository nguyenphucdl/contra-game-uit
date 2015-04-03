#include "String_old.h"

namespace Framework
{	
	String::String(): m_string("") 
	{}
	String::String(const char* str) : m_string(str) 
	{}
	String::~String() {}

	int String::getLength()
	{
		return m_string.length();
	}
	int String::compare(G_String r)
	{
		return m_string.compare(r);
	}
	G_CStr	String::c_str()
	{
		return m_string.c_str();
	}
	void String::concat(G_String r)
	{
		m_string.append(r);
	}
	LPCWSTR String::LpWcharFromChar(const char* orig)
	{
		size_t origsize = strlen(orig) + 1;
		const size_t newsize = 100;
		size_t convertedChars = 0;
		wchar_t wcstring[newsize];
		mbstowcs_s(&convertedChars, wcstring, origsize, orig, _TRUNCATE);
		return wcstring;
	}
}