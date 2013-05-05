#include <sstream>
#include <iostream>

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

		if( lineToParse.substr( 0, 2 ) == OBJ_VERTEX_TOKEN ) {
			try {
				istringstream stream( lineToParse.substr(2) );
				stream >> tmpVector.x >> tmpVector.y >> tmpVector.z;
				vertices.push_back( tmpVector );
			}
			catch( ios_base::failure ) {
				throw ParseException( VERTEX_PARSE_ERROR, lineCount );
			}

		} else
		if( lineToParse.substr( 0, 2 ) == OBJ_NORMAL_TOKEN ) {
			try {
				istringstream stream( lineToParse.substr(2) );
				stream >> tmpVector.x >> tmpVector.y >> tmpVector.z;
				normals.push_back( tmpVector );
			}
			catch( ios_base::failure ) {
				throw ParseException( NORMAL_PARSE_ERROR, lineCount );
			}
		} else
		if( lineToParse.substr( 0, 2 ) == OBJ_FACE_TOKEN ) {
			try {
				istringstream stream( lineToParse.substr(2) );
				hpuint index;
				for( int i = 0; i < OBJ_TRIANGLE_INDICES; i++ ) {
					stream >> index;
					indices.push_back(index - 1);
				}
			}
			catch( ios_base::failure ) {
				throw ParseException( FACE_PARSE_ERROR, lineCount );
			}
		}
	}

	if( vertices.size() == normals.size() ) {
		vector<hpvec3>* verticesAndNormals_ptr = new vector<hpvec3>;
		for( hpuint i = 0; i < vertices.size(); i++ ) {
			verticesAndNormals_ptr->push_back( vertices.at(i) );
			verticesAndNormals_ptr->push_back( normals.at(i) );
		}
		vector<hpuint>* indices_ptr = new vector<hpuint>( indices );
		cout << verticesAndNormals_ptr->size() << " " << indices_ptr->size() << endl;
		triangleMesh = new TriangleMesh3D( verticesAndNormals_ptr, indices_ptr );
	} else
		throw ParseException( NOT_VALID_MESH, 0 );
}
