#ifndef BSPLINECURVE_H
#define BSPLINECURVE_H

#include <glm/glm.hpp>
#include <vector>

#include "happah/gui/Drawable2D.h"
#include "happah/HappahTypes.h"

class BSplineCurve : public Drawable2D {
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
	void setControlPoint( unsigned int index, glm::vec3 newValue );
	glm::vec3 getControlPoint( unsigned int index ) const;
	unsigned int getNumberOfControlPoints() const;
	void resetKnots();

	void addCurve( BSplineCurve *curve );
	void approximatePoints( std::vector<hpvec2>* points , unsigned int numberOfControlPoints ); //KATJA!!!

	void setDegree( unsigned int degree );
	int getDegree() const;
	void setUniform( bool uniform );
	void setPeriodic( bool periodic );
	void setClamped( bool clamped );
	bool getUniform() const;
	bool getPeriodic() const;
	bool getClamped() const;

	glm::vec3 getValueAt( float t ) const;

	virtual void draw( Painter2D* painter );
	virtual void getBounds( glm::vec2* min, glm::vec2* max ) const;

	private:
	void calculateDrawingData();
};

#endif