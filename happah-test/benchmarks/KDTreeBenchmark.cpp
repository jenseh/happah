/*
 * KDTreeBenchmark.cpp
 *
 *  Created on: 26.04.2013
 *      Author: jlabeit
 */

#include "KDTreeBenchmark.h"
#include <ctime>

KDTreeBenchmark::KDTreeBenchmark() {
	for( int i = 1; i < 31; i++) {
		InvoluteGear_ptr gear = InvoluteGear_ptr(new InvoluteGear);
		SurfaceOfRevolution_ptr disc = DiscGenerator::generateDiscFrom(*gear);
		vector<Triangle>* discTriangles = disc->toTriangleMesh(20*i)->toTriangles();
		//cout<<"Triangles count:"<< discTriangles->size()<<endl;
		cout<<discTriangles->size();
		//KDTree tree(discTriangles);
		vector<Ray>* rays = gear->toTriangleMesh()->toRays();
		//cout<<"Rays:"<<rays->size()<<endl;
		clock_t start = clock();
		for( size_t j = 0; j < rays->size(); j++) {
			//tree.intersectFirst(it, 0.18);
			for( vector<Triangle>::iterator it = discTriangles->begin(); it != discTriangles->end(); ++it) {
				rays->at(j).intersect(*it);
			}
		}
		clock_t end = clock();
		cout<<"; "<<(double)(end - start) / (double)rays->size() <<endl;
	}
}

KDTreeBenchmark::~KDTreeBenchmark() {
}

