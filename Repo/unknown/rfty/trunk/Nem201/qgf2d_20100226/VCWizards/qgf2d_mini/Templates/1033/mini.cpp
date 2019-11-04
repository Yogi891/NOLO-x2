#include "SFML/Graphics.hpp"
#include "cmath"
#include "kf/kf_log.h"
#include "qgf2d/system.h"

using namespace std;
using namespace qgf;
using namespace kf;
using namespace sf;

int main()
{
	initDirectory();
	Log::getDefault().addCout();
	Log::getDefault().addFile("tutorial1.log");
	kf_log("This is Tutorial 1");

    RenderWindow window(VideoMode(800, 600, 32), "Tutorial1");

	Image backgroundImage;
    if (!backgroundImage.LoadFromFile("data/space.jpg"))
        return EXIT_FAILURE;
	Image shipImage;
    if (!shipImage.LoadFromFile("data/ships.png"))
        return EXIT_FAILURE;

    Sprite backgroundSprite(backgroundImage);
	Sprite ship(shipImage);

	float x = 400, y = 300;
	ship.SetSubRect(IntRect(91,0,128,53));
	ship.SetCenter(19,27);
	ship.SetPosition(x, y);

	
	while (window.IsOpened())
    {
        Event ev;
        while (window.GetEvent(ev))
        {
            if ((ev.Type == Event::Closed) || ((ev.Type == Event::KeyPressed) && (ev.Key.Code == Key::Escape)))
            {
                window.Close();
                break;
            }
        }

		float deltaT = window.GetFrameTime();

		if(window.GetInput().IsKeyDown(Key::Left))
		{
			x -= 200 * deltaT;
		}
		if(window.GetInput().IsKeyDown(Key::Right))
		{
			x += 200 * deltaT;
		}
		if(window.GetInput().IsKeyDown(Key::Up))
		{
			y -= 200 * deltaT;
		}
		if(window.GetInput().IsKeyDown(Key::Down))
		{
			y += 200 * deltaT;
		}
		ship.SetPosition(x, y);

		window.Clear();
        window.Draw(backgroundSprite);
		window.Draw(ship);
        window.Display();
	}
    return 0;
}
