#include "Game.h"
#include "Controller.h"

Game::Game() :

	m_window(sf::VideoMode(1000, 800), "Speed"),
	m_currentGameState(GameState::credits)

{
	int currentLevel = 1;
	if (!LevelLoader::load(currentLevel, m_level))
	{
		return;
	}
	
	GenerateTrack();

	if (!ai_Txt.loadFromFile("images/Node.png"))
	{
		std::cout << "error loading ai Sprite" << std::endl;
	}
	ai_Sprite.setTexture(ai_Txt);

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

	//Loading final animation
	if (!m_movie.openFromFile("Video/animation4.mov"))
	{
		std::string s("error loading mov file");
		throw std::exception(s.c_str());
	}


	songs[0].setBuffer(songBuffer[0]);
	buttonsound.setBuffer(buttonBuffer);

	m_licence = new Licence(*this, m_HARLOW, m_Motor);
	m_splashscreen = new Splash(*this, m_HARLOW, m_Motor);
	m_carSelect = new CarSelect(*this, m_HARLOW, m_Motor);
	m_option = new Option(*this, m_Motor, m_HARLOW);
	m_credits = new Credits(*this, m_Motor, m_movie);
	m_upgrade = new Upgrade(*this, m_HARLOW, m_Motor);
	m_confirm = new Confirm(*this, m_Motor);
	m_again = new Playagain(*this, m_Motor);
	m_gameplay = new Gameplay(*this, m_Motor, m_player, m_trackCircle);
	m_help = new Help(*this, m_Motor);
	m_map = new Map(*this, m_player);
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

	view.setCenter(500, 400); // set player's position to camera
	view.setSize(sf::Vector2f(1000, 800)); // set camera's size
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
	delete(m_map);
	delete(m_DifficultyScreen);
	delete(m_soundScreen);
	std::cout << "destroying game" << std::endl;
}

void Game::GenerateTrack()
{
	sf::IntRect nodeRect(2, 129, 33, 23);

	for (NodeData const &node : m_level.m_node)
	{
		sf::CircleShape circle(nodeRect.width * 1);
		circle.setFillColor(sf::Color::Black);
		circle.setOrigin(circle.getRadius(), circle.getRadius());
		circle.setPosition(node.m_position);
		m_trackCircle.push_back(std::move(circle));
	}

	sf::IntRect nodeRect1(2, 129, 33, 23);
	for (NodeData const &node1 : m_level.m_node1)
	{
		sf::CircleShape circle1(nodeRect1.width * 1);
		circle1.setFillColor(sf::Color::Blue);
		circle1.setOrigin(circle1.getRadius(), circle1.getRadius());
		circle1.setPosition(node1.m_position);
		m_trackCircle1.push_back(std::move(circle1));
	}

	sf::IntRect nodeRect2(2, 129, 33, 23);
	for (NodeData const &node2 : m_level.m_node2)
	{
		sf::CircleShape circle2(nodeRect2.width * 1);
		circle2.setFillColor(sf::Color::Blue);
		circle2.setOrigin(circle2.getRadius(), circle2.getRadius());
		circle2.setPosition(node2.m_position);
		m_trackCircle2.push_back(std::move(circle2));
	}
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

	switch (m_currentGameState)
	{
	case GameState::licence:
		m_licence->update(time);//adding updates from each gamestate file
		break;
	case GameState::splash:
		processEvents();//accepts process events to change screen 
		m_splashscreen->update(time);
		// std::cout << "splash" << std::endl;//update splash screen when game state is set to splash
		break;
	case GameState::carSelect:
		processEvents();
		m_carSelect->reset();
		for (int i = 0; i < 3; i++)
		{
			m_carSelect->getCarValues(m_upgrade->whiteCar_values[i], m_upgrade->reaCar_values[i], m_upgrade->yellowCar_values[i], m_upgrade->greenCar_values[i], i);
		}
		m_carSelect->update(time, controller);
		std::cout << "car select" << std::endl;
		break;
	case GameState::none:
		std::cout << "Game is playing" << std::endl;
		break;
	case GameState::option:
		//std::cout << "Menu" << std::endl;
		m_option->reset();
		m_option->update(time, controller);
		break;
	case GameState::upgrade:
		//std::cout << "upgrade" << std::endl;
		m_upgrade->update(time.asSeconds(), controller, time);
		break;
	case GameState::gameplay:
		m_map->update();
		switch (m_carSelect->getSelection_ID())
		{
		case 0:
			m_gameplay->getStatus(m_upgrade->whiteCar_values[0], m_upgrade->whiteCar_values[1], m_upgrade->whiteCar_values[2]);
			break;
		case 1 :
			m_gameplay->getStatus(m_upgrade->reaCar_values[0], m_upgrade->reaCar_values[1], m_upgrade->reaCar_values[2]);
			break;
		case 2:
			m_gameplay->getStatus(m_upgrade->yellowCar_values[0], m_upgrade->yellowCar_values[1], m_upgrade->yellowCar_values[2]);
			break;
		case 3:
			m_gameplay->getStatus(m_upgrade->greenCar_values[0], m_upgrade->greenCar_values[1], m_upgrade->greenCar_values[2]);
			break;
		default:
			break;
		}
		m_gameplay->update(time.asSeconds(), m_carSelect->getSelection_ID(), m_controller);
		break;
	case GameState::Difficulty:
		std::cout << "difficulty" << std::endl;
		m_DifficultyScreen->Update(time, controller);
		break;
	case GameState::sound:
		std::cout << "sound" << std::endl;
		m_soundScreen->Update(time, controller);
		m_controller.m_previousState = m_controller.m_currentState;
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
		m_help->update(controller);
		break;
	case GameState::Map:
		m_map->update();
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

		if (m_controller.m_currentState.Back)
		{
			SetGameState(GameState::confirm);
		}
		
		if(m_currentGameState==GameState::option|| m_currentGameState==GameState::sound||m_currentGameState==GameState::carSelect||m_currentGameState==GameState::Difficulty || m_currentGameState ==GameState::upgrade)
		{
			buttonsound.play();
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
		m_map->render(m_window);
		m_gameplay->render(m_window);
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

	if (m_currentGameState != GameState::gameplay)
	{
		view.setCenter(500, 400); // set player's position to camera
		view.setSize(sf::Vector2f(1000, 800)); // set camera's size
		m_window.setView(view);
	}

	m_window.display();
}