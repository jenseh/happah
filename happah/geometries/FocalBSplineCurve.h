/*
 * Copyright (c) 2012, 2013  See the COPYRIGHT-HOLDERS file in the top-level
 * directory of this distribution and at http://github.com/happah-graphics/happah.
 *
 * This file is part of Happah. It is subject to the license terms in the LICENSE
 * file found in the top-level directory of this distribution and at
 * http://github.com/happah-graphics/happah. No part of Happah, including this
 * file, may be copied, modified, propagated, or distributed except according to
 * the terms contained in the LICENSE file.
 *
*/

#ifndef FOCALBSPLINECURVE_H_
#define FOCALBSPLINECURVE_H_

#include <vector>
#include "happah/HappahTypes.h"

using namespace std;

class FocalBSplineCurve {
public:
	FocalBSplineCurve();
	FocalBSplineCurve(vector<hpreal>* knots,vector<hpvec3>* controlPoints);
	void insertKnot(hpreal knot);
	hpvec3 evaluate(hpreal);
	virtual ~FocalBSplineCurve();

private:
	hpvec3 findNewPoint(hpvec3 pim1,hpvec3 pi,hpreal ratio);
	vector<hpreal>* m_knots;
	vector<hpvec3>* m_controlPoints;
	int       m_degree;
};

#endif /* FOCALBSPLINECURVE_H_ */
