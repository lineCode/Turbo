#ifndef PARSER_H_INCLUDED
#define PARSER_H_INCLUDED

/**
*** @package 	parser
*** @author		Christoph Zorn
*** @date		24.02.2017
***
*** @brief		The parser package contains
***
***
**/

#include "extern/extern.h"

namespace EXTERN
{
	/**
	*** @class Parser
	***
	*** @var
	**/
	template<typename T>
	class IParser
	{
	private:
		const std::string TAG = "Parser";

	public:
		FILE_STATE 		file_state;
		std::fstream 	handle;

		IParser(std::string file = "", bool read = true)
		{
			if(this->file_state <= FILE_STATE::CLOSED)
			{
				this->file_state = FILE_STATE::OPENED;
			}
		};
		~IParser()
		{
			if(this->file_state >= FILE_STATE::OPENED)
			{
				this->file_state = FILE_STATE::CLOSED;
			}
		};
		virtual T 			read(std::string file = "") = 0;
		virtual bool 		write(std::string file, T value, std::string extra = "",
								  std::ios::openmode flags = std::ios::out | std::ios::trunc) = 0;
	};

	/**
	*** @class INIParser
	***
	***
	**/
	class INIParser : public IParser<INI>
	{
	private:
		const std::string 	TAG = "INIParser";
        INI					config;

	public:
		INIParser(string file = "", bool read = true);
		~INIParser();
		INI 				read(std::string file = "");
		bool 				write(std::string file, INI config, std::string extra = "",
								  std::ios::openmode flags = std::ios::out | std::ios::trunc);
		INI					getINI();
	};

	/**
	*** @class XMLParser
	***
	***
	**/
	class XMLParser : public IParser<XML>
	{
	private:
		const std::string		TAG = "XMLParser";
		XML 					xml;

	public:
		XMLParser(std::string file = "", bool read = true);
		bool 					hasTags(std::string line);
		bool					isHeadTag(std::string line);
		bool 					isStartTag(std::string line);
		bool 					isEndTag(std::string line);
		bool 					isStartEndTagLine(std::string line);
		bool 					isTagLine(std::string line);
		std::string 			capTags(std::string line);
		std::string 			replaceTags(std::string line);
		std::string 			parseTagName(std::string line);
		std::string				parseContent(std::string line);
		std::map<std::string, std::string> 	parseKVP(std::string line);
		XML 		  		  * parseFile(std::fstream & stream, std::string buffer = "");
		XML 					read(std::string file = "");
		bool 					write(std::string file, XML xml, std::string prepend = "",
								      std::ios::openmode flags = std::ios::out | std::ios::trunc);
		XML						getXML();
		~XMLParser();
	};
}

#endif // PARSER_H_INCLUDED
