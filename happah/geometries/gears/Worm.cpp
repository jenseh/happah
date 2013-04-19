#include "happah/geometries/gears/Worm.h"

Worm::Worm(hpuint toothCount, hpreal module, hpreal pressureAngle, hpreal rotations, hpreal baseRadius)
	: Geometry(), m_toothCount(toothCount), m_module(module), m_pressureAngle(pressureAngle), m_rotations(rotations), m_baseRadius(baseRadius)
{
  m_standardProfile = NULL;

  updateValues();
}

Worm::~Worm() {
    delete m_standardProfile;
}


std::vector<hpvec3>* Worm::createVerticesAndNormals(hpuint pointsPerTooth, hpuint angleResolution) {
    // Create result vectors
    std::vector<hpvec3>* verticesAndNormals = new std::vector<hpvec3>();
    
    
    std::vector<hpvec2> profileTooth = std::vector<hpvec2>();
    profileTooth.reserve(pointsPerTooth);
    m_standardProfile->getProfilePartition(profileTooth);

    
    for(hpuint angleStep = 0; angleStep < angleResolution; angleStep++) {
      hpreal angleRatio     = (hpreal)  angleStep      / angleResolution;
      hpreal nextAngleRatio = (hpreal) (angleStep + 1) / angleResolution;
      
      hpreal angle     = angleRatio     * 2.0 * M_PI;
      hpreal nextAngle = nextAngleRatio * 2.0 * M_PI;
      
      for (hpuint tooth = 0; tooth < m_toothCount; tooth++) {
        
        for (hpuint posZIdx = 0; posZIdx < pointsPerTooth; posZIdx++) {
          hpreal nextPointRatio = (hpreal) (posZIdx + 1) / pointsPerTooth;
          
          hpuint angleOffset     = angleRatio     * pointsPerTooth * m_rotations;
          hpuint nextAngleOffset = nextAngleRatio * pointsPerTooth * m_rotations;
        
          hpvec2 profilePointRZ = profileTooth.at((posZIdx + angleOffset) % pointsPerTooth);
          hpvec2 profilePointRN = profileTooth.at((posZIdx + angleOffset + 1) % pointsPerTooth);
          hpvec2 profilePointNZ = profileTooth.at((posZIdx + nextAngleOffset) % pointsPerTooth);
          hpvec2 profilePointNN = profileTooth.at((posZIdx + nextAngleOffset + 1) % pointsPerTooth);
          
          hpreal radiusRZ = m_baseRadius + m_module + profilePointRZ.y;
          hpreal radiusRN = m_baseRadius + m_module + profilePointRN.y;
          hpreal radiusNZ = m_baseRadius + m_module + profilePointNZ.y;
          hpreal radiusNN = m_baseRadius + m_module + profilePointNN.y;
          
          hpreal posZ_RZ = m_module * M_PI * tooth 							   + profileTooth.at(posZIdx).x;
          hpreal posZ_RN = m_module * M_PI * (tooth + (hpuint) nextPointRatio) + profileTooth.at((posZIdx + 1) % pointsPerTooth).x;
          
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
          verticesAndNormals->push_back(pointRN);
          verticesAndNormals->push_back(normalRZ);
          verticesAndNormals->push_back(pointRZ);
          verticesAndNormals->push_back(normalRZ);
          verticesAndNormals->push_back(pointNZ);
          verticesAndNormals->push_back(normalNZ);
          
          verticesAndNormals->push_back(pointNZ);
          verticesAndNormals->push_back(normalNZ);
          verticesAndNormals->push_back(pointNN);
          verticesAndNormals->push_back(normalNN);
          verticesAndNormals->push_back(pointRN);
          verticesAndNormals->push_back(normalRN);
        }
      }
    }

    return verticesAndNormals;
}

hpuint Worm::getToothCount() {
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

hpreal Worm::getBaseRadius() {
	return m_baseRadius;
}

hpreal Worm::getReferenceRadius() {
	return m_baseRadius + m_module;
}

hpreal Worm::getMaxRadius() {
	return m_baseRadius + 2.0 * m_module;
}

void Worm::setToothCount(hpuint toothCount) {
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


void Worm::setBaseRadius(hpreal baseRadius) {
	m_baseRadius = baseRadius;
	updateValues();
}

TriangleMesh_ptr Worm::toTriangleMesh(hpuint pointsPerTooth, hpuint angleResolution) {
    std::vector<hpvec3>* verticesAndNormals = createVerticesAndNormals(pointsPerTooth, angleResolution);
    std::vector<hpuint>* indices = new std::vector<hpuint>();
    hpuint indexCount =  verticesAndNormals->size() / 2;
    indices->reserve(indexCount);
    for (hpuint index = 0; index < indexCount; index++) {
    	indices->push_back(index);
    }
    TriangleMesh_ptr result = TriangleMesh_ptr(new TriangleMesh(verticesAndNormals, indices));
    return result;
}

ZCircleCloud_ptr Worm::toZCircleCloud(hpuint pointsPerTooth) {
	hpreal maxRadius = getMaxRadius();
	hpreal startZ = 0.0;
	hpreal endZ = m_toothCount * m_module * M_PI;

	// Determine resolution (important for following simulations)
	hpuint resolutionZ = m_toothCount * pointsPerTooth;
	hpvec3 referenceDir = hpvec3(1.0, 0.0, 0.0);

	ZCircleCloud_ptr result = ZCircleCloud_ptr(new ZCircleCloud(maxRadius, startZ, endZ, resolutionZ, referenceDir));
	return result;
}

void Worm::updateValues() {
    if( m_standardProfile != NULL )
    	delete m_standardProfile;
    m_standardProfile = new StandardProfile(m_module, m_pressureAngle, 0.0, 0.0);
}
