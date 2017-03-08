#include "XBOX360CONTROLLER.h"

Xbox360Controller::Xbox360Controller():
	sf_Joystick_index(0u)
{
	initSprites();
}

Xbox360Controller::~Xbox360Controller() {

}

void Xbox360Controller::update() {
	sf::Joystick::update();
	if (m_currentState.A) {
		m_previousState.A = true;
	}
	else
	{
		m_previousState.A = false;
	}

	if (m_currentState.B) {
		m_previousState.B = true;
	}
	else
	{
		m_previousState.B = false;
	}

	if (m_currentState.X) {
		m_previousState.X = true;
	}
	else
	{
		m_previousState.X = false;
	}

	if (m_currentState.Y) {
		m_previousState.Y = true;
	}
	else
	{
		m_previousState.Y = false;
	}

	if (m_currentState.LB) {
		m_previousState.LB = true;
	}
	else
	{
		m_previousState.LB = false;
	}

	if (m_currentState.RB) {
		m_previousState.RB = true;
	}
	else
	{
		m_previousState.RB = false;
	}

	if (m_currentState.LeftThumbStickClick) {
		m_previousState.LeftThumbStickClick = true;
	}
	else
	{
		m_previousState.LeftThumbStickClick = false;
	}

	if (m_currentState.RightThumbStickClick) {
		m_previousState.RightThumbStickClick = true;
	}
	else
	{
		m_previousState.RightThumbStickClick = false;
	}

	if (m_currentState.DpadUp) {
		m_previousState.DpadUp = true;
	}
	else
	{
		m_previousState.DpadUp = false;
	}

	if (m_currentState.DpadDown) {
		m_previousState.DpadDown = true;
	}
	else
	{
		m_previousState.DpadDown = false;
	}

	if (m_currentState.DpadLeft) {
		m_previousState.DpadLeft = true;
	}
	else
	{
		m_previousState.DpadLeft = false;
	}

	if (m_currentState.DpadRight) {
		m_previousState.DpadRight = true;
	}
	else
	{
		m_previousState.DpadRight = false;
	}

	if (m_currentState.Start) {
		m_previousState.Start = true;
	}
	else
	{
		m_previousState.Start = false;
	}

	if (m_currentState.Back) {
		m_previousState.Back = true;
	}
	else
	{
		m_previousState.Back = false;
	}

	if (m_currentState.Xbox) {
		m_previousState.Xbox = true;
	}
	else
	{
		m_previousState.Xbox = false;
	}

	if (m_currentState.LTtigger >= 5) {
		float LTnum = m_currentState.LTtigger;
		text[15].setString(toString(LTnum));
		text[15].setPosition(100, 70);
	}
	else
	{
		text[15].setString("");
	}

	if (m_currentState.RTtigger >= 5) {
		float RTnum = m_currentState.RTtigger;
		text[14].setString(toString(RTnum));
		text[14].setPosition(550, 70);
	}
	else
	{
		text[14].setString("");
	}

	if (m_currentState.RighThumbStick.x >= 10 || m_currentState.RighThumbStick.x <= -10 ||
		m_currentState.RighThumbStick.y >= 10 || m_currentState.RighThumbStick.y <= -10) {
		float Rx = m_currentState.RighThumbStick.x;
		float Ry = m_currentState.RighThumbStick.y;
		text[16].setString(toString(Rx) + " " + toString(Ry));
		text[16].setPosition(500, 480);
	}
	else
	{
		text[16].setString("");
	}

	if (m_currentState.LeftThumbStick.x >= 10 || m_currentState.LeftThumbStick.x <= -10 ||
		m_currentState.LeftThumbStick.y >= 10 || m_currentState.LeftThumbStick.y <= -10) {
		float Lx = m_currentState.LeftThumbStick.x;
		float Ly = m_currentState.LeftThumbStick.y;
		text[17].setString(toString(Lx) + " " + toString(Ly));
		text[17].setPosition(100, 320);
	}
	else
	{
		text[17].setString("");
	}
}

bool Xbox360Controller::connect() {
	return isConnected();
}

bool Xbox360Controller::isConnected() {
	if (sf::Joystick::isConnected(sf_Joystick_index)) {
		return true;
	}
	else {
		return false;
	}
}

void Xbox360Controller::render(sf::RenderWindow & window) {
	if (m_previousState.Y) {
		window.draw(text[0]);
		text[19].setString("Last botton pressed is Y");
	}

	if (m_previousState.X) {
		window.draw(text[1]);
		text[19].setString("Last botton pressed is X");
	}

	if (m_previousState.B) {
		window.draw(text[2]);
		text[19].setString("Last botton pressed is B");
	}

	if (m_previousState.A) {
		window.draw(text[3]);
		text[19].setString("Last botton pressed is A");
	}

	if (m_previousState.LB) {
		window.draw(text[4]);
	}

	if (m_previousState.RB) {
		window.draw(text[5]);
	}

	if (m_previousState.LeftThumbStickClick) {
		window.draw(text[6]);
	}

	if (m_previousState.RightThumbStickClick) {
		window.draw(text[7]);
	}

	if (m_previousState.DpadUp) {
		window.draw(text[8]);
	}

	if (m_previousState.DpadDown) {
		window.draw(text[9]);
	}

	if (m_previousState.DpadRight) {
		window.draw(text[10]);
	}

	if (m_previousState.DpadLeft) {
		window.draw(text[11]);
	}

	if (m_previousState.Start) {
		window.draw(text[12]);
	}

	if (m_previousState.Back) {
		window.close(); // when back button pressed, close the window
	}
	
	window.draw(text[14]); // display axis of RT
	window.draw(text[15]); // display axis of LT
	
	window.draw(text[16]); // display axis position of Right Thumb Stick
	window.draw(text[17]); // display axis position of Left Thumb Stick
	
	window.draw(text[19]);
}
void Xbox360Controller::CheckButton() {
	m_currentState.A = sf::Joystick::isButtonPressed(sf_Joystick_index, 0u);
	m_currentState.B = sf::Joystick::isButtonPressed(sf_Joystick_index, 1u);
	m_currentState.X = sf::Joystick::isButtonPressed(sf_Joystick_index, 2u);
	m_currentState.Y = sf::Joystick::isButtonPressed(sf_Joystick_index, 3u);
	m_currentState.LB = sf::Joystick::isButtonPressed(sf_Joystick_index, 4u);
	m_currentState.RB = sf::Joystick::isButtonPressed(sf_Joystick_index, 5u);
	m_currentState.LeftThumbStickClick = sf::Joystick::isButtonPressed(sf_Joystick_index, 8u);
	m_currentState.RightThumbStickClick = sf::Joystick::isButtonPressed(sf_Joystick_index, 9u);
	m_currentState.Start = sf::Joystick::isButtonPressed(sf_Joystick_index, 7u);
	m_currentState.Back = sf::Joystick::isButtonPressed(sf_Joystick_index, 6u);
	m_currentState.RTtigger = sf::Joystick::getAxisPosition(sf_Joystick_index, sf::Joystick::Z);
	m_currentState.LTtigger = -m_currentState.RTtigger;
	m_currentState.LeftThumbStick.x = sf::Joystick::getAxisPosition(sf_Joystick_index, sf::Joystick::X);
	m_currentState.LeftThumbStick.y = sf::Joystick::getAxisPosition(sf_Joystick_index, sf::Joystick::Y);
	m_currentState.RighThumbStick.x = sf::Joystick::getAxisPosition(sf_Joystick_index, sf::Joystick::U);
	m_currentState.RighThumbStick.y = sf::Joystick::getAxisPosition(sf_Joystick_index, sf::Joystick::R);

	if (sf::Joystick::getAxisPosition(sf_Joystick_index, sf::Joystick::PovX) > 5)
	{
		m_currentState.DpadRight = true;
	}
	else
	{
		m_currentState.DpadRight = false;
	}

	if (sf::Joystick::getAxisPosition(sf_Joystick_index, sf::Joystick::PovX) < -5)
	{
		m_currentState.DpadLeft = true;
	}
	else
	{
		m_currentState.DpadLeft = false;
	}



	if (sf::Joystick::getAxisPosition(sf_Joystick_index, sf::Joystick::PovY) > 5)
	{
		m_currentState.DpadUp = true;
	}
	else
	{
		m_currentState.DpadUp = false;
	}

	if (sf::Joystick::getAxisPosition(sf_Joystick_index, sf::Joystick::PovY) < -5)
	{
		m_currentState.DpadDown = true;
	}
	else
	{
		m_currentState.DpadDown = false;
	}
}

void Xbox360Controller::initSprites() {
	font.loadFromFile("C:\\Windows\\Fonts\\times.ttf");

	for (int i = 0; i < 20; i++) {
		text[i].setFont(font);
		text[i].setScale(0.7f, 0.7f);
		text[i].setColor(sf::Color::Black);
	}

	text[0].setString("Button Y is pressed");
	text[0].setPosition(700, 270);

	text[1].setString("Button X is pressed");
	text[1].setPosition(700, 330);

	text[2].setString("Button B is pressed");
	text[2].setPosition(700, 390);

	text[3].setString("Button A is pressed");
	text[3].setPosition(700, 450);

	text[4].setString("Button LB is pressed");
	text[4].setPosition(690, 120);

	text[5].setString("Button RB is pressed");
	text[5].setPosition(210, 120);

	text[6].setString("Clicked"); // LeftThumbStickClick
	text[6].setPosition(150, 300);

	text[7].setString("Clicked"); // RightThumbStickClick
	text[7].setPosition(400, 500);

	text[8].setString("Up");
	text[8].setPosition(280, 480);

	text[9].setString("Down");
	text[9].setPosition(280, 480);

	text[10].setString("Right");
	text[10].setPosition(280, 500);

	text[11].setString("Left");
	text[11].setPosition(280, 500);

	text[12].setString("Pressed"); // strat button
	text[12].setPosition(700, 520);

	text[13].setString("Pressed"); // xobx button
	text[13].setPosition(400, 350);

	if (connect()) { // check connection
		text[18].setString("Controller connected");
	}
	else {
		text[18].setString("Controller not found");
	}

	text[19].setPosition(650, 200);
}

std::string Xbox360Controller::toString(float num) {
	char numString[256];
	sprintf_s(numString, "%f", num);
	return numString;
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
	return m_currentState.DpadUp;
}
bool Xbox360Controller::DpadDownButton()
{
	return m_currentState.DpadDown;
}
bool Xbox360Controller::DpadRightButton()
{
	return m_currentState.DpadRight;
}
bool Xbox360Controller::DpadLeftButton()
{
	return m_currentState.DpadLeft;
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