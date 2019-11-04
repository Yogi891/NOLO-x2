#include "SFML/Graphics.hpp"
#include "cmath"
#include "kf/kf_log.h"
#include "qgf2d/system.h"

//
//Program include
//
#include "Renderer.h"
#include "StateMgr.h"
#include "Resman.h"
#include "GameConfig.h"
#include <ctime>

void main()
{
	srand(time(NULL));

	Resman& resman = Resman::GetInstance();
	resman.LoadImages("Data/Images/image_keys.txt");

	GameConfig& gameConfig = GameConfig::GetInstance();
	gameConfig.SetConfigFileName("Data/Player/config.cfg");
	gameConfig.LoadConfigs();

	StateMgr::GetInstance().Init();
	StateMgr::GetInstance().Run();
}
