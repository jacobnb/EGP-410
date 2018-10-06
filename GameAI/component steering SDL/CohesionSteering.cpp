#include "CohesionSteering.h"
#include "Game.h"
#include "UnitManager.h"
#include "Unit.h"
CohesionSteering::CohesionSteering(const UnitID & ownerID)
{
}

CohesionSteering::~CohesionSteering()
{
}

Steering * CohesionSteering::getSteering()
{
	Vector2D targetLoc = getCenterOfUnits(
		getUnitsInRadius(
			gpGame->getUnitManager()->getAllUnits()
		)
	);


	return nullptr;
}

std::vector<Vector2D>* CohesionSteering::getUnitsInRadius(std::vector<Unit*> allUnits)
{
	using std::vector;
	vector<Vector2D>* unitPosits = new vector<Vector2D>();

	for (vector<Unit*>::iterator it = allUnits.begin();
		it != allUnits.end(); it++){
		Vector2D loc = (*it)->getPositionComponent()->getPosition();
		if (loc.getLength() < mDetectRadius) {
			unitPosits->push_back(loc);
		}
	}

	return unitPosits;
}

Vector2D CohesionSteering::getCenterOfUnits(std::vector<Vector2D>* unitLocations)
{
	Vector2D centerLoc = ZERO_VECTOR2D;
	for (std::vector<Vector2D>::iterator it = unitLocations->begin();
		it != unitLocations->end(); it++) {
		centerLoc += *it;
	}
	centerLoc /= unitLocations->size;
	return centerLoc;
}
