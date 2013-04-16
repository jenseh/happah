#include "happah/geometries/BSplineCurve.h"
#include "happah/HappahConstants.h"

#include <iostream>

BSplineCurve::BSplineCurve() {
	m_degree = 3;
	m_clamped = false;
	m_periodic = false;
	m_uniform = true;
	m_knots.push_back( 0.0f );
	for( int i = 1; i < m_degree; i++ ) {
		m_knots.push_back( i*(1.0f/((float) m_degree)) );
	}
	m_knots.push_back( 1.0f );
}

BSplineCurve::~BSplineCurve() {
}

BSplineCurve::BSplineCurve( const std::vector<hpvec2>& controlPoints, const std::vector<hpreal>& knots ) : m_knots( knots ) {
	//TODO: put m_controlPoints(controlPoints) in line above and delete these lines until...
	m_controlPoints.resize(controlPoints.size());
	std::vector<hpvec3>::iterator mIt = m_controlPoints.begin();
	for(std::vector<hpvec2>::const_iterator it = controlPoints.begin(), end = controlPoints.end(); it != end; ++it) {
		*mIt = hpvec3((*it).x, (*it).y, 0.0f);
		++mIt;
	}
	//here
	m_degree = m_knots.size() - m_controlPoints.size() - 1;
	if( m_degree <= 0 ) {
		std::cerr << "Number of control points is too big for given knots!" << std::endl;
	}
	m_periodic = false;
	m_uniform = false;
}

void BSplineCurve::addControlPoint( hpvec3 newPoint ) {
	m_controlPoints.push_back(newPoint);

	if( m_uniform ) {
		float scaleFact = 1.0f - 1.0f/(m_knots.size());
		m_knots[0] = 0.0f;
		for( unsigned int i = 1; i < m_knots.size(); i++ ) {
			m_knots[i] *= scaleFact;
		}
		m_knots.push_back( 1.0f );
	/*	// non-normalized version, not tested!
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

	getKnots();
}

void BSplineCurve::addControlPoint( hpvec3 newPoint, float distanceFromLast ) {
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

void BSplineCurve::calculateNormalization() {
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
			m_normalizedKnots[i] = i*( 1.0f/((float) sizeKnots-1) );
		}
	}
	else if(m_clamped && m_normalizedKnots.size() > 2*(m_degree+1)) {
		for( int i = 0; i < m_degree; i++ ) {
			m_normalizedKnots[i] = m_normalizedKnots[m_degree];
			*(m_normalizedKnots.rbegin()+i) = *(m_normalizedKnots.rbegin()+m_degree);
		}
//		for( int i = 0; i < m_normalizedKnots.size() - 2*m_degree; i++ ) {
//			m_normalizedKnots[i+m_degree] = i*( 1.0f/((float) m_normalizedKnots.size() - 2*m_degree) );
//		}
	}
	else if(m_uniform) {
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

void BSplineCurve::getBoundingBox( hpvec2* min, hpvec2* max ) const {
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

bool BSplineCurve::getClamped() const {
	return m_clamped;
}

hpvec3 BSplineCurve::getControlPoint( unsigned int index ) const {
	if( index < m_controlPoints.size() ) {
		return m_controlPoints[index];
	}
	return hpvec3(0, 0, 0);
}

std::vector<hpvec3> BSplineCurve::getControlPoints() const {
	return std::vector<hpvec3>(m_controlPoints);
}

std::vector<hpreal> BSplineCurve::getKnots() const {
	return std::vector<hpreal>(m_knots);
}

int BSplineCurve::getDegree() const {
	return m_degree;
}

unsigned int BSplineCurve::getNumberOfControlPoints() const {
	return m_controlPoints.size();
}

void BSplineCurve::getParameterRange( float& t_low, float& t_high ) const {
	if( m_normalizedPoints.size() < m_degree + 1 ) return;

	t_low =  m_normalizedKnots[m_degree];
	t_high = m_normalizedKnots[m_normalizedPoints.size()];
}

bool BSplineCurve::getPeriodic() const {
	return m_periodic;
}

bool BSplineCurve::getUniform() const {
	return m_uniform;
}

hpvec3 BSplineCurve::getDerivativeAt( hpreal t ) const {
	if( m_normalizedPoints.size() < m_degree + 1 ) {
		return hpvec3(0,0,0);
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

		std::vector<float> knots (m_normalizedKnots.begin()+l-m_degree,m_normalizedKnots.begin()+l+m_degree+1);
		std::vector<hpvec3> output (m_normalizedPoints.begin()+l-m_degree,m_normalizedPoints.begin()+l+1);
		std::vector<hpvec3> old (output);

		for( int k = 1; k < m_degree; k++) {
			for( int i = k; i < m_degree+1; i++) {
				float alpha = (t - knots[i])/(knots[i+m_degree+1-k]-knots[i]);
				output[i] = (1-alpha)*old[i-1] + alpha*old[i];
			}
			old = output;
		}
		return output[m_degree] - output[m_degree-1];
	}
}

hpvec3 BSplineCurve::getValueAt( hpreal t ) const {
	if( m_normalizedPoints.size() < m_degree + 1 ) {
		return hpvec3(0,0,0);
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

bool BSplineCurve::isClamped() const {
	return m_clamped;
}

bool BSplineCurve::isPeriodic() const {
	return m_periodic;
}

bool BSplineCurve::isUniform() const {
	return m_uniform;
}

void BSplineCurve::interpolateControlPoints() {
	// use control points as input points
	std::vector<hpvec3> inputPoints;
	inputPoints.swap(m_controlPoints);

	interpolatePoints( inputPoints );
}

void BSplineCurve::interpolatePoints( std::vector<hpvec2>& points ) {
	std::vector<hpvec3> inputPoints( points.size() );
	std::vector<hpvec3>::iterator itInput = inputPoints.begin();
	for( std::vector<hpvec2>::iterator it = points.begin(), end = points.end(); it != end; ++it, ++itInput ) {
		*itInput = hpvec3( ( *it ).x, ( *it ).y, 0.0f );
	}
	interpolatePoints( inputPoints );
}

void BSplineCurve::interpolatePoints( std::vector<hpvec3>& inputPoints ) {
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
	std::vector<hpvec3>::iterator it = inputPoints.begin() + 1;
	inputPoints.insert( it, hpvec3( 0.0f, 0.0f, 0.0f ) );
	inputPoints.push_back(inputPoints.back());
	*(inputPoints.end() - 2) = hpvec3( 0.0f, 0.0f, 0.0f );

	// solve linear equation system
	std::vector<hpreal> v(tridiagMatrix.size()+1);
	v[0] = 0.0f;
	std::vector<hpvec3> y(tridiagMatrix.size()+1);
	y[0] = hpvec3( 0.0f, 0.0f, 0.0f );
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

void BSplineCurve::removeControlPoints() {
	m_controlPoints.clear();
//	std::vector<hpvec3>().swap(m_controlPoints); // forces reallocation
	m_knots.resize(m_degree+1);
	for( int i = 1; i < m_degree; i++ ) {
		m_knots[i] = i*(1.0f/((float) m_degree));
	}
	m_knots[0] = 0.0f;
	m_knots[m_degree] = 1.0f;
	calculateNormalization();
}

void BSplineCurve::resetKnotsToUniform() {
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
	m_clamped = clamped;
	calculateNormalization();
}

void BSplineCurve::setControlPoint( unsigned int index, hpvec3 newValue ) {
	if( index < m_controlPoints.size() ) {
		m_controlPoints[index] = newValue;
	}
	calculateNormalization();
}

void BSplineCurve::setDegree( unsigned int degree ) {
	if( degree < 1 ) return;
	m_knots.resize( m_controlPoints.size() + degree + 1 );
/*
	if( degree < m_degree && m_uniform ) {
		float scaleFact = 1.0f / m_knots.back();
		for( int i = 0; i < m_knots.size(); i++ ) {
			m_knots[i] *= scaleFact;
		}
	}
	else */
	if( degree > m_degree ) {
/*		if( m_uniform ) {
			float scaleFact = 1.0f/(m_knots.size() - 1);
			for( int i = 0; i < m_knots.size(); i++ ) {
				m_knots[i] = i*scaleFact;
			}
		}
		else {*/
			int oldBack = m_controlPoints.size() + m_degree;
			float stepSize = ( m_knots.at(oldBack) - m_knots.front() ) / oldBack;
			for( int i = 1; i < degree - m_degree + 1; i++ ) {
				m_knots[oldBack+i] = m_knots.at(oldBack) + i*stepSize;
			}
		/*
		}
		float scaleFact = 1.0f / ((float) m_knots.size()-1 );
		int oldNum = m_controlPoints.size() + m_degree + 1;
		for( int i = 0; i < oldNum; i++ ) {
			m_knots[i] *= ((float) oldNum-1)*scaleFact;
		}
		for( int i = oldNum; i < m_knots.size(); i++ ) {
			m_knots[i] = i*scaleFact;
		}
		*/
	}
	m_degree = degree;
	calculateNormalization();
}

void BSplineCurve::setUniform( bool uniform ) {
	m_uniform = uniform;
	if( m_uniform ) {
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
	std::vector<hpvec3>* verticesAndNormals = new std::vector<hpvec3>;
	std::vector<hpuint>* indices = new std::vector<hpuint>;

	hpreal tBegin = 0.0f, tEnd = 0.0f;
	getParameterRange(tBegin, tEnd);

	if( tEnd - tBegin > EPSILON && m_degree > 1 ) {
		verticesAndNormals->resize(202);
		indices->resize(200);

		hpreal stepSize = (tEnd - tBegin) / 100;
		for( hpuint i = 0; i < 100; i++ ) {
			(*verticesAndNormals)[2*i] = getValueAt(tBegin + i*stepSize);
			(*verticesAndNormals)[2*i+1] = hpvec3(1.0f,0.0f,0.0f);
			(*indices)[2*i] = i;
			(*indices)[2*i+1] = i+1;
		}
		(*verticesAndNormals)[200] = getValueAt(tEnd);
		(*verticesAndNormals)[201] = hpvec3(1.0f,0.0f,0.0f);

	}
	else {
		// TODO remove workaround and find bug when adding empty LineMesh
		verticesAndNormals->push_back( hpvec3(0.0f,0.0f,0.0f) );
		verticesAndNormals->push_back( hpvec3(0.0f,0.0f,0.0f) );
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
			(*verticesAndNormals)[nVData + 2*i+1] = hpvec3(1.0f,0.0f,0.0f);
			(*indices)[nIndices + 2*i] = nVData/2 + i;
			(*indices)[nIndices + 2*i+1] = nVData/2 + i+1;
		}
		(*verticesAndNormals)[nVData + 2*n-2] = m_controlPoints.back();
		(*verticesAndNormals)[nVData + 2*n-1] = hpvec3(1.0f,0.0f,0.0f);
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

PointCloud* BSplineCurve::toPointCloud() {
	if(m_controlPoints.size() == 0) {
		std::vector<hpvec3>* verticesAndNormals = new std::vector<hpvec3>;
		verticesAndNormals->push_back( hpvec3(0.0f,0.0f,0.0f) );
		return new PointCloud(verticesAndNormals);
	}
	else {
		// TODO remove workaround and find bug when adding empty PointCloud
		std::vector<hpvec3>* verticesAndNormals = new std::vector<hpvec3>(m_controlPoints);
		return new PointCloud(verticesAndNormals);
	}
}

