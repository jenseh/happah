#include "happah/geometries/BSplineCurve.h"
#include "happah/HappahConstants.h"

#include <iostream>

BSplineCurve::BSplineCurve() {
	m_degree = 3;
	m_clampedEnds = false;
	m_periodic = true;
	m_uniformKnots = true;
	m_knots.push_back( 0.0f );
	for( int i = 1; i < m_degree; i++ ) {
		m_knots.push_back( i*(1.0f/((float) m_degree)) );
	}
	m_knots.push_back( 1.0f );
}

BSplineCurve::~BSplineCurve() {
}

void BSplineCurve::addControlPoint( hpvec3 newPoint ) {
	m_controlPoints.push_back(newPoint);

	if( m_uniformKnots ) {
		float scaleFact = 1.0f - 1.0f/(m_knots.size());
		m_knots[0] = 0.0f;
		for( unsigned int i = 1; i < m_knots.size(); i++ ) {
			m_knots[i] *= scaleFact;
		}
		m_knots.push_back( 1.0f );
	/*	// not normalized version, not tested!
		float scaleFact = (m_knots.back() - m_knots.front()) / m_knots.size();
		m_knots.push_back( m_knots.back() );
		for( unsigned int i = 1; i < m_knots.size()-1; i++ ) {
			 m_knots[i] = m_knots[0] + scaleFact*i;
		}
	*/
	}
	else {
		float stepSize = ( m_knots.back() - m_knots.front() ) / (m_knots.size() - 1);
		m_knots.push_back( m_knots.back() + stepSize );
	}

	calculateNormalization();
}

void BSplineCurve::addControlPoint( hpvec3 newPoint, float distanceFromLast ) {
	if( m_uniformKnots ) {
		this->addControlPoint( newPoint );
	}
	else {
		m_controlPoints.push_back(newPoint);
		if( distanceFromLast < 0 ) distanceFromLast = 0.0f;
		m_knots.push_back( m_knots.back() + distanceFromLast );
		calculateNormalization();
	}
}

//TODO: this method doesn't work at the moment. It's complete rubbish but I need it to see something ^^
void BSplineCurve::approximatePoints( std::vector<hpvec2>* points, unsigned int numberOfControlPoints ) {
	hpreal stepSize = points->size() / ( numberOfControlPoints - 1 ); //subtract one to have first and last point of points!
	for( unsigned int i = 0; i < ( numberOfControlPoints - 1); ++i ) {
		addControlPoint( hpvec3(points->at( static_cast<unsigned int>( i*stepSize ) ), 0.0f ) );
	}
	addControlPoint( hpvec3(points->back(), 0.0f));
}

void BSplineCurve::calculateNormalization() {
	m_normalizedKnots = m_knots;
	m_normalizedPoints = m_controlPoints;
	if(m_periodic && m_controlPoints.size() >= m_degree) {
		// Calculate circular control points array
		int sizePoints = m_controlPoints.size()+m_degree-1;
		m_normalizedPoints.resize(sizePoints);
		std::copy(m_controlPoints.begin(), m_controlPoints.begin()+m_degree, m_normalizedPoints.end()-m_degree);
		// Resize (& unify) knots array
		int sizeKnots = m_knots.size()+m_degree-1;
		m_normalizedKnots.resize(sizeKnots);
		for( int i = 0; i < sizeKnots; i++ ) {
			m_normalizedKnots[i] = i*( 1.0f/((float) sizeKnots-1) );
		}
	}
	else if(m_clampedEnds && m_normalizedKnots.size()>2*m_degree) {
		for( int i = 0; i < m_degree+1; i++ ) {
			m_normalizedKnots[i] = 0.0f;
			m_normalizedKnots[m_normalizedKnots.size()-i-1] = 1.0f;
		}
		for( int i = 0; i < m_normalizedKnots.size() - 2*m_degree; i++ ) {
			m_normalizedKnots[i+m_degree] = i*( 1.0f/((float) m_normalizedKnots.size() - 2*m_degree) );
		}
	}
	else if(m_uniformKnots) {
		float fract = 1.0f/((float) m_normalizedKnots.size() - 1);
		for( int i = 0; i < m_normalizedKnots.size(); i++ ) {
			m_normalizedKnots[i] = i*fract;
		}
	}
}

bool BSplineCurve::check( bool debugOutput ) const {
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

void BSplineCurve::getBounds( hpvec2* min, hpvec2* max ) const {
	if( m_controlPoints.size() > 0 ) {
		// TODO: Use iterator
		min->x = m_controlPoints[0].x - 5;
		max->x = m_controlPoints[0].x + 5;
		min->y = m_controlPoints[0].y - 5;
		max->y = m_controlPoints[0].y + 5;
		for( unsigned int i = 1; i < m_controlPoints.size(); i++ ) {
			if( m_controlPoints[i].x < min->x )
				min->x = m_controlPoints[i].x - 5;
			if( m_controlPoints[i].x > max->x )
				max->x = m_controlPoints[i].x + 5;
			if( m_controlPoints[i].y < min->y )
				min->y = m_controlPoints[i].y - 5;
			if( m_controlPoints[i].y > max->y )
				max->y = m_controlPoints[i].y + 5;
		}

	}
}

bool BSplineCurve::getClamped() const {
	return m_clampedEnds;
}

hpvec3 BSplineCurve::getControlPoint( unsigned int index ) const {
	if( index < m_controlPoints.size() ) {
		return m_controlPoints[index];
	}
	return hpvec3(0, 0, 0);
}

int BSplineCurve::getDegree() const {
	return m_degree;
}

unsigned int BSplineCurve::getNumberOfControlPoints() const {
	return m_controlPoints.size();
}

void BSplineCurve::getParameterRange( float& t_low, float& t_high ) {
	if( m_normalizedKnots.size() < m_degree + 3 ) {
		return;
	}
	t_low =  m_normalizedKnots[m_degree];
	t_high = m_normalizedKnots[m_normalizedKnots.size()-m_degree-1];
}

bool BSplineCurve::getPeriodic() const {
	return m_periodic;
}

bool BSplineCurve::getUniform() const {
	return m_uniformKnots;
}

hpvec3 BSplineCurve::getValueAt( float t ) const {
	// only for uniform, noncyclic, without end-point-interpolation
	if( m_normalizedKnots.size() < m_degree + 3 ) {
		return hpvec3(0,0,0);
	}
	if( t < m_normalizedKnots[m_degree] ) {
		return getValueAt( m_normalizedKnots[m_degree] );
	}
	else if( t > m_normalizedKnots[m_normalizedKnots.size()-m_degree-1] ) {
		return getValueAt( m_normalizedKnots[m_normalizedKnots.size()-m_degree-1] );
	}
	else {
		int l;
		for( int i = m_degree; i < m_normalizedKnots.size()-m_degree-1; i++ ) {
			if( m_normalizedKnots[i] <= t ) {
				l = i;
			}
		}

//		std::cout << "#knts: " << m_normalizedKnots.size() << " > take [" << l-m_degree << ", " << l+m_degree << "] " << std::endl;
//		std::cout << "#pts:  " << m_normalizedPoints.size() << " (last idx: " << m_normalizedPoints.size() - 1 << ") ";
//		std::cout << "> take [" << l-m_degree << ", " << l << "] " << std::endl;
//		std::cout << std::endl;

		std::vector<float> knots (m_normalizedKnots.begin()+l-m_degree,m_normalizedKnots.begin()+l+m_degree+1);
		std::vector<hpvec3> output (m_normalizedPoints.begin()+l-m_degree,m_normalizedPoints.begin()+l+1);
		std::vector<hpvec3> old (output);

		for( int k = 1; k < m_degree+1; k++) {
			for( int i = k; i < m_degree+1; i++) {
				float alpha = (t - knots[i])/(knots[i+m_degree+1-k]-knots[i]);
				output[i] = (1-alpha)*old[i-1] + alpha*old[i];
			}
			old = output;
		}
		return output[m_degree];
	}
}

void BSplineCurve::resetKnots() {
	int num = m_knots.size();
	if( num > 0 ) {
		m_knots[0] = 0.0f;
		m_knots[num-1] = 1.0f;
		for( int i = 1; i < num-1; i++ ) {
			m_knots[i] = i*( 1.0f/((float) num-1) );
		}
	}
	calculateNormalization();
}

void BSplineCurve::setClamped( bool clamped ) {
	m_clampedEnds = clamped;
	calculateNormalization();
}

void BSplineCurve::setControlPoint( unsigned int index, hpvec3 newValue ) {
	if( index < m_controlPoints.size() ) {
		m_controlPoints[index] = newValue;
	}
	calculateNormalization();
}

void BSplineCurve::setDegree( unsigned int degree ) {
	m_knots.resize( m_controlPoints.size() + degree + 1 );
	if( degree < m_degree ) {
		float scaleFact = 1.0f / m_knots.back();
		for( int i = 0; i < m_knots.size(); i++ ) {
			m_knots[i] *= scaleFact;
		}
	}
	else if( degree > m_degree ) {
		float scaleFact = 1.0f / ((float) m_knots.size()-1 );
		int oldNum = m_controlPoints.size() + m_degree + 1;
		for( int i = 0; i < oldNum; i++ ) {
			m_knots[i] *= ((float) oldNum-1)*scaleFact;
		}
		for( int i = oldNum; i < m_knots.size(); i++ ) {
			m_knots[i] = i*scaleFact;
		}
	}
	m_degree = degree;
	calculateNormalization();
}

void BSplineCurve::setUniform( bool uniform ) {
	m_uniformKnots = uniform;
	if( m_uniformKnots ) {
		float scaleFact = 1.0f/(m_knots.size()-1);
		for( unsigned int i = 0; i < m_knots.size(); i++ ) {
			m_knots[i] = scaleFact*i;
		}
	/*	// not normalized version, not tested!
		float scaleFact = (m_knots.back() - m_knots.front()) / (m_knots.size()-1);
		for( unsigned int i = 0; i < m_knots.size(); i++ ) {
			m_knots[i] = m_knots[0] + scaleFact*i;
		}
	*/
	}
	calculateNormalization();
}

void BSplineCurve::setPeriodic( bool periodic ) {
	m_periodic = periodic;
	calculateNormalization();
}

LineMesh* BSplineCurve::toLineMesh() {
	hpreal tBegin = 0.0f, tEnd = 0.0f;
	getParameterRange(tBegin, tEnd);
	if( tEnd - tBegin > EPSILON ) {
		std::vector<hpvec3>* vertexData = new std::vector<hpvec3>;
		vertexData->resize(400);
		std::vector<hpuint>* indices = new std::vector<hpuint>;
		indices->resize(100);

		hpreal stepSize = (tEnd - tBegin) / 99;
		for( hpuint i = 1; i < 100; i++ ) {
			(*vertexData)[4*i] = getValueAt(tBegin+(i-1)*stepSize);
			(*vertexData)[4*i+1] = hpvec3(1.0f,0.0f,0.0f);
			(*vertexData)[4*i+2] = getValueAt(tBegin+i*stepSize);
			(*vertexData)[4*i+3] = hpvec3(1.0f,0.0f,0.0f);
			(*indices)[i] = i;
		}
		return new LineMesh(vertexData, indices);
	}

	return NULL;
}

PointCloud* BSplineCurve::toPointCloud() {
	return new PointCloud(&m_controlPoints);
}
