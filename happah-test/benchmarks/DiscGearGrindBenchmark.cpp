#include "DiscGearGrindBenchmark.h"

DiscGearGrindBenchmark::DiscGearGrindBenchmark() {
	for( int i = 1; i < 21; i++) {
		InvoluteGear_ptr gear = InvoluteGear_ptr(new InvoluteGear);
		SurfaceOfRevolution_ptr disc = DiscGenerator::generateDiscFrom(*gear);
		TriangleMesh_ptr discMesh = disc->toTriangleMesh(20*i);
		TriangleMesh_ptr gearMesh = TriangleMesh_ptr(gear->toTriangleMesh());

		cout<<discMesh->toTriangles()->size();
		//cout<<"Rays:"<<rays->size()<<endl;
		clock_t start = clock();
		DiscGearGrind discGearGrind(disc, discMesh, SimpleGear_ptr(gear->toSimpleGear()), gearMesh);
		discGearGrind.runSimulation();
		clock_t end = clock();
		cout<<"; "<<(double)(end - start) / (double)CLOCKS_PER_SEC<<endl;
	}
}

DiscGearGrindBenchmark::~DiscGearGrindBenchmark() {
}

