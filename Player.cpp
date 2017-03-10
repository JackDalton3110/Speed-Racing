#include "Player.h"

Player::Player():
	m_acceleration(0),
	m_degree(0),
	m_positon(600,600),
	m_velocity(0)
{
	if (!m_font.loadFromFile("c:/windows/fonts/comic.ttf"))
	{
		
	}

	if (!m_texture.loadFromFile("./images/Car-sprits.png"))
	{
		std::string s("error loading texture from file");
		throw std::exception(s.c_str());
	}
	m_sprite.setTexture(m_texture);
	sf::IntRect rect(0,0,200,100);
	m_sprite.setTextureRect(rect);

	m_player.setPosition(m_positon);
	m_player.setSize(sf::Vector2f(30, 20));
	m_player.setFillColor(sf::Color::Blue);
	m_player.setOrigin(15, 10);

	m_text.setFont(m_font);
	m_text.setColor(sf::Color::Black);
}

Player::~Player()
{

}

void Player::update(double t)
{

	controller.update();


	if (controller.RTrigger() >= 5)
	{
		m_acceleration = controller.RTrigger(); // the acceleration follow the trigger
	}

	if (controller.LTrigger() <= -5)
	{
		m_acceleration = controller.LTrigger(); // the acceleration follow the trigger
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
	m_text.setString(intToString(m_velocity));
}

void Player::render(sf::RenderWindow &window)
{
	window.clear(sf::Color::White);
	window.draw(m_player);
	window.draw(m_text);
}

std::string Player::intToString(int num) {
	char numString[10];
	sprintf_s(numString, "%i", num);
	return numString;
}