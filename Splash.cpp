#include "Splash.h"
#include "Controller.h"
#include <iostream>

Splash::Splash(Game & game, sf::Font font, sf::Font font1) :
	m_game(&game),
	m_HARLOW(font),
	m_Motor(font1),
	m_textMessage("Speed", m_Motor, 100),
	m_textMessage1("Press the start button", m_HARLOW, 32)
{
	if (!m_Texture.loadFromFile("images/lambo.png"))
	{
		std::string s("error loading texture from file");
		throw std::exception(s.c_str());
	}
	m_Sprite.setTexture(m_Texture);
	m_Sprite.setPosition(200, 250);
	m_Sprite.setScale(0.4, 0.4);
	m_textMessage.setPosition(340.0f, 275.0f);//set position
	m_textMessage.setColor(sf::Color(255, 0, 0, 255));//set colour

	m_textMessage1.setPosition(340.0f, 375.0f);//set position
	m_textMessage1.setColor(sf::Color(255, 255, 255, 255));//set colour

	if (!shaderTxt.loadFromFile("images/shaderTxt.png"))
	{
		std::string s("error loading shader texture");
		//throw std::exception(s.c_str);
	}
	shaderSprite.setTexture(shaderTxt);
	shaderSprite.setPosition(0, 0);

	if (!shader.loadFromFile("smoke.frag", sf::Shader::Fragment))
	{
		std::string s("error loading shader");
		//throw std::exception(s.c_str);
	}
	shader.setParameter("time", 0);
	shader.setParameter("mouse", 0, 0);
	shader.setParameter("resolution", 1000, 800);

}

Splash::~Splash()
{
	std::cout << "Destroying Splash Screen" << std::endl;

}

void Splash::update(sf::Time deltaTime)
{

	m_cumulativeTime += deltaTime;
	drawTime = true;//set draw time to true (allows text to draw to screen

	updateShader = m_cumulativeTime.asSeconds();
	shader.setParameter("time", updateShader);

	if (change == true)
	{
		if (m_Sprite.getPosition().x < 1000)//any key accepted to change screen to credits
		{
			m_Sprite.move(10, 0);
		}
		else
		{
			m_game->SetGameState(GameState::option);
		}
	}
}

void Splash::changeScreen()
{
	change = true;
	
	m_textMessage.setColor(sf::Color(255, 0, 0, 0));//set colour
	m_textMessage1.setColor(sf::Color(255, 255, 255, 0));//set colour
	
}


void Splash::render(sf::RenderWindow & Window)
{
	Window.clear(sf::Color(0, 0, 1));//different from standards black
	Window.draw(shaderSprite, &shader);
	Window.draw(m_Sprite);
	Window.draw(m_textMessage1);//draw text
	Window.draw(m_textMessage);//draws text when drawTime is true. If key is pressed remove text.
	
}