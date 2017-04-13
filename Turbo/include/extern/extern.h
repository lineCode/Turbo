#ifndef EXTERN_H_INCLUDED
#define EXTERN_H_INCLUDED

/**
*** @module 	extern
*** @author		Christoph Zorn
*** @date		24.02.2017
***
*** @brief		The extern module contains
***
***
**/

#include "Turbo_main.h"

namespace EXTERN
{
    /**
	*** @enum TIMER_STATE
	**/
	enum class TIMER_STATE : Uint8
	{
		STOPPED = 0,
		IDLE	= 1,
		STARTED = 2,
		PAUSED 	= 3
	};

	/**
	*** @enum FILE_STATE
	**/
	enum class FILE_STATE : Uint8
	{
		CLOSED 	= 0,
		OPENED 	= 1
	};

    /**
    *** @struct INI
    ***
    *** @brief  The INI structure represents the contents of an .ini file
    ***         it is quite helpful to load settings or configurations
    **/
    struct INI
    {
    	std::map<std::string, std::map<std::string, std::string>> kvp;

		string 				getValue(std::string key);
		string 				getValue(std::string caption, std::string key);
		int 				getValueAsInt(std::string key);
		int 				getValueAsInt(std::string caption, std::string key);
		float 				getValueAsFloat(std::string key);
		float 				getValueAsFloat(std::string caption, std::string key);
		void 				setValue(std::string key, std::string value);
		void 				setValue(std::string caption, std::string key, std::string value);
    	bool 				isEmpty();
    };

    /**
    *** @struct XML
    **/
    struct XML
    {
    	XML 			  * parent      = nullptr;
    	XML 			  * child       = nullptr;
    	XML				  * next        = nullptr;
    	XML				  * prev        = nullptr;
    	std::string 		tag         = "";
    	std::string 		content     = "";
    	bool 				lineTag     = false;
    	bool				multiTag    = false;
    	bool				head        = false;
    	std::vector<XML *> 	children;
    	std::map<std::string, std::string> kvp;

		std::string 		getValue(std::string key);
		Sint32 				getValueAsInt(std::string key);
		void 				setValue(std::string key, std::string value);
		XML					findTag(std::string tag);
    	bool 				isEmpty();
    	void				printXML();
    };
}

#endif // EXTERN_H_INCLUDED
