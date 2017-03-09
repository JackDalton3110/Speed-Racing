#pragma once
#include <SFML\Graphics.hpp>

#include "Physics.h"

class NPCplayer
{
public:
	NPCplayer();
	~NPCplayer();

	void update(double t);
	void render(sf::RenderWindow &window);
private:
	Physics physics;

	float m_acceleration;
	float m_degree;
	float m_velocity;

	int m_dirction;
	float timer;

	sf::Vector2f m_positon;

	sf::RectangleShape m_driver;
};