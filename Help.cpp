#include "Help.h"


Help::Help(Game & game, sf::Font font) :
	m_game(&game),
	m_helpFont(font),
	m_line1("Brakes - LT", m_helpFont, 25),
	m_line2("Accelerator - RT", m_helpFont, 25),
	m_line3("Steering -", m_helpFont, 25),
	m_line4("Left analog", m_helpFont, 25)
	
	
	
{
	if (!m_texture.loadFromFile("images/360 controller.png"))
	{
		std::string s("error loading texture from file");
		throw std::exception(s.c_str());
	}
	else
	{
		std::cout << "controller loaded" << std::endl;
	}
	m_controllerSprite.setTexture(m_texture);
	m_controllerSprite.setPosition(150, 150);
	m_line1.setPosition(280, 150);
	m_line2.setPosition(630, 150);
	m_line3.setPosition(40, 380);
	m_line4.setPosition(40, 410);
	
	sf::RectangleShape m_line(sf::Vector2f(1000.0f, 1.0f));

	m_line.setPosition(0.0f, 700.0f);
	m_line.setFillColor(sf::Color::White);
	m_line.rotate(0);
}



Help::~Help()
{
}

void Help::update(Xbox360Controller &controller)
{
	if (controller.m_currentState.B)
	{
		m_game->SetGameState(GameState::option);
	}
}

void Help::render(sf::RenderWindow& window)
{
	
	window.clear(sf::Color(0, 0, 1));
	window.draw(m_controllerSprite);
	window.draw(m_line1);
	window.draw(m_line2);
	window.draw(m_line3);
	window.draw(m_line4);
	window.draw(m_line);
}