#include "DijkstraPathfinder.h"
#include "Path.h"
#include "Connection.h"
#include "GridGraph.h"
#include "Game.h"
#include <PerformanceTracker.h>
#include <queue>
#include "PriorityQueue.h"
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
	//set up Open queue and add starting node.
	PriorityQueue<DijkstraNode*, std::vector<DijkstraNode*>, Compare> nodesToVisit;
	DijkstraNode* startNode = new DijkstraNode(pFrom);
	startNode->setCost(0);
	nodesToVisit.push(startNode);

	//Will probably have to change this.
#ifdef VISUALIZE_PATH
	delete mpPath;
	mVisitedNodes.clear();
	mVisitedNodes.push_back(pFrom);
#endif
	
	//create path?
	Path* pPath = new Path();

	//current node to get connections from?
	DijkstraNode* pCurrentNode = nullptr;
	//not sure what this is
	bool toNodeAdded = false;

	//might be faster to compare nodeID? two function calls vs dynamic_cast to base class
	while(dynamic_cast<Node*>(pCurrentNode) != pTo && nodesToVisit.size() > 0){
		pCurrentNode = nodesToVisit.top(); //access the top element
		nodesToVisit.pop(); //remove node, doesn't return it

		//Not sure about this
		pPath->addNode(pCurrentNode); //can pPath take DijkstraNode.

		//get connections from current Node
		std::vector<Connection*> connections = mpGraph->getConnections(pCurrentNode->getId());

		for (unsigned int i = 0; i < connections.size(); i++) {
			Connection* pConnection = connections[i];
			DijkstraNode* pTempToNode = new DijkstraNode(connections[i]->getToNode());

			if (!toNodeAdded && //if end not found
				!pPath->containsNode(pTempToNode) &&  //node is not in path
				nodesToVisit.find(pTempToNode) == nodesToVisit.end()
				//node is not in nodesTovisit
				) {
				nodesToVisit.push(pTempToNode);

				if (pTempToNode == pTo) { //found node, not 100% shortest path.
					toNodeAdded = true;
				}
#ifdef VISUALIZE_PATH
				mVisitedNodes.push_back(pTempToNode);
#endif
			}
		}
	}
	gpPerformanceTracker->stopTracking("path");
	mTimeElapsed = gpPerformanceTracker->getElapsedTime("path");

#ifdef VISUALIZE_PATH
	mpPath = pPath;
#endif
	return pPath;
}
