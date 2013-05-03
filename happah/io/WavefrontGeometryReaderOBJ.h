#pragma once

#include <istream>

#include "happah/geometries/TriangleMesh.h"

using namespace std;

class WavefrontGeometryReaderOBJ {

public:
	static void read(istream& stream, TriangleMesh*& triangleMesh);

};

