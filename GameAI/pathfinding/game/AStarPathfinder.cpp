#include "AStarPathfinder.h"
#include <PerformanceTracker.h>
#include "PriorityQueue.h"
#include "Connection.h"
#include "Compare.h"
#include "Path.h"
#include "Game.h"
#include "GameApp.h"
#include "GridGraph.h"
#include "Grid.h"
#include "Vector2D.h"

AStarPathfinder::AStarPathfinder(Graph * pGraph):
	GridPathfinder(dynamic_cast<GridGraph*>(pGraph))
{
#ifdef VISUALIZE_PATH
	mpPath = NULL;
#endif
}

AStarPathfinder::~AStarPathfinder()
{
#ifdef VISUALIZE_PATH
	delete mpPath;
#endif
}

Path * AStarPathfinder::findPath(Node * pFrom, Node * pTo)
{
	gpPerformanceTracker->clearTracker("path");
	gpPerformanceTracker->startTracking("path");
	//set up Open queue and add starting node.
	PriorityQueue<Node*, std::vector<Node*>, CompareAStar> nodesToVisit;
	Node* startNode = pFrom;
	startNode->setCost(0);
	nodesToVisit.push(startNode);

	//Will probably have to change this.
#ifdef VISUALIZE_PATH
	delete mpPath;
	mVisitedNodes.clear(); //This list seems useless, it is closed list rather than a visualization
	mVisitedNodes.push_back(pFrom);
#endif

	//create path?
	Path* pPath = new Path(); //this is for visualization but also acts as the closed list. 

	//current node to get connections from?
	Node* pCurrentNode = nullptr;
	//end node added.
	bool toNodeAdded = false;

	//might be faster to compare nodeID? two function calls vs dynamic_cast to base class
	while (pCurrentNode != pTo && nodesToVisit.size() > 0) {
		pCurrentNode = nodesToVisit.top(); //access the top element
		nodesToVisit.pop(); //remove node, doesn't return it

		//Not sure about this
		pPath->addNode(pCurrentNode);

		//get connections from current Node
		std::vector<Connection*> connections = mpGraph->getConnections(pCurrentNode->getId());

		for (unsigned int i = 0; i < connections.size(); i++) { //for each neighbor of current node
			Connection* pConnection = connections[i];

			//set up node.
			Node* pTempToNode = connections[i]->getToNode();
			auto cost = pConnection->getCost() + pCurrentNode->getCost();
			auto hCost = heuristic(pTempToNode, pTo);
			auto totalCost = cost + hCost;
			//Check for shorter path or init values.
			if (nodesToVisit.find(pTempToNode) != nodesToVisit.end()) {
				if (pTempToNode->getTotalCost() > totalCost) { //if shorter path has been found.
					pTempToNode->setCost(cost);
					pTempToNode->setHeuristic(hCost);
					pTempToNode->setPrevNode(pCurrentNode);
				}
			}
			else if (pPath->containsNode(pTempToNode)) {
				if (pTempToNode->getCost() > cost) { //if shorter path has been found.
					pTempToNode->setCost(cost);
					pTempToNode->setHeuristic(hCost);
					pTempToNode->setPrevNode(pCurrentNode);
				}
			}
			else if (!pPath->containsNode(pTempToNode)) {
				//once node is not in to visit list or in path.
				pTempToNode->setCost(cost);
				pTempToNode->setHeuristic(hCost);
				pTempToNode->setPrevNode(pCurrentNode);
			}




			if (!toNodeAdded && //if end not found
				!pPath->containsNode(pTempToNode) &&  //node is not in path
				nodesToVisit.find(pTempToNode) == nodesToVisit.end()
				//node is not in nodesTovisit
				) {
				nodesToVisit.push(pTempToNode);

				if (pTempToNode->getId() == pTo->getId()) { //found node, not 100% shortest path.
					toNodeAdded = true;
				}
#ifdef VISUALIZE_PATH
				mVisitedNodes.push_back(pTempToNode);
#endif
			}
		}
	}

	Node* lastPathNode = pTo;
#ifdef VISUALIZE_PATH
	//delete pPath;
	//pPath = new Path();
	//while (lastPathNode != pFrom) {
	//	pPath->addNode(lastPathNode);
	//	lastPathNode = lastPathNode->getPrevNode();
	//	//emergency case
	//	if (lastPathNode == nullptr) {
	//		lastPathNode = pFrom;
	//	}
	//}
#endif

	gpPerformanceTracker->stopTracking("path");
	mTimeElapsed = gpPerformanceTracker->getElapsedTime("path");

#ifdef VISUALIZE_PATH
	mpPath = pPath;
#endif
	return pPath;
}

float AStarPathfinder::heuristic(Node * pFrom, Node * pTo)
{
	Grid* pGrid = dynamic_cast<GameApp*>(gpGame)->getGrid();
	Vector2D diff = pGrid->getULCornerOfSquare(pFrom->getId()) -
	pGrid->getULCornerOfSquare(pTo->getId());

	return diff.getLength();
}

