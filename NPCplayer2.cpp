#include "NPCplayer2.h"

NPCplayer2::NPCplayer2(std::vector<sf::CircleShape> &Node) :
	m_acceleration(100),
	m_degree(255),
	m_postion(570, 750),
	m_dirction(rand() % 5 - 3),
	m_car_id(rand() % 4),
	timer(1.5f),
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

	if (Math::distance(m_postion, target) <= 10)
	{
		currentNode++;
		if (currentNode >= m_NodeCircle.size())
		{
			currentNode = 38;
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

void NPCplayer2::update(double t, int car_id)
{
	sf::Vector2f vectorToNode = follow();

	auto dest = atan2(-1 * m_velocity.y, -1 * m_velocity.x) / thor::Pi * 180 + 180;

	auto currentRotation = m_degree;

	if (std::round(currentRotation - dest) == 0.0)
	{
		m_steering.x = 0;
		m_steering.y = 0;
	}
	else if (static_cast<int>(std::round(dest - currentRotation + 360)) % 360 < 180)
	{

		m_degree += 5;
		if (m_degree > 359)
		{
			m_degree = 0 - m_degree;
		}
	}
	else
	{
		m_degree -= 5;
		if (m_degree < 0)
		{
			m_degree = 359 + m_degree;
		}
	}

	if (m_car_id == car_id)
	{
		m_car_id = rand() % 4;
	}

	sf::IntRect car(0, m_car_id * 30, 50, 30);
	m_sprite.setTextureRect(car);

	if (thor::length(vectorToNode) != 0)
	{
		m_steering += thor::unitVector(vectorToNode);

	}

	//m_steering += collisionAvoidance(aiId, entities);
	m_steering = Math::truncate(m_steering, MAX_FORCE);
	m_velocity = Math::truncate(m_velocity + m_steering, MAX_SPEED);
	m_postion += m_velocity;


	m_sprite.setPosition(m_postion);
	m_sprite.setRotation(m_degree);
}


sf::FloatRect NPCplayer2::getRect()
{
	return sf::FloatRect(m_postion.x - m_sprite.getOrigin().x, m_postion.y - m_sprite.getOrigin().y, 50, 30);
}

void NPCplayer2::render(sf::RenderWindow &window)
{
	window.draw(m_sprite);
}
