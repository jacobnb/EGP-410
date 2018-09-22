#include <Trackable.h>
#include "Steering.h"

class FaceSteering : public Steering
{
public:
	friend class SeekSteering;
	friend class ArriveAndFaceSteering;
	FaceSteering(const UnitID& ownerID, const Vector2D& targetLoc, const UnitID& targetID = INVALID_UNIT_ID);
protected:
	virtual Steering* getSteering();
private:
};