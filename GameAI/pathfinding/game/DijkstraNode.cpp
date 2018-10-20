#include "DijkstraNode.h"
#include <limits>
DijkstraNode::DijkstraNode(const NODE_ID& id) :
	Node(id) 
{
}

DijkstraNode::DijkstraNode(const Node* node):
	Node(*node)
{
	//doesn't work- this = static_cast<DijkstraNode*>(node)
	mpCost = std::numeric_limits<float>::max();
	mpPrevNode = nullptr;
}
DijkstraNode::~DijkstraNode()
{
}

