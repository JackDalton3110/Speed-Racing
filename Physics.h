#pragma once

#include <SFML\System.hpp>

class Physics
{
public:
	Physics();
	~Physics();

	void update(double t, sf::Vector2f motion, float acceleration, float degree);
	sf::Vector2f getDistance();
	sf::Vector2f getMotion();
	float getVelocity();
	void slowDown();
	void resetGravity();

private:
	float pi;
	float m_gravity;
	float m_radius;
	float m_friction_rote;

	sf::Vector2f m_motion;
	sf::Vector2f m_distance;
	sf::Vector2f m_friction;
	sf::Vector2f m_acceleration;


	float m_pixelToMeter;
};
