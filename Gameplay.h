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
	Gameplay(Game &game, sf::Font font);
	~Gameplay();
	void update(double t, int car_id, Xbox360Controller& controller);
	void render(sf::RenderWindow &window);

	void getStatus(float maxspeed, float accelecation, float handling);
private:
	Player m_player;
	NPCplayer m_npc;

	Game *m_game;

	sf::Font m_font;

	float max_speed; // max speed of player
	float m_acceleration; // the acceleration of player
	float m_handling; // the handling of player
};

#endif // GAMEPLAY
