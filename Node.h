#pragma once

#include "entityx/Entity.h"
//enum class NodeType
//{
//	NT_small,
//};

struct Node : public entityx::Component<Node>
{
	//Node(NodeType type = NodeType::NT_small);
	Node();
	//NodeType m_type;
};