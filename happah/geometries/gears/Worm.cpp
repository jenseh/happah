#include "happah/geometries/gears/Worm.h"

Worm::Worm(hpuint toothCount, hpreal module, hpreal pressureAngle, hpuint rotations, hpreal faceWidth)
	: Geometry(), m_toothCount(toothCount), m_module(module), m_pressureAngle(pressureAngle), m_rotations(rotations)
{
  m_standardProfile = NULL;

  updateValues();
}

Worm::~Worm() {
    delete m_standardProfile;
}


std::vector<hpvec3>* Worm::createVertexData() {
    // Create result vectors
    std::vector<hpvec3>* vertexData = new std::vector<hpvec3>();
    
    
    std::vector<hpvec2> profileTooth = std::vector<hpvec2>();
    profileTooth.reserve(m_pointsPerTooth);
    m_standardProfile->getProfilePartition(profileTooth);

    
    for(hpuint angleStep = 0; angleStep < m_angleResolution; angleStep++) {
      hpreal angleRatio     = (hpreal)  angleStep      / m_angleResolution;
      hpreal nextAngleRatio = (hpreal) (angleStep + 1) / m_angleResolution;
      
      hpreal angle     = angleRatio     * 2.0 * M_PI;
      hpreal nextAngle = nextAngleRatio * 2.0 * M_PI;
      
      for (hpuint tooth = 0; tooth < m_toothCount; tooth++) {
//        hpreal toothRatio = (hpreal) tooth / m_toothCount;
        
        for (hpuint posZIdx = 0; posZIdx < m_pointsPerTooth; posZIdx++) {
//          hpreal pointRatio     = (hpreal) posZIdx       / m_pointsPerTooth;
          hpreal nextPointRatio = (hpreal) (posZIdx + 1) / m_pointsPerTooth;
          
          hpuint angleOffset     = angleRatio     * m_pointsPerTooth * m_rotations;
          hpuint nextAngleOffset = nextAngleRatio * m_pointsPerTooth * m_rotations;
        
          hpvec2 profilePointRZ = profileTooth.at((posZIdx + angleOffset) % m_pointsPerTooth);
          hpvec2 profilePointRN = profileTooth.at((posZIdx + angleOffset + 1) % m_pointsPerTooth);
          hpvec2 profilePointNZ = profileTooth.at((posZIdx + nextAngleOffset) % m_pointsPerTooth);
          hpvec2 profilePointNN = profileTooth.at((posZIdx + nextAngleOffset + 1) % m_pointsPerTooth);
          
          hpreal radiusRZ = m_radius + profilePointRZ.y;
          hpreal radiusRN = m_radius + profilePointRN.y;
          hpreal radiusNZ = m_radius + profilePointNZ.y;
          hpreal radiusNN = m_radius + profilePointNN.y;
          
          hpreal posZTooth = tooth * m_module * M_PI;
          hpreal nextPosZTooth = (tooth + (hpuint) nextPointRatio) * m_module * M_PI;
          
          hpreal posZ_RZ = posZTooth + profileTooth.at(posZIdx).x;
          hpreal posZ_RN = nextPosZTooth + profileTooth.at((posZIdx + 1) % m_pointsPerTooth).x;
          
          hpvec3 pointRZ = hpvec3(radiusRZ * cos(angle),     radiusRZ * sin(angle),     posZ_RZ);
          hpvec3 pointRN = hpvec3(radiusRN * cos(angle),     radiusRN * sin(angle),     posZ_RN);
          hpvec3 pointNZ = hpvec3(radiusNZ * cos(nextAngle), radiusNZ * sin(nextAngle), posZ_RZ);
          hpvec3 pointNN = hpvec3(radiusNN * cos(nextAngle), radiusNN * sin(nextAngle), posZ_RN);
          
          // TODO: create real normals
          hpvec2 normalTempRZ = glm::normalize(hpvec2(pointRZ.x, pointRZ.y));
          hpvec2 normalTempRN = glm::normalize(hpvec2(pointRZ.x, pointRZ.y));
          hpvec2 normalTempNZ = glm::normalize(hpvec2(pointRZ.x, pointRZ.y));
          hpvec2 normalTempNN = glm::normalize(hpvec2(pointRZ.x, pointRZ.y));
          
          hpvec3 normalRZ = hpvec3(normalTempRZ.x, normalTempRZ.y, 0.0);
          hpvec3 normalRN = hpvec3(normalTempRN.x, normalTempRN.y, 0.0);
          hpvec3 normalNZ = hpvec3(normalTempNZ.x, normalTempNZ.y, 0.0);
          hpvec3 normalNN = hpvec3(normalTempNN.x, normalTempNN.y, 0.0);
          
          // Push points in counter clockwise direction
          vertexData->push_back(pointRN);
          vertexData->push_back(normalRZ);
          vertexData->push_back(pointRZ);
          vertexData->push_back(normalRZ);
          vertexData->push_back(pointNZ);
          vertexData->push_back(normalNZ);
          
          vertexData->push_back(pointNZ);
          vertexData->push_back(normalNZ);
          vertexData->push_back(pointNN);
          vertexData->push_back(normalNN);
          vertexData->push_back(pointRN);
          vertexData->push_back(normalRN);
        }
      }
    }

    return vertexData;
}

hpreal Worm::getToothCount() {
	return m_toothCount;
}
hpreal Worm::getModule() {
	return m_module;
}
hpreal Worm::getPressureAngle() {
	return m_pressureAngle;
}

hpreal Worm::getRotations() {
	return m_rotations;
}

void Worm::setToothCount(hpreal toothCount) {
	m_toothCount = toothCount;
	updateValues();
}
void Worm::setModule(hpreal module) {
	m_module = module;
	updateValues();
}
void Worm::setPressureAngle(hpreal pressureAngle) {
	m_pressureAngle = pressureAngle;
	updateValues();
}

void Worm::setRotations(hpreal rotations) {
	m_rotations = rotations;
	updateValues();
}

TriangleMesh* Worm::toTriangleMesh() {
    std::vector<hpvec3>* vertexData = createVertexData();
    std::vector<hpuint>* indices = new std::vector<hpuint>();
    hpuint indexCount =  vertexData->size() / 2;
    indices->reserve(indexCount);
    for (hpuint index = 0; index < indexCount; index++) {
    	indices->push_back(index);
    }
    TriangleMesh* result = new TriangleMesh(vertexData, indices);
    return result;
}

ZCircleCloud* Worm::toZCircleCloud() {
	hpreal maxRadius = m_radius + m_standardProfile->getMaxHeight();
	hpreal startZ = 0.0;
	hpreal endZ = m_toothCount * m_module * M_PI;

	// Determine resolution (important for following simulations)
	hpuint resolutionZ = m_toothCount * m_pointsPerTooth;

	hpvec3 referenceDir = hpvec3(1.0, 0.0, 0.0);

	ZCircleCloud* result = new ZCircleCloud(maxRadius, startZ, endZ, resolutionZ, referenceDir);
	return result;
}

void Worm::updateValues(){
	m_radius = 3.0 * m_module * m_toothCount / 2.0;
    if( m_standardProfile != NULL )
    	delete m_standardProfile;
    m_standardProfile = new StandardProfile(m_module, m_pressureAngle, 0.0, 0.0);
}
