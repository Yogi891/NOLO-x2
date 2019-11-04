//-------------------------------------------------------------------------
// Loads all the game configurations
//

#ifndef _GAMECONFIG_H_
#define _GAMECONFIG_H_


#include <map>
#include <string>
#include <SFML/Window/Event.hpp>
#include <SFML/Window/Input.hpp>

class GameConfig
{
public:
	~GameConfig();

	static GameConfig& GetInstance();

	bool SetConfigFileName(std::string a_configFileName);
	bool SetKeyConfigFileName(std::string a_keyConfigFileName);

	bool LoadConfigs();

	float GetConfigValue(const std::string& a_attribute) const;

	sf::Key::Code& GetKey(const std::string& a_action);


private:
	GameConfig();
	std::string m_configFileName;
	std::string m_keyConfigFileName;
	std::map<std::string, float> m_configs;
	std::map<std::string, sf::Key::Code> m_keyConfig;
};

#endif