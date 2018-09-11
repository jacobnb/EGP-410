#include <Trackable.h>
#include "Steering.h"

class SeekSteering : public Steering
{
public:
	SeekSteering(const UnitID& ownerID, const Vector2D& targetLoc, const UnitID& targetID = INVALID_UNIT_ID, bool shouldFlee = false);
	//int testMe(const int value);
protected:
	virtual Steering* getSteering();
};