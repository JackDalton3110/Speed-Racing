#include "Player.h"

Player::Player() :
	m_acceleration(0),
	m_degree(255),
	m_velocity(0),
	m_postion(520, 681),
	location_record(0, 0),
	located_time(0.1),
	m_motion(0, 0),
	m_handbrake(0)
{
	//loads image for player car
	if (!m_font.loadFromFile("c:/windows/fonts/MotorwerkOblique.ttf"))
	{

	}
	for (int i = 0; i < 2; i++)
	{
		m_text[i].setFont(m_font);
		m_text[i].setColor(sf::Color::Red);
	}

	if (!m_texture.loadFromFile("images/carSprite.png"))
	{
		std::string s("error loading texture from file");
		throw std::exception(s.c_str());
	}

	if (!texture_draft_mark.loadFromFile("images/DriftMark.png"))
	{
		std::string s("error loading texture from file");
		throw std::exception(s.c_str());
	}

	for (int i = 0; i < 100; i++)
	{
		sprite_draft_mark[i].setTexture(texture_draft_mark);
		sprite_draft_mark[i].setScale(0.5, 0.5);
		sprite_draft_mark[i].setPosition(-1000, -100);
		sprite_draft_mark[i].setOrigin(11, 15);
	}

	if (!m_Texture.loadFromFile("images/mini.png"))
	{
		std::string s("error loading texture from file");
		throw std::exception(s.c_str());
	}

	//assign tetxtures
	m_sprite.setTexture(m_texture);
	m_Sprite.setTexture(m_Texture);
	m_sprite.setPosition(m_postion);
	m_sprite.setRotation(m_degree);
	m_sprite.setOrigin(10, 15);

	//This scales the player car down
	m_sprite.scale(.5, .5);
	view.setCenter(m_postion); // set player's position to camera
	view.setSize(sf::Vector2f(500, 400)); // set camera's size

	m_timer.setFont(m_font);
	m_lap_timer.setFont(m_font);
	m_timer.setColor(sf::Color::Black);
	m_lap_timer.setColor(sf::Color::Black);

	m_lap_timer.setString(intToString(lap_timer[2]) + "::"
		+ intToString(lap_timer[1]) + "::"
		+ intToString(lap_timer[0])); // convert minute to string

	if (!m_speed_texture.loadFromFile("images/speed.png"))
	{
		std::string s("error loading texture from file");
		throw std::exception(s.c_str());
	}
	m_speed_sprite.setTexture(m_speed_texture);
	m_speed_sprite.setOrigin(48, 48);
	m_speed_sprite.setPosition(m_postion.x + 200, m_postion.y + 130);
	if (!m_needle_texture.loadFromFile("images/needle.png"))
	{
		std::string s("error loading texture from file");
		throw std::exception(s.c_str());
	}
	m_needle_sprite.setTexture(m_needle_texture);
	m_needle_sprite.setOrigin(36, 8);
	m_needle_sprite.setPosition(m_speed_sprite.getPosition());

	m_lap_text.setFont(m_font);
	m_lap_text.setColor(sf::Color::Black);

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
	//normal friction of car
	physics.resetGravity();
}

void Player::resetPlayer()
{
	m_halfway = false;
	m_postion.x = 520;
	m_postion.y = 681;
	m_degree = 255;
	m_motion.x = 0;
	m_motion.y = 0;
	m_laps = 1;

	timer_mis = 0; 
	timer_sec = 0; 
	timer_min = 0;

	for (int i = 0; i < 3; i++)
	{
		lap_timer[i] = 0;
	}

	for (int i = 0; i < 100; i++)
	{
		sprite_draft_mark[i].setPosition(-1000, -100);
	}
}

void Player::setPlayerStatus(float maxspeed, float accelecation, float handling, int car_ID)
{
	sf::IntRect car(0, car_ID * 30, 50, 30); // get rect of player selection
	m_sprite.setTextureRect(car);

	max_speed = (0.2 * 9.8 * maxspeed) / 100; // get max speed from upgrade
	m_turning = maxspeed * 0.65;
	m_handling = handling / 100 + 0.5;

	needle_degree = m_velocity / maxspeed * 270;
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
}

void Player::resetHalfWay()
{
	//halfway bool reset
	m_halfway = false;
}

void Player::getLapTimer()
{
	//get lap time
	if (m_halfway)
	{
		m_lap_timer.setString(intToString(lap_timer[2]) + "::"
			+ intToString(lap_timer[1]) + "::"
			+ intToString(lap_timer[0])); // convert minute to string

		for (int i = 0; i < 3; i++)
		{
			lap_timer[i] = 0;
		}
	}
}

void Player::nextLap()
{
	m_halfway = false;
	m_laps++;
}

void Player::driftMark()
{
	//marks left after car
	sf::FloatRect boundingBox(m_sprite.getGlobalBounds().left + 10, m_sprite.getGlobalBounds().top + 5, m_sprite.getGlobalBounds().width - 15, m_sprite.getGlobalBounds().height - 5);
	if (!boundingBox.intersects(sprite_draft_mark[mark_count - 1].getGlobalBounds()))
	{
		sprite_draft_mark[mark_count].setPosition(m_postion);
		sprite_draft_mark[mark_count].setRotation(degree_record);
		mark_count++;
		if (mark_count >= 100)
		{
			mark_count = 1;
		}
	}
}

void Player::update(double t)
{

	controller.update();

	if (m_postion.y > 1444)
	{
		m_halfway = true;
		std::cout << "halfway::" << std::endl;
	}

	if (controller.Bbutton())
	{
		m_handbrake = m_motion.x * m_handling;
		m_motion.x -= m_handbrake * t;

		m_handbrake = m_motion.y  * m_handling;
		m_motion.y -= m_handbrake * t;

		driftMark();
	}

	located_time -= t;
	if (located_time <= 0)
	{
		location_record = m_postion;
		degree_record = m_degree;
		located_time = 0.1;
	}

	timer(t);

	lap_timer[0] += t * 100;

	if (lap_timer[0] >= 100) // when millisecond great than 100, second add 1
	{
		lap_timer[1]++;
		lap_timer[0] = 0;
	}

	if (lap_timer[1] >= 60) // when second over 60, minute add 1
	{
		lap_timer[2]++;
		lap_timer[1] = 0;
	}


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
	
	m_text[1].setPosition(m_postion.x + 100, m_postion.y + 160);

	m_timer.setPosition(m_postion.x - 250, m_postion.y - 200);
	m_text[0].setPosition(m_postion.x - 250, m_postion.y - 170);
	m_lap_timer.setPosition(m_postion.x - 250, m_postion.y - 140);
	m_lap_text.setPosition(m_postion.x - 250, m_postion.y - 110);

	m_sprite.setRotation(m_degree);
	m_text[1].setString("Speed: " + intToString(m_velocity));
	m_text[0].setString("Lap time:");
	m_lap_text.setString(intToString(m_laps) + " /3 laps");
	m_Sprite.setPosition(m_postion.x + 180, m_postion.y - 180);
	m_speed_sprite.setPosition(m_postion.x + 200, m_postion.y + 130);
	m_needle_sprite.setPosition(m_speed_sprite.getPosition());
	m_needle_sprite.setRotation(needle_degree);
}

sf::FloatRect Player::boundingBox()
{
	//bounding box for collision
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
	//draw images, texts 
	window.setView(view);
	

	for (int i = 0; i < 100; i++)
	{
		window.draw(sprite_draft_mark[i]);
	}

	window.draw(m_sprite); // draw player car

	for (int i = 0; i < 3; i++)
	{
		window.draw(m_text[i]);
	}
	window.draw(m_timer);
	window.draw(m_lap_timer);
	window.draw(m_speed_sprite);
	window.draw(m_needle_sprite);
	window.draw(m_Sprite);
	window.draw(m_lap_text);
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
