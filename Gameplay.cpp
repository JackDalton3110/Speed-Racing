#include "Gameplay.h"

<<<<<<< HEAD
Gameplay::Gameplay(Game &game, sf::Font font, std::vector<sf::CircleShape> &Node) :
	m_game(&game),
	m_font(font),
	m_npc(Node),
	m_npc1(Node),
	m_npc2(Node)
=======
Gameplay::Gameplay(Game &game, sf::Font font, std::vector<sf::CircleShape> &Node):
	m_game(&game),
	m_font(font),
	m_npc(Node)
>>>>>>> 5903129f1052da86f7c06b60224d2bed61d0a256
{

}

Gameplay::~Gameplay()
{

}

void Gameplay::getStatus(float maxspeed, float accelecation, float handling)
{
	max_speed = maxspeed;
	m_acceleration = accelecation;
	m_handling = handling;
}

void Gameplay::update(double t, int car_id,Xbox360Controller& controller)
{
	m_player.setPlayerStatus(max_speed, m_acceleration, m_handling);

	m_player.update(t, car_id);
	m_npc.update(t, car_id);
	m_npc1.update(t, car_id);
	m_npc2.update(t, car_id);

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
<<<<<<< HEAD
	m_npc1.render(window);
	m_npc2.render(window);
=======
>>>>>>> 5903129f1052da86f7c06b60224d2bed61d0a256
}