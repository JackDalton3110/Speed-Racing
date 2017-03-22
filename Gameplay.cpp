#include "Gameplay.h"


Gameplay::Gameplay(Game &game, sf::Font font, Player & player, std::vector<sf::CircleShape> &Node) :
	m_game(&game),
	m_font(font),
	m_player(player),
	m_npc(Node),
	m_npc1(Node),
	m_npc2(Node)
{
	box1.setOutlineThickness(1);
	box1.setOutlineColor(sf::Color::Blue);
	box2.setOutlineThickness(1);
	box2.setOutlineColor(sf::Color::Blue);
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

	if (m_player.boundingBox().intersects(m_npc.boundingBox()))
	{
		m_player.setLocation();
		m_npc.setLocation();
		if (m_player.boundingBox().top - m_npc.boundingBox().top > m_player.boundingBox().left - m_npc.boundingBox().left)
		{
			float temp = m_player.m_motion.x * 0.5;
			m_player.m_motion.x = m_npc.m_motion.x * 0.5;
			m_npc.m_motion.x = temp;

			temp = (m_player.m_motion.y + m_npc.m_motion.y) / 2;
			m_player.m_motion.y = temp;
			m_npc.m_motion.y = temp;
		}
		else
		{
			float temp = m_player.m_motion.y * 0.5;
			m_player.m_motion.y = m_npc.m_motion.y * 0.5;
			m_npc.m_motion.y = temp;

			temp = (m_player.m_motion.x + m_npc.m_motion.x) / 2;
			m_player.m_motion.x = temp;
			m_npc.m_motion.x = temp;
		}
	}

	box1.setPosition(m_player.boundingBox().left, m_player.boundingBox().top);
	box1.setSize(sf::Vector2f(m_player.boundingBox().width, m_player.boundingBox().height));

	box2.setPosition(m_npc.boundingBox().left, m_npc.boundingBox().top);
	box2.setSize(sf::Vector2f(m_npc.boundingBox().width, m_npc.boundingBox().height));
}

void Gameplay::render(sf::RenderWindow &window)
{
	window.draw(box1);
	window.draw(box2);
	// comment or delete this when we finished

	m_player.render(window);
	m_npc.render(window);
	m_npc1.render(window);
	m_npc2.render(window);
}