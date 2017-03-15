#pragma once
#include <SFML\Graphics.hpp>
#include <string>

#include "Physics.h"
#include "Controller.h"

class Game;

class Player
{
public:
	Player();
	~Player();

	void update(double t, int car_ID);
	void render(sf::RenderWindow &window);
	
private:
	Physics physics;
	Xbox360Controller controller;

	sf::Font m_font;
	sf::Text m_text[3]; // text 0 for time, text 1 for motion, text 2 for loop
	sf::Text m_timer; // text for timer

	float m_acceleration;
	float m_degree;
	float m_velocity;

	int timer_mis; // millisecond
	int timer_sec; // second
	int timer_min; // minute

	sf::View view; // camera

	sf::Vector2f m_postion;

	sf::Texture m_texture; // car texture
	sf::Sprite m_sprite; // car sprite

	std::string intToString(int num); // int to string
};