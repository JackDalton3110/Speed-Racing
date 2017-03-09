#include "Licence.h"
#include <iostream>


Licence::Licence(Game &game, sf::Font font) :
	m_game(&game),
	m_Impact(font),
	m_textMessage("Noob", m_Impact, 80),
	m_textMessage1("isoft,inc.", m_Impact, 80)
{
	m_textMessage.setPosition(-300.0f, 240.0f);//set position
	m_textMessage.setColor(sf::Color(255, 0, 0));//set colour

	m_textMessage1.setPosition(800.0f, 240.0f);//set position
	m_textMessage1.setColor(sf::Color(255, 255, 255));//set colour

	

}

Licence::~Licence()
{
	std::cout << "Destructing Licence" << std::endl;

}

void Licence::update(sf::Time deltaTime)
{
	m_cumulativeTime += deltaTime;
	if (m_cumulativeTime.asSeconds() > 4)
	{
		m_game->SetGameState(GameState::splash);//load next gamestate after 4 seconds
	}

	if (m_textMessage.getPosition().x <= 120)
	{
		m_textMessage.move(10, 0);//move text 
	}

	if (m_textMessage1.getPosition().x >= 300)
	{
		m_textMessage1.move(-10, 0);//move text 
	}

	if (m_cumulativeTime.asSeconds() > 3)
	{
		m_textMessage.move(0, 10);
		m_textMessage1.move(0, 10);//after 3 seconds move all text to bottom of screen 
	}

}

void Licence::render(sf::RenderWindow &window)
{
	window.clear(sf::Color(0, 0, 0));//set background colour
	window.draw(m_textMessage);
	window.draw(m_textMessage1);//draw text
	window.display();
}