#include "Physics.h"
#include <math.h>

Physics::Physics() :
	pi(acos(-1)),
	m_motion(0, 0),
	m_distance(0, 0),
	m_gravity(9.8),
	m_friction(0, 0),
	m_pixelToMeter(1),
	m_radius(0),
	m_friction_rote(0.2)
{

}

Physics::~Physics()
{

}

void Physics::update(double t, sf::Vector2f motion, float acceleration, float degree)
{
	m_radius = degree * pi / 180;

	acceleration /= m_pixelToMeter;
	m_acceleration = sf::Vector2f(acceleration / m_pixelToMeter * cos(m_radius), acceleration / m_pixelToMeter * sin(m_radius)); // convert acceleration to vect2f 

	m_friction = sf::Vector2f(m_friction_rote * m_gravity * motion.x, m_friction_rote * m_gravity * motion.y); // get frction by motion

	m_motion = sf::Vector2f(motion.x + (m_acceleration.x - m_friction.x) * t, motion.y + (m_acceleration.y - m_friction.y) * t); // get new motion 

	m_distance.x = motion.x * t + 0.5 * m_acceleration.x * t * t;
	m_distance.y = motion.y * t + 0.5 * m_acceleration.y * t * t; // get movement
}

sf::Vector2f Physics::getDistance()
{
	return m_distance;
}

float Physics::getVelocity()
{
	return sqrt(m_motion.x * m_motion.x + m_motion.y * m_motion.y);
}

sf::Vector2f Physics::getMotion()
{
	return m_motion;
}


