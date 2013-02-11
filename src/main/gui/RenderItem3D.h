#ifndef RENDERITEM3D_H
#define RENDERITEM3D_H

#include <string>
#include "../core/geometries/NonDrawable.h"
#include "../core/models/Drawable.h"

class RenderItem3D {

private:
	NonDrawable* m_nonDrawable;
	Drawable* m_drawable;
	std::string m_name; //TODO: move name stuff into here.
public:
	RenderItem3D(NonDrawable* nondrawable, Drawable* drawable, std::string name);
	~RenderItem3D();

	Drawable* getDrawable();
	NonDrawable* getNonDrawable();
	std::string getName();

};

#endif //RENDERITEM3D_H
