#include "happah/simulations/DiscGearGrind.h"

DiscGearGrind::DiscGearGrind(Disc_ptr disc, TriangleMesh_ptr discMesh, SimpleGear_ptr gear, TriangleMesh_ptr gearMesh):
	m_disc(disc), m_discMesh(discMesh), m_gear(gear), m_gearMesh(gearMesh), m_maxDistance(0.2)
{
    m_gearMovement = Kinematic::getLinearKinematic(glm::vec3(0,-m_disc->getRadius() - m_gear->getBottomRadius(),  -m_disc->getRadius()),
                                                    glm::vec3(0, -m_disc->getRadius() - m_gear->getBottomRadius(), m_disc->getRadius()));
    // Convert to right representation
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
        m_distances[i] = (m_kdTree->intersectFirst(ray, m_maxDistance * 2) - m_maxDistance) / m_maxDistance;
    }
}


DiscGearGrindResult DiscGearGrind::getSimulationResult(double time){
    calculateGrindingDepth(time);
    // Fill color
    for( size_t i = 0; i < m_gearColor->size(); i++){
    	if( m_distances[i] < 0 ){
    		m_gearColor->at(i) = hpcolor(1.0,0.0,0.0,1.0);
    	}else if( m_distances[i] < 0.99){
    		m_gearColor->at(i) = hpcolor(0.0,1.0,0.0,1.0);
    	}else{
    		m_gearColor->at(i) = hpcolor(1.0,1.0,1.0,1.0);
    	}
    	/*
    	if( m_distances[i] >= 0 ){
    		m_gearColor->at(i) = hpcolor(0.0, 1.0, 0.0, 1.0);
    		m_gearColor->at(i) = hpcolor( 0.0, m_distances[i], 1.0, 1.0);
    	}else{
    		m_gearColor->at(i) = hpcolor(1.0, 0.0, 0.0, 1.0);
    		m_gearColor->at(i) = hpcolor(1.0, 1.0 + m_distances[i], 1.0 + m_distances[i], 1.0);
    	}
    	*/
    }
    return DiscGearGrindResult(m_gear, m_gearColor, m_gearMesh,  m_gearMovement.getRigidAffineTransformation(time),  m_disc, m_discMesh, RigidAffineTransformation());
}

void DiscGearGrind::runSimulation(){

}
