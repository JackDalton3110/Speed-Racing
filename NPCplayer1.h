#pragma once
#include <SFML\Graphics.hpp>
#include "BTMath.h" 
#include "Physics.h"
#include "Thor/Vectors.hpp"

class NPCplayer1
{
public:
	NPCplayer1(std::vector<sf::CircleShape> &Node);
	~NPCplayer1();

	void update(double t);
	void render(sf::RenderWindow &window);
	void setLocation();
	void setNPC(int car_ID);
	sf::FloatRect boundingBox();

	sf::Vector2f m_motion;
	sf::Vector2f follow();

	int timer_mis; // millisecond
	int timer_sec; // second
	int timer_min; // minute

private:
	void timer(double t);

	Physics physics;
	
	float m_acceleration;

	double m_degree;

	int m_dirction;
	int m_car_id;
	int currentNode = 26;

	const float MAX_FORCE = 8.0f;
	const float MAX_SEE_AHEAD = 50.0f;
	float MAX_SPEED = 150.0F;

	sf::Vector2f m_steering;

	sf::Texture m_texture; // car texture
	sf::Sprite m_sprite; // car sprite

	sf::Vector2f m_postion;

	float located_time;
	sf::Vector2f location_record;

	std::vector<sf::CircleShape> m_NodeCircle;
}; 
