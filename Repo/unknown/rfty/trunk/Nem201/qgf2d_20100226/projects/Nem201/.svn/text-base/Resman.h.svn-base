#ifndef _RESMAN_H_
#define _RESMAN_H_
#include "qgf2d/anim.h"
#include <string>
#include <map>
namespace sf
{
	class Image;
}

class Resman
{
public:
	~Resman();
	static Resman& GetInstance();
 
 
	void LoadImages(const std::string& filename);
 
	sf::Image& GetImage(const std::string& alias);
 

private:
	Resman();

	std::map<std::string, sf::Image*> m_Images;
	std::map<std::string, qgf::Anim*> m_Anims;

};

#endif