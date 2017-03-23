#include "Licence.h"
#include <iostream>


Licence::Licence(Game &game, sf::Font font, sf::Font font1) :
	m_game(&game),
	m_HARLOW(font),
	m_Motor(font1),
	m_textMessage("Team A", m_Motor, 100),
	m_textMessage1("presents", m_HARLOW, 80)
{
	//load image for licence
	if (!m_Texture.loadFromFile("images/lambo.png"))
	{
		std::string s("error loading texture from file");
		throw std::exception(s.c_str());
	}

	//load shader texture for licence
	if (!shaderTxt.loadFromFile("images/shaderTxt.png"))
	{
		std::string s("error loading shader texture");
		//throw std::exception(s.c_str);
	}
	//assign texture to sprite
	shaderSprite.setTexture(shaderTxt);
	shaderSprite.setPosition(0, 0);

	m_Sprite.setTexture(m_Texture);
	m_Sprite.setPosition(-500, 250);
	m_Sprite.setScale(0.4, 0.4);
	m_textMessage.setPosition(270.0f, 275.0f);//set position
	m_textMessage.setColor(sf::Color(255, 0, 0, 0));//set colour

	m_textMessage1.setPosition(370.0f, 375.0f);//set position
	m_textMessage1.setColor(sf::Color(255, 255, 255, 0));//set colour
	m_textMessage1.setCharacterSize(32);
	
	//loads shader from .frag file
	if (!shader.loadFromFile("smoke.frag", sf::Shader::Fragment))
	{
		std::string s("error loading shader");
		//throw std::exception(s.c_str);
	}
	//set shader parameters
	shader.setParameter("time", 0);
	shader.setParameter("mouse",0, 0);
	shader.setParameter("resolution",1000, 800);

}

Licence::~Licence()
{
	std::cout << "Destructing Licence" << std::endl;

}

void Licence::update(sf::Time deltaTime)
{
	m_cumulativeTime += deltaTime;
	//update shader
	updateShader = m_cumulativeTime.asSeconds();
	shader.setParameter("time", updateShader);
	

	if (m_cumulativeTime.asSeconds() > 4)
	{
		m_game->SetGameState(GameState::splash);//load next gamestate after 4 seconds
	}

	if (m_Sprite.getPosition().x < 200)
	{
		//move sprite on to screen
		m_Sprite.move(10,0);
	}

	if (m_cumulativeTime.asSeconds() > 2)
	{
		//fade text
		if (alpha <= 255)
		{
			alpha= alpha+2;
		}
		
		m_textMessage.setColor(sf::Color(255, 0, 0, alpha));//set colour
		m_textMessage1.setColor(sf::Color(255, 255, 255, alpha));//set colour
	}


}

void Licence::render(sf::RenderWindow &window)
{
	//draw sprites/text/shader
	window.clear(sf::Color(0, 0, 0));//set background colour
	window.draw(shaderSprite, &shader);
	window.draw(m_Sprite);
	window.draw(m_textMessage);
	window.draw(m_textMessage1);//draw text
}