#include "Confirm.h"
#include <iostream>

Confirm::Confirm(Game &game, sf::Font font):
	m_game(&game),
	m_font(font),
	m_confirm(true),
	m_button_released(false),
	m_reset_check(true)
{
	for (int i = 0; i < 3 ;i++)
	{
		m_text[i].setFont(m_font);
		m_text[i].setColor(sf::Color::Black);
	}

	m_text[0].setString("YES");
	m_text[0].setPosition(300, 600);

	m_text[1].setString("NO");
	m_text[1].setPosition(700, 600);

	m_text[2].setString("Exit to desktop?");
	m_text[2].setScale(2, 2);
	m_text[2].setPosition(500, 400);
	sf::FloatRect textRect = m_text[2].getLocalBounds();
	m_text[2].setOrigin(textRect.width / 2, textRect.height / 2);

	if (!m_texture.loadFromFile("images/selector.png"))
	{
		std::string s("error loading texture from file");
		throw std::exception(s.c_str());
	}
	m_Sprite.setTexture(m_texture);
	m_Sprite.setOrigin(17.5,18);
	m_Sprite.setPosition(m_text[0].getPosition());
}

Confirm::~Confirm()
{

}

void Confirm::update(Xbox360Controller& controller)
{
	
	controller.update();

	if (controller.DpadLeftButton()) // select yes
	{
		m_confirm = true;
	}
	else if (controller.DpadRightButton()) // select no
	{
		m_confirm = false;
	}

	if (m_confirm)
	{
		m_Sprite.setPosition(m_text[0].getPosition()); // move sprite to YES text positoin
		m_Sprite.rotate(5); // spin the sprite
		if (controller.Abutton() && m_button_released) // press A button to close game
		{
			m_game->SetGameState(GameState::none);
			m_reset_check = true;
		}
	}
	else
	{
		m_Sprite.setPosition(m_text[1].getPosition()); // move sprite to NO text positoin
		m_Sprite.rotate(10); // spin the sprite faster
		if (controller.Abutton() && m_button_released) // press A button to back to OptionScreen
		{
			m_game->SetGameState(GameState::option);
			m_reset_check = true;
		}
	}

	if (!controller.Abutton())
	{
		m_button_released = true;
	}

}


void Confirm::reset()
{
	if (m_reset_check)
	{
		m_reset_check = false;
		m_button_released = false;
		m_confirm = true;
	}
}

void Confirm::render(sf::RenderWindow &window)
{
	window.clear(sf::Color::White);

	window.draw(m_Sprite);
	for (int i = 0; i < 3; i++)
	{
		window.draw(m_text[i]);
	}
}