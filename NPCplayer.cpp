#include "NPCplayer.h"

NPCplayer::NPCplayer(std::vector<sf::CircleShape> &Node) :
	m_acceleration(10),
	m_degree(0),
	m_postion(500, 500),
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

void NPCplayer::update(double t, int car_id)
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
		m_degree += 1;
	}
	else
	{
		m_degree -= 1;
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
	m_postion += m_steering;

	
	m_sprite.setPosition(m_postion);
	m_sprite.setRotation(m_degree);
}

//void NPCplayer::setLocation()
//{
//	m_postion = location_record;
//	m_acceleration = 0;
//}

sf::FloatRect NPCplayer::getRect()
{
	return sf::FloatRect(m_postion.x - m_sprite.getOrigin().x, m_postion.y - m_sprite.getOrigin().y, 50, 30);
}

void NPCplayer::render(sf::RenderWindow &window)
{
	window.draw(m_sprite);
}
