#pragma once

#include <SFML/System/Vector2.hpp>
#include <vector>
#include <sstream>
#include <fstream>
#include <iostream>
#include "yaml-cpp\yaml.h"
#include "ResourcePath.hpp"

struct NodeData
{
	std::string m_type;
	sf::Vector2f m_position;
};

struct LevelData
{
	std::vector<NodeData> m_node;
};

class LevelLoader
{
public:

	LevelLoader();

	static bool load(int nr, LevelData& level);
};
