#pragma once
#include "Node.h"
class DijkstraNode : public Node {
public:
	DijkstraNode(const NODE_ID& id);
	DijkstraNode(const Node* node); 
	//This is essentially a copy constructor, would be faster not to copy if possible.
	~DijkstraNode();
	inline void setCost(const float newCost) { mpCost = newCost; };
	inline float getCost() { return mpCost; };
	inline void setNode(const Node* prevNode) { mpPrevNode = prevNode; };
private:
	float mpCost; 
	const Node* mpPrevNode;
};