#include "happah/geometries/gears/matinggear/MatingPointSelector.h"

#include "glm/glm.hpp"
#include "glm/gtx/rotate_vector.hpp"

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
		cerr << "MatingPointSelector::constructed with " << m_matingNTeeth << " and " << m_turnDirection  << "and angularPitch = " << m_angularPitchRotation << endl;
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

std::vector<MatingPoint>* MatingPointSelector::chooseSuitableMatingPointsForGear() {
	//every point has to be inside one angular pitch of the gear!
	hpvec2 startPitch = glm::normalize(getFirstNoneErrorMatingPoint().point);
	hpvec2 stopPitch = glm::normalize(glm::rotate(startPitch, m_angularPitchRotation));
	hpmat2x2 betweenStartStop = glm::inverse(hpmat2x2(startPitch, stopPitch));

	std::vector< std::vector<MatingPoint>* > lists = std::vector< std::vector<MatingPoint>* >();
	lists.push_back(new std::vector<MatingPoint>());
	PointPosition lastPosition = PointPosition::IN_ANGULAR_PITCH;

	std::vector<MatingPoint> chosenPoints = std::vector<MatingPoint>();
	for(MatingPointSelector::iterator it = this->begin(), end = this->end(); it != end; ++it) {
		if(it->error != ErrorCode::NO_CUT_WITH_REFERENCE_RADIUS) {
			hpvec2 baryz = betweenStartStop * it->point;

			if(glm::all(glm::greaterThanEqual(baryz, hpvec2(0,0)))) {
				chosenPoints.push_back(*it);
				cerr << "point lies correct" << endl;
				insertInList(*it, lastPosition, PointPosition::IN_ANGULAR_PITCH, lists);
				lastPosition = PointPosition::IN_ANGULAR_PITCH;

			} else if (baryz.x > 0.0f && baryz.y < 0.0f) {
				//startPitch still positive, stopPitch negative => point lies infront of start of tooth
				cerr << "point lies behind end of tooth" << endl;
				insertInList(*it, lastPosition, PointPosition::BEHIND_ANGULAR_PITCH, lists);
				lastPosition = PointPosition::BEHIND_ANGULAR_PITCH;

			} else if (baryz.x < 0.0f && baryz.y > 0.0f) {
				//startPitch negative, stopPitch still positive => point lies behind end of tooth
				cerr << "point lies infront of start of tooth" << endl;
				insertInList(*it, lastPosition, PointPosition::INFRONT_OF_ANGULAR_PITCH, lists);
				lastPosition = PointPosition::INFRONT_OF_ANGULAR_PITCH;

			} else {
				//point lies nearly opposite tooth
				cerr << "point is opposite! That's really bad :-/" << endl;
			}
		} //else: point on original gear has no equivalent on mating gear => do nothing with that point!
	}
	cerr << "lists have a size of: " << lists.size() << endl;
	return new std::vector<MatingPoint>(chosenPoints);
}

void MatingPointSelector::insertInList(
	MatingPoint matingPoint,
	PointPosition lastPosition,
	PointPosition currentPosition,
	std::vector< std::vector<MatingPoint>* >& lists) {

	if(lastPosition != currentPosition && !lists.back()->empty()) {
		MatingPoint lastMatingPoint = lists.back()->back();
		lists.back()->push_back(matingPoint);
		turnPointsOfList(lists.back(), lastPosition);
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

/*
#include "happah/geometries/gears/matinggear/MatingPointSelector.h"

#include "glm/glm.hpp"
#include "glm/gtx/rotate_vector.hpp"

MatingPointSelector::MatingPointSelector() : m_matingNTeeth(10), m_turnDirection(1.0f) {
}

MatingPointSelector::MatingPointSelector(hpuint matingNTeeth, bool matingTurnsClockwise)
  : m_list(std::list<MatingPoint>()),
	m_matingNTeeth(matingNTeeth),
	m_turnDirection((matingTurnsClockwise) ? 1.0f : -1.0f) {
}

MatingPointSelector::~MatingPointSelector() {
}

MatingPoint MatingPointSelector::getFirstNoneErrorMatingPoint() {
	std::list<MatingPoint>::iterator it = m_list.begin();
	while(it->error != ErrorCode::NO_ERROR && it != m_list.end())
		++it;
	return *it; //TODO: what can be returned if end was reached?
}

std::list<MatingPoint>* MatingPointSelector::getMatingPoints() {
	new std::list<MatingPoint>(m_list);
}

#include <iostream>
using namespace std;

std::vector<MatingPoint>* MatingPointSelector::chooseSuitableMatingPointsForGear() {
	//every point has to be inside one angular pitch of the gear!
	hpvec2 startPitch = glm::normalize(getFirstNoneErrorMatingPoint().point);
	hpvec2 stopPitch = glm::normalize(glm::rotate(startPitch, (360.0f * m_turnDirection) / m_matingNTeeth));
	hpmat2x2 betweenStartStop = glm::inverse(hpmat2x2(startPitch, stopPitch));

	std::vector<MatingPoint> chosenPoints = std::vector<hpvec2>();
	for(std::list<MatingPoint>::iterator it = m_list.begin(), end = m_list.end(); it != end; ++it) {
		if(it->error != ErrorCode::NO_CUT_WITH_REFERENCE_RADIUS) {
			hpvec2 baryz = betweenStartStop * it->point;
			if(glm::all(glm::greaterThanEqual(baryz, hpvec2(0,0)))) {
				chosenPoints.push_back(*it);
			} else if (baryz.x > 0.0f && baryz.y < 0.0f) { //point lies behind end of tooth
				cerr << "point lies behind end of tooth" << endl;
			} else if (baryz.x < 0.0f && baryz.y > 0.0f) { //point lies infront of start of tooth
				cerr << "point lies infront of start of tooth" << endl;
			} else {//point lies nearly opposite tooth
				cerr << "point is opposite! That's really bad :-/" << endl;
			}
		} //else: point on original gear has no equivalent on mating gear => do nothing with that point!
	}
	return new std::vector<MatingPoint>(chosenPoints);
}

void MatingPointSelector::push_back(MatingPoint matingPoint) {
	m_list.push_back(matingPoint);
}*/