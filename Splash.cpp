#include "Splash.h"
#include <iostream>

Splash::Splash(Game & game, sf::Font font) :
	m_game(&game),
	m_Impact(font),
	m_textMessage("Press Start Button", m_Impact, 30)
{

	if (!m_Texture.loadFromFile("G:/HCI/button-game-jack-jamie-1/ButtonGame/images/Mash'Em.png"))
	{
		std::string s("error loading texture from file");
		throw std::exception(s.c_str());
	}
	m_Sprite.setTexture(m_Texture);
	m_textMessage.setPosition(250.0f, 250.0f);//set text position
	m_Sprite.setRotation(90);//set image rotation
	m_Sprite.setOrigin(400, 400);//set origin of image
	m_Sprite.setPosition(350, 325);//set image position in relation to origin
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

	if (m_Sprite.getRotation() != 0)
	{
		m_Sprite.rotate(5);//rotate image
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
		if (m_Sprite.getScale().x > 0.10 && m_Sprite.getScale().y > 0.10)//if key is pressed and the scale is more than .10 decrement scale
		{
			m_Sprite.scale(0.99, 0.99);
		}
	}

}
void Splash::changeScreen()
{
	m_game->SetGameState(GameState::option);
}


void Splash::render(sf::RenderWindow & Window)
{
	Window.clear(sf::Color(0, 0, 1));//different from standards black 
	Window.draw(m_Sprite);
	if (drawTime == true)
	{
		Window.draw(m_textMessage);//draws text when drawTime is true. If key is pressed remove text.

	}
	Window.display();
}