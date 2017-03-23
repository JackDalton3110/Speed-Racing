#include "LevelLoader.h"
#include <time.h>

void operator >> (const YAML::Node & trackNode, NodeData& track)
{
	track.m_type = trackNode["type"].as<std::string>();
	track.m_position.x = trackNode["position"]["x"].as<float>();
	track.m_position.y = trackNode["position"]["y"].as<float>();
	track.m_rotation = trackNode["rotation"].as<double>();
}

void operator >> (const YAML::Node& levelNode, LevelData &level)
{
	const YAML::Node& trackNode = levelNode["Nodes"].as<YAML::Node>();//loads nodes from yaml file
	for (unsigned i = 0; i < trackNode.size(); ++i)
	{
		NodeData track;
		trackNode[i] >> track;
		level.m_node.push_back(track);

	}

	const YAML::Node& trackNode1 = levelNode["Nodes1"].as<YAML::Node>();//Loads Nodes1 from yaml file
	for (unsigned i = 0; i < trackNode1.size(); ++i)
	{
		NodeData track;
		trackNode1[i] >> track;
		level.m_node.push_back(track);

	}

	const YAML::Node& trackNode2 = levelNode["Nodes2"].as<YAML::Node>();//load Nodes2 from file
	for (unsigned i = 0; i < trackNode2.size(); ++i)
	{
		NodeData track;
		trackNode2[i] >> track;
		level.m_node.push_back(track);

	}
}

LevelLoader::LevelLoader()
{

}


bool LevelLoader::load(int nr, LevelData &level)
{
	std::stringstream ss;
	ss << "./levels/level";//load form this file
	ss << nr;
	ss << ".yaml";

	try
	{
		YAML::Node baseNode = YAML::LoadFile(ss.str());		
		if (baseNode.IsNull())
		{
			std::string message("file: " + ss.str() + " not found");

			throw std::exception(message.c_str());
		}
		baseNode >> level;
	}
	catch (YAML::ParserException& e)
	{
		std::cout << e.what() << "\n";
		return false;
	}

	catch (std::exception &e)
	{
		std::cout << e.what() << "\n";
		return false;
	}
	return true;
}


