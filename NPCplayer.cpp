#include "NPCplayer.h"

NPCplayer::NPCplayer() :
	m_acceleration(200),
	m_degree(0),
	m_postion(300, 300),
	m_velocity(0),
	m_dirction(rand() % 5 - 3),
	m_car_id(rand() % 4),
	timer(1.5f),
	located_time(0.1)
{
	if (!m_texture.loadFromFile("images/carSprite.png"))
	{
		std::string s("error loading texture from file");
		throw std::exception(s.c_str());
	}
	m_sprite.setTexture(m_texture);
	m_sprite.setOrigin(25, 15);
	m_sprite.setPosition(m_postion);

}

NPCplayer::~NPCplayer()
{

}

void NPCplayer::update(double t, int car_id)
{
	located_time -= t;
	if (located_time <= 0)
	{
		location_record = m_postion;
		located_time = 0.1;
	}

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

	if (m_postion.x > 1350)
	{
		m_motion.x = -m_motion.x * 0.5;
		m_postion.x = 1350;
	}

	if (m_postion.y > 1700)
	{
		m_motion.y = -m_motion.y * 0.5;
		m_postion.y = 1700;
	}

	if (m_postion.x < 0)
	{
		m_motion.x = -m_motion.x * 0.5;
		m_postion.x = 0;
	}

	if (m_postion.y < 0)
	{
		m_motion.y = -m_motion.y * 0.5;
		m_postion.y = 0;
	}

	physics.update(t, m_motion, m_acceleration, m_degree);
	m_motion = physics.getMotion();
	m_velocity = physics.getVelocity();
	m_postion.x += physics.getDistance().x;
	m_postion.y += physics.getDistance().y;

	m_sprite.setPosition(m_postion);
	m_sprite.setRotation(m_degree);
}

sf::FloatRect NPCplayer::getRect()
{
	return sf::FloatRect(m_postion.x - m_sprite.getOrigin().x, m_postion.y - m_sprite.getOrigin().y, 50, 30);
}

void NPCplayer::render(sf::RenderWindow &window)
{
	window.draw(m_sprite);
}
