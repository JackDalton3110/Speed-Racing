#include "Splash.h"
#include <iostream>

Splash::Splash(Game & game, sf::Font font, sf::Font font1) :
	m_game(&game),
	m_HARLOW(font),
	m_Motor(font1),
	m_textMessage("Speed", m_Motor, 80),
	m_textMessage1("Press the start button", m_HARLOW, 32)
{

	m_textMessage.setPosition(200.0f, 180.0f);//set position
	m_textMessage.setColor(sf::Color(255, 0, 0));//set colour

	m_textMessage1.setPosition(180.0f, 300.0f);//set position
	m_textMessage1.setColor(sf::Color(255, 255, 255));//set colour
	/*m_textMessage1.setCharacterSize(32);*/
}

Splash::~Splash()
{
	std::cout << "Destroying Splash Screen" << std::endl;

}

void Splash::update(sf::Time deltaTime)
{

	m_cumulativeTime += deltaTime;
	drawTime = true;//set draw time to true (allows text to draw to screen
}

void Splash::changeScreen()
{
	m_game->SetGameState(GameState::option);
}


void Splash::render(sf::RenderWindow & Window)
{
	Window.clear(sf::Color(0, 0, 1));//different from standards black 
	Window.draw(m_textMessage1);//draw text
	Window.draw(m_textMessage);//draws text when drawTime is true. If key is pressed remove text.
	Window.display();
}