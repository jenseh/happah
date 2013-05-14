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
#include "happah/HappahUtils.h";

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
	cout << "KNOTEN ALT: " << endl;
	for(int i = 0; i < m_knots->size(); i++){
		cout << m_knots->at(i) << endl;
	}
	cout << "KONTROLLPUNKTE ALT: " << endl;
	for(int i = 0; i < m_controlPoints->size(); i++){
			cout << m_controlPoints->at(i) << endl;
		}
	hpreal uk = 0.0f;
	int k = 0;
	vector<hpvec3>* newControlPoints = new vector<hpvec3>;
	cout << "Find Knots surrounding knot to insert;" << endl;
	for(int u = 0; u < m_knots->size()-1;u++){
		if(m_knots->at(u)<= knot && m_knots->at(u+1) > knot){
			uk = m_knots->at(u);
			k = u;
			cout<< " Inserting New Knot after Knot: " << u << endl;
		}
	}
	cout << "Find new control points between the affected ones" << endl;
	for(int v = k-m_degree;v < k ; v++){
		cout << "Starting to Calc Ratio: for knot number: "<< v << endl;
		int i=v+1;
		hpreal ratio = (knot-m_knots->at(i))/(m_knots->at(i+m_degree)-m_knots->at(i));
		cout << "Starting to Calc find new ControlPoint between Points: "<< v <<" "<<v+1<< endl;
		hpvec3 newPoint = findNewPoint(m_controlPoints->at(v),m_controlPoints->at(v+1),ratio);
		newControlPoints->push_back(newPoint);
	}
	cout << " delete obsolete points from controlPoint vektor; " << endl;
	for(int i = k-m_degree+1; i < k; i++){
		m_controlPoints->erase(m_controlPoints->begin()+i);
	}
	cout <<  " insert new ControlPoints " << endl;
	m_controlPoints->insert(m_controlPoints->begin()+k-m_degree+1,newControlPoints->begin(),newControlPoints->end());
	m_knots->insert(m_knots->begin()+k,knot);
	cout << "KNOTEN NEU: " << endl;
	for(int i = 0; i < m_knots->size(); i++){
		cout << m_knots->at(i) << endl;
	}
	cout << "KONTROLLPUNKTE NEU: " << endl;
	for(int i = 0; i < m_controlPoints->size(); i++){
			cout << m_controlPoints->at(i) << endl;
		}
}

hpvec3 FocalBSplineCurve::evaluate(hpreal phi){
	hpvec3 result = hpvec3(0.0f,0.0f,0.0f);
	return result;
}

hpvec3 FocalBSplineCurve::findNewPoint(hpvec3 pim1,hpvec3 pi,hpreal ratio){
	hpvec3 p1 = pim1;
	hpvec3 p2 = pi;
	hpreal phi = p2.x - p1.x;
	hpreal deltaPhi = (ratio)*phi;
	hpreal r1 = p1.z;
	hpreal r2 = p2.z;
	hpreal r1quad = r1*r1;
	hpreal r2quad = r2*r2;
	hpreal aquad = (r2quad + r1quad-(2*r2*r1*cos(phi)));
	hpreal a = sqrt(aquad);
	hpreal beta = acos((r2quad-r1quad-aquad)/(-2*r1*a));
	hpreal gamma = M_PI-deltaPhi-beta;
	hpreal radius = r1*sin(beta)/sin(gamma);

	return hpvec3(p1.x+deltaPhi,0,radius);
}


