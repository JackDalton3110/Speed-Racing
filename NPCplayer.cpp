#include "NPCplayer.h"

NPCplayer::NPCplayer() :
	m_acceleration(200),
	m_degree(0),
	m_positon(300, 300),
	m_velocity(0),
	m_dirction(rand() % 5 - 3),
	timer(1.5f)
{
	m_driver.setPosition(m_positon);
	m_driver.setSize(sf::Vector2f(30, 20));
	m_driver.setFillColor(sf::Color::Red);
	m_driver.setOrigin(15, 10);
}

NPCplayer::~NPCplayer()
{

}

void NPCplayer::update(double t)
{
	if (timer < 0)
	{
		timer = 1.5f;
		m_dirction = rand() % 5 - 3;
	}


	timer -= t;
	m_degree += m_dirction;

	if (m_positon.x > 1000)
	{
		m_velocity = -m_velocity * 0.5;
		m_positon.x = 1000;
	}

	if (m_positon.y > 800)
	{
		m_velocity = -m_velocity * 0.5;
		m_positon.y = 800;
	}

	if (m_positon.x < 0)
	{
		m_velocity = -m_velocity * 0.5;
		m_positon.x = 0;
	}

	if (m_positon.y < 0)
	{
		m_velocity = -m_velocity * 0.5;
		m_positon.y = 0;
	}

	physics.update(t, m_velocity, m_acceleration, m_degree);
	m_velocity = physics.getVelocity();
	m_positon.x += physics.getDistance().x;
	m_positon.y += physics.getDistance().y;

	m_driver.setPosition(m_positon);
	m_driver.setRotation(m_degree);
}

void NPCplayer::render(sf::RenderWindow &window)
{
	window.draw(m_driver);
}
