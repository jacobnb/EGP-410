#pragma once
#include "Node.h"
class DijkstraNode : public Node {
public:
//This isn't being used because I decided to add the extra variables into Node for simplicity.
	DijkstraNode(const NODE_ID& id);
	DijkstraNode(const Node* node); 
	//This is essentially a copy constructor, would be faster not to copy if possible.
	~DijkstraNode();
	inline void setCost(const float newCost) { mpCost = newCost; };
	inline float getCost() { return mpCost; };
	inline void setPrevNode(const Node* prevNode) { mpPrevNode = prevNode; };
	inline const Node* getPrevNode() { return mpPrevNode; };
private:
	float mpCost; 
	const Node* mpPrevNode; //might have to convert this to a dijkstra node
};