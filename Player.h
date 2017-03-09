#pragma once
#include <SFML\Graphics.hpp>

#include "Physics.h"
#include "Controller.h"

class Player
{
public:
	Player();
	~Player();

	void update(double t);
	void render(sf::RenderWindow &window);
private:
	Physics physics;
	Xbox360Controller controller;

	float m_acceleration;
	float m_degree;
	float m_velocity;

	sf::Vector2f m_positon;

	sf::RectangleShape m_player;
};