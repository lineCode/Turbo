#include "extern/directory.h"

using namespace EXTERN;

string String::toLower(string haystack)
{
	std::transform(haystack.begin(), haystack.end(), haystack.begin(), ::tolower);
	return haystack;
}

vector<string> String::explode(string haystack, char needle)
{
	vector<string> result;
    std::istringstream iss(haystack);

    for(string token; std::getline(iss, token, needle); )
    {
        result.push_back(std::move(token));
    }
    return result;
}

string String::implode(vector<string> haystack, string needle)
{
	string result = "";

	for(string s : haystack)
	{
		result += s + needle;
	}
	return result.substr(0, result.rfind(needle) - 1);
}

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

	if(!Directory::isDir(name))
	{
		if(Directory::fileExists(name))
		{
			success = true;
		}
	}
	return success;
}

bool Directory::fileExists(string name)
{
	fstream f(name);
	return f.good();
}

bool Directory::isType(string name, string type)
{
	bool success = false;
	if(Directory::isFile(name))
	{
		if(name.substr(name.rfind('.') + 1, name.length() - name.rfind('.') - 1) == String::toLower(type))
		{
			success = true;
		}
	}
	return success;
}

bool Directory::hasFilter(string name, string filter)
{
	bool success = false;

	if(filter.find(',') != std::string::npos)
	{
		success = Directory::hasFilter(name, String::explode(filter, ','));
	}
	else
	{
		success = Directory::isType(name, filter);
	}
	return success;
}

bool Directory::hasFilter(string name, vector<string> filter)
{
	bool success = false;

	for(string s : filter)
	{
		if(Directory::isType(name, s))
		{
			success = true;
		}
	}
	return success;
}

vector<string> Directory::getDirs()
{
	return this->dirs;
}

vector<string> Directory::getFiles()
{
	return this->files;
}

Directory::~Directory()
{

}