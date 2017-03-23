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
	void collisionCheck();
	void endScreen();
	void startCount();

	Player & m_player;
	NPCplayer m_npc;

	NPCplayer1 m_npc1;
	NPCplayer2 m_npc2;
	
	Game *m_game;
	sf::Font m_font;

	float max_speed; // max speed of player
	float m_acceleration; // the acceleration of player
	float m_handling; // the handling of player

	bool game_start = true;
	bool game_pause = false;
	bool m_countdown = false;
	float restart_countdown = 3.0f;
	float start_count = 5.0f;
	int button_ID = 0;
	sf::Text countdown_text;
	sf::Text m_textMessage[2];
	sf::RectangleShape m_selection[2];

	sf::Texture m_signal_texture;
	sf::Texture m_goTexture;
	sf::Sprite m_signal_sprite;
	sf::Sprite m_goSprite;

	bool game_end = false;
	float end_countdown = 10.0f;
	sf::Vector2f board_position;
	sf::Text time_board[4];
	sf::RectangleShape rank_board[4];
};

#endif // GAMEPLAY
