#include "Game.h"
#include "Controller.h"

Game::Game() :

	m_window(sf::VideoMode(1000, 800), "Speed"),
	m_currentGameState(GameState::licence)

{
	if (m_HARLOW.loadFromFile("C:/Windows/Fonts/HARLOWSI.TTF"))
	{
		std::cout << "Harlow has loaded" << std::endl;
	}
	else
	{
		std::cout << "Harlow not found" << std::endl;
	}

	if (m_Motor.loadFromFile("C:/Windows/Fonts/MotorwerkOblique.ttf"))
	{
		std::cout << "Motor has loaded" << std::endl;
	}
	else
	{
		std::cout << "Motor not found" << std::endl;
	}
	m_licence = new Licence(*this, m_HARLOW, m_Motor);
	m_splashscreen = new Splash(*this, m_HARLOW, m_Motor);
	m_carSelect = new CarSelect(*this, m_HARLOW, m_Motor);
	m_option = new Option(*this, m_Motor, m_HARLOW);
	m_credits = new Credits(*this, m_Motor);
	m_upgrade = new Upgrade(*this, m_HARLOW, m_Motor);
	m_confirm = new Confirm(*this, m_Motor);
	m_again = new Playagain(*this, m_Motor);
	m_gameplay = new Gameplay(*this, m_Motor);
	m_help = new Help(*this, m_Motor);


	m_textMessage[0].setPosition(20, 20);//set position
	m_textMessage[0].setString("Score: ");//set text
	m_textMessage[0].setFont(m_Motor);//set font 
	m_textMessage[0].setColor(sf::Color(255, 255, 255));//set colour
	m_textMessage[1].setPosition(450, 20);//set position
	m_textMessage[1].setString("Time: ");//set text
	m_textMessage[1].setFont(m_Motor);//set font 
	m_textMessage[1].setColor(sf::Color(255, 255, 255));//set colour


}

Game::~Game()
{
	delete(m_licence);//delete game states
	delete(m_splashscreen);
	delete(m_option);
	delete(m_carSelect);
	delete(m_credits);
	delete(m_upgrade);
	delete(m_confirm);
	delete(m_gameplay);
	delete(m_help);
	std::cout << "destroying game" << std::endl;
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

	m_controller.update();

	switch (m_currentGameState)
	{
	case GameState::licence:
		m_licence->update(time);//adding updates from each gamestate file
		break;
	case GameState::splash:
		processEvents();//accepts process events to change screen 
		m_splashscreen->update(time);
		std::cout << "splash" << std::endl;//update splash screen when game state is set to splash
		break;
	case GameState::carSelect:
		processEvents();
		m_carSelect->update(time, controller);
		std::cout << "car select" << std::endl;
		break;
	case GameState::none:
		std::cout << "Game is playing" << std::endl;
		break;
	case GameState::option:
		std::cout << "Menu" << std::endl;
		m_option->reset();
		m_option->update(time, controller);
		break;
	case GameState::upgrade:
		std::cout << "upgrade" << std::endl;
		m_upgrade->update(time, controller);
		break;
	case GameState::gameplay:
		m_gameplay->update(time.asSeconds(), m_carSelect->getSelection_ID(), m_controller);
		break;
	case GameState::credits:
		m_credits->update(time);
		break;
	case GameState::confirm:
		std::cout << "NO!" << std::endl;
		m_confirm->reset();
		m_confirm->update(controller);
		break;
	case GameState::playagain:
		m_again->reset();
		m_again->update(controller);
		break;
	case GameState::Help:
		m_help->update();
		break;
	default:
		break;
	}

	processEvents();
}

void Game::processEvents()
{
	sf::Event event;
	while (m_window.pollEvent(event))
	{
		if (m_controller.m_currentState.Start && m_currentGameState == GameState::splash)//any key accepted to change screen to credits
		{
			m_splashscreen->changeScreen();
		}

		if (m_controller.m_currentState.Back)
		{
			SetGameState(GameState::confirm);
		}

	}
}


void Game::render()
{
	switch (m_currentGameState)
	{
	case GameState::none:
		m_window.close();
		break;
	case GameState::licence:
		m_licence->render(m_window);
		break;
	case GameState::splash:
		m_splashscreen->render(m_window);//draw each gamestate
		break;
	case GameState::carSelect:
		m_carSelect->render(m_window);
		break;
	case GameState::option:
		m_option->render(m_window);
		break;
	case GameState::upgrade:
		m_upgrade->render(m_window);
		break;
	case GameState::gameplay:
		m_gameplay->render(m_window);
		break;
	case GameState::credits:
		m_credits->render(m_window);
		break;
	case GameState::confirm:
		m_confirm->render(m_window);
		break;
	case GameState::playagain:
		m_again->render(m_window);
		break;
	case GameState::Help:
		m_help->render(m_window);
		break;
	default:

		break;
	}

}