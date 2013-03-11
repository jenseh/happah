#include "Worm.h"

Worm::Worm(hpuint toothCount, hpreal module, hpreal pressureAngle, hpuint rotations)
{
  m_toothCount = toothCount;
  m_module = module;
  m_pressureAngle = pressureAngle;
  m_rotations = rotations;
  
  m_radius = 3.0 * m_module * m_toothCount / 2.0;
}

Worm::~Worm() {}


std::vector<hpvec3>* Worm::createVertexData() {
    // Create result vectors
    std::vector<hpvec3>* vertexData = new std::vector<hpvec3>();
    
    // TODO: Where should resolution attributes go?
    hpuint angleResolution = 200;
    hpuint pointsPerTooth = 200;
    
    std::vector<hpvec2> profileTooth = std::vector<hpvec2>();

    StandardProfile* standardProfile = new StandardProfile(m_module, m_pressureAngle, 0.0, 0.0);
    standardProfile->getProfilePartition(profileTooth, pointsPerTooth);

    
    for(hpuint angleStep = 0; angleStep < angleResolution; angleStep++) {
      hpreal angleRatio     = (hpreal)  angleStep      / angleResolution;
      hpreal nextAngleRatio = (hpreal) (angleStep + 1) / angleResolution;
      
      hpreal angle     = angleRatio     * 2.0 * M_PI;
      hpreal nextAngle = nextAngleRatio * 2.0 * M_PI;
      
      for (hpuint tooth = 0; tooth < m_toothCount; tooth++) {
        hpreal toothRatio = (hpreal) tooth / m_toothCount;
        
        for (hpuint posZIdx = 0; posZIdx < pointsPerTooth; posZIdx++) {
          hpreal pointRatio     = (hpreal) posZIdx       / pointsPerTooth;
          hpreal nextPointRatio = (hpreal) (posZIdx + 1) / pointsPerTooth;
          
          hpuint angleOffset     = angleRatio     * pointsPerTooth;
          hpuint nextAngleOffset = nextAngleRatio * pointsPerTooth;          
        
          hpvec2 profilePointRZ = profileTooth.at((posZIdx + angleOffset) % pointsPerTooth);
          hpvec2 profilePointRN = profileTooth.at((posZIdx + angleOffset + 1) % pointsPerTooth);
          hpvec2 profilePointNZ = profileTooth.at((posZIdx + nextAngleOffset) % pointsPerTooth);
          hpvec2 profilePointNN = profileTooth.at((posZIdx + nextAngleOffset + 1) % pointsPerTooth);
          
          hpreal radiusRZ = m_radius + profilePointRZ.y;
          hpreal radiusRN = m_radius + profilePointRN.y;
          hpreal radiusNZ = m_radius + profilePointNZ.y;
          hpreal radiusNN = m_radius + profilePointNN.y;
          
          hpreal posZTooth = tooth * m_module * M_PI;
          hpreal nextPosZTooth = (tooth + (hpuint) nextPointRatio) * m_module * M_PI;
          
          hpreal posZ_RZ = posZTooth + profileTooth.at(posZIdx).x;
          hpreal posZ_RN = nextPosZTooth + profileTooth.at((posZIdx + 1) % pointsPerTooth).x;
          
          hpvec3 pointRZ = hpvec3(radiusRZ * cos(angle),     radiusRZ * sin(angle),     posZ_RZ, 1.0);
          hpvec3 pointRN = hpvec3(radiusRN * cos(angle),     radiusRN * sin(angle),     posZ_RN, 1.0);
          hpvec3 pointNZ = hpvec3(radiusNZ * cos(nextAngle), radiusNZ * sin(nextAngle), posZ_RZ, 1.0);
          hpvec3 pointNN = hpvec3(radiusNN * cos(nextAngle), radiusNN * sin(nextAngle), posZ_RN, 1.0);
          
          // TODO: create real normals
          hpvec2 normalTempRZ = glm::normalize(hpvec2(pointRZ.x, pointRZ.y));
          hpvec2 normalTempRN = glm::normalize(hpvec2(pointRZ.x, pointRZ.y));
          hpvec2 normalTempNZ = glm::normalize(hpvec2(pointRZ.x, pointRZ.y));
          hpvec2 normalTempNN = glm::normalize(hpvec2(pointRZ.x, pointRZ.y));
          
          hpvec3 normalRZ = hpvec3(normalTempRZ.x, normalTempRZ.y, 0.0, 1.0);
          hpvec3 normalRN = hpvec3(normalTempRN.x, normalTempRN.y, 0.0, 1.0);
          hpvec3 normalNZ = hpvec3(normalTempNZ.x, normalTempNZ.y, 0.0, 1.0);
          hpvec3 normalNN = hpvec3(normalTempNN.x, normalTempNN.y, 0.0, 1.0);
          
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

TriangleMesh* Worm::toTriangleMesh() {
    std::vector<hpvec3>* vertexData = createVertexData();
    std::vector<hpuint>* indices = new std::vector<hpuint>();
    for (hpuint index = 0; index < vertexData->size()/2; index++) {
    	indices->at(index) = index;
    }
    TriangleMesh* result = new TriangleMesh(vertexData, indices);
    return result;
}
