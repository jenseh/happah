/*
 * Geomtry.h
 *
 *  Created on: Nov 28, 2012
 *      Author: matthias
 */

#ifndef GEOMETRY_H
#define GEOMETRY_H

#include <string>

class Geometry {

public:
    Geometry(const std::string name);
    Geometry();
    virtual ~Geometry();

protected:
    std::string m_name;
};

#endif // GEOMETRY_H
