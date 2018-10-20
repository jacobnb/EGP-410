#include "DijkstraPathfinder.h"
#include "Path.h"
#include "Connection.h"
#include "GridGraph.h"
#include "Game.h"
#include <PerformanceTracker.h>
#include <queue>
#include "Compare.h"

DijkstraPathfinder::DijkstraPathfinder(Graph * pGraph):
	GridPathfinder(dynamic_cast<GridGraph*>(pGraph))
{
#ifdef VISUALIZE_PATH
	mpPath = NULL;
#endif

}

DijkstraPathfinder::~DijkstraPathfinder()
{
#ifdef VISUALIZE_PATH
	delete mpPath;
#endif
}

Path * DijkstraPathfinder::findPath(Node * pFrom, Node * pTo)
{
	gpPerformanceTracker->clearTracker("path");
	gpPerformanceTracker->startTracking("path");
	std::priority_queue<DijkstraNode*, std::vector<DijkstraNode*>, Compare> nodesToVisit;
	nodesToVisit.push(new DijkstraNode(pFrom));
	return nullptr;
}
