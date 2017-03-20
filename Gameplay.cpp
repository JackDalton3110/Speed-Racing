#include "Gameplay.h"

Gameplay::Gameplay(Game &game, sf::Font font, std::vector<sf::CircleShape> &Node):
	m_game(&game),
	m_font(font),
	m_npc(Node)
{

}

Gameplay::~Gameplay()
{

}


void Gameplay::update(double t, int car_id,Xbox360Controller& controller)
{
	m_player.update(t, car_id);
	m_npc.update(t, car_id);

	if (m_player.getRect().intersects(m_npc.getRect()))
	{
		m_player.setLocation();
		float temp = m_player.m_motion.x * 0.7;
		m_player.m_motion.x = m_npc.m_motion.x * 0.7;
		m_npc.m_motion.x = temp;
	}

}

void Gameplay::render(sf::RenderWindow &window)
{
	m_player.render(window);
	m_npc.render(window);
}