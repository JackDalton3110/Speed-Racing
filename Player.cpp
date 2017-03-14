#include "Player.h"

Player::Player() :
	m_acceleration(0),
	m_degree(0),
	m_positon(600, 600),
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

	if (!m_texture.loadFromFile("images/carSprite.png"))
	{
		std::string s("error loading texture from file");
		throw std::exception(s.c_str());
	}
	m_sprite.setTexture(m_texture); // set car texture
	m_sprite.setOrigin(25, 15); // set origin
	m_sprite.setPosition(m_positon); // set position 
	m_filed.setSize(sf::Vector2f(2000, 2000));
	m_filed.setPosition(0, 0);
	m_filed.setFillColor(sf::Color::Black);

	view.setCenter(m_positon); // set player's position to camera
	view.setSize(sf::Vector2f(1000, 800)); // set camera's size
}

Player::~Player()
{

}

void Player::update(double t, int car_ID)
{

	controller.update();


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

	if (m_positon.x > 2000)
	{
		m_velocity = -m_velocity * 0.5;
		m_positon.x = 2000;
	}

	if (m_positon.y > 2000)
	{
		m_velocity = -m_velocity * 0.5;
		m_positon.y = 2000;
	}

	if (m_positon.x < 0)
	{
		m_velocity = -m_velocity * 0.5;
		m_positon.x = 0;
	}

	if (m_positon.y < 0)
	{
		m_velocity = -m_velocity * 0.5;
		m_positon.y = 0;
	}
	physics.update(t, m_velocity, m_acceleration, m_degree); // sand player statu to physics
	m_velocity = physics.getVelocity(); // get new motion from physics
	m_positon.x += physics.getDistance().x; // get new position 
	m_positon.y += physics.getDistance().y;

	m_sprite.setPosition(m_positon);
	view.setCenter(m_positon);
	m_text[1].setPosition(m_positon.x, m_positon.y + 300);
	m_text[0].setPosition(m_positon.x + 300, m_positon.y - 400);

	m_sprite.setRotation(m_degree);
	m_text[1].setString(intToString(m_velocity));
	m_text[0].setString("Lap time:");
}

void Player::render(sf::RenderWindow &window)
{
	window.clear(sf::Color::White);
	window.setView(view);

	window.draw(m_filed);
	window.draw(m_sprite);
	for (int i = 0; i < 2; i++)
	{
		window.draw(m_text[i]);
	}
}


std::string Player::intToString(int num) {
	char numString[10];
	sprintf_s(numString, "%i", num);
	return numString;
}