#pragma once

#include <memory>

#include "happah/geometries/Mesh.h"
#include "happah/geometries/Segment.h"

using namespace std;

template<typename T>
class LineMesh : public Mesh<T> {//TODO: rename LineMesh to SegmentMesh?
public:

    /* Implements a RandomAccessIterator for SegmentEndpoints */
	template<typename S>
	class SegmentEndpointsIterator : public iterator<random_access_iterator_tag, const SegmentEndpoints<S> > {

		protected:
    			hpuint m_iIndex;            /* Current iteration index */
				LineMesh<T>* m_pMesh;       /* LineMesh structure */

		public:
            
    		typedef random_access_iterator_tag iterator_category;
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
        		pointer;
            
            /* Empty constructor */
    		SegmentEndpointsIterator() : m_iIndex(0), m_pMesh(NULL) {}

            /* Construct from an index value and a LineMesh instance */
			SegmentEndpointsIterator(hpuint iIndex, LineMesh<T>* pMesh) : m_iIndex(iIndex), m_pMesh(pMesh) {}
   
            /* Construct from another SegmentEndpointsIterator instance */
    		SegmentEndpointsIterator(const SegmentEndpointsIterator<S>& r) : m_iIndex(r.m_iIndex), m_pMesh(r.m_pMesh) {}
   
            /* = operator, set index and LineMesh instance from other SegmentEndpointsIterator instance */
    		SegmentEndpointsIterator& operator=(const SegmentEndpointsIterator<S>& r)
        		{ m_iIndex = r.m_iIndex; m_pMesh = r.m_pMesh; return *this; }

            /* Prefix increment */
    		SegmentEndpointsIterator& operator++()  
        		{ m_iIndex += 2; return *this; }

            /* Prefix decrement */
    		SegmentEndpointsIterator& operator--() 
        		{ m_iIndex -= 2; return *this; }

            /* Postfix increment */
    		SegmentEndpointsIterator operator++(int)  
        		{ return SegmentEndpointsIterator(m_iIndex + 2, m_pMesh); }
            
            /* Postfix decrement */
    		SegmentEndpointsIterator operator--(int)  
        		{ return SegmentEndpointsIterator(m_iIndex - 2, m_pMesh); }

            /* + operator, increment by n */
    		SegmentEndpointsIterator operator+(const difference_type& n) const
        		{ return SegmentEndpointsIterator(m_iIndex + 2 * n, m_pMesh); }

            /* += operator, increment current instance by n */
    		SegmentEndpointsIterator& operator+=(const difference_type& n)
        		{ m_iIndex += 2 * n; return *this; }

            /* - operator, decrement by n */
    		SegmentEndpointsIterator operator-(const difference_type& n) const
        		{ return SegmentEndpointsIterator(m_iIndex - 2 * n, m_pMesh); }
            
            /* -= operator, decrement current instance by n */
    		SegmentEndpointsIterator& operator-=(const difference_type& n) 
				{ m_iIndex -= 2 * n; return *this; }

            /* Access current SegmentEndpoints */
    		SegmentEndpoints<S> operator*() const { 
				return this[m_iIndex];
			}

    		//pointer operator->() const { return &this; }
            
            /* Random access a SegmentEndpoints instance at index n */
    		SegmentEndpoints<S> operator[](const difference_type& n) const { 
				vector<S>* pVerticesAndNormals = m_pMesh->getVerticesAndNormals();
				vector<hpuint>* pIndices = m_pMesh->getIndices();
				return SegmentEndpoints<S>(pVerticesAndNormals[2 * pIndices[n]],
								   pVerticesAndNormals[2 * pIndices[n + 1]]); 
			}
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

