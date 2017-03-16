#pragma once
#include <SFML\Graphics.hpp>

#include "Physics.h"

class NPCplayer
{
public:
	NPCplayer();
	~NPCplayer();

	void update(double t, int car_id);
	void render(sf::RenderWindow &window);
private:
	Physics physics;
	float m_velocity;

	float m_acceleration;
	float m_degree;

	sf::Vector2f m_motion;
	int m_dirction;
	float timer;

	int m_car_id;

	sf::Texture m_texture; // car texture
	sf::Sprite m_sprite; // car sprite

	sf::Vector2f m_postion;

	float located_time;
	sf::Vector2f location_record;
};