#ifndef EXTERN_H_INCLUDED
#define EXTERN_H_INCLUDED

#include "Turbo_constants.h"

namespace EXTERN
{
    /**
	*** @enum TIMER_STATE
	**/
	enum class TIMER_STATE : Uint8
	{
		STOPPED = 0,
		STARTED = 1,
		PAUSED 	= 2,
		IDLE	= 3
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
    *** @struct Config
    ***
    *** @var
    **/
    struct Config
    {
    	std::string 		caption     = "";
    	std::map<std::string, std::string> kvp;

		string 				getValue(std::string key);
		int 				getValueAsInt(std::string key);
		void 				setValue(std::string key, std::string value);
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
