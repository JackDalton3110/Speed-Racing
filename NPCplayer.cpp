#include "NPCplayer.h"

NPCplayer::NPCplayer(std::vector<sf::CircleShape> &Node) :
	m_acceleration(10),
	m_degree(0),
	m_postion(500, 500),
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

NPCplayer::~NPCplayer()
{

}

sf::Vector2f NPCplayer::follow()
{
	sf::Vector2f target;
	target = m_NodeCircle.at(currentNode).getPosition();

	if (Math::distance(m_postion, target) <= 10)
	{
		currentNode++;
		if (currentNode >= m_NodeCircle.size())
		{
			currentNode = 0;
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

void NPCplayer::timer(double t)
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

void NPCplayer::update(double t, int car_id)
{
	timer(t);

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
		m_degree += 6;
	}
	else
	{
		m_degree -= 6;
	}

	/*if (thor::length(vectorToNode) > MAX_SEE_AHEAD)
	{
		m_acceleration = thor::length(m_velocity);
	}*/

	if (m_car_id == car_id)
	{
		m_car_id = rand() % 4;
	}

	sf::IntRect car(0, m_car_id * 30, 50, 30);
	m_sprite.setTextureRect(car);
	
	if (thor::length(vectorToNode)!= 0)
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


sf::FloatRect NPCplayer::boundingBox()
{
	sf::FloatRect boundingBox(m_sprite.getGlobalBounds().left + 2, m_sprite.getGlobalBounds().top + 2, m_sprite.getGlobalBounds().width - 4, m_sprite.getGlobalBounds().height - 5);
	return boundingBox;
}

void NPCplayer::render(sf::RenderWindow &window)
{
	window.draw(m_sprite);
}
