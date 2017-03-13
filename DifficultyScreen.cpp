#include "DifficultyScreen.h"

Difficulty::Difficulty(Game &game, sf::Font font, sf::Font font2) :
	m_game(&game),
	m_motor(font),
	m_harlow(font2)
{
	message[0].setFont(m_motor);
	message[0].setCharacterSize(100);
	message[0].setPosition(150, 50);
	message[0].setString("Choose Difficulty");
	message[0].setColor(sf::Color::Red);

	message[1].setFont(m_harlow);
	message[1].setCharacterSize(50);
	message[1].setPosition(200, 500);
	message[1].setString("Easy");
	message[1].setColor(sf::Color::Black);

	message[2].setFont(m_harlow);
	message[2].setCharacterSize(50);
	message[2].setPosition(400, 500);
	message[2].setString("Medium");
	message[2].setColor(sf::Color::Black);

	message[3].setFont(m_harlow);
	message[3].setCharacterSize(50);
	message[3].setPosition(625, 500);
	message[3].setString("Hard");
	message[3].setColor(sf::Color::Black);

	for (int i = 0; i < 3; i++)
	{
		difficulties[i].setOutlineColor(sf::Color(65, 965, 396));
		difficulties[i].setOutlineThickness(5);
		difficulties[i].setRadius(10);
	}
	difficulties[0].setPosition(200, 600);
	difficulties[1].setPosition(400, 600);
	difficulties[2].setPosition(700, 600);
}

Difficulty::~Difficulty()
{
	std::cout << "destroying difficulty screen" << std::endl;
}

void Difficulty::Update(sf::Time time, Xbox360Controller &controller)
{
	if (controller.m_currentState.B)
	{
		changeScreen();
	}

	if (controller.m_currentState.DPadRight && !controller.m_previousState.DPadRight)
	{
		if (button_ID < 2)
		{
			button_ID++;
		}
		else
		{
			button_ID = 0;
		}
	}

	if (controller.m_currentState.DPadLeft && !controller.m_previousState.DPadLeft)
	{
		if (button_ID > 0)
		{
			button_ID--;
		}
		else
		{
			button_ID = 2;
		}
	}

	if (button_ID == 0)
	{
		if (controller.m_currentState.A && !controller.m_previousState.A)
		{
			Easy = true;
			Medium = false;
			Hard = false;
		}
		difficulties[0].setOutlineColor(sf::Color::Black);
		difficulties[1].setOutlineColor(sf::Color(65, 965, 396));
		difficulties[2].setOutlineColor(sf::Color(65, 965, 396));
		controller.m_previousState = controller.m_currentState;
	}

	else if (button_ID == 1)
	{
		if (controller.m_currentState.A && !controller.m_previousState.A)
		{
			Easy = false;
			Medium = true;
			Hard = false;
		}
		difficulties[1].setOutlineColor(sf::Color::Black);
		difficulties[0].setOutlineColor(sf::Color(65, 965, 396));
		difficulties[2].setOutlineColor(sf::Color(65, 965, 396));
		controller.m_previousState = controller.m_currentState;
	}
	else if (button_ID == 2)
	{
		if (controller.m_currentState.A && !controller.m_previousState.A)
		{
			Easy = false;
			Medium = false;
			Hard = true;
		}
		difficulties[2].setOutlineColor(sf::Color::Black);
		difficulties[0].setOutlineColor(sf::Color(65, 965, 396));
		difficulties[1].setOutlineColor(sf::Color(65, 965, 396));
		controller.m_previousState = controller.m_currentState;
	}

	if (Medium == true)
	{
		difficulties[1].setFillColor(sf::Color::Green);
		Easy = false;
		Hard = false;
	}
	else if (Medium == false)
	{
		difficulties[1].setFillColor(sf::Color::White);
	}

	if (Easy == true)
	{
		difficulties[0].setFillColor(sf::Color::Green);
		Medium = false;
		Hard = false;

	}
	else if (Easy == false)
	{
		difficulties[0].setFillColor(sf::Color::White);
	}

	if (Hard == true)
	{
		difficulties[2].setFillColor(sf::Color::Green);
		Easy = false;
		Medium=false;
	}
	else if (Hard == false)
	{
		difficulties[2].setFillColor(sf::Color::White);
	}
}

void Difficulty::changeScreen()
{
	m_game->SetGameState(GameState::option);
}

void Difficulty::render(sf::RenderWindow &window)
{
	window.clear(sf::Color(215, 215, 215));
	
		window.draw(difficulties[0]);
		window.draw(difficulties[1]);
		window.draw(difficulties[2]);
		window.draw(message[0]);
		window.draw(message[1]);
		window.draw(message[2]);
		window.draw(message[3]);

	window.display();
}