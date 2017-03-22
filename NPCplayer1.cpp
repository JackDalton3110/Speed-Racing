#include "NPCplayer1.h"

NPCplayer1::NPCplayer1(std::vector<sf::CircleShape> &Node) :
	m_acceleration(150),
	m_degree(255),
	m_postion(540, 734),
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

NPCplayer1::~NPCplayer1()
{

}

sf::Vector2f NPCplayer1::follow()
{
	sf::Vector2f target;
	target = m_NodeCircle.at(currentNode).getPosition();

	if (Math::distance(m_postion, target) <= 14)
	{
		currentNode++;
		if (currentNode >= 39)
		{
			currentNode = 25;
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

void NPCplayer1::update(double t, int car_id)
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
		m_degree += 6;
	}
	else
	{
		m_degree -= 6;
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

	m_steering = Math::truncate(m_steering, MAX_FORCE);
	m_velocity = Math::truncate(m_velocity + m_steering, MAX_SPEED);
	m_postion += m_velocity;


	m_sprite.setPosition(m_postion);
	m_sprite.setRotation(m_degree);
}


sf::FloatRect NPCplayer1::getRect()
{
	return sf::FloatRect(m_postion.x - m_sprite.getOrigin().x, m_postion.y - m_sprite.getOrigin().y, 50, 30);
}

void NPCplayer1::render(sf::RenderWindow &window)
{
	window.draw(m_sprite);
}
