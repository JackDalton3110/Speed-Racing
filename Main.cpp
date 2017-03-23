#ifdef _DEBUG
#pragma comment (lib, "sfml-graphics-d.lib")
#pragma comment (lib, "sfml-audio-d.lib")
#pragma comment (lib, "sfml-system-d.lib")
#pragma comment (lib, "sfml-window-d.lib")
#pragma comment (lib, "sfml-main-d.lib")
#pragma comment (lib, "sfml-network-d.lib")
#pragma comment (lib, "sfeMovie-d.lib")
#pragma comment (lib, "thor-d.lib") 
#pragma comment(lib,"libyaml-cppmdd")
#pragma comment(lib, "libyaml-cppmdd.lib")

#else
#pragma comment (lib, "sfml-graphics.lib")
#pragma comment (lib, "sfml-audio.lib")
#pragma comment (lib, "sfml-system.lib")
#pragma comment (lib, "sfml-window.lib")
#pragma comment (lib, "sfml-main.lib")
#pragma comment (lib, "sfml-network.lib")
#pragma comment (lib, "sfeMovie.lib")
#pragma comment (lib, "thor.lib") 
#pragma comment(lib,"libyaml-cppmd") // NB –cppmd (not –cppmdd)
#endif

#include "game.h"

int main()
{
	Game Game;
	Game.run();
	return 1;
}