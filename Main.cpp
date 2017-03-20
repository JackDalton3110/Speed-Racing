#ifdef _DEBUG
#pragma comment (lib, "sfml-graphics-d.lib")
#pragma comment (lib, "sfml-audio-d.lib")
#pragma comment (lib, "sfml-system-d.lib")
#pragma comment (lib, "sfml-window-d.lib")
#pragma comment (lib, "sfml-main-d.lib")
#pragma comment (lib, "sfml-network-d.lib")
#pragma comment (lib, "sfeMovie-d.lib")
#pragma comment (lib, "thor-d.lib") 
<<<<<<< HEAD
#pragma comment(lib, "libyaml-cppmdd.lib")
=======
#pragma comment(lib,"libyaml-cppmdd")
>>>>>>> bce91fc31c547773468f566ae57721987f17200a
#else
#pragma comment (lib, "sfml-graphics-d.lib")
#pragma comment (lib, "sfml-audio-d.lib")
#pragma comment (lib, "sfml-system-d.lib")
#pragma comment (lib, "sfml-window-d.lib")
#pragma comment (lib, "sfml-main-d.lib")
#pragma comment (lib, "sfml-network-d.lib")
#pragma comment (lib, "sfeMovie-d.lib")
#pragma comment (lib, "thor.lib") 
#pragma comment (lib, "libyaml-cppmdd.lib")
#endif

#include "game.h"

int main()
{
	Game Game;
	Game.run();
	return 1;
}