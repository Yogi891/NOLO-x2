#include "Resman.h"
#include "SFML/Graphics/Image.hpp"
#include <fstream>

Resman::Resman()
{

}

Resman::~Resman()
{
}

Resman& Resman::GetInstance()
{
	static Resman resman;
	return resman;
}

 
void Resman::LoadImages(const std::string& a_filename)
{
	std::ifstream file(a_filename.c_str());
 
	if(!file.is_open())
		return;
 
	char buffer[48];
 
	while(!file.eof())
	{
		//grab alias
		file.get(buffer,sizeof(buffer),'	');
		std::string alias = buffer;
 
		while(true)
		{
			char c = file.peek();
			if(c == '	')
			{
				file.ignore();
			}
			else
			{
				break;
			}
		}

		//read until newline
		std::string append = "Data/Images/";
		file.get(buffer,sizeof(buffer),'\n');

		std::string imageLocation = append + buffer;
		

		//attempt to load the image
		sf::Image* img = new sf::Image();
		if(img->LoadFromFile(imageLocation))
		{
			m_Images[alias] = img;
		}
		else
		{
			delete img;
		}
		file.ignore();
	}
	file.close();
}

sf::Image& Resman::GetImage(const std::string& alias)
{
	std::map<std::string, sf::Image*>::const_iterator loc = m_Images.find(alias);

	if(loc != m_Images.end())
	{
		return *loc->second;
	}
	return *m_Images["Error"];
}

