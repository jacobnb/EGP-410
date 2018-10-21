#pragma once
#include "GridPathfinder.h"


class Path;
class Graph;
class GraphicsBuffer;
class Grid;
class DijkstraPathfinder : public GridPathfinder {
public:
	DijkstraPathfinder(Graph* pGraph);
	~DijkstraPathfinder();
	Path* findPath(Node* pFrom, Node* pTo); //don't forget to delete path
private:

};