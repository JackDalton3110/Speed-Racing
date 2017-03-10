#include "Player.h"

Player::Player() :
	m_acceleration(0),
	m_degree(0),
	m_positon(600, 600),
	m_velocity(0)
{
	if (!m_font.loadFromFile("c:/windows/fonts/comic.ttf"))
	{

	}

	m_player.setPosition(m_positon);
	m_player.setSize(sf::Vector2f(30, 20));
	m_player.setFillColor(sf::Color::Blue);
	m_player.setOrigin(15, 10);

	m_filed.setSize(sf::Vector2f(1000, 800));
	m_filed.setPosition(0, 0);
	m_filed.setFillColor(sf::Color::Black);


	m_text.setFont(m_font);
	m_text.setColor(sf::Color::White);

	view.setCenter(sf::Vector2f(m_player.getPosition()));
	view.setSize(sf::Vector2f(1000, 800));
}

Player::~Player()
{

}

void Player::update(double t)
{

	controller.update();


	if (controller.RTrigger() >= 5) // right trigger to speed up
	{
		m_acceleration = controller.RTrigger() * 2;
	}
	else if (controller.RTrigger() < 5 && controller.RTrigger() >= 0)
	{
		m_acceleration = 0;
	}

	if (controller.LTrigger() <= -5)
	{
		m_acceleration = controller.LTrigger() * 2;
	}
	else if (controller.LTrigger() > -5 && controller.LTrigger() <= 0)
	{
		m_acceleration = 0;
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

	physics.update(t, m_velocity, m_acceleration, m_degree); // sand player statu to physics
	m_velocity = physics.getVelocity(); // get new motion from physics
	m_positon.x += physics.getDistance().x; // get new position 
	m_positon.y += physics.getDistance().y;

	m_player.setPosition(m_positon);
	view.setCenter(sf::Vector2f(m_player.getPosition()));


	m_player.setRotation(m_degree);
	m_text.setString(intToString(m_velocity));
}

void Player::render(sf::RenderWindow &window)
{
	window.clear(sf::Color::White);
	window.setView(view);

	window.draw(m_filed);
	window.draw(m_player);
	window.draw(m_text);
}

std::string Player::intToString(int num) {
	char numString[10];
	sprintf_s(numString, "%i", num);
	return numString;
}