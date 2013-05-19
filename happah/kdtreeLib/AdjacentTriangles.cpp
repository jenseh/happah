#include <algorithm>
#include <iostream>
#include<iterator>

#include "AdjacentTriangles.h"
//#define	ADJ_DEBUG
//#define ADJ_DEBUG_SAME


int AdjacentTriangles::getSameIndicesWithoutCurrent(vector<hpuint>& vertex_1, vector<hpuint>& vertex_2, hpuint currentIndex ) const {
	vector<hpuint> sameIndices;
	std::sort( vertex_1.begin(), vertex_1.end() );
	std::sort( vertex_2.begin(), vertex_2.end() );
	std::set_intersection( vertex_1.begin(), vertex_1.end(), vertex_2.begin(), vertex_2.end(), std::back_inserter( sameIndices) );
#ifdef ADJ_DEBUG_SAME
	std::cout << "Index " << currentIndex << ' ' << vertex_1.size() << ' ' << vertex_2.size() << std::endl;
	for( int i = 0; i < sameIndices.size(); i++ ) {
		std::cout << sameIndices[i] << std::endl;
	}
#endif
	if( sameIndices.size() == 2 )
		return sameIndices[ 0 ] == currentIndex ? sameIndices[ 1 ] : sameIndices[ 0 ];
	return -1;
}

AdjacentTriangles::AdjacentTriangles(const TriangleMesh3D_ptr triangleMesh) {

	vector<hpuint>* indices = triangleMesh->getIndices();
	hpuint verticesCount = triangleMesh->getVerticesAndNormals()->size() / 2;
	hpuint indicesCount = indices->size() / 3;
#ifdef ADJ_DEBUG
	std::cout << "Vertices: " << verticesCount << " Indices: " << indicesCount << std::endl;
#endif
	vector<hpuint>* verticesInIndices = new vector<hpuint>[verticesCount];
	m_adjacentTriangles = new Adjacents[ indicesCount ];
	m_inidicesCount = indicesCount;

	for( hpuint index = 0; index < indicesCount; ++index) {
		hpuint vertex;
#ifdef ADJ_DEBUG
		std::cout << "Index: " << index << std::endl;
#endif
		vertex = indices->at( index * 3 );
#ifdef ADJ_DEBUG
		std::cout << "\tVertex: " << vertex << std::endl;
#endif
		verticesInIndices[ vertex ].push_back( index );

		vertex = indices->at( index * 3 + 1 );
#ifdef ADJ_DEBUG
		std::cout << "\tVertex: " << vertex << std::endl;
#endif
		verticesInIndices[ vertex ].push_back( index );

		vertex = indices->at( index * 3 + 2 );
#ifdef ADJ_DEBUG
		std::cout << "\tVertex: " << vertex << std::endl;
#endif
		verticesInIndices[ vertex ].push_back( index );
	}
#ifdef ADJ_DEBUG
	std::cout << "Array:" << std::endl;
	for( hpuint i = 0; i < verticesCount; ++i ) {
		std::cout << "Vertex: " << i << std::endl;
		for(int j = 0; j < verticesInIndices[ i ].size(); j++ ) {
			std::cout << verticesInIndices[ i ].at( j ) << ' ';
		}
		std::cout << std::endl;
	}
#endif
	for( hpuint index = 0; index < indicesCount; ++index) {
		hpuint vertex_0 = indices->at( index * 3  );
		hpuint vertex_1 = indices->at( index * 3 + 1 );
		hpuint vertex_2 = indices->at( index * 3 + 2 );

		m_adjacentTriangles[ index ].adjacentsCount = 0;
		m_adjacentTriangles[ index ].tiangleIndex[ 0 ] = getSameIndicesWithoutCurrent( verticesInIndices[ vertex_0 ], verticesInIndices[ vertex_1 ], index );
		m_adjacentTriangles[ index ].tiangleIndex[ 1 ] = getSameIndicesWithoutCurrent( verticesInIndices[ vertex_0 ], verticesInIndices[ vertex_2 ], index );
		m_adjacentTriangles[ index ].tiangleIndex[ 2 ] = getSameIndicesWithoutCurrent( verticesInIndices[ vertex_1 ], verticesInIndices[ vertex_2 ], index );
		std::sort( std::begin( m_adjacentTriangles[ index ].tiangleIndex ), std::end( m_adjacentTriangles[ index ].tiangleIndex ), std::greater<int>() );
#ifdef ADJ_DEBUG
	std::cout << "Triangle: " << index << std::endl;
#endif
		for( hpuint i = 0; i < 3; ++i ) {

			if( m_adjacentTriangles[ index ].tiangleIndex[ i ] >= 0 ) {
				m_adjacentTriangles[ index ].adjacentsCount += 1;
			}
		}
#ifdef ADJ_DEBUG
		std::cout << "\tAdjacents count: " << m_adjacentTriangles[ index ].adjacentsCount	<< std::endl;
		for( int i = 0; i < m_adjacentTriangles[ index ].adjacentsCount; i++ ) {
			std::cout << "\tAdjacent: " << m_adjacentTriangles[ index ].tiangleIndex[ i ] << std::endl;
		}
#endif
	}
	delete[] verticesInIndices;
}


AdjacentTriangles::~AdjacentTriangles() {
	delete[] m_adjacentTriangles;
}


int AdjacentTriangles::getAdjacentTrianglesIndices(const int triangleIndex, AdjacentTriangles::Adjacents& adjacents) const {
	if( triangleIndex < 0 || triangleIndex > m_inidicesCount ) {
		return -1;
	}
	adjacents = m_adjacentTriangles[ triangleIndex ];
	return adjacents.adjacentsCount;
}
