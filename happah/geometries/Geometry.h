#ifndef GEOMETRY_H
#define GEOMETRY_H

#include <memory>

class Geometry {
public:
    Geometry();
    virtual ~Geometry();
    virtual void handleSelection() = 0;
    virtual void handleSelection(int pointIndex)= 0;

};

typedef std::shared_ptr<Geometry> Geometry_ptr;

#endif // GEOMETRY_H
