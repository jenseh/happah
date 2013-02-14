#include "BSplineCurve.h"

#include <iostream>

BSplineCurve::BSplineCurve() {
	m_degree = 3;
	m_uniformKnots = true;
	m_interpolateEnds = false;
	m_cyclic = true;
	m_knots.push_back( 0.0f );
	for( int i = 1; i < m_degree; i++ ) {
		m_knots.push_back( i*(1.0f/((float) m_degree)) );
	}
	m_knots.push_back( 1.0f );
}

BSplineCurve::~BSplineCurve() {
}

void BSplineCurve::addControlPoint( glm::vec3 newPoint ) {
	m_controlPoints.push_back(newPoint);

	float scaleFact = 1 - 1.0f/(m_knots.size());
	for( unsigned int i = 1; i < m_knots.size(); i++ ) {
		m_knots[i] *= scaleFact;
	}
	m_knots.push_back( 1.0f );

	calculateDrawingData();
}

void BSplineCurve::addControlPoint( float x, float y, float z ) {
	addControlPoint( glm::vec3(x,y,z) );
}

//TODO: single insertion is not a good idea here. But as knots have similar weights at the moment, I'll leave it like that.
void BSplineCurve::addCurve( BSplineCurve *curve ) {
	for( unsigned int i = 0; i < curve->getNumberOfControlPoints(); ++i ) {
		addControlPoint( curve->getControlPoint( i ));
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
unsigned int BSplineCurve::getNumberOfControlPoints() const {
	return m_controlPoints.size();
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
	calculateDrawingData();
}

void BSplineCurve::calculateDrawingData() {
	m_drawKnots = m_knots;
	m_drawPoints = m_controlPoints;
	if(m_cyclic && m_controlPoints.size() >= m_degree) {
		// Calculate circular control points array
		int sizePoints = m_controlPoints.size()+m_degree-1;
		m_drawPoints.resize(sizePoints);
		std::copy(m_controlPoints.begin(), m_controlPoints.begin()+m_degree, m_drawPoints.end()-m_degree);
		// Resize (& unify) knots array
		int sizeKnots = m_knots.size()+m_degree-1;
		m_drawKnots.resize(sizeKnots);
		for( int i = 0; i < sizeKnots; i++ ) {
			m_drawKnots[i] = i*( 1.0f/((float) sizeKnots-1) );
		}
	}
	else if(m_interpolateEnds && m_drawKnots.size()>2*m_degree) {
		for( int i = 0; i < m_degree+1; i++ ) {
			m_drawKnots[i] = 0.0f;
			m_drawKnots[m_drawKnots.size()-i-1] = 1.0f;
		}
		for( int i = 0; i < m_drawKnots.size() - 2*m_degree; i++ ) {
			m_drawKnots[i+m_degree] = i*( 1.0f/((float) m_drawKnots.size() - 2*m_degree) );
		}
	}
	else if(m_uniformKnots) {
		float fract = 1.0f/((float) m_drawKnots.size() - 1);
		for( int i = 0; i < m_drawKnots.size(); i++ ) {
			m_drawKnots[i] = i*fract;
		}
	}
}

void BSplineCurve::setControlPoint( unsigned int index, glm::vec3 newValue ) {
	if( index < m_controlPoints.size() ) {
		m_controlPoints[index] = newValue;
	}
	calculateDrawingData();
}

glm::vec3 BSplineCurve::getControlPoint( unsigned int index ) const {
	if( index < m_controlPoints.size() ) {
		return m_controlPoints[index];
	}
	return glm::vec3(0, 0, 0);
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
	calculateDrawingData();
}

int BSplineCurve::getDegree() const {
	return m_degree;
}

void BSplineCurve::setUniform( bool uniform ) {
	m_uniformKnots = uniform;
	calculateDrawingData();
}

bool BSplineCurve::getUniform() const {
	return m_uniformKnots;
}

void BSplineCurve::setPeriodic( bool periodic ) {
	m_cyclic = periodic;
	calculateDrawingData();
}

bool BSplineCurve::getPeriodic() const {
	return m_cyclic;
}

void BSplineCurve::setClamped( bool clamped ) {
	m_interpolateEnds = clamped;
	calculateDrawingData();
}

bool BSplineCurve::getClamped() const {
	return m_interpolateEnds;
}

void BSplineCurve::draw( Painter2D* painter ) {
	if( m_controlPoints.size() > 0 ) {
		painter->drawPoint( m_controlPoints[0] );
		for( unsigned int i = 1; i < m_controlPoints.size(); i++ ) {
			// TODO: Use iterator
			painter->drawPoint( m_controlPoints[i] );
			painter->drawDashedLine( m_controlPoints[i-1], m_controlPoints[i] );
//			std::cout << "Drawn point at " << m_controlPoints[i].x << " " << m_controlPoints[i].y << std::endl;
		}
		if( m_cyclic && m_controlPoints.size() > 2 ) {
			painter->drawDashedLine( m_controlPoints.back(), m_controlPoints[0] );
		}

		if( m_controlPoints.size() >= m_degree ) {
			float dt = 0.001f;
			glm::vec3 oldPt = getValueAt(m_drawKnots[m_degree]);
			glm::vec3 newPt;
			for( float t = m_drawKnots[m_degree];
			           t <=  m_drawKnots[ m_drawKnots.size() - m_degree - 1 ];
			           t += dt )
			{
				newPt = getValueAt(t);
				painter->drawLine( oldPt, newPt );
				oldPt = newPt;
//				std::cout << "Drawn at " << newPt.x << " " << newPt.y << std::endl;
			}
		}
				
/*		if( m_cyclic ) {}

		std::vector<float> drawingKnots;
		std::vector<glm::vec3> drawingControlPoints;
		int drawingNumPoints;
		if( m_controlPoints.size() > ... ) {
*/
	}
}

void BSplineCurve::getBounds( glm::vec2* min, glm::vec2* max ) const {
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

glm::vec3 BSplineCurve::getValueAt( float t ) const {
	// only for uniform, noncyclic, without end-point-interpolation
	if( m_drawKnots.size() < m_degree + 2 ) {
		return glm::vec3(0,0,0);
	}
	if( t < m_drawKnots[m_degree] ) {
		return getValueAt( m_drawKnots[m_degree] );
	}
	else if( t > m_drawKnots[m_drawKnots.size()-m_degree-1] ) {
		return getValueAt( m_drawKnots[m_drawKnots.size()-m_degree-1] );
	}
	else {
		int l;
		for( int i = m_degree; i < m_drawKnots.size()-m_degree; i++ ) {
			if( m_drawKnots[i] <= t ) {
				l = i;
			}
		}
		std::vector<float> knots (m_drawKnots.begin()+l-m_degree,m_drawKnots.begin()+l+m_degree+1);
		std::vector<glm::vec3> output (m_drawPoints.begin()+l-m_degree,m_drawPoints.begin()+l+1);
		std::vector<glm::vec3> old (output);

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



