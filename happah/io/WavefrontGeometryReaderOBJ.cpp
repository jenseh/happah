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
#include <sstream>

#include "happah/io/WavefrontGeometryReaderOBJ.h"

const string WavefrontGeometryReaderOBJ::OBJ_VERTEX_TOKEN = "v ";
const string WavefrontGeometryReaderOBJ::OBJ_NORMAL_TOKEN = "vn";
const string WavefrontGeometryReaderOBJ::OBJ_FACE_TOKEN = "f ";

void WavefrontGeometryReaderOBJ::read(istream& stream, TriangleMesh3D*& triangleMesh) {
	triangleMesh = NULL;

	std::auto_ptr< std::vector<hpvec3> > verticesAndNormals( new std::vector<hpvec3> );
	std::auto_ptr< std::vector<hpuint> > indices( new std::vector<hpuint> );
	hpuint verticesCount = 0;
	hpuint normalsCount = 0;
	hpuint lineCount = 0;
	const hpvec3 emptyVector = hpvec3( 0.0f );
	hpvec3 readedVector;
	string lineToParse;

	while( !stream.eof() )
	{
		getline( stream, lineToParse );
		lineCount++;

		if( lineToParse.substr(0, 2) == OBJ_VERTEX_TOKEN ) {
			istringstream stream( lineToParse.substr(2) );
			stream >> readedVector.x >> readedVector.y >> readedVector.z;
			if( stream.fail() ) {
				throw ParseException( VERTEX_PARSE_ERROR, lineCount );
			}
			if( verticesCount >= normalsCount) {
				verticesAndNormals->push_back( readedVector );
				verticesAndNormals->push_back( emptyVector );
			} else {
				verticesAndNormals->at( verticesCount * 2 ) = readedVector;
			}
			verticesCount += 1;
		} else
		if( lineToParse.substr(0, 2) == OBJ_NORMAL_TOKEN ) {
			istringstream stream( lineToParse.substr(2) );
			stream >> readedVector.x >> readedVector.y >> readedVector.z;
			if( stream.fail() ) {
				throw ParseException( NORMAL_PARSE_ERROR, lineCount );
			}
			if( normalsCount >= verticesCount) {
				verticesAndNormals->push_back( emptyVector);
				verticesAndNormals->push_back( readedVector );
			} else {
				verticesAndNormals->at( normalsCount * 2 + 1 ) = readedVector;
			}
			normalsCount += 1;
		} else
		if( lineToParse.substr(0, 2) == OBJ_FACE_TOKEN ) {
			istringstream stream( lineToParse.substr(2) );
			string faceTriplet;
			hpuint vertexIndex;
			hpuint textureIndex;
			hpuint normalIndex;
			for( int i = 0; i < OBJ_TRIANGLE_INDICES; ++i ) {
				stream >> faceTriplet;
				if( stream.fail() || parseFaceTriplet( faceTriplet, vertexIndex, textureIndex, normalIndex ) == false ) {
					throw ParseException( FACE_PARSE_ERROR, lineCount );
				}
				indices->push_back( vertexIndex - 1 );
			}
		}
	}


	if( verticesAndNormals->size() && indices->size() && verticesCount == normalsCount ) {
		triangleMesh = new TriangleMesh3D( verticesAndNormals.release(), indices.release() );
	} else
		throw ParseException( NOT_VALID_MESH, 0 );
}


bool WavefrontGeometryReaderOBJ::parseFaceTriplet(const string& faceTriplet, hpuint& vertex, hpuint& texture, hpuint& normal) {
	size_t firstSlash = faceTriplet.find( '/' );
	size_t lastSlash = faceTriplet.rfind( '/' );
	if( firstSlash == string::npos || firstSlash == lastSlash ) {
		return false;
	}
	vertex = atoi( faceTriplet.substr( 0, firstSlash ).c_str() );
	texture = atoi( faceTriplet.substr( firstSlash + 1, lastSlash - firstSlash - 1).c_str() );
	normal = atoi( faceTriplet.substr( lastSlash + 1, string::npos ).c_str() );

//	stringstream( faceTriplet.substr( 0, firstSlash ) ) >> vertex;
//	stringstream( faceTriplet.substr( firstSlash + 1, lastSlash - firstSlash ) ) >> texture;
//	stringstream( faceTriplet.substr( lastSlash + 1, string::npos ) ) >> normal;
	return true;
}
