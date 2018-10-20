#pragma once
#include "Graph.h"
class Grid;
class DijkstraGraph : Graph {
	//copy GridGraph
	//needs to hold DijkstraNodes
	//Needs to set DijkstraNodes Cost to infinity and prev to nullptr;
public:
	DijkstraGraph(Grid* pGrid);
	~DijkstraGraph();

private:
};