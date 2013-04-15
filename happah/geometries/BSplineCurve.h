#ifndef BSPLINECURVE_H
#define BSPLINECURVE_H

#include <glm/glm.hpp>
#include <memory>
#include <vector>

#include "happah/geometries/Mesh.h"
#include "happah/geometries/PointCloud.h"
#include "happah/HappahTypes.h"

class BSplineCurve {
protected:
	std::vector<hpvec3>	m_controlPoints;
	bool		m_clampedEnds;
	bool		m_clamped;
	int		m_degree;
	std::vector<hpvec3>	m_normalizedPoints;
	std::vector<float>	m_normalizedKnots;
	std::vector<float>	m_knots;
	bool		m_periodic;
	bool		m_uniformKnots;
	bool		m_uniform;


public:
	BSplineCurve();
	~BSplineCurve();

	void addControlPoint( hpvec3 newPoint );

	/**
	  * Adds a control new point to the curve.
	  *
	  * @param newPoint Control point to be added.
	  * @param distanceFromLast Distance of the corresponding added knot from currently last knot
	  * 	in the knot vector. If the curve is uniform, this parameter will be ignored.
	  * 	If the parameter is negative, it will be set to zero.
	  * @see getUniform(), setUniform( bool uniform )
	  */
	void addControlPoint( hpvec3 newPoint, float distanceFromLast );

	void approximatePoints( std::vector<hpvec2>* points , unsigned int numberOfControlPoints ); //KATJA!!!

private:
	void calculateNormalization();

public:
	bool check( bool debugOutput ) const;

	virtual void getBoundingBox( hpvec2* min, hpvec2* max ) const;
	bool getClamped() const;
	hpvec3 getControlPoint( unsigned int index ) const;
	std::vector<hpvec3> getControlPoints() const;
	int getDegree() const;
	unsigned int getNumberOfControlPoints() const;
	void getParameterRange( float& t_low, float& t_high ) const;
	bool getPeriodic() const;
	bool getUniform() const;
	hpvec3 getDerivativeAt( hpreal t ) const;
	hpvec3 getValueAt( hpreal t ) const;
	void interpolateControlPoints();
	void interpolatePoints( std::vector<hpvec2>& points );
	void interpolatePoints( std::vector<hpvec3>& points );
	bool isClamped() const;
	bool isPeriodic() const;
	bool isUniform() const;

	void removeControlPoints();
	void resetKnotsToUniform();

	void setClamped( bool clamped );
	void setControlPoint( unsigned int index, hpvec3 newValue );
	void setDegree( unsigned int degree );
	void setPeriodic( bool periodic );
	void setUniform( bool uniform );
	PointCloud* toPointCloud();
	LineMesh* toLineMesh();


};

typedef std::shared_ptr<BSplineCurve> BSplineCurve_ptr;

#endif // BSPLINECURVE_H
