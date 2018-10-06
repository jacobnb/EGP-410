#include "CohesionSteering.h"
#include "Game.h"
#include "UnitManager.h"
#include "Unit.h"
#include "SeekSteering.h"
CohesionSteering::CohesionSteering(const UnitID & ownerID, float detectionRadius)
{
	mDetectRadius = detectionRadius;
	setOwnerID(ownerID);
	mpSeekSteering = new SeekSteering(ownerID, ZERO_VECTOR2D);
}

CohesionSteering::~CohesionSteering()
{
	delete mpSeekSteering;
}

Steering * CohesionSteering::getSteering()
{
	//set up
	Unit* pOwner = gpGame->getUnitManager()->getUnit(mOwnerID);
	auto data = pOwner->getPhysicsComponent()->getData();

	//Find location
	Vector2D targetLoc = getCenterOfUnits(
		getUnitsInRadius(
			pOwner->getPositionComponent()->getPosition(),
			gpGame->getUnitManager()->getAllUnits()
		)
	);

	setTargetLoc(targetLoc);

	//Seek location
	mpSeekSteering->setTargetLoc(targetLoc);
	data = mpSeekSteering->getSteering()->getData();
	
	this->mData = data;
	return this;
}

std::vector<Vector2D>* CohesionSteering::getUnitsInRadius(Vector2D ownerPosit, std::vector<Unit*> allUnits)
{
	//this gets all units (including self) in mDetectRadius
	using std::vector;
	vector<Vector2D>* unitPosits = new vector<Vector2D>();

	for (vector<Unit*>::iterator it = allUnits.begin();
		it != allUnits.end(); it++){
		Vector2D loc = (*it)->getPositionComponent()->getPosition();
		if ((ownerPosit-loc).getLength() < mDetectRadius) {
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
	if (unitLocations->size() > 0) {
		centerLoc *= (1.0 / unitLocations->size());
	}
	return centerLoc;
}
