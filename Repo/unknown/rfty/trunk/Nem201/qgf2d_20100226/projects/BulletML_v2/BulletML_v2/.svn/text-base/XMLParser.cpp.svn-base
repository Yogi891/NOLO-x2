#include "XMLParser.h"
#include <fstream>
#include <iostream>

XMLParser::XMLParser()
: m_pTags(NULL)
, m_typeConfirm(false)
, m_bulletAmout(0)
{
	

}

XMLParser::~XMLParser()
{
}

bool XMLParser::ParseXML(std::string a_fileName)
{
	bool closeTag = false;

	std::ifstream file(a_fileName.c_str());

	std::string xMLErr("XML ERROR: ");

	if(!file.is_open())
	{
		std::cout << "BulletML file could not open!\n";
		return false;
	}

	m_pTags = new std::vector<XMLTag*>;

	char buffer[1024];

	while(!file.eof())
	{
		std::string content;
		// Having empty lines or whitespace before tags is acceptable
		// Nothing to see here, move along
		ParseWhiteSpace(&file);

		// In case there was a new line at the end of the file
		char c = file.peek();

		if(c == EOF) break;

		// The first char on every line must 
		// be an opening tag
		if(c != '<')
		{
			std::cout << xMLErr << "Expected '<'\n";
			file.close();
			return false;
		}
		file.ignore();
		
		ParseWhiteSpace(&file);

		// We are going to ignore all tags with
		// useless information that we don't need
		c = file.peek();
		if(c == '?' || c == '!')
		{
			file.get(buffer, sizeof(buffer), '\n');
			file.ignore(); // now ignore the new line char
			continue;
		}
		
		// We will attempt to read to the end of the tag
		file.get(buffer, sizeof(buffer), '>');
		c = file.peek();

		// If we don't find the closing bracket, the xml tag thus file is invalid
		if(c != '>')
		{
			std::cout << xMLErr << "Expected '>'\n";
			file.close();
			return false;

		}
		file.ignore();

		// Now to handle what is inside the tag
		int i = 0;
		int size = strlen(buffer);
		std::string tag;

		// Find out what type of tag it is
		while(i < size)
		{
			c = buffer[i];

			if(c == '	' || c == '\n')
			{
				break;
			}
			if(c == '/' && buffer[i+1] == NULL)
			{
				break;
			}
			if(c == ' ')
			{
				break;
			}
			tag += c;
			++i;
		}

		// tag will contain the name

		// Handle the tag
		if(tag[0] == '/')
		{
			file.ignore();
			closeTag = true;
			int size = tag.size() - 1; //ignoring the first char '/'
			std::string temp = tag.substr(1, size);
			tag = temp;	// put back for further comparison

			// the buffer still has the '/' char inside
			// we can assume that either there is a valid /tag
			// or it was incorrectly used, which case there will
			// be an error
			strcpy_s(buffer,tag.size() + 1, tag.c_str());
		}	
		if(tag == "fire")
		{
			// attribute if label has been used
			content = buffer;
			std::string expectedAttribute("label");
			std::string attriName;

			if(strcmp(content.c_str(), "fire") == 0)
			{
				
			}
			// Check if it is a redundant tag: <fire/> = <fire></fire>
			else if(content.size() == content.find("/") + 1)
			{
				if(!GetAttriInfo(&content, &expectedAttribute, &tag, &attriName))
				{
					std::cout << xMLErr << "Invalid info in " << tag << " Tag\n";
					file.close();
					return false;
				}
				TagFire* tagFire = new TagFire();
				if(!attriName.empty())
				{
					tagFire->SetLabel(&attriName);
				}
				m_pTags->push_back(tagFire);
				closeTag = true;
			}

			else
			{
				if(!GetAttriInfo(&content, &expectedAttribute, &tag, &attriName))
				{
					std::cout << xMLErr << "Invalid info in " << tag << " Tag\n";
					file.close();
					return false;
				}
			}
			TagFire* tagFire = new TagFire();
			if(closeTag) tagFire->SetCloseTag();
			if(!attriName.empty())
			{
				tagFire->SetLabel(&attriName);
			}
			m_pTags->push_back(tagFire);
		}
		else if(tag == "bullet")
		{
			content = buffer;
			std::string expectedAttribute("label");
			std::string attriName;

			// attribute if label has been used
			if(strcmp(content.c_str(), "bullet") == 0)
			{
				
			}
			// Check if it is a redundant tag: <bullet/> = <bullet></bullet>
			else if(content.size() == content.find("/") + 1)
			{
				if(!GetAttriInfo(&content, &expectedAttribute, &tag, &attriName))
				{
					std::cout << xMLErr << "Invalid info in " << tag << " Tag\n";
					file.close();
					return false;
				}
				TagBullet* tagBullet = new TagBullet();
				if(!attriName.empty())
				{
					tagBullet->SetLabel(&attriName);
				}
				m_pTags->push_back(tagBullet);
				closeTag = true;

				m_bulletAmout++;
			}
			else
			{
				if(!GetAttriInfo(&content, &expectedAttribute, &tag, &attriName))
				{
					std::cout << xMLErr << "Invalid info in " << tag << " Tag\n";
					file.close();
					return false;
				}
			}

			TagBullet* tagBullet = new TagBullet();
			if(closeTag) tagBullet->SetCloseTag();
			else m_bulletAmout++;
			if(!attriName.empty())
			{
				tagBullet->SetLabel(&attriName);
			}
			m_pTags->push_back(tagBullet);

		}
		else if(tag == "bulletRef")
		{
			content = buffer;
			std::string expectedAttribute("label");
			std::string attriName;
			// attribute if label has been used
			if(strcmp(content.c_str(), "bullet") == 0)
			{
				
			}
			// Check if it is a redundant tag: <fire/> = <fire></fire>
			else if(content.size() == content.find("/") + 1)
			{
				if(!GetAttriInfo(&content, &expectedAttribute, &tag, &attriName))
				{
					std::cout << xMLErr << "Invalid info in " << tag << " Tag\n";
					file.close();
					return false;
				}
				TagBulletRef* tagBulletRef = new TagBulletRef();
				if(!attriName.empty())
				{
					tagBulletRef->SetLabel(&attriName);
				}
				m_pTags->push_back(tagBulletRef);
				closeTag = true;
			}
			else
			{
				if(!GetAttriInfo(&content, &expectedAttribute, &tag, &attriName))
				{
					std::cout << xMLErr << "Invalid info in " << tag << " Tag\n";
					file.close();
					return false;
				}
			}
			TagBulletRef* tagBulletRef = new TagBulletRef();
			if(closeTag) tagBulletRef->SetCloseTag();
			if(!attriName.empty())
			{
				tagBulletRef->SetLabel(&attriName);
			}
			m_pTags->push_back(tagBulletRef);
		}
		else if(tag == "action")
		{

			// attribute if label has been used
			content = buffer;
			std::string expectedAttribute("label");
			std::string attriName;
			if(strcmp(content.c_str(), "action") == 0)
			{

			}
			// Check if it is a redundant tag: <action/> = <action></action>
			else if(content.size() == content.find("/") + 1)
			{
				if(!GetAttriInfo(&content, &expectedAttribute, &tag, &attriName))
				{
					std::cout << xMLErr << "Invalid info in " << tag << " Tag\n";
					file.close();
					return false;
				}
				TagAction* tagAction = new TagAction();
				if(!attriName.empty())
				{
					tagAction->SetLabel(&attriName);
				}
				m_pTags->push_back(tagAction);	
				closeTag = true;
			}
			else
			{
				if(!GetAttriInfo(&content, &expectedAttribute, &tag, &attriName))
				{
					std::cout << xMLErr << "Invalid info in " << tag << " Tag\n";
					file.close();
					return false;
				}
			}

			TagAction* tagAction = new TagAction();
			if(closeTag) tagAction->SetCloseTag();	
			if(!attriName.empty())
			{
				tagAction->SetLabel(&attriName);
			}
			m_pTags->push_back(tagAction);

		}
		else if(tag == "term")
		{
			std::string content;

			// Attempt to fetch the information inside
			// up to the closing tag
			if(!GetTagContent(&tag, &file, &content))
			{
				std::cout << xMLErr << tag << " has error\n";
			}
		
			// Need to attribute if there is a valid closing tag
			if(!CheckValidCloseTag(&tag, &file))
			{
				std::cout << xMLErr << "Tag " << tag << " is invalid\n";
				file.close();
				return false;
			}

			TagTerm* tagTerm = new TagTerm();
			if(closeTag) tagTerm->SetCloseTag();
			else tagTerm->SetContent(&content);

			m_pTags->push_back(tagTerm);		
		}
		else if(tag == "changeSpeed")
		{
			TagChangeSpeed* tagChangeSpeed = new TagChangeSpeed();
			if(closeTag) tagChangeSpeed->SetCloseTag();
			m_pTags->push_back(tagChangeSpeed);
		}
		else if(tag == "changeDirection")
		{
			TagChangeDirection* tagChangeDirection = new TagChangeDirection();
			if(closeTag) tagChangeDirection->SetCloseTag();
			m_pTags->push_back(tagChangeDirection);
		}
		else if(tag == "speed")
		{

			// in this case "type" is all I am concerned about
			content = buffer;
			std::string expectedAttribute("type");
			std::string attriName;
			if(strcmp(content.c_str(), "speed") == 0)
			{
				attriName = "absolute";
			}
			else
			{
				if(!GetAttriInfo(&content, &expectedAttribute, &tag, &attriName))
				{
					std::cout << xMLErr << "Invalid info in " << tag << " Tag\n";
					file.close();
					return false;
				}
			}

			if(attriName == "absolute")
			{

			}
			else if(attriName == "relative")
			{

			}
			else if(attriName == "sequence")
			{

			}
			else
			{
				std::cout << xMLErr << tag << " type is either invalid or not defined\n";
				file.close();
				return false;
			}

			// Attempt to fetch the information inside
			// up to the closing tag
			if(!GetTagContent(&tag, &file, &content))
			{
				std::cout << xMLErr << tag << " has error\n";
			}

			// Need to attribute if there is a valid closing tag
			if(!CheckValidCloseTag(&tag, &file))
			{
				std::cout << xMLErr << "Tag " << tag << " is invalid\n";
				file.close();
				return false;
			}

			TagSpeed* tagSpeed = new TagSpeed();
			if(closeTag) tagSpeed->SetCloseTag();
			if(!attriName.empty())
			{
				tagSpeed->SetType(&attriName);
			}
			if(!content.empty())
			{
				tagSpeed->SetContent(&content);
			}
			m_pTags->push_back(tagSpeed);

		}
		else if(tag == "vanish")
		{		
			// Check if it is a redundant tag: <fire/> = <fire></fire>
			if(content.size() == content.find("/") + 1)
			{
				TagVanish* tagVanish = new TagVanish();
				m_pTags->push_back(tagVanish);
				closeTag = true;
			}

			TagVanish* tagVanish = new TagVanish();
			if(closeTag) tagVanish->SetCloseTag();
			m_pTags->push_back(tagVanish);
		}
		else if(tag == "repeat")
		{
			TagRepeat* tagRepeat = new TagRepeat();
			if(closeTag) tagRepeat->SetCloseTag();
			m_pTags->push_back(tagRepeat);
		}
		else if(tag == "accel")
		{
			TagAccel* tagAccel = new TagAccel();
			if(closeTag) tagAccel->SetCloseTag();
			m_pTags->push_back(tagAccel);
		}
		else if(tag == "horizontal")
		{
			std::string content;

			// Attempt to fetch the information inside
			// up to the closing tag
			if(!GetTagContent(&tag, &file, &content))
			{
				std::cout << xMLErr << tag << " has error\n";
			}
		
			// Need to attribute if there is a valid closing tag
			if(!CheckValidCloseTag(&tag, &file))
			{
				std::cout << xMLErr << "Tag " << tag << " is invalid\n";
				file.close();
				return false;
			}

			TagHori* tagHori = new TagHori();
			if(closeTag) tagHori->SetCloseTag();
			else tagHori->SetContent(&content);

			m_pTags->push_back(tagHori);	
		}
		else if(tag == "vertical")
		{
			std::string content;

			// Attempt to fetch the information inside
			// up to the closing tag
			if(!GetTagContent(&tag, &file, &content))
			{
				std::cout << xMLErr << tag << " has error\n";
			}
		
			// Need to attribute if there is a valid closing tag
			if(!CheckValidCloseTag(&tag, &file))
			{
				std::cout << xMLErr << "Tag " << tag << " is invalid\n";
				file.close();
				return false;
			}
			TagVert* tagVert = new TagVert();
			if(closeTag) tagVert->SetCloseTag();
			else tagVert->SetContent(&content);

			m_pTags->push_back(tagVert);	
			
		}
		else if(tag == "actionRef")
		{
			content = buffer;
			std::string expectedAttribute("label");
			std::string attriName;
			
			if(strcmp(content.c_str(), "actionRef") == 0)
			{

			}
			// Check if it is a redundant tag: <action/> = <action></action>
			else if(content.size() == content.find("/") + 1)
			{
				if(!GetAttriInfo(&content, &expectedAttribute, &tag, &attriName))
				{
					std::cout << xMLErr << "Invalid info in " << tag << " Tag\n";
					file.close();
					return false;
				}
				TagActionRef* tagActionRef = new TagActionRef();
				if(!attriName.empty())
				{
					tagActionRef->SetLabel(&attriName);
				}
				m_pTags->push_back(tagActionRef);	
				closeTag = true;
			}
			else
			{
				if(!GetAttriInfo(&content, &expectedAttribute, &tag, &attriName))
				{
					std::cout << xMLErr << "Invalid info in " << tag << " Tag\n";
					file.close();
					return false;
				}
			}
			TagActionRef* tagActionRef = new TagActionRef();
			if(closeTag) tagActionRef->SetCloseTag();
			if(!attriName.empty())
			{
				tagActionRef->SetLabel(&attriName);
			}
			m_pTags->push_back(tagActionRef);
		}
		else if(tag == "fireRef")
		{
			content = buffer;
			std::string expectedAttribute("label");
			std::string attriName;
			
			if(strcmp(content.c_str(), "fireRef") == 0)
			{

			}
			// Check if it is a redundant tag: <action/> = <action></action>
			else if(content.size() == content.find("/") + 1)
			{
				if(!GetAttriInfo(&content, &expectedAttribute, &tag, &attriName))
				{
					std::cout << xMLErr << "Invalid info in " << tag << " Tag\n";
					file.close();
					return false;
				}
				TagFireRef* tagFireRef = new TagFireRef();
				if(!attriName.empty())
				{
					tagFireRef->SetLabel(&attriName);
				}
				m_pTags->push_back(tagFireRef);	
				closeTag = true;
			}
			else
			{
				if(!GetAttriInfo(&content, &expectedAttribute, &tag, &attriName))
				{
					std::cout << xMLErr << "Invalid info in FireRef Tag\n";
					file.close();
					return false;
				}
			}
			TagFireRef* tagFireRef = new TagFireRef();
			if(closeTag) tagFireRef->SetCloseTag();
			if(!attriName.empty())
			{
				tagFireRef->SetLabel(&attriName);
			}
			m_pTags->push_back(tagFireRef);
		}
		else if(tag == "param")
		{
			std::string content;

			// Attempt to fetch the information inside
			// up to the closing tag
			if(!GetTagContent(&tag, &file, &content))
			{
				std::cout << xMLErr << tag << " has error\n";
			}
		
			// Need to attribute if there is a valid closing tag
			if(!CheckValidCloseTag(&tag, &file))
			{
				std::cout << xMLErr << "Tag " << tag << " is invalid\n";
				file.close();
				return false;
			}

			TagParam* tagParam = new TagParam();
			if(closeTag) tagParam->SetCloseTag();
			else tagParam->SetContent(&content);

			m_pTags->push_back(tagParam);	
		}
		else if(tag == "times")
		{
			std::string content;

			// Attempt to fetch the information inside
			// up to the closing tag
			if(!GetTagContent(&tag, &file, &content))
			{
				std::cout << xMLErr << tag << " has error\n";
			}
		
			// Need to attribute if there is a valid closing tag
			if(!CheckValidCloseTag(&tag, &file))
			{
				std::cout << xMLErr << "Tag " << tag << " is invalid\n";
				file.close();
				return false;
			}
			TagTimes* tagTimes = new TagTimes();
			if(closeTag) tagTimes->SetCloseTag();
			else tagTimes->SetContent(&content);

			m_pTags->push_back(tagTimes);	

		}
		else if(tag == "wait")
		{

			std::string content;
			// Attempt to fetch the information inside
			// up to the closing tag
			if(!GetTagContent(&tag, &file, &content))
			{
				std::cout << xMLErr << tag << " has error\n";
			}

			// Need to attribute if there is a valid closing tag
			if(!CheckValidCloseTag(&tag, &file))
			{
				std::cout << xMLErr << "Tag " << tag << " is invalid\n";
				file.close();
				return false;
			}
			TagWait* tagWait = new TagWait();
			if(closeTag) tagWait->SetCloseTag();
			else tagWait->SetContent(&content);

			m_pTags->push_back(tagWait);	
		}
		else if(tag == "bulletml")
		{
			// in this case "type" is all I am concerned about
			content = buffer;
			std::string expectedAttribute("type");
			std::string attriName;
			if(strcmp(content.c_str(), "bulletml") == 0)
			{

			}
			else
			{

				if(!GetAttriInfo(&content, &expectedAttribute, &tag, &attriName))
				{
					std::cout << xMLErr << "Invalid info in " << tag << " Tag\n";
					file.close();
					return false;
				}

				if(attriName == "vertical")
				{
					m_typeConfirm = true;
					m_isVertical = true;
				}
				else if(attriName == "horizontal")
				{
					m_typeConfirm = true;
					m_isVertical = false;
				}
				else
				{
					m_typeConfirm = false;	
					std::cout << xMLErr << "bulletml type is either invalid or not defined\n";
					file.close();
					return false;
				}
			}

			TagBulletML* tagBulletML = new TagBulletML();
			if(closeTag) tagBulletML->SetCloseTag();
			if(!attriName.empty())
			{
				tagBulletML->SetShmupType(&attriName);
			}
			m_pTags->push_back(tagBulletML);

		}
		else if(tag == "direction")
		{
			// in this case "type" is all I am concerned about
			content = buffer;
			std::string expectedAttribute("type");
			std::string attriName;
			if(strcmp(content.c_str(), "direction") == 0)
			{
				attriName = "aim";
			}
			else
			{
				if(!GetAttriInfo(&content, &expectedAttribute, &tag, &attriName))
				{
					std::cout << xMLErr << "Invalid info in " << tag << " Tag\n";
					file.close();
					return false;
				}
			}

			if(attriName == "aim")
			{

			}
			else if(attriName == "absolute")
			{

			}
			else if(attriName == "relative")
			{

			}
			else if(attriName == "sequence")
			{

			}
			else
			{
				std::cout << xMLErr << tag << " type is either invalid or not defined\n";
				file.close();
				return false;
			}

			// Attempt to fetch the information inside
			// up to the closing tag
			if(!GetTagContent(&tag, &file, &content))
			{
				std::cout << xMLErr << tag << " has error\n";
			}

			// Need to attribute if there is a valid closing tag
			if(!CheckValidCloseTag(&tag, &file))
			{
				std::cout << xMLErr << "Tag " << tag << " is invalid\n";
				file.close();
				return false;
			}

			TagDirection* tagDirection = new TagDirection();
			if(closeTag) tagDirection->SetCloseTag();
			if(!attriName.empty())
			{
				tagDirection->SetType(&attriName);
			}
			if(!content.empty())
			{
				tagDirection->SetContent(&content);
			}
			m_pTags->push_back(tagDirection);

		}
		else
		{
			std::cout << "I am 12 and what is this? -> " << tag << "\n";
			file.ignore();
		}

		closeTag = false;
	}
	file.close();	

	// Now the big attribute to see if the rules are followed for BulletML

	// First there needs to be an Action label as top: <action label = "top">

	bool checkForTop = false;
	m_pTopActions = new std::vector<TagAction*>;
	for(int i = 0, size = m_pTags->size(); i < size; ++i)
	{
		XMLTag* curTag = m_pTags->at(i);
		if(curTag->GetTagType() == ACTION)
		{
			TagAction* curTagAction = (TagAction*)curTag;
			if(!curTagAction->GetLabel())
			{
				// This tag has no label
				continue;
			}
			std::string label = *curTagAction->GetLabel();
			// Needs to be at least one "top" label
			// can be named as top1, top2, topcool, topnoob, ...
			if(label.find("top") == 0)
			{
				checkForTop = true;
				m_pTopActions->push_back(curTagAction);
			}
		}
	}
	if(!checkForTop)
	{
		std::cout << xMLErr << " No TOP ACTION tag. No entry point for BulletML script\n";
		return false;
	}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////
// This is used for debugging purposes
// To see if this is parsing in the same
// way the xml file is layed out
///////////////////////////////////////////////////////////////////////////////////////////////////////////////
	checkForTop = false;
/*
	for(int i = 0, size = m_pTags->size(); i < size; ++i)
	{
		std::string bMLTag;

		XMLTag* curTag = m_pTags->at(i);
		int findType = curTag->GetTagType();

		std::cout << "<";

		if(curTag->CheckCloseTag()) std::cout << "/";

		switch(findType)
		{
		case FIRE:
			{
				bMLTag = "fire";
				
				TagFire* tagFire = (TagFire*)curTag;
				std::cout << bMLTag;
				if(tagFire->GetLabel() != 0)
				{
					std::cout << " label = \"" << *tagFire->GetLabel() << "\"";
				}
				std::cout << ">\n";
			}
			break;
		case ACTION:
			{
				bMLTag = "action";
				
				TagAction* tagAction = (TagAction*)curTag;
				std::cout << bMLTag;
				if(tagAction->GetLabel() != 0)
				{
					std::cout << " label = \"" << *tagAction->GetLabel() << "\"";
				}
				std::cout << ">\n";
			}
			break;
		case BULLET:
			{
				bMLTag = "bullet";
				
				TagBullet* tagBullet = (TagBullet*)curTag;
				std::cout << bMLTag;
				if(tagBullet->GetLabel() != 0)
				{
					std::cout << " label = \"" << *tagBullet->GetLabel() << "\"";
				}
				std::cout << ">\n";
			}
			break;
		case FIREREF:
			{
				bMLTag = "fireRef";
				
				TagFireRef* tagFireRef = (TagFireRef*)curTag;
				std::cout << bMLTag;
				if(tagFireRef->GetLabel() != 0)
				{
					std::cout << " label = \"" << *tagFireRef->GetLabel() << "\"";
				}
				std::cout << ">\n";
			}
			break;
		case ACTIONREF:
			{
				bMLTag = "actionRef";
				
				TagActionRef* tagActionRef = (TagActionRef*)curTag;
				std::cout << bMLTag;
				if(tagActionRef->GetLabel() != 0)
				{
					std::cout << " label = \"" << *tagActionRef->GetLabel() << "\"";
				}
				std::cout << ">\n";
			}
			break;
		case BULLETREF:
			{
				bMLTag = "bulletRef";
				
				TagBulletRef* tagBulletRef = (TagBulletRef*)curTag;
				std::cout << bMLTag;
				if(tagBulletRef->GetLabel() != 0)
				{
					std::cout << " label = \"" << *tagBulletRef->GetLabel() << "\"";
				}
				std::cout << ">\n";
			}
			break;
		case TERM:
			{
				bMLTag = "term";
				
				TagTerm* tagTerm = (TagTerm*)curTag;
				std::cout << bMLTag << ">";
				if(tagTerm->GetContent() != 0)
				{
					std::cout << *tagTerm->GetContent();
				}
				std::cout << "</" << bMLTag << ">\n";
			}
			break;
		case CHANGESPEED:
			{
				bMLTag = "changeSpeed";
				std::cout << bMLTag << ">\n";
			}
			break;
		case CHANGEDIRECTION:
			{
				bMLTag = "changeDirection";
				std::cout << bMLTag << ">\n";
			}
			break;
		case SPEED:
			{
				bMLTag = "speed";
				
				TagSpeed* tagSpeed = (TagSpeed*)curTag;
				std::cout << bMLTag << ">";
				if(tagSpeed->GetContent() != 0)
				{
					std::cout << *tagSpeed->GetContent();
				}
				std::cout << "</" << bMLTag << ">\n";
			}
			break;
		case DIRECTION:
			{
				bMLTag = "direction";
				
				TagDirection* tagDirection = (TagDirection*)curTag;
				std::cout << bMLTag;
				if(tagDirection->GetType() != 0)
				{
					std::cout << " type = \"" << *tagDirection->GetType() << "\">";
				}
				if(tagDirection->GetContent() != 0)
				{
					std::cout << *tagDirection->GetContent();
				}
				std::cout << "</" << bMLTag << ">\n";
			}
			break;
		case VANISH:
			{
				bMLTag = "vanish";
				std::cout << bMLTag << ">\n";
			}
			break;
		case TIMES:
			{
				bMLTag = "times";
				
				TagTimes* tagTimes = (TagTimes*)curTag;
				std::cout << bMLTag << ">";
				if(tagTimes->GetContent() != 0)
				{
					std::cout << *tagTimes->GetContent();
				}
				std::cout << "</" << bMLTag << ">\n";
			}
			break;
		case REPEAT:
			{
				bMLTag = "repeat";
				std::cout << bMLTag << ">\n";
			}
			break;
		case ACCELR:
			{
				bMLTag = "accel";
				std::cout << bMLTag << ">\n";
			}
			break;
		case HORIZONTAL:
			{
				bMLTag = "horizontal";
				
				TagHori* tagHori = (TagHori*)curTag;
				std::cout << bMLTag << ">";
				if(tagHori->GetContent() != 0)
				{
					std::cout << *tagHori->GetContent();
				}
				std::cout << "</" << bMLTag << ">\n";
			}
			break;
		case VERTICAL:
			{
				bMLTag = "vertical";
				
				TagVert* tagVert = (TagVert*)curTag;
				std::cout << bMLTag << ">";
				if(tagVert->GetContent() != 0)
				{
					std::cout << *tagVert->GetContent();
				}
				std::cout << "</" << bMLTag << ">\n";
			}
			break;
		case PARAM:
			{
				bMLTag = "param";
				
				TagParam* tagParam = (TagParam*)curTag;
				std::cout << bMLTag << ">";
				if(tagParam->GetContent() != 0)
				{
					std::cout << *tagParam->GetContent();
				}
				std::cout << "</" << bMLTag << ">\n";
			}
			break;
		case WAIT:
			{
				bMLTag = "wait";
				
				TagWait* tagWait = (TagWait*)curTag;
				std::cout << bMLTag << ">";
				if(tagWait->GetContent() != 0)
				{
					std::cout << *tagWait->GetContent();
				}
				std::cout << "</" << bMLTag << ">\n";
			}
			break;
		case BULLETML:
			{
				bMLTag = "bulletml";
				
				TagBulletML* tagBulletML = (TagBulletML*)curTag;
				std::cout << bMLTag;
				if(tagBulletML->GetShmupType() != 0)
				{
					std::cout << " type = \"" << *tagBulletML->GetShmupType() << "\"";
				}
				std::cout << ">\n";
			}
			break;
		default:
			break;
		}
		
	}

*/

	for(int i = 0, size = m_pTags->size(); i < size; ++i)
	{
		
	}
	return true;
}

bool XMLParser::CheckValidCloseTag(std::string* pTagName, std::ifstream* pFileStream)
{
	char c;
	char buffer [1024];
	std::string xMLErr("XML ERROR: ");

	c = pFileStream->peek();
	if(c != '<')
	{
		std::cout << xMLErr << "Expected '<'\n";
		return false;
	}
	pFileStream->ignore();
	c = pFileStream->peek();
	if(c != '/')
	{
		std::cout << xMLErr << "Expected '/'\n";
		return false;
	}
	pFileStream->ignore();
	// Need to make sure the closing tag is "wait"
	// before doing any calculations

	pFileStream->get(buffer, sizeof(buffer), '>');
	c = pFileStream->peek();
	if(c != '>')
	{
		std::cout << xMLErr << "Expected '>'\n";
		return false;
	}
	pFileStream->ignore();

	int i = 0;
	int size = strlen(buffer);
	std::string tagClose;

	// Find out what type of tag it is
	while(i < size)
	{
		c = buffer[i];

		if(c == '	' || c == '\n')
		{
			break;
		}
		if(c == '/' && buffer[i+1] == '>')
		{
			break;
		}
		if(c == ' ')
		{
			break;
		}
		tagClose += c;
		++i;
	}

	if(*pTagName != tagClose)
	{
		std::cout << xMLErr << "Tried to match " << *pTagName << " with " << tagClose << std::endl;
		return false;
	}
	return true;
}

bool XMLParser::GetTagContent(std::string* pTagName, std::ifstream* pFileStream, std::string* pContent)
{
	char buffer[1024];
	// Attempt to fetch the information inside
	// up to the closing tag

	ParseWhiteSpace(pFileStream);

	pFileStream->get(buffer, sizeof(buffer), '<');

	*pContent = buffer;

	return true;
}

void XMLParser::ParseWhiteSpace(std::ifstream* pFileStream)
{
	while(true)
	{
		char c = pFileStream->peek();

		if(c == '\n' || c == '	' || c == ' ')
		{
			pFileStream->ignore();
			continue;
		}
		else
		{
			return;
		}
	}


}

bool XMLParser::GetAttriInfo(std::string* pContent, std::string* pExpectedAttribute, std::string* pTag, std::string* pAttriName)
{
	// Seperate the tag type from its attribute
	int tagNameLength = pTag->size();
	int attributeLength = pExpectedAttribute->size();

	std::string check;
	int pos = pContent->find(*pExpectedAttribute);
	if(pos == -1)
	{
		return false;
	}
	
	check = pContent->substr(pos, attributeLength);

	// If the following things are not found then this label
	// info is invalid thus XML file is invalid

	// Check if we get the expected Attribute 
	if(check != *pExpectedAttribute)
	{
		return false;
	}
	
	// find the position of "="
	pos = pContent->find("=");
	if(pos == -1)
	{
		return false;
	}

	//////////////////////////////////////////////////////////
	// Need an exception for the bulletml tag
	// as it comes with other information within
	// the tag. Since this is useless, a special case 
	// will be set up.
	//////////////////////////////////////////////////////////

	if(*pTag == "bulletml")
	{
		pos = pContent->find("vertical");
		if(pos == -1)
		{
			pos = pContent->find("horizontal");
			if(pos == -1)
			{
				return false; // There are only two valid types otherwise invalid
			}
			else
			{
				*pAttriName = pContent->substr(pos, 10);
			}
		}
		else
		{
			*pAttriName = pContent->substr(pos, 8);
		}
		return true;
	}

	// find the position of Opening Quote
	pos = pContent->find("\"");
	if(pos == -1)
	{
		return false;
	}

	// find the position of Closing Quote
	int pos2 = pContent->find_last_of("\"");
	if(pos2 == -1)
	{
		return false;
	}

	// This determines the length of the Attribute Name
	int attriNameLength = pos2 - pos - 1;
	
	*pAttriName = pContent->substr(pos + 1, attriNameLength);

	// Make sure there is no quote mark within this Attribute Name

	for(int i = 0, size = pAttriName->size(); i < size; ++i)
	{
		if(pAttriName->at(i) == '\"')
		{
			return false; // I am error: contains quote mark
		}
	}

	return true;
}

const int XMLParser::GetBulletAmout()
{
	return m_bulletAmout;
}