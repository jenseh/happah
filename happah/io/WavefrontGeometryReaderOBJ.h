#pragma once

#include <istream>

#include "happah/geometries/Mesh.h"

using namespace std;

class WavefrontGeometryReaderOBJ {

public:
	static void read(istream& stream, TriangleMesh*& triangleMesh);

};

