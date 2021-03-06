#include "NPCplayer1.h"

NPCplayer1::NPCplayer1(std::vector<sf::CircleShape> &Node) :
	m_acceleration(0),
	m_degree(255),
	m_postion(540, 734),
	m_dirction(rand() % 5 - 3),
	m_car_id(rand() % 4),
	located_time(0.1),
	m_NodeCircle(Node)
{
	//loads image
	if (!m_texture.loadFromFile("images/carSprite.png"))
	{
		std::string s("error loading texture from file");
		throw std::exception(s.c_str());
	}
	//set stats
	m_sprite.setTexture(m_texture);
	m_sprite.setOrigin(25, 15);
	m_sprite.setPosition(m_postion);
	m_sprite.setScale(0.5f, 0.5f);
	m_sprite.setRotation(m_degree);

}

NPCplayer1::~NPCplayer1()
{

}

void NPCplayer1::resetNPC()
{
	//reset for race starting again 
	m_halfway = false;
	m_postion.x = 540;
	m_postion.y = 734;
	m_degree = 255;
	m_motion.x = 0;
	m_motion.y = 0;
	m_acceleration = 0;
	currentNode = 26;
	m_laps = 1;
}

void NPCplayer1::nextLap()
{
	//change halfway to false, up laps
	m_halfway = false;
	m_laps++;
}

sf::Vector2f NPCplayer1::follow()
{
	//AI cars follow nodes path
	sf::Vector2f target;
	target = m_NodeCircle.at(currentNode).getPosition();

	if (Math::distance(m_postion, target) <= 50)
	{

		m_acceleration *= 0.3;
		if (currentNode == 33)
		{
			m_halfway = true;
		}

		currentNode++;
		if (currentNode >= 40)
		{
			currentNode = 26;
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

void NPCplayer1::setNPC(int car_ID)
{
	//sets car colour
	if (m_car_id == car_ID)
	{
		m_car_id = rand() % 4;
	}

	sf::IntRect car(0, m_car_id * 30, 50, 30);
	m_sprite.setTextureRect(car);
}

sf::FloatRect NPCplayer1::boundingBox()
{
	//bounding box for collision
	sf::FloatRect boundingBox(m_sprite.getGlobalBounds().left + 2, m_sprite.getGlobalBounds().top + 2, m_sprite.getGlobalBounds().width - 5, m_sprite.getGlobalBounds().height - 5);
	return boundingBox;
}


void NPCplayer1::DifficultyAdjust(bool easy, bool normal, bool hard)
{
	//change speed through difficulty
	if (easy == true)
	{
		MAX_SPEED = 110.0f;
	}

	if (normal == true)
	{
		MAX_SPEED = 135.0f;
	}

	if (hard == true)
	{
		MAX_SPEED = 150.0f;
	}
}
void NPCplayer1::timer(double t)
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

void NPCplayer1::update(double t)
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
		m_degree += 6;
		if (m_degree > 359)
		{
			m_degree = 0 - m_degree;
		}
	}
	else
	{
		m_degree -= 6;
		if (m_degree < 0)
		{
			m_degree = 359 + m_degree;
		}
	}

	if (thor::length(vectorToNode) != 0)
	{
		m_steering += thor::unitVector(vectorToNode);

	}

	m_steering = Math::truncate(m_steering, MAX_FORCE);
	m_motion = Math::truncate(m_motion + m_steering, m_acceleration);
	m_postion.x += m_motion.x * t;
	m_postion.y += m_motion.y * t;


	m_sprite.setPosition(m_postion);
	m_sprite.setRotation(m_degree);
}

void NPCplayer1::setLocation()
{
	m_postion = location_record;
	m_acceleration = 0;
}

void NPCplayer1::render(sf::RenderWindow &window)
{
	window.draw(m_sprite);
}
