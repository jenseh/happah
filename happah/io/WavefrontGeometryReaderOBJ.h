/*
 * Copyright (c) 2012, 2013 See the COPYRIGHT-HOLDERS file in the top-level
 * directory of this distribution and at http://github.com/happah-graphics/happah.
 *
 * This file is part of Happah. It is subject to the license terms in the LICENSE
 * file found in the top-level directory of this distribution and at
 * http://github.com/happah-graphics/happah. No part of Happah, including this
 * file, may be copied, modified, propagated, or distributed except according to
 * the terms contained in the LICENSE file.
 *
*/
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
	static void write(ostream& stream, const TriangleMesh3D_ptr triangleMesh);

private:
	static const string OBJ_VERTEX_TOKEN;
	static const string OBJ_NORMAL_TOKEN;
	static const string OBJ_FACE_TOKEN;
	static const int OBJ_TRIANGLE_INDICES = 3;
	static bool parseFaceTriplet(const string& faceTriplet, hpuint& vertex, hpuint& texture, hpuint& normal);
};

