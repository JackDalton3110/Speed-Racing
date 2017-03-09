#include "Splash.h"
#include <iostream>

Splash::Splash(Game & game, sf::Font font) :
	m_game(&game),
	m_Impact(font),
	m_textMessage("Press Y Button", m_Impact, 30)
{
	m_textMessage.setPosition(250.0f, 250.0f);//set text position
	m_textMessage.setStyle(sf::Text::Underlined | sf::Text::Bold);//change style of text
	m_textMessage.setColor(sf::Color(0, 50, 100));//change text colour to custom colour 
}

Splash::~Splash()
{
	std::cout << "Destroying Splash Screen" << std::endl;

}

void Splash::update(sf::Time deltaTime)
{

	m_cumulativeTime += deltaTime;

	if (m_cumulativeTime.asSeconds() > 4)
	{
		//m_game->SetGameState(GameState::game);//load next gamestate after 4 seconds
	}

	if (m_cumulativeTime.asSeconds() > 1.25)
	{
		drawTime = true;//set draw time to true (allows text to draw to screen
	}
	rollCredits();

}

void Splash::rollCredits()
{
	if (credits == true)//waits 2 seconds beefore screen can be changed 
	{

	}

}
void Splash::changeScreen()
{
	m_game->SetGameState(GameState::option);
}


void Splash::render(sf::RenderWindow & Window)
{
	Window.clear(sf::Color(0, 0, 1));//different from standards black 
	if (drawTime == true)
	{
		Window.draw(m_textMessage);//draws text when drawTime is true. If key is pressed remove text.

	}
	Window.display();
}