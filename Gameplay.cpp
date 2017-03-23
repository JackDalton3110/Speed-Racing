#include "Gameplay.h"


Gameplay::Gameplay(Game &game, sf::Font font, Player & player, std::vector<sf::CircleShape> &Node) :
	m_game(&game),
	m_font(font),
	m_player(player),
	m_npc(Node),
	m_npc1(Node),
	m_npc2(Node),
	board_position(0,0)
{
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

	/// count down text
	countdown_text.setFont(m_font);
	countdown_text.setPosition(500, 400);
	countdown_text.setScale(2, 2);
	countdown_text.setColor(sf::Color::Black);

	/// images for countdown signal
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

	/// text for record timer
	for (int i = 0; i < 4; i++)
	{
		time_board[i].setFont(m_font);
		time_board[i].setColor(sf::Color::Black);
		time_board[i].setString("NOT FINISH");

		rank_board[i].setSize(sf::Vector2f(200, 50));
		rank_board[i].setOrigin(100, 25);
		rank_board[i].setOutlineThickness(2);
		rank_board[i].setOutlineColor(sf::Color::Black);
		rank_board[i].setFillColor(sf::Color::White);
	}

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

	
	if (m_player.m_postion.x >= m_finishLine.getPosition().x && m_player.m_postion.x <= m_finishLine.getPosition().x + 100)
	{
		if (m_player.m_postion.y >= m_finishLine.getPosition().y && m_player.m_postion.y <= m_finishLine.getPosition().y + 30)
		{
			std::cout << "!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!" << std::endl;
			m_player.getLapTimer();
			if (m_player.m_halfway)
			{
				m_changeLap = true;
				time_board[m_rank].setString(m_game->intToString(m_player.timer_min) + "::"
											+ m_game->intToString(m_player.timer_sec) + "::"
											+ m_game->intToString(m_player.timer_mis));
				start_ending_count = true; // start count down
				m_rank++;
			}
			m_player.resetHalfWay();
		}
	}

	if (m_npc.m_postion.x >= m_finishLine.getPosition().x && m_npc.m_postion.x <= m_finishLine.getPosition().x + 100)
	{
		if (m_npc.m_postion.y >= m_finishLine.getPosition().y && m_npc.m_postion.y <= m_finishLine.getPosition().y + 30)
		{
			std::cout << "!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!" << std::endl;
			if (m_npc.m_halfway)
			{
				time_board[m_rank].setString(m_game->intToString(m_player.timer_min) + "::"
					+ m_game->intToString(m_player.timer_sec) + "::"
					+ m_game->intToString(m_player.timer_mis));
				start_ending_count = true; // start count down
				m_rank++;
			}
			m_npc.m_halfway = false;
		}
	}

	if (m_npc1.m_postion.x >= m_finishLine.getPosition().x && m_npc1.m_postion.x <= m_finishLine.getPosition().x + 100)
	{
		if (m_npc1.m_postion.y >= m_finishLine.getPosition().y && m_npc1.m_postion.y <= m_finishLine.getPosition().y + 30)
		{
			std::cout << "!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!" << std::endl;
			if (m_npc1.m_halfway)
			{
				time_board[m_rank].setString(m_game->intToString(m_player.timer_min) + "::"
					+ m_game->intToString(m_player.timer_sec) + "::"
					+ m_game->intToString(m_player.timer_mis));
				start_ending_count = true; // start count down
				m_rank++;
			}
			m_npc1.m_halfway = false;
		}
	}

	if (m_npc2.m_postion.x >= m_finishLine.getPosition().x && m_npc2.m_postion.x <= m_finishLine.getPosition().x + 100)
	{
		if (m_npc2.m_postion.y >= m_finishLine.getPosition().y && m_npc2.m_postion.y <= m_finishLine.getPosition().y + 30)
		{
			std::cout << "!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!" << std::endl;
			if (m_npc2.m_halfway)
			{
				time_board[m_rank].setString(m_game->intToString(m_player.timer_min) + "::"
					+ m_game->intToString(m_player.timer_sec) + "::"
					+ m_game->intToString(m_player.timer_mis));
				start_ending_count = true; // start count down
				m_rank++;
			}
			m_npc2.m_halfway = false;
		}
	}
}

void Gameplay::changeLap()
{
	if (m_changeLap == true)
	{
		m_laps = m_laps + 1;
		if (m_laps + 1)
		{
			m_changeLap = false;
		}
		
		//actual lap
		m_lapString = std::to_string(m_laps);
		m_lapstxt.setString(m_lapString);
		m_lapstxt.setColor(sf::Color::Black);
		m_lapstxt.setCharacterSize(40);
		m_lapstxt.setFont(m_font);
		m_lapstxt.setPosition(m_player.m_postion.x + 150, m_player.m_postion.y - 45);

		//lap label
		m_labelString = "lap:";
		m_lapLabel.setString(m_labelString);
		m_lapLabel.setColor(sf::Color::Black);
		m_lapLabel.setCharacterSize(40);
		m_lapLabel.setFont(m_font);
		m_lapLabel.setPosition(m_player.m_postion.x + 70, m_player.m_postion.y - 45);
		
	}
}

void Gameplay::startCount()
{
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

void Gameplay::endScreen()
{
	for (int i = 0; i < 4; i++)
	{
		rank_board[i].setPosition(board_position.x, board_position.y - 100 + 50 * i);
		time_board[i].setPosition(rank_board[i].getPosition());

		sf::FloatRect textRect = time_board[i].getLocalBounds();
		time_board[i].setOrigin(textRect.width / 2, textRect.height / 2);
	}

}

void Gameplay::update(double t, int car_id, Xbox360Controller& controller)
{
	m_player.setPlayerStatus(max_speed, m_acceleration, m_handling, car_id);
	m_npc.setNPC(car_id);
	m_npc1.setNPC(car_id);
	m_npc2.setNPC(car_id);

	if (game_start && !game_end) // run the game
	{
		if (!game_pause)
		{
			m_player.update(t);
			m_npc.update(t);
			m_npc1.update(t);
			m_npc2.update(t);

			collisionCheck();
			changeLap();
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

	
	/// <summary>
	/// ending count down 
	/// after 10s to ending screen
	/// </summary>
	/// <param name="t"></param>
	/// <param name="car_id"></param>
	/// <param name="controller"></param>
	if (start_ending_count)
	{
		ending_countdown -= t;
		if (ending_countdown <= 0)
		{
			game_end = true;
			start_ending_count = false;
		}
		countdown_text.setString(m_game->intToString(ending_countdown));
	}
	
	/// <summary>
	/// start count down
	/// </summary>
	/// <param name="t"></param>
	/// <param name="car_id"></param>
	/// <param name="controller"></param>
	if (!game_start)
	{
		start_count -= t;
		startCount();
	}
	countdown_text.setPosition(m_player.m_postion);
	m_signal_sprite.setPosition(m_player.boundingBox().left - 100, m_player.boundingBox().top - 100);

	/// <summary>
	/// ending screen
	/// </summary>
	/// <param name="t"></param>
	/// <param name="car_id"></param>
	/// <param name="controller"></param>
	if (game_end)
	{
		if (controller.Abutton()) // at ending screen presss A button to next
		{
			m_game->SetGameState(GameState::playagain);
		}
		endScreen();
	}
	
	board_position = m_player.m_postion;
}


void Gameplay::render(sf::RenderWindow &window)
{

	/*window.draw(box1);
	window.draw(box2);*/
	
	// comment or delete this when we finished
	//window.draw(m_finishLine);
	/*window.draw(m_finishLine);*/

	m_player.render(window);
	m_npc.render(window);
	m_npc1.render(window);
	m_npc2.render(window);
	window.draw(m_lapstxt);
	window.draw(m_lapLabel);

	if (game_pause && !m_countdown)
	{
		for (int i = 0; i < 2; i++)
		{
			window.draw(m_selection[i]);
			window.draw(m_textMessage[i]);
		}
	}

	if (m_countdown || start_ending_count)
	{
		window.draw(countdown_text);
	}

	if (!game_start)
	{
		window.draw(countdown_text);
		window.draw(m_signal_sprite);
	}

	if (game_end)
	{
		for (int i = 0; i < 4; i++)
		{
			window.draw(rank_board[i]);
			window.draw(time_board[i]);
		}
	}
}

/// The dark lord returns
/// 
/// 
/// 
/// 
/// 
/// 
/// 
/// 
/// 
/// 
/// 
/// 
/// 
/// 
/// 
/// 
/// 
/// 
/// 
/// 
/// 
/// 
/// 
/// 
/// 
/// 
/// 
/// 
/// 
/// 
/// 
/// 
/// 
/// 
/// 
/// 
/// 
/// 
/// 
/// 
/// 
/// 
/// 
/// 
/// 
/// 
/// 
/// 
/// 
/// 
/// 
/// 
/// 
/// 
/// 
/// 
/// 
/// 
/// 
/// 
/// 
/// 
/// 
/// 
/// 
/// 
/// 
/// 
/// 
/// 
/// 
/// 
/// 
/// 
/// 
/// 
/// 
/// 
/// 
/// 
/// 
/// 
/// 
/// 
/// 
/// 
/// 
/// 
/// 
/// 
/// 
/// 
/// 
/// 
/// 
/// 
/// 
/// 
/// 
/// 
/// 
/// 
/// 
/// 
/// 
/// 
/// 
/// 
/// 
/// 
/// 
/// 
/// 
/// 
/// 
/// 
/// 
/// 
/// 
/// 
/// 
/// 
/// 
/// 
/// 
/// 
/// 
/// 
/// 
/// 
/// 
/// 
/// 
/// 
/// 
/// 
/// 
/// 
/// 
/// 
/// 
/// 
/// 
/// 
/// 
/// 
/// 
/// 
/// 
/// 
/// 
/// 
/// 
/// 
/// 
/// 
/// 
/// 
/// 
/// 
/// 
/// 
/// 
/// 
/// 
/// 
/// 
/// 
/// 
/// 
/// 
/// 
/// 
/// 
/// 
/// 
/// 
/// 
/// 
/// 
/// 
/// 
/// 
/// 
/// 
/// 
/// 
/// 
/// 
/// 
/// 
/// 
/// 
/// 
/// 
/// 
/// 
/// 
/// 
/// 
/// 
/// 
/// 
/// 
/// 
/// 
/// 
/// 
/// 
/// 
/// 
/// 
/// 
/// 
/// 
/// 
/// 
/// 
/// 
/// 
/// 
/// 
/// 
/// 
/// 
/// 
/// 
/// 
/// 
/// 
/// 
/// 
/// 
/// 
/// 
/// 
/// 
/// 
/// 
/// 
/// 
/// 
/// 
/// 
/// 
/// 
/// 
/// 
/// 
/// 
/// 
/// 
/// 
/// 
/// 
/// 
/// 
/// 
/// 
/// 
/// 
/// 
/// 
/// 
/// 
/// 
/// 
/// 
/// 
/// 
/// 
/// 
/// 
/// 
/// 
/// 
/// 
/// 
/// 
/// 
/// 
/// 
/// 
/// 
/// 
/// 
/// 
/// 
/// 
/// 
/// 
/// 
/// 
/// 
/// 
/// 
/// 
/// 
/// 
/// 
/// 
/// 
/// 
/// 
/// 
/// 
/// 
/// 
/// 
/// 
/// 
/// 
/// 
/// 
/// 
/// 
/// 
/// 
/// 
/// 
/// 
/// 
/// 
/// 
/// 
/// 
/// 