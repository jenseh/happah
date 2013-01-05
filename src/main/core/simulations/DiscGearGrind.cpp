#include "DiscGearGrind.h"

DiscGearGrind::DiscGearGrind(Disc* disc, SpurGear* gear):
    m_disc(disc), m_gear(gear)
{
    // both are initially placed in (0,0,0)
    // move gear radius down
    m_gear->translate(0, -m_disc->getRadius(), 0);
}

DiscGearGrind::~DiscGearGrind() {

}

void DiscGearGrind::calculateGrindingDepth(){
    TriangleMesh* discMesh = m_disc->toQuadMesh()->toTriangleMesh();
    RayCloud* rayCloud = m_gear->toQuadMesh()->toTriangleMesh()->toRayCloud(); //TODO: this is terribly inefficient
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
    return;
}

void DiscGearGrind::runSimulation() {
  calculateGrindingDepth();
}
