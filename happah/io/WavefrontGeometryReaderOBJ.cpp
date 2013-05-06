#include <sstream>

#include "happah/io/WavefrontGeometryReaderOBJ.h"

const string WavefrontGeometryReaderOBJ::OBJ_VERTEX_TOKEN = "v ";
const string WavefrontGeometryReaderOBJ::OBJ_NORMAL_TOKEN = "vn";
const string WavefrontGeometryReaderOBJ::OBJ_FACE_TOKEN = "f ";

void WavefrontGeometryReaderOBJ::read(istream& stream, TriangleMesh3D*& triangleMesh) {
	triangleMesh = NULL;

	vector<hpvec3> vertices;
	vector<hpvec3> normals;
	vector<hpuint> indices;
	string lineToParse;
	hpvec3 tmpVector;
	int lineCount = 0;

	while( !stream.eof() )
	{
		getline( stream, lineToParse );
		lineCount++;

		if( lineToParse.substr(0, 2) == OBJ_VERTEX_TOKEN ) {
			istringstream stream( lineToParse.substr(2) );
			stream >> tmpVector.x >> tmpVector.y >> tmpVector.z;
			if( stream.fail() ) {
				throw ParseException( VERTEX_PARSE_ERROR, lineCount );
			}
			vertices.push_back( tmpVector );
		} else
		if( lineToParse.substr(0, 2) == OBJ_NORMAL_TOKEN ) {
			istringstream stream( lineToParse.substr(2) );
			stream >> tmpVector.x >> tmpVector.y >> tmpVector.z;
			if( stream.fail() ) {
				throw ParseException( NORMAL_PARSE_ERROR, lineCount );
			}
			normals.push_back( tmpVector );
		} else
		if( lineToParse.substr(0, 2) == OBJ_FACE_TOKEN ) {
			istringstream stream( lineToParse.substr(2) );
			hpuint index;
			for( int i = 0; i < OBJ_TRIANGLE_INDICES; i++ ) {
				stream >> index;
				if( stream.fail() ) {
					throw ParseException( FACE_PARSE_ERROR, lineCount );
				}
				indices.push_back(index - 1);
				stream.ignore(32,' ');
			}
		}
	}


	if( vertices.size() && vertices.size() == normals.size() ) {
		vector<hpvec3>* verticesAndNormals_ptr = new vector<hpvec3>;
		for( hpuint i = 0; i < vertices.size(); i++ ) {
			verticesAndNormals_ptr->push_back( vertices.at(i) );
			verticesAndNormals_ptr->push_back( normals.at(i) );
		}
		vector<hpuint>* indices_ptr = new vector<hpuint>( indices );
		triangleMesh = new TriangleMesh3D( verticesAndNormals_ptr, indices_ptr );
	} else
		throw ParseException( NOT_VALID_MESH, 0 );
}
