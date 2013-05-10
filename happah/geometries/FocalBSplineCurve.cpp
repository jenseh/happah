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
#include <iostream>
#include "happah/geometries/FocalBSplineCurve.h"


FocalBSplineCurve::FocalBSplineCurve() {
	m_knots = new vector<hpreal>;
	m_controlPoints = new vector<hpvec3>;
	m_degree = 0;

}

FocalBSplineCurve::FocalBSplineCurve(vector<hpreal>* knots,vector<hpvec3>* controlPoints)
	:m_knots(knots),m_controlPoints(controlPoints){
	// Sanity check
	int a = m_knots->size()-1;
	int p = m_controlPoints->size()-1;
	m_degree = a-p-1;
	if (m_degree < 1)
		cout << "SOMETHING TERRIBLE HAPPENED" << endl;

}

FocalBSplineCurve::~FocalBSplineCurve() {
	// TODO Auto-generated destructor stub
}


void FocalBSplineCurve::insertKnot(hpreal knot){
	//TODO knot insertin algorithm
}

hpvec3 FocalBSplineCurve::evaluate(hpreal phi){
	hpvec3 result = hpvec3(0.0f,0.0f,0.0f);
	return result;
}
