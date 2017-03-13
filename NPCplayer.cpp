#include "NPCplayer.h"

NPCplayer::NPCplayer() :
	m_acceleration(200),
	m_degree(0),
	m_positon(300, 300),
	m_velocity(0),
	m_dirction(rand() % 5 - 3),
	m_car_id(rand()%4),
	timer(1.5f)
{
	if (!m_texture.loadFromFile("images/carSprite.png"))
	{
		std::string s("error loading texture from file");
		throw std::exception(s.c_str());
	}
	m_sprite.setTexture(m_texture);
	m_sprite.setOrigin(25, 15);
	m_sprite.setPosition(m_positon);

}

NPCplayer::~NPCplayer()
{

}

void NPCplayer::update(double t, int car_id)
{
	if (timer < 0)
	{
		timer = 1.5f;
		m_dirction = rand() % 5 - 3;
	}

	if (m_car_id == car_id)
	{
		m_car_id = rand() % 4;
	}

	sf::IntRect car(0, m_car_id * 30, 50, 30);
	m_sprite.setTextureRect(car);

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

	m_sprite.setPosition(m_positon);
	m_sprite.setRotation(m_degree);
}

void NPCplayer::render(sf::RenderWindow &window)
{
	window.draw(m_sprite);
}
