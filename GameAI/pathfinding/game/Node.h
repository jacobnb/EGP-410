#pragma once

#include <Trackable.h>

const int BAD_NODE_ID = -1;
#define NODE_ID int

class Node:public Trackable
{
public:
	Node( const NODE_ID& id );
	Node();
	~Node();

	const NODE_ID& getId() const {return mId;};

	inline void setCost(const float newCost) { mpCost = newCost; };
	inline float getCost() { return mpCost; };
	inline void setPrevNode(const Node* prevNode) { mpPrevNode = prevNode; };
	inline const Node* getPrevNode() { return mpPrevNode; };

private:
	const NODE_ID mId;
	float mpCost;
	const Node* mpPrevNode;
};