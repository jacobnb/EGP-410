#pragma once
#include <Trackable.h>
#include "Steering.h"
#include <vector>

class Unit;

class CohesionSteering : public Steering
{
public:
	CohesionSteering(const UnitID& ownerID);
	~CohesionSteering();
	inline void setRadius(const float detectionRadius) { mDetectRadius = detectionRadius; };
protected:
	virtual Steering* getSteering();
private:
	float mDetectRadius;
	std::vector<Vector2D>* getUnitsInRadius(std::vector<Unit*> allUnits);
	//pass in gpGame->getUnitManager()->getAllUnits(); so it's more easily testable.

	Vector2D getCenterOfUnits(std::vector<Vector2D>* unitLocations);
};