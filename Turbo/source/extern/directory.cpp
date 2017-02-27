#include "extern/directory.h"

using namespace EXTERN;

Directory::Directory(string directory)
{
	DIR   		  * dir 	= opendir(directory.c_str());
	struct dirent * entry;

	if(dir != NULL)
	{
		while((entry = readdir(dir)) != NULL)
		{
			if(entry->d_name != (string)"." && entry->d_name != (string)"..")
			{
				if(this->isDir(entry->d_name))
				{
					this->dirs.push_back(entry->d_name);
				}
				else if(this->isFile(entry->d_name))
				{
					this->files.push_back(entry->d_name);
				}
			}
		}
	}
}

bool Directory::isDir(string name)
{
	bool success = false;
	DIR * dir = opendir(name.c_str());

	if(dir != NULL)
	{
		success = true;
	}

	return success;
}

bool Directory::isFile(string name)
{
	bool success = false;

	if(!this->isDir(name))
	{
		success = true;
	}

	return success;
}

list<string> Directory::getDirs()
{
	return this->dirs;
}

list<string> Directory::getFiles()
{
	return this->files;
}

Directory::~Directory()
{

}