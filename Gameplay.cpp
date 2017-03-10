#include "Gameplay.h"

Gameplay::Gameplay(Game &game, sf::Font font):
	m_game(&game),
	m_font(font)
{

}

Gameplay::~Gameplay()
{

}

void Gameplay::update(double t)
{
	m_player.update(t);
	m_npc.update(t);


}

void Gameplay::render(sf::RenderWindow &window)
{
	window.clear(sf::Color::White);

	m_player.render(window);
	m_player.render(window);

	window.display();
}