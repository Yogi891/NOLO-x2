#include "GameConfig.h"
#include <iostream>
#include <fstream>
#include "qgf2d/system.h"


GameConfig::GameConfig()
{


}

GameConfig::~GameConfig()
{
}

GameConfig& GameConfig::GetInstance()
{
	static GameConfig gameCfg;
	return gameCfg;
}

bool GameConfig::SetConfigFileName(std::string a_configFileName)
{
	m_configFileName = a_configFileName;
	std::ifstream file(m_configFileName.c_str());
	if(!file.is_open())
	{
		std::cout << m_configFileName << " could not be found\n";
		file.close();
		return false;
	}
	file.close();
	return true;
}

bool GameConfig::SetKeyConfigFileName(std::string a_keyConfigFileName)
{
	m_keyConfigFileName = a_keyConfigFileName;
	std::ifstream file(m_keyConfigFileName.c_str());
	if(!file.is_open())
	{
		std::cout << m_keyConfigFileName << " could not be found\n";
		return false;
	}
	return true;
}


bool GameConfig::LoadConfigs()
{
	
	// Set up the Game Configurations -------------------------------------------------------------------------------------------
	std::ifstream file(m_configFileName.c_str());

	if(!file.is_open())
	{
		std::cout << "Game Config file could not open!\n";
		return false;
	}

	char buffer[1024];

	while(!file.eof())
	{
		// Check if there are comments or new lines

		while(true)
		{	
			char c = file.peek();
			if(c == '\n')
			{
				file.ignore();
				continue;
			}
			else if(c == '/')
			{
				file.ignore();

				c = file.peek();
				if(c == '/')
				{
					file.get(buffer, sizeof(buffer), '\n');
					file.ignore();
					continue;
				}
				else
				{
					std::cout << "Improper use of comment '/'\n";
					return false;
				}
			}
			else
			{
				break;
			}
		}
		
		// Check
		// Get config attribute
		file.get(buffer, sizeof(buffer), '	');
		std::string attribute = buffer;

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
		

		file.get(buffer, sizeof(buffer), '\n');
		float value = atof(buffer);

		m_configs[attribute] = value;

		file.ignore();

	}
	file.close();	


	// Set up the Key Configurations -----------------------------------------------------------------------------------------
	std::ifstream keyFile(m_keyConfigFileName.c_str());

	if(!keyFile.is_open())
	{
		std::cout << "Key Config file could not open!\n";
		return false;
	}
	

	while(!keyFile.eof())
	{
		

		// Check if there are comments or new lines

		while(true)
		{	
			char c = keyFile.peek();
			if(c == '\n')
			{
				keyFile.ignore();
				continue;
			}
			else if(c == '/')
			{
				keyFile.ignore();

				c = keyFile.peek();
				if(c == '/')
				{
					keyFile.get(buffer, sizeof(buffer), '\n');
					keyFile.ignore();
					continue;
				}
				else
				{
					std::cout << "Improper use of comment '/'\n";
					return false;
				}
			}
			else
			{
				break;
			}
		}

		// Get key config
		keyFile.get(buffer, sizeof(buffer), '	');
		std::string action = buffer;

		while(true)
		{
			char c = keyFile.peek();
			if(c == '	')
			{
				keyFile.ignore();
			}
			else
			{
				break;
			}
		}

		keyFile.get(buffer, sizeof(buffer), '\n');

		char keyValue = buffer[0];

		sf::Event::KeyEvent key;

		switch(keyValue)
		{
		case '/':
			key.Code = sf::Key::Code::Slash;
			break;
		case ' ':
			key.Code = sf::Key::Code::Space;
			break;
		case '.':
			key.Code = sf::Key::Code::Period;
			break;
		default:
			keyValue = tolower(keyValue);
			key.Code = sf::Key::Code(keyValue);
		}

		m_keyConfig[action] = key.Code;

		keyFile.ignore();

	}
	keyFile.close();	

	// Everything Loaded
	return true;

}

float GameConfig::GetConfigValue(const std::string& a_attribute) const
{
	std::map<std::string, float>::const_iterator configValue = m_configs.find(a_attribute);
	if(configValue != m_configs.end())
	{
		return configValue->second;
	}
	return 0.0f;
}

sf::Key::Code& GameConfig::GetKey(const std::string& a_action)
{
	std::map<std::string, sf::Key::Code>::iterator keyValue = m_keyConfig.find(a_action);
	if(keyValue != m_keyConfig.end())
	{
		return keyValue->second;
	}

}