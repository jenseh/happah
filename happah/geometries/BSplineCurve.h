#ifndef BSPLINECURVE_H
#define BSPLINECURVE_H

#include <glm/glm.hpp>
#include <memory>
#include <vector>

#include "happah/geometries/Mesh.h"
#include "happah/geometries/PointCloud.h"
#include "happah/HappahTypes.h"
#include "happah/math/Ray.h"

template <class T>
class BSplineCurve {
protected:
	bool		m_clampedEnds;
	bool		m_clamped;
	std::vector<T>	m_controlPoints;
	int		m_degree;
	std::vector<hpreal>	m_knots;
	std::vector<T>	m_normalizedPoints;
	std::vector<hpreal>	m_normalizedKnots;
	bool		m_periodic;
	bool		m_uniformKnots;
	bool		m_uniform;


public:
	BSplineCurve();
	BSplineCurve( const BSplineCurve& other );
	BSplineCurve( const std::vector<T>& controlPoints, const std::vector<hpreal>& knots );
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
	void addControlPoint( T newPoint, hpreal distanceFromLast );

private:
	void calculateNormalization();
	int findSpan( hpreal t ) const;
	int findSpan( hpreal t, std::vector<hpreal>& knots) const;

	std::vector<T> knotRefinement( hpreal minDist );
	void refine (
		std::vector<hpreal>& knots,
		std::vector<T>& points,
		std::vector<hpreal>& newKnots
	) const;

public:
	bool check( bool debugOutput ) const;

	void getBoundingBox( hpvec2* min, hpvec2* max ) const;
	bool getClamped() const;
	T getControlPoint( unsigned int index ) const;
	std::vector<T> getControlPoints() const;
	std::vector<hpreal> getKnots() const;
	int getDegree() const;
	void getIntersectionPointsWithRay( const Ray& ray, std::vector<T>& intersectionPoints ) const;
	hpuint getMultiplicityOfKnotValue( hpreal knotValue ) const;
	hpuint getMultiplicity( hpuint knotIndex ) const;
	unsigned int getNumberOfControlPoints() const;
	void getParameterRange( hpreal& t_low, hpreal& t_high ) const;
	bool getPeriodic() const;
	bool getUniform() const;
	T getDerivativeAt( hpreal t ) const;
	T getValueAt( hpreal t ) const;
	void interpolateControlPoints();
	// void interpolatePoints( std::vector<hpvec2>& points );
	void interpolatePoints( std::vector<T>& points );
	bool isClamped() const;
	bool isPeriodic() const;
	bool isUniform() const;

	void removeControlPoints();
	void removeControlPoint( unsigned int index );
	void resetKnotsToUniform();

	void setClamped( bool clamped );
	void setControlPoint( unsigned int index, T newValue );
	void setControlPoints( const std::vector<T>& points );
	void setDegree( unsigned int degree );
	void setPeriodic( bool periodic );
	void setUniform( bool uniform );
	PointCloud* toPointCloud();
	LineMesh* toLineMesh();
	BSplineCurve<hpvec3>* to3dBSplineCurve() const;
	BSplineCurve<hpvec2>* to2dBSplineCurve() const;


	// TODO: methods and things below here are only here for short testing time!
	// => remove them!
	// void drawAdditionalPoints(const std::vector<hpvec3>& additionalPoints);
	// std::vector<hpvec3> m_furtherDrawPoints;
	// void drawArray(const std::vector<hpvec3>& points) const;
	// void drawArray(const std::vector<hpvec2>& points) const;
	// void drawArray(const std::vector<hpreal>& values) const;
	// void addAdditionalCurve(const BSplineCurve& bSplineCurve);
	// std::vector<BSplineCurve*> m_additionalCurves;

};

typedef std::shared_ptr<BSplineCurve<hpvec3>> BSplineCurve_ptr;
typedef std::shared_ptr<BSplineCurve<hpvec2>> BSplineCurve2D_ptr;

#endif // BSPLINECURVE_H
