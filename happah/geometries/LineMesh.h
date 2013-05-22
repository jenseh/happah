#pragma once

#include <memory>

#include "happah/geometries/Mesh.h"
#include "happah/geometries/Segment.h"

using namespace std;

template<typename T>
class LineMesh : public Mesh<T> {//TODO: rename LineMesh to SegmentMesh?
public:
	template<typename S>
	class SegmentEndpointsIterator : public iterator<random_access_iterator_tag, const SegmentEndpoints<S> > {
		protected:
    		hpuint m_iIndex;   
			LineMesh<T>* m_pMesh;

		public:

    		/*typedef random_access_iterator_tag iterator_category;
    		typedef
        		typename iterator<random_access_iterator_tag, SegmentEndpoints<S>>::value_type
        		value_type;
    		typedef
        		typename iterator<random_access_iterator_tag, SegmentEndpoints<S>>::difference_type
        		difference_type;
    		typedef
        		typename iterator<random_access_iterator_tag, SegmentEndpoints<S>>::reference
        		reference;
    		typedef
        		typename iterator<random_access_iterator_tag, SegmentEndpoints<S>>::pointer
        		pointer;*/
   
    SegmentEndpointsIterator() : m_iIndex(0), m_pMesh(NULL) {}

	SegmentEndpointsIterator(hpuint iIndex, LineMesh<T>* pMesh) : m_iIndex(iIndex), m_pMesh(pMesh) {}
   
    SegmentEndpointsIterator(const SegmentEndpointsIterator<S>& r) : m_iIndex(r.m_iIndex), m_pMesh(r.m_pMesh) {}
   
    SegmentEndpointsIterator& operator=(const SegmentEndpointsIterator<S>& r)
        { m_iIndex = r.m_iIndex; m_pMesh = r.m_pMesh; return *this; }

    SegmentEndpointsIterator& operator++()  // PREFIX
        { m_iIndex += 2; return *this; }
    SegmentEndpointsIterator& operator--()  // PREFIX
        { m_iIndex -= 2; return *this; }
    SegmentEndpointsIterator operator++(int)  // POSTFIX
        { return SegmentEndpointsIterator(m_iIndex + 2, m_pMesh); }
    SegmentEndpointsIterator operator--(int)  // POSTFIX
        { return SegmentEndpointsIterator(m_iIndex - 2, m_pMesh); }
    SegmentEndpointsIterator operator+(const difference_type& n) const
        { return SegmentEndpointsIterator(m_iIndex + 2 * n, m_pMesh); }
    SegmentEndpointsIterator& operator+=(const difference_type& n)
        { m_iIndex += 2 * n; return *this; }
    SegmentEndpointsIterator operator-(const difference_type& n) const
        { return SegmentEndpointsIterator(m_iIndex - 2 * n, m_pMesh); }
    SegmentEndpointsIterator& operator-=(const difference_type& n) { m_iIndex -= 2 * n; return *this; }

    reference operator*() const { 
		vector<S>* pVerticesAndNormals = m_pMesh->getVerticesAndNormals();
		vector<hpuint>* pIndices = m_pMesh->getIndices();
		return SegmentEndpoints<S>(pVerticesAndNormals[2 * pIndices[iIndex]],
								   pVerticesAndNormals[2 * pIndices[iIndex + 1]]); 
	}

    pointer operator->() const { return m_pData; }
    reference operator[](const difference_type& n) const { return m_pData[n]; }
	};

	LineMesh(vector<T>* verticesAndNormals, vector<hpuint>* indices);
	~LineMesh();

	SegmentEndpointsIterator<T> getBeginningOfSegmentEndpointsIteration();
	SegmentEndpointsIterator<T> getEndOfSegmentEndpointsIteration();

};
typedef LineMesh<hpvec2> LineMesh2D;
typedef shared_ptr<LineMesh2D> LineMesh2D_ptr;
typedef LineMesh<hpvec3> LineMesh3D;
typedef shared_ptr<LineMesh3D> LineMesh3D_ptr;

