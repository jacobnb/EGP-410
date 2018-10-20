#pragma once
#include "DijkstraNode.h"
//This is for the priority queue

class Compare {
public:
	inline bool operator() (DijkstraNode* node1, DijkstraNode* node2)
	{
		return node1->getCost() < node2->getCost() ? true : false;
	};
	//inline bool operator() (AStarNode* node1, AStarNode* node2)
	//{
	//	return node1->getCost() < node2->getCost() ? true : false;
	//};
};