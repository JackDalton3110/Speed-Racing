#include "LevelLoader.h"

void operator >> (const YAML::Node& followNode, NodeData& Nodes)
{
	Nodes.m_type = followNode["type"].as<std::string>();
	Nodes.m_position.x = followNode["position"]["x"].as<float>();
	Nodes.m_position.y = followNode["position"]["y"].as<float>();
}

void operator >> (const YAML::Node& levelNode, LevelData& level)
{
	const YAML::Node& Node = levelNode["Nodes"].as<YAML::Node>();
	for (unsigned i = 0; i < Node.size(); i++)
	{
		NodeData node;
		Node[i] >> node;
		level.m_node.push_back(node);
	}
}

LevelLoader::LevelLoader()
{
}

bool LevelLoader::load(int nr, LevelData& level)
{
	std::stringstream ss;

	ss << resourcePath();
	ss << "levels/level";
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
	catch (std::exception& e)
	{
		std::cout << e.what() << "\n";
		return false;
	}

	return true;
}
