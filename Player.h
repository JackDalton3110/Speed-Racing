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
	float getPositionX(float xPos);
	float getPositionY(float yPos);
	
private:
	Physics physics;
	Xbox360Controller controller;

	sf::Font m_font;
	sf::Text m_text[3]; // text 0 for time, text 1 for motion, text 2 for loop


	float m_acceleration;
	float m_degree;
	float m_velocity;

	sf::View view; // camera

	sf::Vector2f m_positon;

	sf::Texture m_texture; // car texture
	sf::Sprite m_sprite; // car sprite

	sf::RectangleShape m_filed;

	std::string intToString(int num); // int to string
};