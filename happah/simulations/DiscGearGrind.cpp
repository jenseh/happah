#include "happah/simulations/DiscGearGrind.h"

DiscGearGrind::DiscGearGrind(SurfaceOfRevolution_ptr disc, TriangleMesh_ptr discMesh, SimpleGear_ptr gear, TriangleMesh_ptr gearMesh):
	m_disc(disc), m_discMesh(discMesh), m_gear(gear), m_gearMesh(gearMesh), m_maxDistance(0.1)
{
	hpreal alpha = m_gear->getHelixAngle();
	hpreal z = -m_gear->getFaceWidth();
	hpreal y = -m_disc->getRadius() - m_gear->getRootRadius();
	hpvec3 start = hpvec3(0, y,  0);
	hpvec3 end = hpvec3(sin(alpha) * z, y, z);
    m_gearMovement = Kinematic::getLinearKinematic(start, end, -alpha / M_PI * 180);
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

        m_distances[i] = 2 * m_maxDistance;
        m_distances[i] = (m_kdTree->intersectFirst(ray, m_maxDistance * 2) - m_maxDistance) / m_maxDistance;
    }
}


DiscGearGrindResult DiscGearGrind::calculateSimulationResult(double time){
    calculateGrindingDepth(time);
    // Fill color
    for( size_t i = 0; i < m_gearColor->size(); i++){
    	if( m_distances[i] >= 0 ){
    		m_gearColor->at(i) = hpcolor( 0.0, m_distances[i], 1.0, 1.0);
    	}else{
            m_gearColor->at(i) = hpcolor(1.0, 1.0 + m_distances[i], 1.0 + m_distances[i], 1.0);
    	}
    }
    return DiscGearGrindResult(m_gear, m_gearColor, m_gearMesh,  RigidAffineTransformation(),  m_disc, m_discMesh, m_gearMovement.getRigidAffineTransformation(time).inverse());
}

DiscGearGrindResult DiscGearGrind::getSimulationResult(double time){
	map<hpreal,DiscGearGrindResult>::iterator it = m_precalcResults.lower_bound(time);
	if( it == m_precalcResults.end() ){
		it--;
	}
	return it->second;
}

void DiscGearGrind::runSimulation(){
    // "-1.0"because 0.0 and 1.0 have to be calculated.
    hpreal deltaT = 1.0 / ((hpreal)STEP_COUNT-1.0);
	m_precalcResults.clear();
	for( hpreal t = 0.0; t <= 1.0; t += deltaT ) {
		m_precalcResults.insert(pair<hpreal, DiscGearGrindResult>(t, calculateSimulationResult(t)));
	}
}
