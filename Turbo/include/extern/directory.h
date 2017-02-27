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
	/**
	*** @class Directory
	***
	*** @var dirs
	*** @var files
	**/
	class Directory
	{
	private:
		const std::string		TAG = "Directory";
		std::list<std::string> 	dirs;
		std::list<std::string>	files;

	public:
		Directory(std::string dir);
		bool 					isDir(std::string name);
		bool 					isFile(std::string name);
		std::list<std::string> 	getDirs();
		std::list<std::string> 	getFiles();
		~Directory();
	};
}

#endif // DIRECTORY_H_INCLUDED
