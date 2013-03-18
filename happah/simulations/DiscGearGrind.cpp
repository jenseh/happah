#include "happah/simulations/DiscGearGrind.h"

DiscGearGrind::DiscGearGrind(Disc_ptr disc, SimpleGear_ptr gear):
	m_disc(disc), m_gear(gear), m_maxDistance(1.0)
{
    m_gearMovement = Kinematic::getLinearKinematic(glm::vec3(0,-m_disc->getRadius(),  -m_disc->getRadius()),
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
    hpmat4x4 matrix = m_gearMovement.getMatrix(time);
    for( size_t i = 0; i < m_gearRays->size(); i++){
        // Transform Ray
        Ray ray = m_gearRays->at(i);
        ray.transform(matrix);
        ray.moveOrigin(-m_maxDistance);
        m_distances[i] = m_kdTree->intersectFirst(ray, m_maxDistance * 2);
    }
}


DiscGearGrindResult DiscGearGrind::getSimulationResult(double time){
    calculateGrindingDepth(time);
    // Fill color
    for( size_t i = 0; i < m_gearColor->size(); i++){
    	//TODO: @ Julian: Be aware, your distances are all in [0; 2*m_maxDistance], you should change that in calculateGrindingDepth
    	m_gearColor->at(i) = hpcolor(1.0, 0.0, 0.0, 1.0); //hpcolor(m_distances[i] / m_maxDistance * 2, 0.5, 1.0, 1.0);
    	if (i > (int)m_gearColor->size() * 0.9
    	||  i < (int)m_gearColor->size() * 0.1) m_gearColor->at(i) = hpcolor(0.0, 0.0, 1.0, 1.0);
    }
    return DiscGearGrindResult(m_gear, m_gearColor, m_gearMesh, m_gearMovement.getRigidAffineTransformation(time),  m_disc, m_discMesh, RigidAffineTransformation());
}

void DiscGearGrind::runSimulation(){

}
