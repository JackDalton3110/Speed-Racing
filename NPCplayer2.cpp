#include "NPCplayer2.h"

NPCplayer2::NPCplayer2(std::vector<sf::CircleShape> &Node) :
	m_acceleration(150),
	m_degree(255),
	m_postion(570, 750),
	m_dirction(rand() % 5 - 3),
	m_car_id(rand() % 4),
	located_time(0.1),
	m_NodeCircle(Node)
{
	if (!m_texture.loadFromFile("images/carSprite.png"))
	{
		std::string s("error loading texture from file");
		throw std::exception(s.c_str());
	}
	m_sprite.setTexture(m_texture);
	m_sprite.setOrigin(25, 15);
	m_sprite.setPosition(m_postion);
	m_sprite.setScale(0.5f, 0.5f);

}

NPCplayer2::~NPCplayer2()
{

}

sf::Vector2f NPCplayer2::follow()
{
	sf::Vector2f target;
	target = m_NodeCircle.at(currentNode).getPosition();

	if (Math::distance(m_postion, target) <= 50)
	{
		if (currentNode == 45)
		{
			m_halfway = true;
		}

		currentNode++;
		if (currentNode >= m_NodeCircle.size())
		{
			currentNode = 39;
		}
	}

	if (thor::length(target) != 0)
	{
		return target - m_postion;
	}
	else
	{
		return sf::Vector2f();
	}
}

void NPCplayer2::setNPC(int car_ID)
{
	if (m_car_id == car_ID)
	{
		m_car_id = rand() % 4;
	}

	sf::IntRect car(0, m_car_id * 30, 50, 30);
	m_sprite.setTextureRect(car);
}

sf::FloatRect NPCplayer2::boundingBox()
{
	sf::FloatRect boundingBox(m_sprite.getGlobalBounds().left + 2, m_sprite.getGlobalBounds().top + 2, m_sprite.getGlobalBounds().width - 5, m_sprite.getGlobalBounds().height - 5);
	return boundingBox;
}

void NPCplayer2::timer(double t)
{
	// timer part
	timer_mis += t * 100;

	if (timer_mis >= 100) // when millisecond great than 100, second add 1
	{
		timer_sec++;
		timer_mis = 0;
	}

	if (timer_sec >= 60) // when second over 60, minute add 1
	{
		timer_min++;
		timer_sec = 0;
	}
}

void NPCplayer2::update(double t)
{
	timer(t);

	sf::Vector2f vectorToNode = follow();

	located_time -= t;
	if (located_time <= 0)
	{
		location_record = m_postion;
		located_time = 0.1;
	}

	if (m_acceleration < MAX_SPEED)
	{
		m_acceleration += 5;
	}

	auto dest = atan2(-1 * m_motion.y, -1 * m_motion.x) / thor::Pi * 180 + 180;

	auto currentRotation = m_degree;

	if (std::round(currentRotation - dest) == 0.0)
	{
		m_steering.x = 0;
		m_steering.y = 0;
	}
	else if (static_cast<int>(std::round(dest - currentRotation + 360)) % 360 < 180)
	{

		m_degree += 10;
		if (m_degree > 359)
		{
			m_degree = 0 - m_degree;
		}
	}
	else
	{
		m_degree -= 10;
		if (m_degree < 0)
		{
			m_degree = 359 + m_degree;
		}
	}

	sf::IntRect car(0, m_car_id * 30, 50, 30);
	m_sprite.setTextureRect(car);

	if (thor::length(vectorToNode) != 0)
	{
		m_steering += thor::unitVector(vectorToNode);

	}

	//m_steering += collisionAvoidance(aiId, entities);
	m_steering = Math::truncate(m_steering, MAX_FORCE);
	m_motion = Math::truncate(m_motion + m_steering, m_acceleration);
	m_postion.x += m_motion.x * t;
	m_postion.y += m_motion.y * t;


	m_sprite.setPosition(m_postion);
	m_sprite.setRotation(m_degree);
}

void NPCplayer2::setLocation()
{
	m_postion = location_record;
	m_acceleration = 0;
}

void NPCplayer2::render(sf::RenderWindow &window)
{
	window.draw(m_sprite);
}
