/*
 * Sphere.cpp
 *
 *  Created on: Nov 28, 2012
 *      Author: matthias
 */

#include "Sphere.h"
#include <iostream>

Sphere::Sphere(float radius) {
    m_radius = radius;
}

Sphere::~Sphere() {
}

bool Sphere::hit(glm::vec3 rayPos, glm::vec3 rayDir) {
    float A, B, C;
    A = rayDir.x * rayDir.x + rayDir.y * rayDir.y + rayDir.z * rayDir.z;
    B = 2 * (rayDir.x * rayPos.x + rayDir.y * rayPos.y + rayDir.z * rayPos.z);
    C = rayPos.x * rayPos.x + rayPos.y * rayPos.y + rayPos.z * rayPos.z
            - m_radius * m_radius;

    float t0, t1;
    if (!quad(A, B, C, &t0, &t1))
        return false;
    float tmin = glm::min(t0, t1);
    m_hitpoint = rayPos + tmin * rayDir;

    return true;
}

bool Sphere::quad(float A, float B, float C, float *t0, float *t1) {
    float q;
    float discrim = B * B - 4.0f * A * C;

    if (discrim < 0)
        return false;
    float root = std::sqrt(discrim);
    if (B < 0)
        q = -0.5f * (B - root);
    else
        q = -0.5f * (B + root);
    *t0 = q / A;
    *t1 = C / q;

    if (*t0 > *t1) {
        float temp = *t0;
        *t0 = *t1;
        *t1 = temp;
    }
    return true;

}

float Sphere::getRadius() {
    return m_radius;
}

glm::vec3 Sphere::getHitpoint() {
    return m_hitpoint;
}

QuadMesh* Sphere::toQuadMesh() {
    int dtheta = 1;
    int dphi = 1;
    const float toRad = M_PI / 180.0f;
    for (int theta = -90; theta <= 90 - dtheta; theta = theta + dtheta) {
        for (int phi = 0; phi <= 360 - dphi; phi = phi + dphi) {
            glm::vec4 a, b, c, d, normA, normB, normC, normD,colA,colB,colC,colD;
            a.x = cos(theta * toRad) * cos(phi * toRad);
            a.y = cos(theta * toRad) * sin(phi * toRad);
            a.z = sin(theta * toRad);
            a.w = 1.0f;
            normA = glm::normalize(a);
            colA = glm::vec4(1.0f,0.0f,0.0f,0.0f);

            b.x = cos((theta + dtheta) * toRad) * cos(phi * toRad);
            b.y = cos((theta + dtheta) * toRad) * sin(phi * toRad);
            b.z = sin((theta + dtheta) * toRad);
            b.w = 1.0f;
            normB = glm::normalize(b);
            colB = glm::vec4(1.0f,0.0f,0.0f,0.0f);

            c.x = cos((theta + dtheta) * toRad) * cos((phi + dphi) * toRad);
            c.y = cos((theta + dtheta) * toRad) * sin((phi + dphi) * toRad);
            c.z = sin((theta + dtheta) * toRad);
            c.w = 1.0f;
            normC = glm::normalize(c);
            colC = glm::vec4(1.0f,0.0f,0.0f,0.0f);

            d.x = cos(theta * toRad) * cos((phi + dphi) * toRad);
            d.y = cos(theta * toRad) * sin((phi + dphi) * toRad);
            d.z = sin(theta * toRad);
            d.w = 1.0f;
            normD = glm::normalize(d);
            colD = glm::vec4(1.0f,0.0f,0.0f,0.0f);

            m_vertexData.push_back(a);
            m_vertexData.push_back(normA);
             m_vertexData.push_back(colA);
            m_vertexData.push_back(b);
            m_vertexData.push_back(normB);
             m_vertexData.push_back(colB);
            m_vertexData.push_back(c);
            m_vertexData.push_back(normC);
             m_vertexData.push_back(colC);
            m_vertexData.push_back(d);
            m_vertexData.push_back(normD);
             m_vertexData.push_back(colC);
        }
    }
    QuadMesh* result = new QuadMesh(m_vertexData);
    result->setModelMatrix(m_modelMatrix);
    result->setName(m_name + " - Instance 1");
    std::cout << "Kreis Vertices" << m_vertexData.size()<<endl;
    return result;
}

TriangleMesh* Sphere::toTriangleMesh() {
  //TODO: Implement this function
  return 0;
}
