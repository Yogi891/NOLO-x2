#ifndef _XMLPARSER_H_
#define _XMLPARSER_H_

#include <string>
#include <stack>
#include <vector>
#include "XMLTag.h"


class XMLParser
{
public:
	XMLParser();
	~XMLParser();

	bool ParseXML(std::string a_fileName);

	std::vector<XMLTag*>* GetTags() const
	{
		return m_pTags;
	}

	const int GetBulletAmout();
	
private:
	// Helper function to get tag calculations
	bool CheckValidCloseTag(std::string* pTagName, std::ifstream* pFileStream);
	bool GetTagContent(std::string* pTagName, std::ifstream* pFileStream, std::string* pContent);
	void ParseWhiteSpace(std::ifstream* pFileStream);
	bool GetAttriInfo(std::string* pContent, std::string* pAttribute, std::string* pTag, std::string* pAttriName);


	bool m_typeConfirm;
	bool m_isVertical;
	std::vector<XMLTag*>* m_pTags;
	std::vector<TagAction*>* m_pTopActions;

	int m_bulletAmout;

};

#endif