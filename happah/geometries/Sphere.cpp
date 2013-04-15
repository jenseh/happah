/*
 * Sphere.cpp
 *
 *  Created on: Nov 28, 2012
 *      Author: matthias
 */

#include "happah/geometries/Sphere.h"
#include <iostream>
#include <glm/glm.hpp>

Sphere::Sphere(float radius, glm::vec4 center){
    m_radius = radius;
    m_center = center;
}

Sphere::~Sphere() {
}

float Sphere::getRadius() {
    return m_radius;
}
/*
QuadMesh* Sphere::toQuadMesh() {
    int dtheta = 1;
    int dphi = 1;
    const float toRad = M_PI / 180.0f;
    for (int theta = -90; theta <= 90 - dtheta; theta = theta + dtheta) {
        for (int phi = 0; phi <= 360 - dphi; phi = phi + dphi) {
            glm::vec4 a, b, c, d, normA, normB, normC, normD;
            a.x = cos(theta * toRad) * cos(phi * toRad)+ m_center.x;
            a.y = cos(theta * toRad) * sin(phi * toRad)+ m_center.y;
            a.z = sin(theta * toRad)+m_center.z;
            a.w = 1.0f;
            normA = glm::normalize(a-m_center);
            //normA = glm::vec4(1.0f,0.0f,0.0f,0.0f);

            b.x = cos((theta + dtheta) * toRad) * cos(phi * toRad)+ m_center.x;
            b.y = cos((theta + dtheta) * toRad) * sin(phi * toRad)+ m_center.y;
            b.z = sin((theta + dtheta) * toRad)+m_center.z;
            b.w = 1.0f;
            normB = glm::normalize(b-m_center);
            //normB = glm::vec4(0.0f,1.0f,0.0f,0.0f);

            c.x = cos((theta + dtheta) * toRad) * cos((phi + dphi) * toRad)+ m_center.x;
            c.y = cos((theta + dtheta) * toRad) * sin((phi + dphi) * toRad)+ m_center.y;
            c.z = sin((theta + dtheta) * toRad)+m_center.z;
            c.w = 1.0f;
            normC = glm::normalize(c-m_center);
            //normC = glm::vec4(0.0f,0.0f,1.0f,0.0f);

            d.x = cos(theta * toRad) * cos((phi + dphi) * toRad)+ m_center.x;
            d.y = cos(theta * toRad) * sin((phi + dphi) * toRad)+ m_center.y;
            d.z = sin(theta * toRad)+m_center.z;
            d.w = 1.0f;
            normD = glm::normalize(d-m_center);
            //normD = glm::vec4(1.0f,1.0f,0.0f,0.0f);

            m_verticesAndNormals.push_back(a);
            m_verticesAndNormals.push_back(normA);

            m_verticesAndNormals.push_back(b);
            m_verticesAndNormals.push_back(normB);

            m_verticesAndNormals.push_back(c);
            m_verticesAndNormals.push_back(normC);

            m_verticesAndNormals.push_back(d);
            m_verticesAndNormals.push_back(normD);

        }
    }

    QuadMesh* result = new QuadMesh(m_verticesAndNormals, concatStringNumber(m_name + " - Instance ", m_objectIdCounter++));
    std::cout << "Kreis Vertices" << m_verticesAndNormals.size()<<endl;
    return result;
}

*/
TriangleMesh* Sphere::toTriangleMesh() {
  //TODO: Implement this function
  return 0;
}
