#include "Controller.h"

Xbox360Controller::Xbox360Controller()
{

}

void Xbox360Controller::update()
{
	m_previousState.A = m_currentState.A;
	m_previousState.B = m_currentState.B;
	m_previousState.X = m_currentState.X;
	m_previousState.Y = m_currentState.Y;
	m_previousState.LB = m_currentState.LB;
	m_previousState.RB = m_currentState.RB;
	m_previousState.Back = m_currentState.Back;
	m_previousState.Start = m_currentState.Start;
	m_previousState.RightThumbStickClick = m_currentState.RightThumbStickClick;
	m_previousState.LeftThumbStickClick = m_currentState.LeftThumbStickClick;
	m_previousState.DPadUp = m_currentState.DPadUp;
	m_previousState.DPadLeft = m_currentState.DPadLeft;
	m_previousState.DPadRight = m_currentState.DPadRight;
	m_previousState.LTrigger = m_currentState.LTrigger;
	m_previousState.RTrigger = m_currentState.RTrigger;
	m_previousState.LeftThumbSticks = m_currentState.LeftThumbSticks;
	m_previousState.RightThumbStick = m_currentState.RightThumbStick;

	if (isConnected())
	{
		m_currentState.A = sf::Joystick::isButtonPressed(sf_Joystick_index, 0);
		m_currentState.B = sf::Joystick::isButtonPressed(sf_Joystick_index, 1);
		m_currentState.X = sf::Joystick::isButtonPressed(sf_Joystick_index, 2);
		m_currentState.Y = sf::Joystick::isButtonPressed(sf_Joystick_index, 3);
		m_currentState.LB = sf::Joystick::isButtonPressed(sf_Joystick_index, 4);
		m_currentState.RB = sf::Joystick::isButtonPressed(sf_Joystick_index, 5);
		m_currentState.Back = sf::Joystick::isButtonPressed(sf_Joystick_index, 6);
		m_currentState.Start = sf::Joystick::isButtonPressed(sf_Joystick_index, 7);

		m_currentState.LeftThumbStickClick = sf::Joystick::isButtonPressed(sf_Joystick_index, 8);
		m_currentState.RightThumbStickClick = sf::Joystick::isButtonPressed(sf_Joystick_index, 9);
		m_currentState.Xbox = sf::Joystick::isButtonPressed(sf_Joystick_index, 10);
		m_currentState.DPadRight = (sf::Joystick::getAxisPosition(sf_Joystick_index, sf::Joystick::Axis::PovX) > dpadThreshold) ? true : false;
		m_currentState.DPadLeft = (sf::Joystick::getAxisPosition(sf_Joystick_index, sf::Joystick::Axis::PovX) < -dpadThreshold ? true : false);
		m_currentState.DPadUp = (sf::Joystick::getAxisPosition(sf_Joystick_index, sf::Joystick::Axis::PovY) > dpadThreshold ? true : false);
		m_currentState.DPadDown = (sf::Joystick::getAxisPosition(sf_Joystick_index, sf::Joystick::Axis::PovY) < -dpadThreshold ? true : false);
		m_currentState.LTrigger = -sf::Joystick::getAxisPosition(sf_Joystick_index, sf::Joystick::Z);
		m_currentState.RTrigger = -sf::Joystick::getAxisPosition(sf_Joystick_index, sf::Joystick::Z);
		m_currentState.LeftThumbSticks = sf::Vector2f(sf::Joystick::getAxisPosition(sf_Joystick_index, sf::Joystick::X),
			sf::Joystick::getAxisPosition(sf_Joystick_index, sf::Joystick::Y));
		m_currentState.RightThumbStick = sf::Vector2f(sf::Joystick::getAxisPosition(sf_Joystick_index, sf::Joystick::U),
			sf::Joystick::getAxisPosition(sf_Joystick_index, sf::Joystick::R));
	}
}

bool Xbox360Controller::isConnected()
{
	if (sf_Joystick_index < 0 || sf_Joystick_index>sf::Joystick::Count)
		return false;
	else
		return sf::Joystick::isConnected(sf_Joystick_index);
}

bool Xbox360Controller::connect()
{
	for (int i = 0; i < sf::Joystick::Count; i++)
	{
		if (sf::Joystick::isConnected(i))
		{
			sf_Joystick_index = i;
			return true;
		}
	}
	return false;
}

Xbox360Controller::~Xbox360Controller()
{

}

bool Xbox360Controller::Abutton()
{
	return m_currentState.A;
}
bool Xbox360Controller::Bbutton()
{
	return m_currentState.B;
}
bool Xbox360Controller::Xbutton()
{
	return m_currentState.X;
}
bool Xbox360Controller::Ybutton()
{
	return m_currentState.Y;
}
bool Xbox360Controller::LBbutton()
{
	return m_currentState.LB;
}
bool Xbox360Controller::RBbutton()
{
	return m_currentState.RB;
}
bool Xbox360Controller::LeftThumbStickClickButton()
{
	return m_currentState.LeftThumbStickClick;
}
bool Xbox360Controller::RightThumbStickClickButton()
{
	return m_currentState.RightThumbStickClick;
}
bool Xbox360Controller::DpadUpButton()
{
	return m_currentState.DPadUp;
}
bool Xbox360Controller::DpadDownButton()
{
	return m_currentState.DPadDown;
}
bool Xbox360Controller::DpadRightButton()
{
	return m_currentState.DPadRight;
}
bool Xbox360Controller::DpadLeftButton()
{
	return m_currentState.DPadLeft;
}
bool Xbox360Controller::StartButton()
{
	return m_currentState.Start;
}
bool Xbox360Controller::BackButton()
{
	return m_currentState.Back;
}
bool Xbox360Controller::XboxButton()
{
	return m_currentState.Xbox;
}
float Xbox360Controller::RTrigger()
{
	return m_currentState.RTrigger;
}
float Xbox360Controller::LTrigger()
{
	return m_currentState.LTrigger;
}
sf::Vector2f Xbox360Controller::RightThumbStick()
{
	return m_currentState.RightThumbStick;
}
sf::Vector2f Xbox360Controller::LeftThumbSticks()
{
	return m_currentState.LeftThumbSticks;
}