#include "Licence.h"
#include <iostream>


Licence::Licence(Game &game, sf::Font font, sf::Font font1) :
	m_game(&game),
	m_HARLOW(font),
	m_Motor(font1),
	m_textMessage("Team A", m_Motor, 80),
	m_textMessage1("presents", m_HARLOW, 80)
{
	m_textMessage.setPosition(200.0f, 180.0f);//set position
	m_textMessage.setColor(sf::Color(255, 0, 0));//set colour

	m_textMessage1.setPosition(260.0f, 300.0f);//set position
	m_textMessage1.setColor(sf::Color(255, 255, 255));//set colour
	m_textMessage1.setCharacterSize(32);

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

}

void Licence::render(sf::RenderWindow &window)
{
	window.clear(sf::Color(0, 0, 0));//set background colour
	window.draw(m_textMessage);
	window.draw(m_textMessage1);//draw text
	window.display();
}