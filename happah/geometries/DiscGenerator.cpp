#include "DiscGenerator.h"



SurfaceOfRevolution_ptr DiscGenerator::generateDiscFrom(Gear& gear) {
    std::vector<hpvec2> vertexData;
    vertexData.reserve(100);
    gear.getToothSpaceProfile(vertexData);
    return SurfaceOfRevolution_ptr(new SurfaceOfRevolution(vertexData));
}

SurfaceOfRevolution_ptr DiscGenerator::generateDiscFrom(StandardProfile profile) {
    std::vector<hpvec2> vertexData;
    vertexData.reserve(100);
    profile.getProfilePartition(vertexData);
    return SurfaceOfRevolution_ptr(new SurfaceOfRevolution(vertexData));
}
