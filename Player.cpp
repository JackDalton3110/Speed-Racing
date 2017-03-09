#include "Player.h"

Player::Player():
	m_acceleration(0),
	m_degree(0),
	m_positon(300,300),
	m_velocity(0)
{
	m_player.setPosition(m_positon);
	m_player.setSize(sf::Vector2f(30, 20));
	m_player.setFillColor(sf::Color::Blue);
	m_player.setOrigin(15, 10);
}

Player::~Player()
{

}

void Player::update(double t)
{

	controller.update();


	if (controller.RTrigger() >= 5)
	{
		m_acceleration = controller.RTrigger();
	}

	if (controller.LTrigger() <= -5)
	{
		m_acceleration = controller.LTrigger();
	}

	if (controller.LeftThumbSticks().x <= -20 ||
		controller.LeftThumbSticks().x >= 20)
	{
		m_degree += controller.LeftThumbSticks().x / 20;
		if (m_degree > 360)
		{
			m_degree = 0;
		}
		
		if (m_degree < 0)
		{
			m_degree = 360;
		}
	}

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

	m_player.setPosition(m_positon);
	m_player.setRotation(m_degree);
}

void Player::render(sf::RenderWindow &window)
{
	window.clear(sf::Color::White);
	window.draw(m_player);
}
