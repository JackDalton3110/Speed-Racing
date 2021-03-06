#include "NPCplayer.h"

NPCplayer::NPCplayer(std::vector<sf::CircleShape> &Node) :
	m_acceleration(0),
	m_degree(255),
	m_postion(563, 700),
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
	//assign to sprite
	m_sprite.setTexture(m_texture);
	m_sprite.setOrigin(25, 15);//set origin
	m_sprite.setPosition(m_postion);//set position
	m_sprite.setScale(0.5f, 0.5f);//set scale
	m_sprite.setRotation(m_degree);

}



NPCplayer::~NPCplayer()
{

}

void NPCplayer::resetNPC()
{
	m_halfway = false;
	m_postion.x = 563;
	m_postion.y = 700;
	m_degree = 255;
	m_motion.x = 0;
	m_motion.y = 0;
	m_acceleration = 0;
	currentNode = 0;
	m_laps = 1;
}

void NPCplayer::nextLap()
{
	//reset halfway bool, up laps
	m_halfway = false;
	m_laps++;
}

sf::Vector2f NPCplayer::follow()
{
	//make npc car follow node path
	sf::Vector2f target;
	target = m_NodeCircle.at(currentNode).getPosition();

	if (Math::distance(m_postion, target) <= 50)
	{
		//once within certain distancew of node
		m_acceleration *= 0.3;
		if (currentNode == 13)
		{
			m_halfway = true;
		}

		currentNode++;
		m_acceleration *= 0.8;
		if (currentNode >= 25)
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

void NPCplayer::DifficultyAdjust(bool easy, bool normal, bool hard)
{
	//adjust speed of ai car dependant of difficulty
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

void NPCplayer::setNPC(int car_ID)
{
	//set npc car
	if (m_car_id == car_ID)
	{
		m_car_id = rand() % 4;
	}

	sf::IntRect car(0, m_car_id * 30, 50, 30);
	m_sprite.setTextureRect(car);
}

void NPCplayer::update(double t)
{
	timer(t);

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

	sf::Vector2f vectorToNode = follow();
	//steering and motion of AI cars
	auto dest = atan2(-1 * m_motion.y, -1 * m_motion.x) / thor::Pi * 180 + 180;

	auto currentRotation = m_degree;

	if (std::round(currentRotation - dest) == 0.0)
	{
		m_steering.x = 0;
		m_steering.y = 0;
	}
	else if (static_cast<int>(std::round(dest - currentRotation + 360)) % 360 < 180)
	{
		//turning and degree of which cars turn at
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

	sf::IntRect car(0, m_car_id * 30, 50, 30);
	m_sprite.setTextureRect(car);

	if (thor::length(vectorToNode) != 0)
	{
		//distance AI cars to node
		m_steering += thor::unitVector(vectorToNode);

	}

	m_steering = Math::truncate(m_steering, MAX_FORCE);
	m_motion = Math::truncate(m_motion + m_steering, m_acceleration);
	m_postion.x += m_motion.x * t;
	m_postion.y += m_motion.y * t;

	m_sprite.setPosition(m_postion);
	m_sprite.setRotation(m_degree);
}



void NPCplayer::setLocation()
{
	m_postion = location_record;
	m_acceleration = 0;
}

sf::FloatRect NPCplayer::boundingBox()
{
	//bounding box for collision
	sf::FloatRect boundingBox(m_sprite.getGlobalBounds().left + 2, m_sprite.getGlobalBounds().top + 2, m_sprite.getGlobalBounds().width - 5, m_sprite.getGlobalBounds().height - 5);
	return boundingBox;
}

void NPCplayer::render(sf::RenderWindow &window)
{
	window.draw(m_sprite);
}

