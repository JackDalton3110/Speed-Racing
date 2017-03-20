#pragma once
#include <SFML\Graphics.hpp>
#include "Physics.h"
#include "BTMath.h"
#include <Thor/Vectors.hpp>
#include "LevelLoader.h"

class NPCplayer
{
public:
	NPCplayer(std::vector<sf::CircleShape> & Node);
	~NPCplayer();
	void update(double t, int car_id);
	void render(sf::RenderWindow &window);
	sf::Vector2f follow();

	sf::FloatRect getRect();
	sf::Vector2f m_motion;

private:
	Physics physics;
	float m_velocity;

	float m_acceleration;
	float m_degree;

	int m_dirction;
	float timer;

	int m_car_id;
	int currentNode = 0;

	sf::Texture m_texture; // car texture
	sf::Sprite m_sprite; // car sprite

	sf::Vector2f m_postion;

	float located_time;
	sf::Vector2f location_record;

	std::vector<sf::CircleShape> & m_NodeCircle;
};