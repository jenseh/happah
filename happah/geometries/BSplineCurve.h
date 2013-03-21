#ifndef BSPLINECURVE_H
#define BSPLINECURVE_H

#include <glm/glm.hpp>
#include <memory>
#include <vector>

#include "happah/geometries/PointCloud.h"
#include "happah/HappahTypes.h"

class BSplineCurve {
protected:
	int m_degree;
	std::vector<glm::vec3> m_controlPoints;
	std::vector<float> m_knots;

	std::vector<glm::vec3> m_drawPoints;
	std::vector<float> m_drawKnots;

	bool m_uniformKnots;
	bool m_interpolateEnds;
	bool m_cyclic;


public:
	BSplineCurve();
	~BSplineCurve();

	void addControlPoint( glm::vec3 newPoint );
	void addControlPoint( float x, float y, float z );
	void addCurve( BSplineCurve *curve );
	void approximatePoints( std::vector<hpvec2>* points , unsigned int numberOfControlPoints ); //KATJA!!!

	bool check( bool debugOutput ) const;

	virtual void getBounds( glm::vec2* min, glm::vec2* max ) const;
	bool getClamped() const;
	glm::vec3 getControlPoint( unsigned int index ) const;
	int getDegree() const;
	unsigned int getNumberOfControlPoints() const;
	bool getPeriodic() const;
	bool getUniform() const;
	glm::vec3 getValueAt( float t ) const;

	void setClamped( bool clamped );
	void setControlPoint( unsigned int index, glm::vec3 newValue );
	void setDegree( unsigned int degree );
	void setPeriodic( bool periodic );
	void setUniform( bool uniform );

	PointCloud* toPointCloud();

	void resetKnots();


private:
	void calculateDrawingData();

};

typedef std::shared_ptr<BSplineCurve> BSplineCurve_ptr;

#endif // BSPLINECURVE_H
