#include "SFML/Graphics.hpp"
#include "cmath"
#include "kf/kf_log.h"
#include "qgf2d/system.h"
#include "qgf2d/anim.h"

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

	Image gabeImage;
    if (!gabeImage.LoadFromFile("data/gabe.png"))
        return EXIT_FAILURE;

	Sprite gabeSprite(gabeImage);
	gabeSprite.SetCenter(23,63);

	Anim gabeAnim(&gabeSprite,0,0,46,64,6,2);
	gabeAnim.addSequence("idle",0,5,0.5,true);
	gabeAnim.addSequence("run",6,11,0.5,true);

	Shape circle = Shape::Circle(200.0f,300.0f,100.0f,Color::White,2);
	//circle.Rectangle(10,10,100,100,Color::Red);
	circle.EnableFill(true);
	circle.EnableOutline(true);

	float x = 400, y = 300;

	String text;
	text.SetPosition(400,300);
	text.SetText("Hi There");
	
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

		gabeAnim.play("idle",false);
		if(x>window.GetInput().GetMouseX())
		//if(window.GetInput().IsKeyDown(Key::Left))
		{
			x -= 200 * deltaT;
			gabeAnim.play("run",false);
			gabeSprite.FlipX(true);
		}
		if(x<window.GetInput().GetMouseX())
//		if(window.GetInput().IsKeyDown(Key::Right))
		{
			x += 200 * deltaT;
			gabeSprite.FlipX(false);
			gabeAnim.play("run",false);
		}
		if(window.GetInput().IsKeyDown(Key::Up))
		{
			y -= 200 * deltaT;
		}
		if(window.GetInput().IsKeyDown(Key::Down))
		{
			y += 200 * deltaT;
		}
		gabeSprite.SetPosition(x, window.GetInput().GetMouseY());
		gabeAnim.update(deltaT);

		window.Clear(Color(32,200,255));
		window.Draw(Shape::Circle(x,y,40,Color::White,1));
		window.Draw(gabeSprite);
		window.Draw(text);
        window.Display();
	}
    return 0;
}
