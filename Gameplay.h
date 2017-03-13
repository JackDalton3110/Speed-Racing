#pragma once

#include "Player.h"
#include "NPCplayer.h"
#include "Game.h"

#ifndef GAMEPLAY
#define GAMEPLAY

class Game;

class Gameplay
{
public:
	Gameplay(Game &game, sf::Font font);
	~Gameplay();

	void update(double t, int car_id);
	void render(sf::RenderWindow &window);

private:
	Player m_player;
	NPCplayer m_npc;

	Game *m_game;

	sf::Font m_font;

};

#endif // GAMEPLAY
