#include "Playagain.h"
#include <iostream>

Playagain::Playagain(Game &game, sf::Font font) :
	m_game(&game),
	m_font(font),
	m_button_released(false),
	m_reset_check(true)
{
	for (int i = 0; i < 3; i++)
	{
		m_text[i].setFont(m_font);
		m_text[i].setColor(sf::Color::Black);
	}

	m_text[0].setString("Let's try that again");
	m_text[0].setPosition(300, 600);

	m_text[1].setString("Not this time");
	m_text[1].setPosition(700, 600);

	m_text[2].setString("Play again?");
	m_text[2].setScale(2, 2);
	m_text[2].setPosition(500, 400);
	sf::FloatRect textRect = m_text[2].getLocalBounds();
	m_text[2].setOrigin(textRect.width / 2, textRect.height / 2);

	if (!m_texture.loadFromFile("images/buttons.png"))
	{
		std::string s("error loading texture from file");
		throw std::exception(s.c_str());
	}
	m_SpriteA.setTexture(m_texture);
	sf::IntRect Abutton(150, 0, 50, 48); // the rect of A button
	m_SpriteA.setTextureRect(Abutton);
	m_SpriteA.setOrigin(Abutton.width, 0);
	m_SpriteA.setPosition(m_text[0].getPosition());

	m_SpriteB.setTexture(m_texture);
	sf::IntRect Bbutton(100, 0, 50, 48); // the rect of B button
	m_SpriteB.setTextureRect(Bbutton);
	m_SpriteB.setOrigin(Bbutton.width, 0);
	m_SpriteB.setPosition(m_text[1].getPosition());
}

Playagain::~Playagain()
{

}

void Playagain::update(Xbox360Controller& controller)
{

	if (controller.Abutton() && m_button_released) // press A button to play again
	{
		m_game->SetGameState(GameState::none);
		m_reset_check = true;
	}

	if (controller.Bbutton() && m_button_released) // press B button to Main menu
	{
		m_game->SetGameState(GameState::option);
		m_reset_check = true;
	}


	if (!controller.Abutton() && !controller.Bbutton())
	{
		m_button_released = true;
	}

}


/// <summary>
/// reset everything when player enter this screen
/// </summary>
void Playagain::reset()
{
	if (m_reset_check)
	{
		m_reset_check = false;
		m_button_released = false;
	}
}

void Playagain::render(sf::RenderWindow &window)
{
	window.clear(sf::Color::White);

	window.draw(m_SpriteA);
	window.draw(m_SpriteB);
	for (int i = 0; i < 3; i++)
	{
		window.draw(m_text[i]);
	}

	window.display();
}