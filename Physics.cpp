#include "Physics.h"
#include <math.h>

Physics::Physics() :
	pi(acos(-1)),
	m_velocity(0),
	m_distance(0),
	m_gravity(9.8),
	m_friction(0),
	m_pixelToMeter(10),
	m_radius(0)
{

}

Physics::~Physics()
{

}

void Physics::update(double t, float velocity, float acceleration, float degree)
{
	acceleration /= m_pixelToMeter;

	m_friction = (0.05 * m_gravity * velocity) / m_pixelToMeter;

	m_velocity = velocity + (acceleration - m_friction) * t;

	m_distance = velocity * t + 0.5 * acceleration * t * t;

	m_radius = degree * pi / 180;
}

sf::Vector2f Physics::getDistance()
{
	return sf::Vector2f(cos(m_radius) * m_distance, sin(m_radius) * m_distance);
}

float Physics::getVelocity()
{
	return m_velocity;
}