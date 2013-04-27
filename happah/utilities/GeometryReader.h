#ifndef GEOMETRY_READER_H
#define GEOMETRY_READER_H

#include <istream>

#include "happah/geometries/Mesh.h"

using namespace std;

class GeometryReader {

public:
	static void readWavefrontObj(istream& stream, TriangleMesh*& triangleMesh);

};

#endif //GEOMETRY_READER_H
