#pragma once
#ifndef GAMEPLAY
#define GAMEPLAY
#include "Player.h"
#include "NPCplayer.h"
#include "Game.h"
#include "Controller.h"


class Game;

class Gameplay
{
public:
	Gameplay(Game &game, sf::Font font, Player & player);
	~Gameplay();
	void update(double t, int car_id, Xbox360Controller& controller);
	void render(sf::RenderWindow &window);

private:
	Player & m_player;
	NPCplayer m_npc;

	Game *m_game;

	sf::Font m_font;

};

#endif // GAMEPLAY
