#include "happah/simulations/DiscGearGrind.h"

DiscGearGrind::DiscGearGrind(Disc_ptr disc, Gear_ptr gear):
    m_disc(disc), m_gear(gear), m_maxDistance(1.0)
{
    m_gearMouvement = Kinematic::getLinearKinematic(glm::vec3(0,-m_disc->getRadius(),  -m_disc->getRadius()),
                                                    glm::vec3(0, -m_disc->getRadius(), m_disc->getRadius()));
    // Convert to right representation
    m_discMesh = TriangleMesh_ptr(m_disc->toTriangleMesh());
    m_gearMesh = TriangleMesh_ptr(m_gear->toTriangleMesh());
    m_gearRays = m_gearMesh->toRays();
    // resize distances array
    m_distances.resize(m_gearRays->size());
    m_gearColor = new vector<hpcolor>;
    m_gearColor->resize(m_gearRays->size());
    // Build kdtree
    m_kdTree = new KDTree(m_discMesh->toTriangles());
}

DiscGearGrind::~DiscGearGrind() {
    delete m_gearColor;
    delete m_gearRays;
    delete m_kdTree;
}

void DiscGearGrind::calculateGrindingDepth(double time){
    hpmat4x4 matrix = m_gearMouvement.getMatrix(time);
    for( size_t i = 0; i < m_gearRays->size(); i++){
        // Transform Ray
        Ray ray = m_gearRays->at(i);
        ray.transform(matrix);
        ray.origin -= m_maxDistance * ray.direction;
        m_distances[i] = m_kdTree->intersectFirst(ray, m_maxDistance * 2);
    }
}


SimulationResult DiscGearGrind::getDisplay(double time){
    calculateGrindingDepth(time);
    // Fill color
    for( size_t i = 0; i < m_distances.size(); i++){
    	m_gearColor->at(i) = hpcolor(m_distances[i] / m_maxDistance, 0.5, 1.0, 1.0);
    }
//    // Transform disc ethen though gear is actually mouving
//    //glm::mat4 tempMat = glm::inverse(m_gearMouvement.getMatrix(time));
//    glm::mat4 tempMat = m_gearMouvement.getMatrix(time);
//    m_gearMesh->setModelMatrix(QMatrix4x4(tempMat[0][0], tempMat[1][0], tempMat[2][0], tempMat[3][0],
//                                          tempMat[0][1], tempMat[1][1], tempMat[2][1], tempMat[3][1],
//                                          tempMat[0][2], tempMat[1][2], tempMat[2][2], tempMat[3][2],
//                                          tempMat[0][3], tempMat[1][3], tempMat[2][3], tempMat[3][3]));
    return SimulationResult(m_gearColor, m_gearMesh, m_discMesh);
}
