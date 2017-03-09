#include "Game.h"
#include "Controller.h"

Game::Game() :
	m_window(sf::VideoMode(1000, 800), "Mash 'Em"),
	m_currentGameState(GameState::licence)
{
	/*if (m_Impact.loadFromFile("c:/windows/fonts/impact.ttf"))
	{
		std::cout << "Impact has loaded" << std::endl;
	}
	else
	{
		std::cout << "Impact not found" << std::endl;
	}
	m_licence = new Licence(*this, m_Impact);
	m_splashscreen = new Splash(*this, m_Impact);
	m_option = new Option(*this, m_Impact);
	m_credits = new Credits(*this, m_Impact);

	m_textMessage[0].setPosition(20, 20);//set position
	m_textMessage[0].setString("Score: ");//set text
	m_textMessage[0].setFont(m_Impact);//set font 
	m_textMessage[0].setColor(sf::Color(255, 255, 255));//set colour
	m_textMessage[1].setPosition(450, 20);//set position
	m_textMessage[1].setString("Time: ");//set text
	m_textMessage[1].setFont(m_Impact);//set font 
	m_textMessage[1].setColor(sf::Color(255, 255, 255));//set colour
	*/

}

Game::~Game()
{
	/*
	delete(m_licence);//delete game states
	delete(m_splashscreen);
	delete(m_option);
	delete(m_credits);
	std::cout << "destroying game" << std::endl;
	*/
}

void Game::run()
{
	sf::Clock clock;
	sf::Time timeSinceLastUpdate = sf::Time::Zero;
	sf::Time timePerFrame = sf::seconds(1.f / 60.0f);

	while (m_window.isOpen())
	{
		processEvents();
		timeSinceLastUpdate += clock.restart();
		while (timeSinceLastUpdate > timePerFrame)
		{
			timeSinceLastUpdate -= timePerFrame;
			update(timePerFrame, m_controller);
		}

		render();
	}
}

void Game::SetGameState(GameState gamestate)
{
	m_currentGameState = gamestate;
}

void Game::update(sf::Time time, Xbox360Controller &controller)
{
	/*
<<<<<<< HEAD
=======
	if (controller.m_currentState.Back)
	{
		m_window.close();
	}
>>>>>>> 9ecea5490fcb49a254ca604fc73ce3f51c9f3a4d
	switch (m_currentGameState)
	{
	case GameState::licence:
		m_licence->update(time);//adding updates from each gamestate file
		break;
	case GameState::splash:
		processEvents();//accepts process events to change screen 
		m_splashscreen->update(time); //update splash screen when game state is set to splash
		break;
	case GameState::none:
		std::cout << "Game is playing" << std::endl;
		break;
	case GameState::option:
		std::cout << "Menu" << std::endl;
		m_option->update(time, controller);
		break;
	case GameState::credits:
		m_credits->update(time);
		break;
	default:
		break;
	}

	if (m_controller.m_currentState.B && score == 0)//any key accepted to change screen to credits
	{
		score++;
	}
	if (m_controller.m_currentState.Y && score == 1)//any key accepted to change screen to credits
	{
		score++;
	}
	if (m_controller.m_currentState.X && score == 2)//any key accepted to change screen to credits
	{
		score++;
	}
	if (m_controller.m_currentState.A && score == 3)
	{
		m_currentGameState = GameState::credits;
	}

	*/

	m_controller.update();

	m_npc.update(time.asSeconds());
	m_player.update(time.asSeconds());
	processEvents();
}

void Game::processEvents()
{
	sf::Event event;
	while (m_window.pollEvent(event))
	{
		if (m_controller.m_currentState.Y && m_currentGameState == GameState::splash)//any key accepted to change screen to credits
		{
			m_splashscreen->changeScreen();

		}
		if (m_controller.m_currentState.Start && m_currentGameState == GameState::none)//any key accepted to change screen to credits
		{
			m_option->changeToOption();
		}
		//if (m_controller.m_currentState.B && m_currentGameState == GameState::option&& m_option->settings==false)//any key accepted to change screen to credits
		//{
		//	m_option->changeScreen();
		//}

	}
}

void Game::render()
{
	/*
	switch (m_currentGameState)
	{
	case GameState::licence:
		m_licence->render(m_window);
		break;
	case GameState::splash:
		m_splashscreen->render(m_window);//draw each gamestate
		break;
	case GameState::option:
		m_option->render(m_window);
		break;
	case GameState::credits:
		m_credits->render(m_window);
		break;
	default:
		m_window.clear(sf::Color(93, 194, 30));
		m_window.draw(m_textMessage[0]);
		m_window.draw(m_textMessage[1]);
		//m_window.draw(shape);
		break;
	}
	*/
	m_player.render(m_window);
	m_npc.render(m_window);
	m_window.display();

}