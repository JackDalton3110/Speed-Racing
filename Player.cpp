#include "Player.h"

Player::Player() :
	m_acceleration(100),
	m_degree(255),
	m_velocity(0),
	m_postion(520, 681),
	location_record(0, 0),
	located_time(0.1),
	m_motion(0, 0),
	m_handbrake(0)
{
	if (!m_font.loadFromFile("c:/windows/fonts/comic.ttf"))
	{

	}
	for (int i = 0; i < 2; i++)
	{
		m_text[i].setFont(m_font);
		m_text[i].setColor(sf::Color::Yellow);
	}

	if (!m_texture.loadFromFile("images/carSprite.png"))
	{
		std::string s("error loading texture from file");
		throw std::exception(s.c_str());
	}

	m_sprite.setTexture(m_texture);

	m_sprite.setPosition(m_postion);

	m_sprite.setOrigin(10, 15);


	
	//This scales the player car down
	m_sprite.scale(.5, .5);
	view.setCenter(m_postion); // set player's position to camera
	view.setSize(sf::Vector2f(500, 400)); // set camera's size

	m_timer.setFont(m_font);
	m_lap_timer.setFont(m_font);
	m_timer.setColor(sf::Color::Black);
	m_lap_timer.setColor(sf::Color::Black);
}

Player::~Player()
{

}

void Player::highFriction()
{
	physics.slowDown();
	int x = 0;
}

void Player::normalFriction()
{
	physics.resetGravity();
}


void Player::setPlayerStatus(float maxspeed, float accelecation, float handling)
{
	max_speed = (0.2 * 9.8 * maxspeed) / 100; // get max speed from upgrade
	m_turning = maxspeed * 0.65;
	m_handling = handling / 100 + 0.5;
}

void Player::timer(double t)
{
	controller.update();

	located_time -= t;
	if (located_time <= 0)
	{
		/*location_record = m_postion;*/
		located_time = 0.1;
	}
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
	m_timer.setString(intToString(timer_min) + "::"
		+ intToString(timer_sec) + "::"
		+ intToString(timer_mis)); // convert minute to string

	m_lap_timer.setString(intToString(lap_timer[0]) + "::"
		+ intToString(lap_timer[1]) + "::"
		+ intToString(lap_timer[2])); // convert minute to string

	if (m_postion.y > 1444)
	{
		m_halfway = true;
		std::cout << "halfway::" << std::endl;
	}
}

void Player::resetHalfWay()
{
	m_halfway = false;
}

void Player::getLapTimer()
{
	lap_timer[0] = timer_mis - lap_timer[0];
	lap_timer[1] = timer_sec - lap_timer[1];
	lap_timer[2] = timer_min - lap_timer[2];
	if (lap_timer[0] < 0)
	{
		lap_timer[1] --; // less 1 second
		lap_timer[0] += 100; // gain 100 millisecond
	}

	if (lap_timer[1] < 0)
	{
		lap_timer[2]--; // less 1 minute
		lap_timer[1] += 60; // gain 60 second
	}
}

void Player::update(double t, int car_ID)
{

	controller.update();

	located_time -= t;
	if (located_time <= 0)
	{
		location_record = m_postion;
		located_time = 0.1;
	}

	timer(t);

	sf::IntRect car(0, car_ID * 30, 50 , 30); // get rect of player selection

	m_sprite.setTextureRect(car);

	if (controller.RTrigger() >= 5) // right trigger to speed up
	{
		m_acceleration = controller.RTrigger() * max_speed;
	}
	else if (controller.RTrigger() < 5 && controller.RTrigger() >= 0)
	{
		m_acceleration = 0;
		std::cout << m_postion.x << std::endl;
		std::cout << m_postion.y << std::endl;
	}

	if (controller.LTrigger() <= -5)
	{
		m_acceleration = controller.LTrigger() * max_speed / 4;
		std::cout << m_postion.x << std::endl;
		std::cout << m_postion.y << std::endl;

	}
	else if (controller.LTrigger() > -5 && controller.LTrigger() <= 0)
	{
		m_acceleration = 0;
	}

	if (controller.Bbutton())
	{
		m_handbrake = m_motion.x * m_handling;
		m_motion.x -= m_handbrake * t;

		m_handbrake = m_motion.y  * m_handling;
		m_motion.y -= m_handbrake * t;
	}

	if (controller.LeftThumbSticks().x <= -20 ||
		controller.LeftThumbSticks().x >= 20) 
	{

		m_degree += controller.LeftThumbSticks().x * m_velocity / m_turning * t;
		if (m_degree > 360)
		{
			m_degree = 0;
		}

		if (m_degree < 0)
		{
			m_degree = 360;
		}
	}

	if (m_postion.x > 1350)
	{
		m_motion.x = -m_motion.x * 0.2;
		m_postion.x = 1350;
	}

	if (m_postion.y > 1700)
	{
		m_motion.y = -m_motion.y * 0.2;
		m_postion.y = 1700;
	}

	if (m_postion.x < 0)
	{
		m_motion.x = -m_motion.x * 0.2;
		m_postion.x = 0;
	}

	if (m_postion.y < 0)
	{
		m_motion.y = -m_motion.y * 0.2;
		m_postion.y = 0;
	}

	physics.update(t, m_motion, m_acceleration, m_degree); // sand player statu to physics
	m_motion = physics.getMotion();
	m_velocity = physics.getVelocity(); // get new motion from physics
	m_postion.x += physics.getDistance().x; // get new position 
	m_postion.y += physics.getDistance().y;

	m_sprite.setPosition(m_postion);

	view.setCenter(m_postion);
	m_text[1].setPosition(m_postion.x, m_postion.y + 150);

	m_timer.setPosition(m_postion.x - 250, m_postion.y - 200);
	m_text[0].setPosition(m_postion.x - 250, m_postion.y - 170);
	m_lap_timer.setPosition(m_postion.x - 250, m_postion.y - 140);

	m_sprite.setRotation(m_degree);
	m_text[1].setString(intToString(m_velocity));
	m_text[0].setString("Lap time:");
}

sf::FloatRect Player::boundingBox()
{
	sf::FloatRect boundingBox(m_sprite.getGlobalBounds().left + 2, m_sprite.getGlobalBounds().top + 2, m_sprite.getGlobalBounds().width - 5, m_sprite.getGlobalBounds().height - 5);
	return boundingBox;
}
void Player::setLocation()
{
	//m_postion = location_record;
	m_acceleration = 0;
}

void Player::render(sf::RenderWindow &window)
{
	window.setView(view);

	window.draw(m_sprite);
	for (int i = 0; i < 3; i++)
	{
		window.draw(m_text[i]);
	}
	window.draw(m_timer);
	window.draw(m_lap_timer);
}

std::string Player::intToString(int num) {
	char numString[10];
	sprintf_s(numString, "%i", num);
	return numString;
}

sf::Vector2f Player::getSpritePosition() const
{
	return m_sprite.getPosition();
}
