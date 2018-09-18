#include <Trackable.h>
#include "Steering.h"

class WanderSteering : public Steering
{
public:
	//need to pass radius and center?
	WanderSteering(const UnitID& ownerID, const Vector2D& targetLoc, const UnitID& targetID = INVALID_UNIT_ID);
protected:
	virtual Steering* getSteering();
	
};