#ifndef MATINGPOINTSELECTOR_H
#define MATINGPOINTSELECTOR_H

#include "happah/geometries/gears/matinggear/MatingPoint.h"
#include <list>
#include <vector>

enum class PointPosition {
	IN_ANGULAR_PITCH,
	BEHIND_ANGULAR_PITCH,
	INFRONT_OF_ANGULAR_PITCH
};

class MatingPointSelector : public std::list<MatingPoint> {
public:
	MatingPointSelector(); //TODO: this should not be used!
	MatingPointSelector(hpuint matingNTeeth, bool matingTurnsClockwise);
	~MatingPointSelector();

	MatingPoint getFirstNoneErrorMatingPoint();
	std::list<MatingPoint>* getMatingPoints();
	std::vector<MatingPoint>* chooseSuitableMatingPointsForGear();
private:
	hpuint m_matingNTeeth;
	hpreal m_turnDirection;
	hpreal m_angularPitchRotation;

	void insertInList(
		MatingPoint matingPoint,
		PointPosition lastPosition,
		PointPosition currentPosition,
		std::vector< std::vector<MatingPoint>* >& lists);

	void turnPointsOfList(std::vector<MatingPoint>* list, PointPosition positionOfListPoints);

};

#endif //MATINGPOINTSELECTOR_H