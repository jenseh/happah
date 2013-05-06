#pragma once

#include <istream>

#include "happah/geometries/TriangleMesh.h"

using namespace std;

enum ErrCode {
	VERTEX_PARSE_ERROR,
	NORMAL_PARSE_ERROR,
	FACE_PARSE_ERROR,
	NOT_VALID_MESH
};

class WavefrontGeometryReaderOBJ {

public:
	class ParseException {
	public:
		ParseException(ErrCode errCode, int line): m_errCode(errCode), m_errLine(line) {}
		ErrCode getErrCode() { return m_errCode; }
		int getErrLine() { return m_errLine; }
	private:
		ErrCode m_errCode;
		int m_errLine;
	};

	static void read(istream& stream, TriangleMesh3D*& triangleMesh);

private:
	static const string OBJ_VERTEX_TOKEN;
	static const string OBJ_NORMAL_TOKEN;
	static const string OBJ_FACE_TOKEN;
	static const int OBJ_TRIANGLE_INDICES = 3;
};

