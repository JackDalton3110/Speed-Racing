#include "Game.h"
#include "Controller.h"

Game::Game() :
	m_window(sf::VideoMode(1000, 800), "Mash 'Em"),
	m_currentGameState(GameState::licence)
{
	if (m_Impact.loadFromFile("c:/windows/fonts/impact.ttf"))
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


	if (!m_Texture1.loadFromFile("G:/HCI/button-game-jack-jamie-1/ButtonGame/images/A.png"))
	{
		std::string s("error loading texture from file");
		throw std::exception(s.c_str());
	}

	if (!m_Texture2.loadFromFile("G:/HCI/button-game-jack-jamie-1/ButtonGame/images/X.png"))
	{
		std::string s("error loading texture from file");
		throw std::exception(s.c_str());
	}
	if (!m_Texture3.loadFromFile("G:/HCI/button-game-jack-jamie-1/ButtonGame/images/Y.png"))
	{
		std::string s("error loading texture from file");
		throw std::exception(s.c_str());
	}
	if (!m_Texture4.loadFromFile("G:/HCI/button-game-jack-jamie-1/ButtonGame/images/B.png"))
	{
		std::string s("error loading texture from file");
		throw std::exception(s.c_str());
	}

	m_Sprite1.setTexture(m_Texture1);
	m_Sprite2.setTexture(m_Texture2);
	m_Sprite3.setTexture(m_Texture3);
	m_Sprite4.setTexture(m_Texture4);

	m_Sprite1.setOrigin(325, 325);//set origin of image
	m_Sprite1.setPosition(250, 250);//set image position in relation to origin
	m_Sprite1.setScale(0.1f, 0.1f);

	if (!m_Texture5.loadFromFile("G:/HCI/button-game-jack-jamie-1/ButtonGame/images/arrow.png"))
	{
		std::string s("error loading texture from file");
		throw std::exception(s.c_str());
	}

	m_Sprite1.setTexture(m_Texture1);
	m_Sprite2.setTexture(m_Texture2);
	m_Sprite3.setTexture(m_Texture3);
	m_Sprite4.setTexture(m_Texture4);
	m_Sprite5.setTexture(m_Texture5);
	m_Sprite1.setOrigin(325, 325);//set origin of image
	m_Sprite1.setPosition(250, 100);//set image position in relation to origin
	m_Sprite1.setScale(0.1f, 0.1f);
	m_Sprite2.setOrigin(325, 325);//set origin of image
	m_Sprite2.setPosition(100, 250);//set image position in relation to origin
	m_Sprite2.setScale(0.1f, 0.1f);
	m_Sprite3.setOrigin(350, 325);//set origin of image
	m_Sprite3.setPosition(400, 250);//set image position in relation to origin
	m_Sprite3.setScale(0.1f, 0.1f);
	m_Sprite4.setOrigin(325, 325);//set origin of image
	m_Sprite4.setPosition(275, 450);//set image position in relation to origin
	m_Sprite4.setScale(0.2f, 0.2f);
	m_Sprite5.setOrigin(300, 300);//set origin of image
	m_Sprite5.setPosition(350, 350);//set image position in relation to origin
	m_Sprite5.setScale(0.2f, 0.2f);
}

Game::~Game()
{
	delete(m_licence);//delete game states
	delete(m_splashscreen);
	delete(m_option);
	delete(m_credits);
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
		m_Sprite5.setPosition(350, 310);
		m_Sprite5.setRotation(270);
		score++;
	}
	if (m_controller.m_currentState.Y && score == 1)//any key accepted to change screen to credits
	{
		m_Sprite5.setPosition(300, 340);
		m_Sprite5.setRotation(90);
		score++;
	}
	if (m_controller.m_currentState.X && score == 2)//any key accepted to change screen to credits
	{
		m_Sprite5.setPosition(300, 300);
		m_Sprite5.setRotation(180);
		score++;
	}
	if (m_controller.m_currentState.A && score == 3)
	{
		m_currentGameState = GameState::credits;
	}


	m_controller.update();
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
		m_window.draw(m_Sprite1);
		m_window.draw(m_Sprite3);
		m_window.draw(m_Sprite2);
		m_window.draw(m_Sprite4);
		m_window.draw(m_Sprite5);
		m_window.draw(m_textMessage[0]);
		m_window.draw(m_textMessage[1]);
		//m_window.draw(shape);
		m_window.display();
		break;
	}

}