#ifndef BSPLINECURVE_H
#define BSPLINECURVE_H

#include <glm/glm.hpp>
#include <memory>
#include <vector>

#include "happah/geometries/Mesh.h"
#include "happah/geometries/PointCloud.h"
#include "happah/HappahTypes.h"

template <class T>
class BSplineCurve {
protected:
	std::vector<T>	m_controlPoints;
	bool		m_clampedEnds;
	bool		m_clamped;
	int		m_degree;
	std::vector<T>	m_normalizedPoints;
	std::vector<float>	m_normalizedKnots;
	std::vector<float>	m_knots;
	bool		m_periodic;
	bool		m_uniformKnots;
	bool		m_uniform;


public:
	BSplineCurve();
	BSplineCurve(const BSplineCurve& other);
	BSplineCurve( const std::vector<hpvec2>& controlPoints, const std::vector<hpreal>& knots );
	~BSplineCurve();

	void addControlPoint( T newPoint );

	/**
	  * Adds a control new point to the curve.
	  *
	  * @param newPoint Control point to be added.
	  * @param distanceFromLast Distance of the corresponding added knot from currently last knot
	  * 	in the knot vector. If the curve is uniform, this parameter will be ignored.
	  * 	If the parameter is negative, it will be set to zero.
	  * @see getUniform(), setUniform( bool uniform )
	  */
	void addControlPoint( T newPoint, float distanceFromLast );

private:
	void calculateNormalization();
	int findSpan( hpreal t ) const;
	int findSpan( hpreal t, std::vector<hpreal>& knots) const;

	std::vector<hpvec3> knotRefinement( hpreal minDist );
	void refine(
		std::vector<hpreal>& knots,
		std::vector<hpvec3>& points,
		std::vector<hpreal>& newKnots
	);

public:
	bool check( bool debugOutput ) const;

	virtual void getBoundingBox( hpvec2* min, hpvec2* max ) const;
	bool getClamped() const;
	T getControlPoint( unsigned int index ) const;
	std::vector<T> getControlPoints() const;
	std::vector<hpreal> getKnots() const;
	int getDegree() const;
	unsigned int getNumberOfControlPoints() const;
	void getParameterRange( float& t_low, float& t_high ) const;
	bool getPeriodic() const;
	bool getUniform() const;
	T getDerivativeAt( hpreal t ) const;
	T getValueAt( hpreal t ) const;
	void interpolateControlPoints();
	void interpolatePoints( std::vector<hpvec2>& points );
	void interpolatePoints( std::vector<T>& points );
	bool isClamped() const;
	bool isPeriodic() const;
	bool isUniform() const;

	void removeControlPoints();
	void resetKnotsToUniform();

	void setClamped( bool clamped );
	void setControlPoint( unsigned int index, T newValue );
	void setControlPoints( const std::vector<T>& points );
	void setDegree( unsigned int degree );
	void setPeriodic( bool periodic );
	void setUniform( bool uniform );
	PointCloud* toPointCloud();
	LineMesh* toLineMesh();


};

typedef std::shared_ptr<BSplineCurve<hpvec3>> BSplineCurve_ptr;

#include "happah/geometries/BSplineCurve.cpp"
#endif // BSPLINECURVE_H
