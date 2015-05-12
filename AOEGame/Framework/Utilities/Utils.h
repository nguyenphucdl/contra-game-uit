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
	static std::string getNameWithoutExt(std::string filePath)
	{
		std::string nameOffile = getNameOfFile(filePath);
		unsigned found = nameOffile.find_first_of(".");
		if (found == std::string::npos)
			return nameOffile;
		else
			return nameOffile.substr(0, found);
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