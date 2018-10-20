#pragma once
#include "DijkstraNode.h"
//This is for the priority queue

class Compare {
public:
	//priority queue prioritizes largest. 
	//compare by default returns lhs < rhs, we want the opposite.
	inline bool operator() (DijkstraNode* node1, DijkstraNode* node2)
	{ //return LHS > RHS
		return node1->getCost() > node2->getCost();
	}; 
	//inline bool operator() (AStarNode* node1, AStarNode* node2)
	//{
	//	return node1->getCost() > node2->getCost();
	//};
};