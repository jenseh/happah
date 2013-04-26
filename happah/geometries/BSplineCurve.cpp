#include "happah/geometries/BSplineCurve.h"
#include "happah/HappahConstants.h"

#include <iostream>

template <class T> BSplineCurve<T>::BSplineCurve() {
	m_degree = 3;
	m_clamped = false;
	m_periodic = false;
	m_uniform = true;
	m_knots.push_back( 0.0f );
	for( int i = 1; i < m_degree; i++ ) {
		m_knots.push_back( i*(1.0f/((hpreal) m_degree)) );
	}
	m_knots.push_back( 1.0f );
}

template <class T> BSplineCurve<T>::BSplineCurve( const BSplineCurve<T>& other )
  : m_clamped(other.m_clamped),
	m_controlPoints(other.m_controlPoints),
	m_degree(other.m_degree),
	m_knots(other.m_knots),
	m_normalizedKnots(other.m_normalizedKnots),
	m_normalizedPoints(other.m_normalizedPoints),
	m_periodic(other.m_periodic),
	m_uniform(other.m_uniform) {
}

template <class T> BSplineCurve<T>::BSplineCurve( const std::vector<T>& controlPoints, const std::vector<hpreal>& knots )
  : m_controlPoints( controlPoints ),
	m_knots( knots ),
	m_normalizedKnots( knots ),
	m_normalizedPoints( controlPoints )
{
	m_degree = m_knots.size() - m_controlPoints.size() - 1;
	m_periodic = false;
	m_uniform = false;
	m_clamped = false;
	if( m_degree <= 0 ) {
		std::cerr << "Number of control points is too big for given knots!" << std::endl;
	}
	else {
		calculateNormalization();
	}
}

template <class T> BSplineCurve<T>::~BSplineCurve() {
}

template <class T> void BSplineCurve<T>::addControlPoint( T newPoint ) {
	m_controlPoints.push_back(newPoint);

	if( m_uniform ) {
		hpreal scaleFact = 1.0f - 1.0f/(m_knots.size());
		m_knots[0] = 0.0f;
		for( unsigned int i = 1; i < m_knots.size(); i++ ) {
			m_knots[i] *= scaleFact;
		}
		m_knots.push_back( 1.0f );
	/*	// non-normalized version, not tested!
		hpreal scaleFact = (m_knots.back() - m_knots.front()) / m_knots.size();
		m_knots.push_back( m_knots.back() );
		for( unsigned int i = 1; i < m_knots.size()-1; i++ ) {
			 m_knots[i] = m_knots[0] + scaleFact*i;
		}
	*/
	}
	else {
		hpreal stepSize = ( m_knots.back() - m_knots.front() ) / (m_knots.size() - 1);
		m_knots.push_back( m_knots.back() + stepSize );
	}

	calculateNormalization();

	getKnots();
}

template <class T> void BSplineCurve<T>::addControlPoint( T newPoint, hpreal distanceFromLast ) {
	if( m_uniform ) {
		this->addControlPoint( newPoint );
	}
	else {
		m_controlPoints.push_back(newPoint);
		if( distanceFromLast < 0 ) distanceFromLast = 0.0f;
		m_knots.push_back( m_knots.back() + distanceFromLast );
		calculateNormalization();
	}
}

template <class T> void BSplineCurve<T>::calculateNormalization() {
	m_normalizedKnots = m_knots;
	m_normalizedPoints = m_controlPoints;
	if(m_periodic && m_controlPoints.size() >= m_degree) {
		// Calculate circular control points array
		int sizePoints = m_controlPoints.size()+m_degree;
		m_normalizedPoints.resize(sizePoints);
		std::copy(m_controlPoints.begin(), m_controlPoints.begin()+m_degree, m_normalizedPoints.end()-m_degree);
		// Resize (& unify) knots array
		int sizeKnots = m_knots.size()+m_degree;
		m_normalizedKnots.resize(sizeKnots);
		for( int i = 0; i < sizeKnots; i++ ) {
			m_normalizedKnots[i] = i*( 1.0f/((hpreal) sizeKnots-1) );
		}
	}
	else if(m_clamped && m_normalizedKnots.size() > 2*(m_degree+1)) {
		for( int i = 0; i < m_degree; i++ ) {
			m_normalizedKnots[i] = m_normalizedKnots[m_degree];
			*(m_normalizedKnots.rbegin()+i) = *(m_normalizedKnots.rbegin()+m_degree);
		}
//		for( int i = 0; i < m_normalizedKnots.size() - 2*m_degree; i++ ) {
//			m_normalizedKnots[i+m_degree] = i*( 1.0f/((hpreal) m_normalizedKnots.size() - 2*m_degree) );
//		}
	}
	else if(!m_clamped && m_uniform) {
		hpreal fract = 1.0f/((hpreal) m_normalizedKnots.size() - 1);
		for( int i = 0; i < m_normalizedKnots.size(); i++ ) {
			m_normalizedKnots[i] = i*fract;
		}
	}
}

template <class T> bool BSplineCurve<T>::check( bool debugOutput ) const {
	m_controlPoints.size() == m_degree + 1; // Bezier-curve property per segment
	if( debugOutput ) {
		std::cout << "BSplineCurve checking routine\n";
		std::cout << "degree:\t " << m_degree << " \t control points:\t " << m_controlPoints.size() << std::endl;
		std::cout << "knots :\t " << m_knots.size() << " (" << m_knots.size()-1 << " knot spans)" << std::endl;
		std::cout << "number of segments (degree & coefficients):\t " << m_controlPoints.size() - m_degree << std::endl;
		std::cout << "number of segments (breakpoints / knots)  :\t " << m_knots.size() -1 << std::endl;
		std::cout << "valid configuration:\t " << ( m_controlPoints.size() == m_knots.size() - 1 - m_degree ) << std::endl << std::endl;
	}
	if( m_controlPoints.size() != m_knots.size() - 1 - m_degree ) {
		return false;
	}
	for( int i = 1; i < m_knots.size(); i++ ) {
		if( m_knots[i-1] > m_knots[i] ) {
			if( debugOutput ) {
				std::cout << "Non monotone knot vector at " << i-1 << "!" << std::endl;
			}
			return false;
		}
	}
	return true;
}

template <class T> void BSplineCurve<T>::getBoundingBox( hpvec2* min, hpvec2* max ) const {
	if( m_controlPoints.size() > 0 ) {
		// TODO: Use iterator
		min->x = m_controlPoints[0].x;
		max->x = m_controlPoints[0].x;
		min->y = m_controlPoints[0].y;
		max->y = m_controlPoints[0].y;
		for( unsigned int i = 1; i < m_controlPoints.size(); i++ ) {
			if( m_controlPoints[i].x < min->x )
				min->x = m_controlPoints[i].x;
			if( m_controlPoints[i].x > max->x )
				max->x = m_controlPoints[i].x;
			if( m_controlPoints[i].y < min->y )
				min->y = m_controlPoints[i].y;
			if( m_controlPoints[i].y > max->y )
				max->y = m_controlPoints[i].y;
		}
	}
}

template <class T> bool BSplineCurve<T>::getClamped() const {
	return m_clamped;
}

template <class T> T BSplineCurve<T>::getControlPoint( unsigned int index ) const {
	if( index < m_controlPoints.size() ) {
		return m_controlPoints[index];
	}
	return T(0.0f);
}

template <class T> std::vector<T> BSplineCurve<T>::getControlPoints() const {
	return std::vector<T>(m_controlPoints);
}

template <class T> std::vector<hpreal> BSplineCurve<T>::getKnots() const {
	return std::vector<hpreal>(m_knots);
}

template <class T> int BSplineCurve<T>::getDegree() const {
	return m_degree;
}

// TODO: better solution than template specialization would be overloading ?
template <> void BSplineCurve<hpvec2>::getIntersectionPointsWithRay( const Ray& ray, std::vector<hpvec2>& intersectionPoints ) const {
	intersectionPoints.resize(0); //ensure that no wrong values are returned

	for(hpuint i = 0; i < m_controlPoints.size() - 1; ++i) {
		hpvec2 startLine, endLine, intersectionPoint;
		startLine = hpvec2(m_controlPoints[i]);
		endLine = hpvec2(m_controlPoints[i + 1]);

		if(ray.intersect(startLine, endLine, intersectionPoint)) {
			if(m_degree == 1) {
				intersectionPoints.push_back(intersectionPoint);
			} else {
				std::vector<hpreal> knots(m_normalizedKnots);
				std::vector<hpvec2> points(m_normalizedPoints);

				int startKnotIndex = i - (m_degree - 1);
				if(startKnotIndex < m_degree)
					startKnotIndex = m_degree;
				int stopKnotIndex = i + m_degree + 1 + m_degree + 1;
				if(stopKnotIndex > points.size())
					stopKnotIndex = points.size();
				bool newPointsInserted = false;
				do {
					std::vector<hpreal> newKnots;
					for(hpuint j = startKnotIndex; j < stopKnotIndex; ++j) {
						if(knots[j + 1] - knots[j] > 0.05f) {
							hpreal newKnot = knots[j] + (knots[j + 1] - knots[j]) / 2.0f;
							newKnots.push_back(newKnot);
						}
					}
					stopKnotIndex += newKnots.size();
					newPointsInserted = !newKnots.empty();
					refine(knots, points, newKnots);
				} while(newPointsInserted);

				for(hpuint j = startKnotIndex; j < stopKnotIndex - m_degree - 1; ++j) {
					hpvec2 startLine, endLine, intersectionPoint;
					startLine = hpvec2(points[j]);
					endLine = hpvec2(points[j + 1]);
					if(ray.intersect(startLine, endLine, intersectionPoint)) {
						intersectionPoints.push_back(intersectionPoint);
					}
				}
			}
		}
	}
}

template <> void BSplineCurve<hpvec3>::getIntersectionPointsWithRay( const Ray& ray, std::vector<hpvec3>& intersectionPoints ) const {
	intersectionPoints.resize(0); //ensure that no wrong values are returned

	for(hpuint i = 0; i < m_controlPoints.size() - 1; ++i) {
		hpvec2 startLine, endLine, intersectionPoint;
		startLine = hpvec2(m_controlPoints[i]);
		endLine = hpvec2(m_controlPoints[i + 1]);

		if(ray.intersect(startLine, endLine, intersectionPoint)) {
			if(m_degree == 1) {
				intersectionPoints.push_back(hpvec3(intersectionPoint, 0.0f));
			} else {
				std::vector<hpreal> knots(m_normalizedKnots);
				std::vector<hpvec3> points(m_normalizedPoints);

				int startKnotIndex = i - (m_degree - 1);
				if(startKnotIndex < m_degree)
					startKnotIndex = m_degree;
				int stopKnotIndex = i + m_degree + 1 + m_degree + 1;
				if(stopKnotIndex > points.size())
					stopKnotIndex = points.size();
				bool newPointsInserted = false;
				do {
					std::vector<hpreal> newKnots;
					for(hpuint j = startKnotIndex; j < stopKnotIndex; ++j) {
						if(knots[j + 1] - knots[j] > 0.05f) {
							hpreal newKnot = knots[j] + (knots[j + 1] - knots[j]) / 2.0f;
							newKnots.push_back(newKnot);
						}
					}
					stopKnotIndex += newKnots.size();
					newPointsInserted = !newKnots.empty();
					refine(knots, points, newKnots);
				} while(newPointsInserted);

				for(hpuint j = startKnotIndex; j < stopKnotIndex - m_degree - 1; ++j) {
					hpvec2 startLine, endLine, intersectionPoint;
					startLine = hpvec2(points[j]);
					endLine = hpvec2(points[j + 1]);
					if(ray.intersect(startLine, endLine, intersectionPoint)) {
						intersectionPoints.push_back(hpvec3(intersectionPoint, 0.0f));
					}
				}
			}
		}
	}
}

template <class T> void BSplineCurve<T>::getIntersectionPointsWithRay( const Ray& ray, std::vector<T>& intersectionPoints ) const {
	intersectionPoints.resize(0); //ensure that no wrong values are returned

	for(hpuint i = 0; i < m_controlPoints.size() - 1; ++i) {
		hpvec2 startLine, endLine, intersectionPoint;
		startLine = hpvec2(m_controlPoints[i]);
		endLine = hpvec2(m_controlPoints[i + 1]);

		if(ray.intersect(startLine, endLine, intersectionPoint)) {
			if(m_degree == 1) {
//				intersectionPoints.push_back(intersectionPoint);
			} else {
				std::vector<hpreal> knots(m_normalizedKnots);
				std::vector<T> points(m_normalizedPoints);

				int startKnotIndex = i - (m_degree - 1);
				if(startKnotIndex < m_degree)
					startKnotIndex = m_degree;
				int stopKnotIndex = i + m_degree + 1 + m_degree + 1;
				if(stopKnotIndex > points.size())
					stopKnotIndex = points.size();
				bool newPointsInserted = false;
				do {
					std::vector<hpreal> newKnots;
					for(hpuint j = startKnotIndex; j < stopKnotIndex; ++j) {
						if(knots[j + 1] - knots[j] > 0.05f) {
							hpreal newKnot = knots[j] + (knots[j + 1] - knots[j]) / 2.0f;
							newKnots.push_back(newKnot);
						}
					}
					stopKnotIndex += newKnots.size();
					newPointsInserted = !newKnots.empty();
					refine(knots, points, newKnots);
				} while(newPointsInserted);

				for(hpuint j = startKnotIndex; j < stopKnotIndex - m_degree - 1; ++j) {
					hpvec2 startLine, endLine, intersectionPoint;
					startLine = hpvec2(points[j]);
					endLine = hpvec2(points[j + 1]);
					if(ray.intersect(startLine, endLine, intersectionPoint)) {
//						intersectionPoints.push_back(T(intersectionPoint));
					}
				}
			}
		}
	}
}

template <class T> hpuint BSplineCurve<T>::getMultiplicityOfKnotValue( hpreal knotValue ) const {
	hpuint count = 0;
	for (hpuint i = 0; i < m_normalizedKnots.size(); ++i) {
		if (m_normalizedKnots[i] == knotValue)
			++count;
	}
	return count;
}

template <class T> hpuint BSplineCurve<T>::getMultiplicity( hpuint knotIndex ) const {
	hpuint count = 1;
	for(hpuint i = knotIndex - 1; i >= 0 && m_normalizedKnots[i] == m_normalizedKnots[knotIndex]; --i)
		++count;
	for(hpuint i = knotIndex + 1; i < m_normalizedKnots.size() && m_normalizedKnots[knotIndex] == m_normalizedKnots[i]; ++i)
		++count;
	return count;
}

template <class T> unsigned int BSplineCurve<T>::getNumberOfControlPoints() const {
	return m_controlPoints.size();
}

template <class T> void BSplineCurve<T>::getParameterRange( hpreal& t_low, hpreal& t_high ) const {
	if( m_normalizedPoints.size() < m_degree + 1 ) return;

	t_low =  m_normalizedKnots[m_degree];
	t_high = m_normalizedKnots[m_normalizedPoints.size()];
}

template <class T> bool BSplineCurve<T>::getPeriodic() const {
	return m_periodic;
}

template <class T> bool BSplineCurve<T>::getUniform() const {
	return m_uniform;
}

template <class T> T BSplineCurve<T>::getDerivativeAt( hpreal t ) const {
	if( m_normalizedPoints.size() < m_degree + 1 ) {
		return T(0.0f);
	}
	if( t < m_normalizedKnots[m_degree] ) {
		return getDerivativeAt( m_normalizedKnots[m_degree] );
	}
	else if( t > m_normalizedKnots[m_normalizedPoints.size()] ) {
		return getDerivativeAt( m_normalizedKnots[m_normalizedPoints.size()] );
	}
	else {
		int l;
		for( int i = m_degree; i < m_normalizedKnots.size()-m_degree-1; i++ ) {
			if( m_normalizedKnots[i] <= t ) {
				l = i;
			}
		}

		std::vector<hpreal> knots (m_normalizedKnots.begin()+l-m_degree,m_normalizedKnots.begin()+l+m_degree+1);
		std::vector<T> output (m_normalizedPoints.begin()+l-m_degree,m_normalizedPoints.begin()+l+1);
		std::vector<T> old (output);

		for( int k = 1; k < m_degree; k++) {
			for( int i = k; i < m_degree+1; i++) {
				hpreal alpha = (t - knots[i])/(knots[i+m_degree+1-k]-knots[i]);
				output[i] = (1-alpha)*old[i-1] + alpha*old[i];
			}
			old = output;
		}
		return output[m_degree] - output[m_degree-1];
	}
}

template <class T> T BSplineCurve<T>::getValueAt( hpreal t ) const {
	if( m_normalizedPoints.size() < m_degree + 1 ) {
		return T(0.0f);
	}
	if( t < m_normalizedKnots[m_degree] ) {
		return getValueAt( m_normalizedKnots[m_degree] );
	}
	else if( t > m_normalizedKnots[m_normalizedPoints.size()] ) {
		return getValueAt( m_normalizedKnots[m_normalizedPoints.size()] );
	}
	else {
		int l;
		for( int i = m_degree; i < m_normalizedKnots.size()-m_degree-1; i++ ) {
			if( m_normalizedKnots[i] <= t ) {
				l = i;
			}
		}

		std::vector<hpreal> knots (m_normalizedKnots.begin()+l-m_degree,m_normalizedKnots.begin()+l+m_degree+1);
		std::vector<T> output (m_normalizedPoints.begin()+l-m_degree,m_normalizedPoints.begin()+l+1);
		std::vector<T> old (output);

		for( int k = 1; k < m_degree+1; k++) {
			for( int i = k; i < m_degree+1; i++) {
				hpreal alpha = (t - knots[i])/(knots[i+m_degree+1-k]-knots[i]);
				output[i] = (1-alpha)*old[i-1] + alpha*old[i];
			}
			old = output;
		}
		return output[m_degree];
	}
}

template <class T> bool BSplineCurve<T>::isClamped() const {
	return m_clamped;
}

template <class T> bool BSplineCurve<T>::isPeriodic() const {
	return m_periodic;
}

template <class T> bool BSplineCurve<T>::isUniform() const {
	return m_uniform;
}

template <class T> void BSplineCurve<T>::interpolateControlPoints() {
	// use control points as input points
	std::vector<T> inputPoints;
	inputPoints.swap(m_controlPoints);

	interpolatePoints( inputPoints );
}

// template <class T> void BSplineCurve<T>::interpolatePoints( std::vector<hpvec2>& points ) {
// 	std::vector<hpvec3> inputPoints( points.size() );
// 	std::vector<hpvec3>::iterator itInput = inputPoints.begin();
// 	for( std::vector<hpvec2>::iterator it = points.begin(), end = points.end(); it != end; ++it, ++itInput ) {
// 		*itInput = hpvec3( ( *it ).x, ( *it ).y, 0.0f );
// 	}
// 	interpolatePoints( inputPoints );
// }

template <class T> void BSplineCurve<T>::interpolatePoints( std::vector<T>& inputPoints ) {
	if( inputPoints.size() == 0 ) return;

	m_degree = 3;
	m_clamped = true;
	m_uniform = false;
	m_periodic = false;
	unsigned int m = inputPoints.size() - 1;

	m_knots.resize( inputPoints.size() + 2*m_degree ); // yields inputPoints.size() inner knots

	// equidistant parameterization
	for( unsigned int i = 0; i < m_knots.size(); i++ ) m_knots[i] = i-3;

	// clamping ends
	m_knots[0] = m_knots[1] = m_knots[2] = m_knots[3] = 0;
	m_knots.back() = m_knots[m_knots.size()-2] = m_knots[m_knots.size()-3] = m_knots[m_knots.size()-4];

	m_controlPoints.resize( m_knots.size() - m_degree - 1 ); // yields inputPoints.size()+2 control points

	// calculate tri-diagonal matrix
	std::vector<hpvec3> tridiagMatrix( m_controlPoints.size() );
	tridiagMatrix[0].x = 0;
	tridiagMatrix[0].y = 1;
	tridiagMatrix[0].z = 0;
	hpreal alpha_2 = (m_knots[4] - m_knots[2]) / (m_knots[5] - m_knots[2]);
	tridiagMatrix[1].x = -1;
	tridiagMatrix[1].y = 1 + alpha_2;
	tridiagMatrix[1].z = -alpha_2;
	for( unsigned int i = 2; i < tridiagMatrix.size()-2; i++ ) {
		hpreal alpha_i = (m_knots[i+2]-m_knots[i]) / (m_knots[i+3]-m_knots[i]);
		hpreal beta_i  = (m_knots[i+2]-m_knots[i+1]) / (m_knots[i+3]-m_knots[i+1]);
		hpreal gama_i  = (m_knots[i+2]-m_knots[i+1]) / (m_knots[i+4]-m_knots[i+1]);
		tridiagMatrix[i].x = (1-beta_i)*(1-alpha_i);
		tridiagMatrix[i].y = (1-beta_i)*alpha_i + beta_i*(1-gama_i);
		tridiagMatrix[i].z = beta_i*gama_i;
	}
	hpreal gamma_m = (m_knots[m+2] - m_knots[m+1]) / (m_knots[m+4] - m_knots[m+1]);
	tridiagMatrix[tridiagMatrix.size()-2].x = -1 + gamma_m;
	tridiagMatrix[tridiagMatrix.size()-2].y = -gamma_m + 2;
	tridiagMatrix[tridiagMatrix.size()-2].z = -1;
	tridiagMatrix.back().x = 0;
	tridiagMatrix.back().y = 1;
	tridiagMatrix.back().z = 0;

	// resize inputPoints & insert two zero-vectors (right side of matrix equation)
	auto it = inputPoints.begin() + 1;
	inputPoints.insert( it, T(0.0f) );
	inputPoints.push_back(inputPoints.back());
	*(inputPoints.end() - 2) = T(0.0f);

	// solve linear equation system
	std::vector<hpreal> v(tridiagMatrix.size()+1);
	v[0] = 0.0f;
	std::vector<T> y(tridiagMatrix.size()+1);
	y[0] = T(0.0f);
	for( unsigned int k = 0; k < tridiagMatrix.size(); k++ ) {
		hpreal z = 1.0f / (tridiagMatrix[k].y - v[k]*tridiagMatrix[k].x);
		v[k+1] = z*tridiagMatrix[k].z;
		y[k+1] = z*(inputPoints[k] - (tridiagMatrix[k].x)*y[k]);
	}
	m_controlPoints.back() = y[ tridiagMatrix.size() ];
	for( int k = m_controlPoints.size() - 2; k >= 0 ; k-- ) {
		m_controlPoints[k] = y[k+1] - v[k+1]*m_controlPoints[k+1];
	}

	calculateNormalization();
}

template <class T> void BSplineCurve<T>::removeControlPoint( unsigned int index ) {
	if( index < m_controlPoints.size() ) {
		m_controlPoints.erase( m_controlPoints.begin() + index );
		m_knots.resize( m_knots.size() - 1 );
		calculateNormalization();
	}
}

template <class T> void BSplineCurve<T>::removeControlPoints() {
	m_controlPoints.clear();
//	std::vector<T>().swap(m_controlPoints); // forces reallocation
	m_knots.resize(m_degree+1);
	for( int i = 1; i < m_degree; i++ ) {
		m_knots[i] = i*(1.0f/((hpreal) m_degree));
	}
	m_knots[0] = 0.0f;
	m_knots[m_degree] = 1.0f;
	calculateNormalization();
}

template <class T> void BSplineCurve<T>::resetKnotsToUniform() {
	int num = m_knots.size();
	if( num > 0 ) {
		m_knots[0] = 0.0f;
		m_knots[num-1] = 1.0f;
		for( int i = 1; i < num-1; i++ ) {
			m_knots[i] = i*( 1.0f/((hpreal) num-1) );
		}
	}
	calculateNormalization();
}

template <class T> void BSplineCurve<T>::setClamped( bool clamped ) {
	m_clamped = clamped;
	calculateNormalization();
}

template <class T> void BSplineCurve<T>::setControlPoint( unsigned int index, T newValue ) {
	if( index < m_controlPoints.size() ) {
		m_controlPoints[index] = newValue;
	}
	calculateNormalization();
}

template <class T> void BSplineCurve<T>::setControlPoints( const std::vector<T>& points ) {
	if( m_controlPoints.size() == points.size() )
		m_controlPoints = std::vector<T>( points );
	calculateNormalization();
}

template <class T> void BSplineCurve<T>::setDegree( unsigned int degree ) {
	if( degree < 1 ) return;
	m_knots.resize( m_controlPoints.size() + degree + 1 );
/*
	if( degree < m_degree && m_uniform ) {
		hpreal scaleFact = 1.0f / m_knots.back();
		for( int i = 0; i < m_knots.size(); i++ ) {
			m_knots[i] *= scaleFact;
		}
	}
	else */
	if( degree > m_degree ) {
/*		if( m_uniform ) {
			hpreal scaleFact = 1.0f/(m_knots.size() - 1);
			for( int i = 0; i < m_knots.size(); i++ ) {
				m_knots[i] = i*scaleFact;
			}
		}
		else {*/
			int oldBack = m_controlPoints.size() + m_degree;
			hpreal stepSize = ( m_knots.at(oldBack) - m_knots.front() ) / oldBack;
			for( int i = 1; i < degree - m_degree + 1; i++ ) {
				m_knots[oldBack+i] = m_knots.at(oldBack) + i*stepSize;
			}
		/*
		}
		hpreal scaleFact = 1.0f / ((hpreal) m_knots.size()-1 );
		int oldNum = m_controlPoints.size() + m_degree + 1;
		for( int i = 0; i < oldNum; i++ ) {
			m_knots[i] *= ((hpreal) oldNum-1)*scaleFact;
		}
		for( int i = oldNum; i < m_knots.size(); i++ ) {
			m_knots[i] = i*scaleFact;
		}
		*/
	}
	m_degree = degree;
	calculateNormalization();
}

template <class T> void BSplineCurve<T>::setUniform( bool uniform ) {
	m_uniform = uniform;
	if( m_uniform ) {
		hpreal scaleFact = 1.0f/(m_knots.size()-1);
		for( unsigned int i = 0; i < m_knots.size(); i++ ) {
			m_knots[i] = scaleFact*i;
		}
	/*	// not normalized version, not tested!
		hpreal scaleFact = (m_knots.back() - m_knots.front()) / (m_knots.size()-1);
		for( unsigned int i = 0; i < m_knots.size(); i++ ) {
			m_knots[i] = m_knots[0] + scaleFact*i;
		}
	*/
	}
	calculateNormalization();
}

template <class T> void BSplineCurve<T>::setPeriodic( bool periodic ) {
	m_periodic = periodic;
	calculateNormalization();
}

template <class T> LineMesh* BSplineCurve<T>::toLineMesh() {
	std::vector<T>* verticesAndNormals = new std::vector<T>;
	std::vector<hpuint>* indices = new std::vector<hpuint>;

	hpreal tBegin = 0.0f, tEnd = 0.0f;
	getParameterRange(tBegin, tEnd);
	if( tEnd - tBegin > EPSILON && m_degree > 1 ) {
		if( m_clamped && !m_periodic ) {
			std::vector<T> knots = knotRefinement( 0.05f );
			if( knots.size() > 1 ) {
				verticesAndNormals->resize(2*knots.size());
				indices->resize(2*(knots.size()-1));
				for( unsigned int i = 0; i < knots.size()-1; i++ ) {
					(*verticesAndNormals)[2*i] = knots[i];
					(*verticesAndNormals)[2*i+1] = glm::normalize(T(1.0f));
					(*indices)[2*i] = i;
					(*indices)[2*i+1] = i+1;
				}
				*(verticesAndNormals->end()-2) = knots.back();
				verticesAndNormals->back() = glm::normalize(T(1.0f));
			}
		}
		else {
			verticesAndNormals->resize(202);
			indices->resize(200);

			hpreal stepSize = (tEnd - tBegin) / 100;
			for( hpuint i = 0; i < 100; i++ ) {
				(*verticesAndNormals)[2*i] = getValueAt(tBegin + i*stepSize);
				(*verticesAndNormals)[2*i+1] = glm::normalize(T(1.0f));
				(*indices)[2*i] = i;
				(*indices)[2*i+1] = i+1;
			}
			(*verticesAndNormals)[200] = getValueAt(tEnd);
			(*verticesAndNormals)[201] = glm::normalize(T(1.0f));
		}

	}
	else {
		// TODO remove workaround and find bug when adding empty LineMesh
		verticesAndNormals->push_back( T(0.0f) );
		verticesAndNormals->push_back( T(0.0f) );
		indices->push_back( 0 );
		indices->push_back( 0 );
	}

	// control polygon
	if( m_controlPoints.size() > 1 ) {
		unsigned int n = m_controlPoints.size();
		unsigned int nVData = verticesAndNormals->size();
		unsigned int nIndices = indices->size();

		verticesAndNormals->resize(nVData+2*n);
		indices->resize(nIndices+2*n-2);

		for( hpuint i = 0; i < n-1; i++ ) {
			(*verticesAndNormals)[nVData + 2*i] = m_controlPoints[i];
			(*verticesAndNormals)[nVData + 2*i+1] = glm::normalize(T(1.0f));
			(*indices)[nIndices + 2*i] = nVData/2 + i;
			(*indices)[nIndices + 2*i+1] = nVData/2 + i+1;
		}
		(*verticesAndNormals)[nVData + 2*n-2] = m_controlPoints.back();
		(*verticesAndNormals)[nVData + 2*n-1] = glm::normalize(T(1.0f));
	}

	// tangents
	/*
	if( m_normalizedKnots.size() > 2*m_degree && m_degree > 1 ) {
		unsigned int n = m_normalizedKnots.size() - 2*m_degree;
		unsigned int nVData = verticesAndNormals->size();
		unsigned int nIndices = indices->size();

		verticesAndNormals->resize(nVData+4*n);
		indices->resize(nIndices+2*n);

		for( unsigned int i = 0; i < n; i++ ) {
			(*verticesAndNormals)[nVData + 4*i] = getValueAt(m_normalizedKnots[i+m_degree]);
			(*verticesAndNormals)[nVData + 4*i+1] = hpvec3(1.0f,0.0f,0.0f);
			std::cout << "p: " << (*verticesAndNormals)[nVData + 4*i].x << " | " << (*verticesAndNormals)[nVData + 4*i].y << " | " << (*verticesAndNormals)[nVData + 4*i].z << std::endl;

			(*verticesAndNormals)[nVData + 4*i+2] = (*verticesAndNormals)[nVData + 4*i]
				+ getDerivativeAt(m_normalizedKnots[i+m_degree]);
			(*verticesAndNormals)[nVData + 4*i+3] = hpvec3(1.0f,0.0f,0.0f);
			std::cout << "d: " << (*verticesAndNormals)[nVData + 4*i+2].x << " | " << (*verticesAndNormals)[nVData + 4*i+2].y << " | " << (*verticesAndNormals)[nVData + 4*i+2].z << std::endl;

			(*indices)[nIndices + 2*i] = nVData/2 + 2*i;
			(*indices)[nIndices + 2*i + 1] = nVData/2 + 2*i+1;
		}
	}
	*/
	return new LineMesh(verticesAndNormals, indices);
}

template <class T> PointCloud* BSplineCurve<T>::toPointCloud() {
	if(m_controlPoints.size() == 0) {
		std::vector<T>* verticesAndNormals = new std::vector<T>;
		verticesAndNormals->push_back( T(0.0f) );
		return new PointCloud(verticesAndNormals);
	}
	else {
		// TODO remove workaround and find bug when adding empty PointCloud
		std::vector<T>* verticesAndNormals = new std::vector<T>(m_controlPoints);
		return new PointCloud(verticesAndNormals);
	}
}

template <class T> int BSplineCurve<T>::findSpan( hpreal t ) const {
	unsigned int l = 0;
	while( l < m_normalizedKnots.size() - 1 && m_normalizedKnots[l+1] <= t ) {
		l++;
	}
	return l;

	/*
	// newer version. doesn't work with knot refinement?
	if( t < m_normalizedKnots.front() ) return -1;

	//unsigned int l = 0;
	for( unsigned int i = 0; i < m_normalizedKnots.size()-1; i++ ) {
		if( m_normalizedKnots[i+1] > t ) return i;
		else if( m_normalizedKnots[i] < t ) l = i+1;
	}
	return l;
	*/
}


template <class T> BSplineCurve<hpvec3>* BSplineCurve<T>::to3dBSplineCurve() const {

	std::vector<hpvec3> controlPoints = std::vector<hpvec3>(m_controlPoints.size());
	std::vector<hpvec3>::iterator it = controlPoints.begin();
	for(auto itOther = m_controlPoints.begin(), endOther = m_controlPoints.end(); itOther != endOther; ++itOther) {
		(*it) = hpvec3(itOther->x, itOther->y, 0.0f);
		++it;
	}
	std::vector<hpreal> knots = std::vector<hpreal>(m_knots);

	BSplineCurve<hpvec3>* curve3D = new BSplineCurve<hpvec3>(controlPoints, knots);
	curve3D->setPeriodic( m_periodic );
	curve3D->setUniform( m_uniform );
	curve3D->setClamped( m_clamped );

	return curve3D;
}


template <class T> BSplineCurve<hpvec2>* BSplineCurve<T>::to2dBSplineCurve() const {

	std::vector<hpvec2> controlPoints = std::vector<hpvec2>(m_controlPoints.size());
	std::vector<hpvec2>::iterator it = controlPoints.begin();
	for(auto itOther = m_controlPoints.begin(), endOther = m_controlPoints.end(); itOther != endOther; ++itOther) {
		(*it) = hpvec2(itOther->x, itOther->y);
		++it;
	}
	std::vector<hpreal> knots = std::vector<hpreal>(m_knots);

	BSplineCurve<hpvec2>* curve2D = new BSplineCurve<hpvec2>(controlPoints, knots);
	curve2D->setPeriodic( m_periodic );
	curve2D->setUniform( m_uniform );
	curve2D->setClamped( m_clamped );

	return curve2D;
}

template <class T> int BSplineCurve<T>::findSpan( hpreal t, std::vector<hpreal>& knots ) const {
	unsigned int l = 0;
	while( l < knots.size() - 1 && knots[l+1] <= t ) {
		l++;
	}
	return l;

	/*
	// newer version (better). doesn't work with knot refinement?
	if( t < knots.front() ) return -1;
	if( knots.size() < 2 ) return 0;

	//unsigned int l = 0;
	for( unsigned int i = 0; i < knots.size()-1; i++ ) {
		if( knots[i+1] > t ) return i;
		else if( knots[i] < t ) l = i+1;
	}
	return l;
	*/
}

template <class T> std::vector<T> BSplineCurve<T>::knotRefinement( hpreal minDist ) {
	if( m_normalizedPoints.size() < m_degree + 1 ) return std::vector<T>();
	unsigned int numberSubdivisionSteps = 6;

	std::vector<hpreal> newKnots;

	std::vector<hpreal> refinedKnots( m_normalizedKnots );
	std::vector<T> refinedPoints( m_normalizedPoints );

	// TODO: do not subdivide fixed number of steps, but until all segments have distance <= minDist 
	unsigned int subdivisionStep = 0;
	do {
		newKnots.clear();
		for( int i = m_degree; i < refinedKnots.size() - m_degree - 1; i++ ) {
			if( refinedKnots[i+1] - refinedKnots[i] > EPSILON ) {
				bool refineCurrent = false;
				for( int k = i - m_degree; k < i; k++ )
				{
					refineCurrent |= minDist < glm::length(refinedPoints[k+1] - refinedPoints[k]);
				}
				if( refineCurrent ) {
					newKnots.push_back( 0.5f*(refinedKnots[i+1]+refinedKnots[i]) );
				}
			}
		}

		refine( refinedKnots, refinedPoints, newKnots );

		subdivisionStep++;
	} while(subdivisionStep < numberSubdivisionSteps);

//	} while(newKnots.size() > 0);

	refinedPoints.erase( refinedPoints.begin(), refinedPoints.begin()+m_degree-1 );
	refinedPoints.erase( refinedPoints.end()-m_degree+1, refinedPoints.end() );
	return refinedPoints;
}

template <class T> void BSplineCurve<T>::refine(
    std::vector<hpreal>& knots,
    std::vector<T>& points,
    std::vector<hpreal>& newKnots ) const
{
	if( newKnots.size() == 0 ) return;

	std::vector<hpreal> refinedKnots( knots.size() + newKnots.size() );
	std::vector<T> refinedPoints( points.size() + newKnots.size() );

	int lb = findSpan( newKnots.front(), knots );
	int ub = findSpan( newKnots.back(), knots );

	int beginUpperUnaffected = ub + 1;
	int numUpperUnaffected  = knots.size() - beginUpperUnaffected;
	int endLowerUnaffeffected = lb;

	// copy unaffected knots
	if( lb > m_degree )
		std::copy( points.begin(), points.begin()+lb-m_degree, refinedPoints.begin() );
	if( numUpperUnaffected > 0 )
		std::copy( points.rbegin(), points.rbegin()+numUpperUnaffected, refinedPoints.rbegin() );

	std::copy( knots.begin(), knots.begin()+lb+1, refinedKnots.begin() );
	std::copy( knots.begin()+ub+m_degree+1, knots.end(), refinedKnots.begin()+ub+m_degree+1+newKnots.size() );

	int p = m_degree;
	int i = ub + p;
	int k = ub + p + newKnots.size();
	std::vector<hpreal>::reverse_iterator newKnotIt;

	for( newKnotIt = newKnots.rbegin(); newKnotIt != newKnots.rend(); newKnotIt++ ) {
		while( *newKnotIt <= knots[i] && i > lb ) {
			refinedPoints[k-p-1] = points[i-p-1];
			refinedKnots[k] = knots[i];
			i--; k--;
		}
		refinedPoints[k-p-1] = refinedPoints[k-p];

		for( int l = 1; l <= p; l++ ) {
			int ind = k - p + l;
			hpreal alpha = refinedKnots[k+l] - *newKnotIt;
			if( std::abs(alpha) < EPSILON ) {
				refinedPoints[ind-1] = refinedPoints[ind];
			} else {
				alpha = alpha / ( refinedKnots[k+l] - knots[i-p+l]);
				refinedPoints[ind-1] = alpha*refinedPoints[ind-1] +  (1.0f-alpha)*refinedPoints[ind];
			}
		}
		refinedKnots[k] = *newKnotIt;
		k--;
	}
	points.swap(refinedPoints);
	knots.swap(refinedKnots);

}


// template <class T> void BSplineCurve<T>::drawAdditionalPoints(const std::vector<hpvec3>& additionalPoints) {
// 	m_furtherDrawPoints = std::vector<hpvec3>(additionalPoints);
// }

// template <class T> void BSplineCurve<T>::addAdditionalCurve(const BSplineCurve& bSplineCurve) {
// 	m_additionalCurves.push_back(new BSplineCurve(bSplineCurve));
// }

// template <class T> void BSplineCurve<T>::drawArray(const std::vector<hpvec3>& points) const {
// 	cerr << "[	";
// 	if(points.size() != 0) {
// 		for(hpuint i = 0; i < points.size() - 1; ++i) {
// 			cerr << "[" << points[i].x << "," << points[i].y << "," << points[i].z <<"] |	";
// 		}
// 		cerr << "[" << points.back().x << "," << points.back().y << "," << points.back().z <<"]";
// 	}
// 	cerr << "	]" << endl;
// }

// template <class T> void BSplineCurve<T>::drawArray(const std::vector<hpvec2>& points) const {
// 	cerr << "[	";
// 	if(points.size() != 0) {
// 		for(hpuint i = 0; i < points.size() - 1; ++i) {
// 			cerr << "[" << points[i].x << "," << points[i].y << "] |	";
// 		}
// 		cerr << "[" << points.back().x << "," << points.back().y << "]";
// 	}
// 	cerr << "	]" << endl;
// }

// template <class T> void BSplineCurve<T>::drawArray(const std::vector<hpreal>& values) const {
// 	cerr << "[	";
// 	for(hpuint i = 0; i < values.size() - 1; ++i) {
// 		cerr << values[i] << " |	";
// 	}
// 	cerr << values.back() << "	]" << endl;
// }

template class BSplineCurve<hpvec3>;
template class BSplineCurve<hpvec2>;
