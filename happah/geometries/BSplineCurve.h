#ifndef BSPLINECURVE_H
#define BSPLINECURVE_H

#include <glm/glm.hpp>
#include <memory>
#include <vector>

#include "happah/HappahTypes.h"
#include "happah/geometries/PointCloud.h"
#include "happah/geometries/LineMesh.h"
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

	/**
	  * Adds a new control point to the curve.
	  *
	  * @param newPoint Control point to be added.
	  */
	void addControlPoint( T newPoint );

	/**
	  * Adds a new control point with a knot value to the curve.
	  *
	  * @param newPoint Control point to be added.
	  * @param distanceFromLast Distance of the corresponding added knot from currently last knot
	  * 	in the knot vector. If the curve is uniform, this parameter will be ignored.
	  * 	If the parameter is negative, it will be set to zero.
	  * @see isUniform(), setUniform( bool uniform )
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
	/**
	  * Checks the curve for consistency and gives debug output.
	  *
	  * @param debugOutput Give debug output if true.
	  * @return True if curve is consistent.
	  */
	bool check( bool debugOutput ) const;

	/**
	  * Gives the i-th control point.
	  */
	T getControlPoint( unsigned int index ) const;

	/**
	  * Gives vector of all control points of this curve.
	  */
	std::vector<T> getControlPoints() const;

	/**
	  * Gives knot vector.
	  */
	std::vector<hpreal> getKnots() const;

	/**
	  * Gives the curve's degree.
	  */
	int getDegree() const;

	void getIntersectionPointsWithRay( const Ray& ray, std::vector<T>& intersectionPoints ) const;
	hpuint getMultiplicityOfKnotValue( hpreal knotValue ) const;
	hpuint getMultiplicity( hpuint knotIndex ) const;

	/**
	  * Gives number of control points of this curve.
	  */
	unsigned int getNumberOfControlPoints() const;

	/**
	  * Gives lower and upper limit for parameter values this curve can be evaluated for.
	  * @param [out] t_low,t_high Lower and upper limit of the parameter range. If the number
	 	 of knots is to small, both limits will be equal.
	  * @see getValueAt( hpreal t ), getDerivativeAt( hpreal t )
	  */
	void getParameterRange( hpreal& t_low, hpreal& t_high ) const;

	/**
	  * Gives the tangent vector at a parameter value.
	  * @param t Parameter value. If not in parameter range, the lower / upper limit is assumed.
	  * @return Vector of the tangent's direction.
	  * @see getParameterRange( hpreal& t_low, hpreal& t_high )
	  */
	T getDerivativeAt( hpreal t ) const;

	/**
	  * Gives the curve's position at a parameter value.
	  * @param t Parameter value. If not in parameter range, the lower / upper limit is assumed.
	  * @see getParameterRange( hpreal& t_low, hpreal& t_high )
	  */
	T getValueAt( hpreal t ) const;

	/**
	  * Interpolates the control points of this curve with a third degree B-spline and 
	  	calculate new control points.
	  */
	void interpolateControlPoints();
	// void interpolatePoints( std::vector<hpvec2>& points );

	/**
	  * Interpolate a given number of control points with a third degree B-spline.
	  */
	void interpolatePoints( std::vector<T>& points );

	bool isClamped() const;
	bool isPeriodic() const;
	bool isUniform() const;

	/**
	  * Removes all control points.
	  */
	void removeControlPoints();

	/**
	  * Remove the i-th control point.
	  * @param index Index of the control point. If not in range, curve will not be altered.
	  */
	void removeControlPoint( unsigned int index );

	/**
	  * Distributes all knots equal-distant between 0 and 1.
	  */
	void resetKnotsToUniform();

	void setClamped( bool clamped );

	/**
	  * Sets the value of the i-th control point.
	  * @param index Index of the control point. If not in range, curve will not be altered.
	  */
	void setControlPoint( unsigned int index, T newValue );

	/**
	  * Sets values of all control points.
	  * @param points Vector of new control point values. If number of entries is not equal
	  	to number of control points of this curve, the courve will not be altered.
	  */
	void setControlPoints( const std::vector<T>& points );

	void setDegree( unsigned int degree );
	void setPeriodic( bool periodic );
	void setUniform( bool uniform );

	PointCloud* toPointCloud();
	LineMesh<T>* toLineMesh();
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
