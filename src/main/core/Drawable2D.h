#ifndef DRAWABLE2D_H
#define DRAWABLE2D_H

#include <string>

#include "Painter2D.h"

class Drawable2D {

private:
	std::string m_name;

public:
	virtual void draw( Painter2D* painter ) = 0;
	virtual void getBounds( glm::vec2* min, glm::vec2* max ) const = 0;

	void setName( std::string newName );
	std::string getName();
};

#endif // DRAWABLE2D_H
