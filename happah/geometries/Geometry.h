#ifndef GEOMETRY_H
#define GEOMETRY_H

#include <memory>

class Geometry {
public:
    Geometry();
    virtual ~Geometry();


};

typedef std::shared_ptr<Geometry> Geometry_ptr;

#endif // GEOMETRY_H
