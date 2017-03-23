#pragma once
#include <SFML\Graphics.hpp>
#include <string>
#include <iostream>
#include "Physics.h"
#include "Controller.h"

class Game;

class Player
{
public:
	Player();
	~Player();

	void update(double t);
	void render(sf::RenderWindow &window);
	
	sf::FloatRect boundingBox();
	sf::Vector2f m_motion;

	sf::Vector2f m_postion;

	void setLocation();
	float m_acceleration;
	void highFriction();
	void normalFriction();
	sf::Vector2f getSpritePosition() const;
	void setPlayerStatus(float maxspeed, float accelecation, float handling, int car_ID);
	void getLapTimer();
	void resetHalfWay();
	bool m_halfway;
	sf::View view; // camera


private:
	void timer(double t);
	void driftMark();

	Physics physics;
	Xbox360Controller controller;

	sf::Font m_font;
	sf::Text m_text[3]; // text 0 for time, text 1 for motion, text 2 for loop
	sf::Text m_timer; // text for timer
	sf::Text m_lap_timer; // text for lap timer
	int timer_mis; // millisecond
	int timer_sec; // second
	int timer_min; // minute

	int lap_timer[3] = {0,0,0}; // 0 for millisecond, 1 for second, 2 for minute

	float m_degree;
	float m_velocity;

	float m_handbrake;

	float max_speed; // max speed
	float m_turning;
	float m_handling;

	//sf::View view; // camera

	sf::Texture m_texture; // car texture
	sf::Sprite m_sprite; // car sprite

	sf::Vector2f location_record;
	float degree_record;
	float located_time;

	sf::Texture texture_draft_mark;
	sf::Sprite sprite_draft_mark[100];
	int mark_count = 1;
	float draw_time = 0.1f;

	std::string intToString(int num); // int to string
};