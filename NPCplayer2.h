#pragma once
#include <SFML\Graphics.hpp>
#include "BTMath.h" 
#include "Physics.h"
#include "Thor/Vectors.hpp"

class NPCplayer2
{
public:
	NPCplayer2(std::vector<sf::CircleShape> &Node);
	~NPCplayer2();

	void update(double t);
	void render(sf::RenderWindow &window);
	void setLocation();
	void setNPC(int car_ID);
	sf::FloatRect boundingBox();

	sf::Vector2f m_motion;
	sf::Vector2f follow();

private:
	Physics physics;

	float timer;
	float m_acceleration;

	double m_degree;

	int m_dirction;
	int m_car_id;
	int currentNode = 38;

	const float MAX_FORCE = 10.0f;
	const float MAX_SEE_AHEAD = 50.0f;
	float MAX_SPEED = 200.0F;

	sf::Vector2f m_steering;

	sf::Texture m_texture; // car texture
	sf::Sprite m_sprite; // car sprite

	sf::Vector2f m_postion;

	float located_time;
	sf::Vector2f location_record;

	std::vector<sf::CircleShape> m_NodeCircle;
};
