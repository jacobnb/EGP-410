#include "DijkstraNode.h"

DijkstraNode::DijkstraNode(const NODE_ID& id) :
	Node(id) 
{
}

DijkstraNode::DijkstraNode(const Node* node):
	Node(*node)
{
	//doesn't work- this = static_cast<DijkstraNode*>(node)
	mpCost = nullptr;
	mpPrevNode = nullptr;
}
DijkstraNode::~DijkstraNode()
{
}

