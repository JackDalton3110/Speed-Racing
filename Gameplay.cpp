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
	m_finishLine.setOutlineThickness(1);
	m_finishLine.setOutlineColor(sf::Color::Blue);

	//Setting the position for the finish line collision box
	m_finishLinePos.x = 100;
	m_finishLinePos.y = 12;
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

	if (!m_signal_texture.loadFromFile("images/signal.png"))
	{
		std::string s("error loading texture from file");
		throw std::exception(s.c_str());
	}
	m_signal_sprite.setTexture(m_signal_texture);

	if (!m_goTexture.loadFromFile("images/guesswhatisthis.png"))
	{
		std::string s("error loading texture from file");
		throw std::exception(s.c_str());
	}
	m_goSprite.setTexture(m_goTexture);

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
	m_player.setPlayerStatus(max_speed, m_acceleration, m_handling);

	m_player.update(t, car_id);
	m_npc.update(t, car_id);
	m_npc1.update(t, car_id);
	m_npc2.update(t, car_id);

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

	if (m_player.boundingBox().intersects(m_npc1.boundingBox()))
	{
		m_player.setLocation();
		m_npc1.setLocation();

		float temp = (m_player.m_motion.x + m_npc1.m_motion.x) / 2;
		m_player.m_motion.x = temp;
		m_npc1.m_motion.x = temp;

		temp = (m_player.m_motion.y + m_npc1.m_motion.y) / 2;
		m_player.m_motion.y = temp;
		m_npc1.m_motion.y = temp;
	}

	if (m_player.boundingBox().intersects(m_npc2.boundingBox()))
	{
		m_player.setLocation();
		m_npc2.setLocation();

		float temp = (m_player.m_motion.x + m_npc2.m_motion.x) / 2;
		m_player.m_motion.x = temp;
		m_npc2.m_motion.x = temp;

		temp = (m_player.m_motion.y + m_npc2.m_motion.y) / 2;
		m_player.m_motion.y = temp;
		m_npc2.m_motion.y = temp;
	}
}


void Gameplay::update(double t, int car_id, Xbox360Controller& controller)
{
	m_player.setPlayerStatus(max_speed, m_acceleration, m_handling, car_id);
	m_npc.setNPC(car_id);
	m_npc1.setNPC(car_id);
	m_npc2.setNPC(car_id);

	if (game_start)
	{
		if (!game_pause)
		{


			m_player.update(t);
			m_npc.update(t);
			m_npc1.update(t);
			m_npc2.update(t);

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

	}
	/*if (m_player.boundingBox().intersects(intersectLine()))
	{
		std::cout << "!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!" << std::endl;
	}*/

	//This is collision with the finish line

	if (m_player.m_postion.x >= m_finishLine.getPosition().x && m_player.m_postion.x <= m_finishLine.getPosition().x + 100)
	{
		if (m_player.m_postion.y >= m_finishLine.getPosition().y && m_player.m_postion.y <= m_finishLine.getPosition().y + 30)
		{
			std::cout << "!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!" << std::endl;
			m_player.getLapTimer();
		}
	}
	box1.setPosition(m_player.boundingBox().left, m_player.boundingBox().top);
	box1.setSize(sf::Vector2f(m_player.boundingBox().width, m_player.boundingBox().height));

	box2.setPosition(m_npc.boundingBox().left, m_npc.boundingBox().top);
	box2.setSize(sf::Vector2f(m_npc.boundingBox().width, m_npc.boundingBox().height));

	m_finishLine.setPosition(482, 645);
	m_finishLine.setSize(sf::Vector2f(m_finishLinePos.x, m_finishLinePos.y));
	m_finishLine.setRotation(345.0f);


//sf::FloatRect Gameplay::intersectLine(Xbox360Controller & controller, double t)
//{
//	sf::FloatRect intersectLine(645 + m_finishLine.getSize().y, 482,
//		482 + m_finishLine.getSize().x, 645);
//	return intersectLine;


		if (controller.StartButton())
		{
			game_pause = true;
		}

		if (m_countdown) // restart count down
		{
			restart_countdown -= t;
			if (restart_countdown < 0)
			{
				restart_countdown = 3.0f;
				m_countdown = false;
				game_pause = false;
			}
		

		for (int i = 0; i < 2; i++)
		{
			m_selection[i].setPosition(m_player.boundingBox().left, m_player.boundingBox().top + i * 60);
			m_textMessage[i].setPosition(m_selection[i].getPosition());
		}
		countdown_text.setString(m_game->intToString(restart_countdown));
	}
	else
	{
		start_count -= t;
		if (start_count < 0)
		{
			game_start = true;
			start_count = 5.0f;
		}
		else if (start_count < 1)
		{
			m_signal_sprite = m_goSprite;
		}
		else if (start_count < 2)
		{
			sf::IntRect signal(75, 0, 25, 60); // get signal of player selection
			m_signal_sprite.setTextureRect(signal);
		}
		else if (start_count < 3)
		{
			sf::IntRect signal(50, 0, 25, 60); // get signal of player selection
			m_signal_sprite.setTextureRect(signal);
		}
		else if (start_count < 4)
		{
			sf::IntRect signal(25, 0, 25, 60); // get signal of player selection
			m_signal_sprite.setTextureRect(signal);
		}
		else if (start_count < 5)
		{
			sf::IntRect signal(0, 0, 25, 60); // get signal of player selection
			m_signal_sprite.setTextureRect(signal);
		}

		countdown_text.setString(m_game->intToString(start_count));
	}
	countdown_text.setPosition(m_player.boundingBox().left, m_player.boundingBox().top);
	m_signal_sprite.setPosition(m_player.boundingBox().left - 100, m_player.boundingBox().top - 100);

}


void Gameplay::render(sf::RenderWindow &window)
{

	/*window.draw(box1);
	window.draw(box2);*/
	
	// comment or delete this when we finished
	window.draw(m_finishLine);


	m_player.render(window);
	m_npc.render(window);
	m_npc1.render(window);
	m_npc2.render(window);

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

	if (!game_start)
	{
		window.draw(countdown_text);
		window.draw(m_signal_sprite);
	}
}