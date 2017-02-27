#include "extern/extern.h"

using namespace EXTERN;

string XML::getValue(string key)
{
	return this->kvp[key];
}

int XML::getValueAsInt(string key)
{
	return atoi(this->kvp[key].c_str());
}

void XML::setValue(string key, string value)
{
	this->kvp[key] = value;
}

XML XML::findTag(string tag)
{
	XML result;
	if(this->tag == tag)
		result = *this;
	else if(this->children.size() > 0)
	{
		for(XML * child : this->children)
		{
			if(child->tag == tag)
			{
				result = *child;
				break;
			}
		}
		if(result.isEmpty())
		{
			for(XML * child : this->children)
			{
				if(result.isEmpty())
				{
					result = child->findTag(tag);
				}
				else
				{
					break;
				}
			}
		}
	}
	else if(this->next != nullptr)
	{
		result = this->next->findTag(tag);
	}
	return result;
}

bool XML::isEmpty()
{
	bool success = false;

	if(this->tag == "" && this->content == "" &&
	   this->kvp.size() == 0 && this->children.size() == 0 &&
	   this->prev == nullptr && this->next == nullptr &&
	   this->parent == nullptr && this->next == nullptr)
	{
		success = true;
	}
	return success;
}

void XML::printXML()
{
	cout << this->tag << "\n";
	for(auto & kvp : this->kvp)
	{
		cout << "  -> " << kvp.first << " = " << kvp.second << "\n";
	}
	cout << "  -> \"" << this->content << "\"" << endl;
	if(this->child != nullptr)
	{
		this->child->printXML();
	}
}