#ifndef __UTILS_H__
#define __UTILS_H__

#include <string>

class Utils
{

public: 
	static std::string getPathOfFile(std::string filePath)
	{
		unsigned found = filePath.find_last_of("/\\");
		if (found == std::string::npos)
			return "";
		else
			return filePath.substr(0, found);
	}

	static std::string getNameOfFile(std::string filePath)
	{
		unsigned found = filePath.find_last_of("/\\");
		if (found == std::string::npos)
			return filePath;
		else
			return filePath.substr(found + 1);
	}
	 
	static bool isPath(std::string filePath)
	{
		unsigned found = filePath.find_first_of("/\\");
		if (found == std::string::npos)
			return false;
		else
			return true;
	}
};


#endif