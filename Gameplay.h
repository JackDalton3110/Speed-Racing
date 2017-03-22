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

	Gameplay(Game &game, sf::Font font, Player & player, std::vector<sf::CircleShape> &Node);
	~Gameplay();
	void update(double t, int car_id, Xbox360Controller& controller);
	void render(sf::RenderWindow &window);

	void getStatus(float maxspeed, float accelecation, float handling);
private:
	void collisionCheck();

	Player & m_player;
	NPCplayer m_npc;

	Game *m_game;

	sf::Font m_font;

	float max_speed; // max speed of player
	float m_acceleration; // the acceleration of player
	float m_handling; // the handling of player

	bool game_pause = false;
	bool m_countdown = false;
	int button_ID = 0;
	float restart_countdown = 3.0f;
	sf::Text countdown_text;
	sf::Text m_textMessage[2];
	sf::RectangleShape m_selection[2];
};

#endif // GAMEPLAY
