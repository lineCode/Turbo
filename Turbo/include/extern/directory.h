#ifndef DIRECTORY_H_INCLUDED
#define DIRECTORY_H_INCLUDED

/**
*** @package 	directory
*** @author		Christoph Zorn
*** @date		24.02.2017
***
*** @brief		The directory package contains classes to collect information about the file system :
***
***
**/

#include <dirent.h>

#include "extern/extern.h"

namespace EXTERN
{
	struct String
	{
		static std::string                 toLower(std::string haystack);
		static std::vector<std::string>    explode(std::string haystack, char needle);
		static std::string                 implode(std::vector<std::string> haystack, std::string needle);
	};
	/**
	*** @class Directory
	***
	*** @var dirs
	*** @var files
	**/
	class Directory
	{
	private:
		const std::string			TAG = "Directory";
		std::vector<std::string> 	dirs;
		std::vector<std::string>	files;

	public:
		Directory(std::string dir);
		static bool 				isDir(std::string name);
		static bool 				isFile(std::string name);
		static bool					isType(std::string name, std::string type);
		static bool 				hasFilter(std::string name, std::string filter);
		static bool 				hasFilter(std::string name, std::vector<std::string> filter);
		std::vector<std::string> 	getDirs();
		std::vector<std::string> 	getFiles();
		~Directory();
	};
}

#endif // DIRECTORY_H_INCLUDED
