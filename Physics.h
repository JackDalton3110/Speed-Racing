#pragma once

#include <SFML\System.hpp>

class Physics
{
public:
	Physics();
	~Physics();

	void update(double t, float velocity, float acceleration, float degree);
	sf::Vector2f getDistance();
	float getVelocity();
	bool impactCheck();

private:
	float pi;
	float m_velocity;
	float m_distance;
	float m_gravity;
	float m_friction;
	float m_radius;


	float m_pixelToMeter;
};
