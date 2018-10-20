#pragma once
#include "DijkstraNode.h"
//This is for the priority queue

class Compare {
public:
	//priority queue prioritizes largest. 
	//compare by default returns lhs < rhs, we want the opposite.
	inline bool operator() (Node* node1, Node* node2)
	{ //return LHS > RHS
		return node1->getCost() > node2->getCost();
	};
};