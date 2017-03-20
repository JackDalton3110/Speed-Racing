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

	if (m_player.getRect().intersects(m_npc.getRect()))
	{
<<<<<<< HEAD
		float temp = m_player.m_motion.x;
		m_player.m_motion.x = m_npc.m_motion.x;
=======
		m_player.setLocation();
		float temp = m_player.m_motion.x * 0.7;
		m_player.m_motion.x = m_npc.m_motion.x * 0.7;
>>>>>>> 050b7539f24fe526bf50edec9d04a79e4aa8cb92
		m_npc.m_motion.x = temp;
	}

}

void Gameplay::render(sf::RenderWindow &window)
{
	

	m_player.render(window);
	m_npc.render(window);

	
}