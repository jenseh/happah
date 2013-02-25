#include "happah/simulations/DiscGearGrind.h"

DiscGearGrind::DiscGearGrind(Disc* disc, Gear* gear):
    m_disc(disc), m_gear(gear)
{
    m_gearMouvement = Kinematic::getLinearKinematic(glm::vec3(0,-m_disc->getRadius(),  -m_disc->getRadius()),
                                                    glm::vec3(0, -m_disc->getRadius(), m_disc->getRadius()));
    // Convert to right representation
    m_discMesh = m_disc->toQuadMesh()->toTriangleMesh();
    m_gearMesh = m_gear->toQuadMesh()->toTriangleMesh(); // TODO: m_gear->toTriangle does not work!?
    m_gearRays = *m_gearMesh->toRayCloud()->getRays();
    // resize distances array
    m_distances.resize(m_gearRays.size());
    m_discMesh->setColor(0.2,0.5,0.5,0.5);
    // Add color Array
    vector<Color> colorData(m_distances.size());
    m_gearMesh->setColorData(colorData);
    // Build kdtree
    m_kdTree.build(*m_discMesh);


}

DiscGearGrind::~DiscGearGrind() {
    delete m_discMesh;
    delete m_gearMesh;
    for(size_t i = 0; i < m_gearRays.size(); i++){
        delete m_gearRays[i];
    }
}

void DiscGearGrind::calculateGrindingDepth(double time){
    glm::mat4 matrix = m_gearMouvement.getMatrix(time);
    for( size_t i = 0; i < m_gearRays.size(); i++){
        // Transform Ray
        Ray ray = *m_gearRays[i];
        ray.transform(matrix);
        Ray inverseRay = ray;
        inverseRay.direction = ray.inverse_direction;
        inverseRay.inverse_direction = ray.direction;


        // Calculate Ray triangle intersection
        IntersectInfo info;
        m_distances[i] = 100;
        if( m_kdTree.intersect(inverseRay, info)){
            m_distances[i] = -glm::distance(inverseRay.origin , info.hit_point);
        }else if( m_kdTree.intersect(ray, info) ){
            m_distances[i] = glm::distance(ray.origin , info.hit_point);
        }
    }
}


pair<TriangleMesh*,TriangleMesh*> DiscGearGrind::getDisplay(double time){
    calculateGrindingDepth(time);
    // Fill color
    vector<Color>* colorData = m_gearMesh->getColorData();
    for( size_t i = 0; i < m_distances.size(); i++){
        (*colorData)[i].green = 0.5;
        //(*colorData)[i].red = min((*colorData)[i].red, (float)(m_distances[i]*0.2));
        (*colorData)[i].red = m_distances[i];
    }
    // Transform disc ethen though gear is actually mouving
    //glm::mat4 tempMat = glm::inverse(m_gearMouvement.getMatrix(time));
    glm::mat4 tempMat = m_gearMouvement.getMatrix(time);
    m_gearMesh->setModelMatrix(QMatrix4x4(tempMat[0][0], tempMat[1][0], tempMat[2][0], tempMat[3][0],
                                          tempMat[0][1], tempMat[1][1], tempMat[2][1], tempMat[3][1],
                                          tempMat[0][2], tempMat[1][2], tempMat[2][2], tempMat[3][2],
                                          tempMat[0][3], tempMat[1][3], tempMat[2][3], tempMat[3][3]));
    return pair<TriangleMesh*,TriangleMesh*>(m_gearMesh, m_discMesh);
}
