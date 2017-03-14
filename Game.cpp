#include "Game.h"
#include "Controller.h"

Game::Game() :
	m_window(sf::VideoMode(1000, 800), "Mash 'Em"),
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

	if (!songBuffer[0].loadFromFile("sounds/song1.wav"))
	{
		std::string s("error loading wav file");
		throw std::exception(s.c_str());
	}

	if (!buttonBuffer.loadFromFile("sounds/ButtonClick.wav"))
	{
		std::string s("error loading wav file");
		throw std::exception(s.c_str());
	}

	songs[0].setBuffer(songBuffer[0]);
	buttonsound.setBuffer(buttonBuffer);

	m_licence = new Licence(*this, m_HARLOW, m_Motor);
	m_splashscreen = new Splash(*this, m_HARLOW, m_Motor);
	m_carSelect = new CarSelect(*this, m_HARLOW);
	m_option = new Option(*this, m_Motor, m_HARLOW);
	m_credits = new Credits(*this, m_Motor);
	m_DifficultyScreen = new Difficulty(*this, m_Motor, m_HARLOW);
	m_soundScreen = new Sound(*this, m_Motor, m_HARLOW);

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
	delete(m_DifficultyScreen);
	delete(m_soundScreen);
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

	if (controller.m_currentState.Back)
	{
		m_window.close();
	}

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
		m_option->update(time, controller);
		break;
	case GameState::Difficulty:
		std::cout << "difficulty" << std::endl;
		m_DifficultyScreen->Update(time, controller);
		break;
	case GameState::sound:
		std::cout << "sound" << std::endl;
		m_soundScreen->Update(time, controller);
		break;
	case GameState::credits:
		m_credits->update(time);
		break;
	default:
		break;
	}
	m_controller.update();
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
			songs[0].play();
		}
		if (m_controller.m_currentState.Start && m_currentGameState == GameState::none)//any key accepted to change screen to credits
		{
			m_option->changeToOption();
		}

		if (m_controller.m_currentState.A && m_currentGameState == GameState::option && m_option->strtgame == true)
		{
				m_option->changeScreen();
		}

		if (m_controller.m_currentState.A && !m_controller.m_previousState.A && m_currentGameState == GameState::option && m_option->sound == true)
		{
			m_option->changeToSound();
		}

		if(m_controller.m_currentState.A && !m_controller.m_previousState.A && m_currentGameState == GameState::option && m_option->difficulty == true)
		{
			m_option->changeToDifficulty();
			m_option->settings = true;
		}

		if (m_controller.m_currentState.B && m_currentGameState == GameState::Difficulty)
		{
			m_DifficultyScreen->changeScreen();
			m_option->settings = true;
		}
		if (m_controller.m_currentState.B&&m_currentGameState == GameState::sound)
		{
			m_soundScreen->changeScreen();
		}
		
		if(m_currentGameState==GameState::option|| m_currentGameState==GameState::sound||m_currentGameState==GameState::carSelect||m_currentGameState==GameState::Difficulty)
		{
			buttonsound.play();
		}

		

	}
}

void Game::render()
{
	switch (m_currentGameState)
	{
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
	case GameState::sound:
		m_soundScreen->render(m_window);
		break;
	case GameState::Difficulty:
		m_DifficultyScreen->render(m_window);
		break;
	case GameState::credits:
		m_credits->render(m_window);
		break;
	default:
		m_window.clear(sf::Color(93, 194, 30));
		m_window.draw(m_textMessage[0]);
		m_window.draw(m_textMessage[1]);
		m_window.display();
		break;
	}

}