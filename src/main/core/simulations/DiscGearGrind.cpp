#include "DiscGearGrind.h"

DiscGearGrind::DiscGearGrind(Disc* disc, InvoluteSpurGear* gear):
    m_disc(disc), m_gear(gear)
{
    // both are initially placed in (0,0,0)
    // move gear radius down
    m_gear->translate(0, -m_disc->getRadius(), 0);
}

DiscGearGrind::~DiscGearGrind() {

}

Drawable* DiscGearGrind::calculateGrindingDepth(){

    TriangleMesh* discMesh = m_disc->toQuadMesh()->toTriangleMesh();
    TriangleMesh* result = m_gear->toQuadMesh()->toTriangleMesh(); // TODO: m_gear->toTriangle does not work!?
    RayCloud* rayCloud = result->toRayCloud();
    std::vector<Ray*> gearMesh = *(rayCloud->getRays());
    TriangleKDTree kdTree;
    kdTree.build(*discMesh);
    vector<double> distances(gearMesh.size());
    for( size_t i = 0; i < gearMesh.size(); i++){
        IntersectInfo info;
        distances[i] = 100;
        Ray inverseRay = *gearMesh[i];
        inverseRay.direction = gearMesh[i]->inverse_direction;
        inverseRay.inverse_direction = gearMesh[i]->direction;
        if( kdTree.intersect(inverseRay, info)){
            distances[i] = -glm::distance(inverseRay.origin , info.hit_point);
        }else if( kdTree.intersect(*gearMesh[i], info) ){
            distances[i] = glm::distance(gearMesh[i]->origin , info.hit_point);
        }
    }
    vector<Color> colorArray;
    for( size_t i = 0; i < distances.size(); i++){
        Color curCol;
        curCol.red = distances[i];
        curCol.alpha = 1.0;
        colorArray.push_back(curCol);

    }
    result->setColorData(colorArray);
    return result;
}

void DiscGearGrind::runSimulation() {
  calculateGrindingDepth();
}
