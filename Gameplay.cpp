#include "Gameplay.h"

Gameplay::Gameplay(Game &game, sf::Font font):
	m_game(&game),
	m_font(font)
{

}

Gameplay::~Gameplay()
{

}

void Gameplay::update(double t, int car_id,Xbox360Controller& controller)
{
	m_player.update(t, car_id);
	m_npc.update(t, car_id);


}

void Gameplay::render(sf::RenderWindow &window)
{
	window.clear(sf::Color::White);

	m_player.render(window);
	m_npc.render(window);

	window.display();
}