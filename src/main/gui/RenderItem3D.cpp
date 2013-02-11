#include "RenderItem3D.h"

RenderItem3D::RenderItem3D(NonDrawable* nonDrawable, Drawable* drawable, std::string name) :
				m_nonDrawable(nonDrawable), m_drawable(drawable), m_name(name) {}

RenderItem3D::~RenderItem3D() {}

Drawable* RenderItem3D::getDrawable() {
	return m_drawable;
}
NonDrawable* RenderItem3D::getNonDrawable() {
	return m_nonDrawable;
}
std::string RenderItem3D::getName() {
	return m_name;
}