#include "Gameplay.h"

Gameplay::Gameplay(Game &game, sf::Font font):
	m_game(&game),
	m_font(font),
	button_ID(0)
{

}

Gameplay::~Gameplay()
{

}


void Gameplay::update(double t, int car_id,Xbox360Controller& controller)
{

	if (!controller.StartButton())
	{
		m_player.update(t, car_id);
		m_npc.update(t, car_id);
	}
	else
	{

	}

}

void Gameplay::render(sf::RenderWindow &window)
{
	window.clear(sf::Color::White);

	m_player.render(window);
	m_npc.render(window);

	window.display();
}