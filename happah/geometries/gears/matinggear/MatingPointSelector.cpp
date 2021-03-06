#include "happah/geometries/gears/matinggear/MatingPointSelector.h"

#include "glm/glm.hpp"
#include "glm/gtx/rotate_vector.hpp"
#include "happah/HappahUtils.h"

#include <iostream>
using namespace std;


MatingPointSelector::MatingPointSelector()
  : m_matingNTeeth(10),
	m_turnDirection(1.0f),
	m_angularPitchRotation((360.0f * m_turnDirection) / m_matingNTeeth) {
}

MatingPointSelector::MatingPointSelector(hpuint matingNTeeth, bool matingTurnsClockwise)
  : m_matingNTeeth(matingNTeeth),
	m_turnDirection((matingTurnsClockwise) ? 1.0f : -1.0f),
	m_angularPitchRotation((360.0f * m_turnDirection) / m_matingNTeeth) {
}

MatingPointSelector::~MatingPointSelector() {
}

MatingPoint MatingPointSelector::getFirstNoneErrorMatingPoint() {
	std::list<MatingPoint>::iterator it = begin();
	while(it->error != ErrorCode::NO_ERROR && it != end())
		++it;
	return *it; //TODO: what can be returned if end was reached?
}

std::list<MatingPoint>* MatingPointSelector::getMatingPoints() {
	return new std::list<MatingPoint>(*this);
}

std::vector<MatingPoint>* MatingPointSelector::getSuitableMatingPointsForGear() {
	std::vector< std::vector<MatingPoint>* > lists = std::vector< std::vector<MatingPoint>* >();
	return getSuitableMatingPointsForGearAndLists(lists);
}

std::vector<MatingPoint>* MatingPointSelector::getSuitableMatingPointsForGearAndLists(std::vector< std::vector<MatingPoint>* >& lists) {
	//every point has to be inside one angular pitch of the gear!
	//create lists with MatingPoints which lay either out of the angular pitch region or in it
	//lists with points that lay outside are rotated to the start or respectively to the end
	//of the angular pitch region so that they lay inside the region, too.
	hpvec2 startPitch = glm::normalize(getFirstNoneErrorMatingPoint().point);
	hpvec2 stopPitch = glm::normalize(glm::rotate(startPitch, m_angularPitchRotation));
	hpmat2x2 betweenStartStop = glm::inverse(hpmat2x2(startPitch, stopPitch));

	if (!lists.empty()) {
		lists.resize(0); //assure that no wrong points are included!
	}

	lists.push_back(new std::vector<MatingPoint>());
	PointPosition lastPosition = PointPosition::IN_ANGULAR_PITCH;

	std::vector<PointPosition> positionList = std::vector<PointPosition>();

	for(MatingPointSelector::iterator it = this->begin(), end = this->end(); it != end; ++it) {
		if(it->error != ErrorCode::NO_CUT_WITH_REFERENCE_RADIUS) {
			hpvec2 baryz = betweenStartStop * it->point;

			if(glm::all(glm::greaterThanEqual(baryz, hpvec2(0,0)))) {
				insertInList(*it, lastPosition, PointPosition::IN_ANGULAR_PITCH, lists, positionList);
				lastPosition = PointPosition::IN_ANGULAR_PITCH;

			} else if (baryz.x > 0.0f && baryz.y < 0.0f) {
				//startPitch still positive, stopPitch negative => point lies infront of start of tooth
				insertInList(*it, lastPosition, PointPosition::BEHIND_ANGULAR_PITCH, lists, positionList);
				lastPosition = PointPosition::BEHIND_ANGULAR_PITCH;

			} else if (baryz.x < 0.0f && baryz.y > 0.0f) {
				//startPitch negative, stopPitch still positive => point lies behind end of tooth
				insertInList(*it, lastPosition, PointPosition::INFRONT_OF_ANGULAR_PITCH, lists, positionList);
				lastPosition = PointPosition::INFRONT_OF_ANGULAR_PITCH;

			} //else: point lies nearly opposite tooth
		} //else: point on original gear has no equivalent on mating gear => do nothing with that point!
	}
	positionList.push_back(lastPosition); //as positionList is filled only when new one list ends, the last list needs its position
	assert(lists.size() == positionList.size());

	// Now all points of all lists are compared and only points, which are not covered by any of the rectangles
	// which are constructed by two other points with their forbidden area are chosen for the mating gear.
	// First mark all points as not covered.
	std::vector<MatingPoint> chosenPoints = std::vector<MatingPoint>();
	for(std::vector< std::vector<MatingPoint>* >::iterator listIt = lists.begin(), listEnd = lists.end(); listIt != listEnd; ++listIt) {
		for(std::vector<MatingPoint>::iterator it = (*listIt)->begin(), end = (*listIt)->end(); it != end; ++it) {
			it->isCovered = false;
		}
	}
	// Find all covered points
	// This loop is quite expensive but it is quite complicated to reduce the cicles, as no constraint is known for the points.
	for(std::vector< std::vector<MatingPoint>* >::iterator listIt = lists.begin(), listEnd = lists.end(); listIt != listEnd; ++listIt) {
		for(std::vector<MatingPoint>::iterator it = (*listIt)->begin(), end = --((*listIt)->end()); it != end; ++it) {

			for(std::vector< std::vector<MatingPoint>* >::iterator list2It = lists.begin(), list2End = lists.end(); list2It != list2End; ++list2It) {
				for(std::vector<MatingPoint>::iterator it2 = (*list2It)->begin(), end2 = (*list2It)->end(); it2 != end2; ++it2) {
					if(it != it2 && (it+1) != it2) {//don't compare points itself!
						if(matingPointIsCovered(*it2, *it, *(it+1))) {
							it2->isCovered = true;
						}
					}
				}
			}

		}
	}
	// ???
	for(hpuint i = 0; i < positionList.size(); ++i) {
		if(positionList[i] == PointPosition::IN_ANGULAR_PITCH) {
			for(std::vector<MatingPoint>::iterator it = lists[i]->begin(), end = lists[i]->end(); it != end; ++it) {
				if(!it->isCovered) {
					chosenPoints.push_back(*it);
				}
			}
		}
	}
	return new std::vector<MatingPoint>(chosenPoints);
}

bool MatingPointSelector::intersectLines(hpvec2& intersection, hpvec2 lineAStart, hpvec2 lineAEnd, hpvec2 lineBStart, hpvec2 lineBEnd) {
	hpvec2 x = lineAStart - lineAEnd;
	hpvec2 y = lineBEnd - lineBStart;
	hpvec2 z = lineAStart - lineBStart;
	hpmat2x2 matrix = hpmat2x2(x, y);
	if(glm::determinant(matrix) != 0) {
		hpmat2x2 invMatrix = glm::inverse(matrix);
		hpvec2 t = invMatrix * z;
		if (0 <= t.x && 0 <= t.y && t.x <= 1 && t.y <= 1) {
			intersection = lineBStart + t.y * y;
			return true;
		}
	}
	return false;
}

//TODO: is the epsilon value e a suitable one? Maybe it catches too much or too less?
bool MatingPointSelector::isPointInTriangle(hpvec2 point, hpvec2 a, hpvec2 b, hpvec2 c) {
	hpreal e = 0.01f;
	hpvec2 start = a - b;
	hpvec2 stop = c - b;
	hpmat2x2 betweenStartStop = glm::inverse(hpmat2x2(start, stop));
	hpvec2 baryz = betweenStartStop * (point - b);
	if(glm::all(glm::greaterThan(baryz, hpvec2(e,e))) && glm::all(glm::lessThan(baryz, hpvec2(1.0f - e, 1.0f - e))) && (baryz.x + baryz.y < 1.0f - 2 * e)) {
		return true;
	}
	return false;
}

bool MatingPointSelector::matingPointIsCovered(MatingPoint candidate, MatingPoint a, MatingPoint b) {
	// in each case two tests to make!
	hpvec2 intersection;
	if(intersectLines(intersection, a.point, a.forbiddenAreaEndPoint, b.point, b.forbiddenAreaEndPoint)) {
		return isPointInTriangle(candidate.point, a.point, intersection, b.point)
			|| isPointInTriangle(candidate.point, a.forbiddenAreaEndPoint, intersection, b.forbiddenAreaEndPoint);
	} else {
		return isPointInTriangle(candidate.point, b.forbiddenAreaEndPoint, a.point, a.forbiddenAreaEndPoint)
			|| isPointInTriangle(candidate.point, b.point, a.point, b.forbiddenAreaEndPoint);
		}
}

void MatingPointSelector::insertInList(
	MatingPoint matingPoint,
	PointPosition lastPosition,
	PointPosition currentPosition,
	std::vector< std::vector<MatingPoint>* >& lists,
	std::vector<PointPosition>& positionList) {

	if(lastPosition != currentPosition && !lists.back()->empty()) {
		MatingPoint lastMatingPoint = lists.back()->back();
		lists.back()->push_back(matingPoint);
		turnPointsOfList(lists.back(), lastPosition);
		positionList.push_back(lastPosition);
		lists.push_back(new std::vector<MatingPoint>());
		lists.back()->push_back(lastMatingPoint);
	}
	lists.back()->push_back(matingPoint);
}

void MatingPointSelector::turnPointsOfList(std::vector<MatingPoint>* list, PointPosition positionOfListPoints) {
	if(positionOfListPoints == PointPosition::IN_ANGULAR_PITCH) {
		return;
	} else {
		hpreal rotation = 0.0f;
		if(positionOfListPoints == PointPosition::INFRONT_OF_ANGULAR_PITCH) {
			rotation = -m_angularPitchRotation;
		} else { //positionOfListsPoints == PointPosition::BEHIND_ANGULAR_PITCH
			rotation = m_angularPitchRotation;
		}
		for(std::vector<MatingPoint>::iterator it = list->begin(), end = list->end(); it != end; ++it) {
			it->rotate(rotation);
		}
	}
}
