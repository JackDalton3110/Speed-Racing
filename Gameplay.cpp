#include "Gameplay.h"


Gameplay::Gameplay(Game &game, sf::Font font, Player & player, std::vector<sf::CircleShape> &Node) :
	m_game(&game),
	m_font(font),
	m_player(player),
	m_npc(Node)

{
	m_textMessage[0].setString("Continue");
	m_textMessage[1].setString("Exit");

	for (int i = 0; i < 2; i++)
	{
		m_selection[i].setSize(sf::Vector2f(150, 50));
		m_selection[i].setOrigin(75, 25);
		m_selection[i].setOutlineThickness(2);
		m_selection[i].setOutlineColor(sf::Color::Black);
		m_selection[i].setFillColor(sf::Color::White);

		m_textMessage[i].setColor(sf::Color::Black);
		m_textMessage[i].setFont(m_font);
		sf::FloatRect textRect = m_textMessage[i].getLocalBounds();
		m_textMessage[i].setOrigin(textRect.width / 2, textRect.height / 2);
	}

	countdown_text.setFont(m_font);
	countdown_text.setPosition(500, 400);
	countdown_text.setScale(2, 2);
	countdown_text.setColor(sf::Color::Black);
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

void Gameplay::collisionCheck()
{
	if (m_player.boundingBox().intersects(m_npc.boundingBox()))
	{
		m_player.setLocation();
		m_npc.setLocation();

		float temp = (m_player.m_motion.x + m_npc.m_motion.x) / 2;
		m_player.m_motion.x = temp;
		m_npc.m_motion.x = temp;

		temp = (m_player.m_motion.y + m_npc.m_motion.y) / 2;
		m_player.m_motion.y = temp;
		m_npc.m_motion.y = temp;
	}
}


void Gameplay::update(double t, int car_id, Xbox360Controller& controller)
{
	m_player.setPlayerStatus(max_speed, m_acceleration, m_handling);

	if (!game_pause)
	{

		m_player.update(t, car_id);
		m_npc.update(t, car_id);

		collisionCheck();
	}
	else // game pause part
	{
		if (controller.m_currentState.DPadDown && !controller.m_previousState.DPadDown)
		{
			if (button_ID < 1)
			{
				button_ID = button_ID + 1;
			}
			else
			{
				button_ID = 0;
			}
		}


		if (controller.m_currentState.DPadUp && !controller.m_previousState.DPadUp)
		{
			if (button_ID > 0)
			{
				button_ID--;
			}
			else
			{
				button_ID = 1;
			}
		}
		controller.m_previousState = controller.m_currentState;

		switch (button_ID)
		{
		case 0:
			m_selection[1].setFillColor(sf::Color::White);
			if (controller.Abutton())
			{
				m_countdown = true;
			}
			break;
		case 1:
			m_selection[0].setFillColor(sf::Color::White);
			if (controller.Abutton())
			{
				m_game->SetGameState(GameState::option);
			}
			break;
		default:
			break;
		}

		m_selection[button_ID].setFillColor(sf::Color::Red);
		
	}

	if (controller.StartButton())
	{
		game_pause = true;
	}

	if (m_countdown) // restart count down
	{
		restart_countdown -= t;
		if (restart_countdown < 0)
		{
			m_countdown = false;
			game_pause = false;
		}
	}

	for (int i = 0; i < 2; i++)
	{
		m_selection[i].setPosition(m_player.boundingBox().left, m_player.boundingBox().top + i * 60);
		m_textMessage[i].setPosition(m_selection[i].getPosition());
	}
	countdown_text.setPosition(m_player.boundingBox().left, m_player.boundingBox().top);

	countdown_text.setString(m_game->intToString(restart_countdown));
}

void Gameplay::render(sf::RenderWindow &window)
{

	m_player.render(window);
	m_npc.render(window);

	if (game_pause && !m_countdown)
	{
		for (int i = 0; i < 2; i++)
		{
			window.draw(m_selection[i]);
			window.draw(m_textMessage[i]);
		}
	}

	if (m_countdown)
	{
		window.draw(countdown_text);
	}
}