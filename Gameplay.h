#pragma once
#ifndef GAMEPLAY
#define GAMEPLAY
#include "Player.h"
#include "NPCplayer.h"
#include "Game.h"
#include "Controller.h"
#include "NPCplayer1.h"
#include "NPCplayer2.h"


class Game;

class Gameplay
{
public:

	Gameplay(Game &game, sf::Font font, Player & player, std::vector<sf::CircleShape> &Node);
	~Gameplay();
	void update(double t, int car_id, Xbox360Controller& controller);
	void render(sf::RenderWindow &window);

	void getStatus(float maxspeed, float accelecation, float handling);
private:
	Player & m_player;
	NPCplayer m_npc;

	NPCplayer1 m_npc1;
	NPCplayer2 m_npc2;
	
	Game *m_game;
	sf::Font m_font;

	float max_speed; // max speed of player
	float m_acceleration; // the acceleration of player
	float m_handling; // the handling of player

	sf::RectangleShape box1;
	sf::RectangleShape box2;
	sf::FloatRect intersectLine();
	sf::RectangleShape m_finishLine;

	sf::Vector2f m_finishLinePos;
};

#endif // GAMEPLAY
