#include "Player.h"

Player::Player() :
	m_acceleration(0),
	m_degree(0),
	m_postion(600, 600),
	m_velocity(0)
{
	if (!m_font.loadFromFile("c:/windows/fonts/comic.ttf"))
	{

	}
	for (int i = 0; i < 2; i++)
	{
		m_text[i].setFont(m_font);
		m_text[i].setColor(sf::Color::Yellow);
	}
	m_timer.setFont(m_font);
	m_timer.setColor(sf::Color::Blue);

	if (!m_texture.loadFromFile("images/carSprite.png"))
	{
		std::string s("error loading texture from file");
		throw std::exception(s.c_str());
	}

	m_sprite.setTexture(m_texture); // set car texture
	m_sprite.setOrigin(25, 15); // set origin
	m_sprite.setPosition(m_postion); // set position 

	view.setCenter(m_postion); // set player's position to camera
	view.setSize(sf::Vector2f(1000, 800)); // set camera's size
}

Player::~Player()
{

}

void Player::update(double t, int car_ID)
{

	controller.update();

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

	sf::IntRect car(0, car_ID * 30, 50 , 30); // get rect of player selection

	m_sprite.setTextureRect(car);

	if (controller.RTrigger() >= 5) // right trigger to speed up
	{
		m_acceleration = controller.RTrigger();
	}
	else if (controller.RTrigger() < 5 && controller.RTrigger() >= 0)
	{
		m_acceleration = 0;
	}

	if (controller.LTrigger() <= -5)
	{
		m_acceleration = controller.LTrigger();
	}
	else if (controller.LTrigger() > -5 && controller.LTrigger() <= 0)
	{
		m_acceleration = 0;
	}


	if (controller.LeftThumbSticks().x <= -20 ||
		controller.LeftThumbSticks().x >= 20) 
	{
		m_degree += controller.LeftThumbSticks().x / 20;
		if (m_degree > 360)
		{
			m_degree = 0;
		}

		if (m_degree < 0)
		{
			m_degree = 360;
		}
	}

	if (m_postion.x > 1000)
	{
		m_velocity = -m_velocity * 0.5;
		m_postion.x = 1000;
	}

	if (m_postion.y > 800)
	{
		m_velocity = -m_velocity * 0.5;
		m_postion.y = 800;
	}

	if (m_postion.x < 0)
	{
		m_velocity = -m_velocity * 0.5;
		m_postion.x = 0;
	}

	if (m_postion.y < 0)
	{
		m_velocity = -m_velocity * 0.5;
		m_postion.y = 0;
	}
	physics.update(t, m_velocity, m_acceleration, m_degree); // sand player statu to physics
	m_velocity = physics.getVelocity(); // get new motion from physics
	m_postion.x += physics.getDistance().x; // get new position 
	m_postion.y += physics.getDistance().y;

	m_sprite.setPosition(m_postion);
	view.setCenter(m_postion);
	m_text[1].setPosition(m_postion.x, m_postion.y + 300);
	m_text[0].setPosition(m_postion.x + 300, m_postion.y - 400);


	
	m_timer.setPosition(m_postion.x - 500, m_postion.y - 400);
	

	m_sprite.setRotation(m_degree);
	m_text[1].setString(intToString(m_velocity));
	m_text[0].setString("Lap time:");
}

void Player::render(sf::RenderWindow &window)
{
	window.clear(sf::Color::White);
	window.setView(view);

	window.draw(m_sprite);
	for (int i = 0; i < 3; i++)
	{
		window.draw(m_text[i]);
	}
	window.draw(m_timer);
}


std::string Player::intToString(int num) {
	char numString[10];
	sprintf_s(numString, "%i", num);
	return numString;
}