#include "FlockingSteering.h"
#include "AlignSteering.h"
#include "CohesionSteering.h"
#include "SeparationSteering.h"
#include "WanderSteering.h"
#include "Game.h"
#include "UnitManager.h"
#include "Unit.h"
#include "DataLoader.h"
FlockingSteering::FlockingSteering(const UnitID & ownerID)
{
	setOwnerID(ownerID);
	DataLoader* dl = gpGame->getDataLoader();
	mpAlignSteer = new AlignSteering(ownerID
	, dl->getAlignmentRadius());
	mpCohesionSteer = new CohesionSteering(ownerID
	, dl->getCohesionRadius());
	mpSeparationSteer = new SeparationSteering(ownerID
	, dl->getSeparationRadius());
	mpWanderSteer = new WanderSteering(ownerID);
	mCohesionMult = dl->getCohesionFactor();
	mSeparationMult = dl->getSeparationFactor();
	mAlignMult = dl->getAlignmentFactor();
	mWanderMult = dl->getWanderFactor();
}

FlockingSteering::~FlockingSteering()
{
	delete mpAlignSteer;
	delete mpCohesionSteer;
	delete mpSeparationSteer;
	delete mpWanderSteer;
}

void FlockingSteering::incrementCohesionRadius(float toAdd)
{
	mpCohesionSteer->incrementRadius(toAdd);
}

void FlockingSteering::incrementAlignRadius(float toAdd)
{
	mpAlignSteer->incrementRadius(toAdd);
}

void FlockingSteering::incrementSeparationRadius(float toAdd)
{
	mpSeparationSteer->incrementRadius(toAdd);
}

float FlockingSteering::getCohesionRadius()
{
	return mpCohesionSteer->getRadius();
}

float FlockingSteering::getAlignRadius()
{
	return mpAlignSteer->getRadius();
}

float FlockingSteering::getSeparationRadius()
{
	return mpSeparationSteer->getRadius();
}

Steering * FlockingSteering::getSteering()
{
	Unit* pOwner = gpGame->getUnitManager()->getUnit(mOwnerID);
	auto data = pOwner->getPhysicsComponent()->getData();
	auto cohesionVel = mpCohesionSteer->getSteering()->getData().acc;
	auto separationVel = mpSeparationSteer->getSteering()->getData().acc;
	auto alignVel = mpAlignSteer->getSteering()->getData().acc;
	auto wanderVel = mpWanderSteer->getSteering()->getData().acc;
	data.acc = cohesionVel * mCohesionMult
		+ separationVel * mSeparationMult
		+ alignVel * mAlignMult
		+ wanderVel * mWanderMult;

	//I think all the steerings include face (through seek) but if not, add face here.
	this->mData = data;
	return this;
}
