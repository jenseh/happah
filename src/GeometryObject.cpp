/*
 * GeometryObject.cpp
 *
 *  Created on: Oct 24, 2012
 *      Author: matthias
 */

#include "GeometryObject.h"

GeometryObject::GeometryObject(QWidget *parent) {
	// TODO Auto-generated constructor stub

}

GeometryObject::~GeometryObject() {
	// TODO Auto-generated destructor stub
}

// Prepare Vertex and Index Buffer to be filled with Data


int GeometryObject::InitVertexBuffer(enum QGLBuffer::UsagePattern usagePattern){


	vertexBuffer.create();
	vertexBuffer.setUsagePattern(usagePattern);
	if (!vertexBuffer.bind()) {
			qWarning() << "Could not bind vertex buffer";
			return -1;
	}
	return 0;
}

int GeometryObject::FillVertexBuffer(){
	if (!vertexBuffer.isCreated()){
		qWarning() << " Vertex Buffer does not exist yet";
		return -1;
	}
	if (!vertexBuffer.bind()) {
				qWarning() << "Could not bind vertex buffer";
				return -1;
	}
	vertexBuffer.allocate(&(vertexData[0]),vertexData.size()*sizeof(vertexData[0]));
	return 0;
}
// Just in here for simplicity remove later to some Basic Setup Object or whatever

void GeometryObject::CreateGrid(){
	for (float x = -2.0; x <= 2.0; x = x + 0.5f) {
		for (float z = -2.0f; z <= 2.0f; z = z + 0.5f) {
			vertexData.push_back(glm::vec4(x, -1.0f, -2.0, 1.0f));
			vertexData.push_back(glm::vec4(x, -1.0f, 2.0, 1.0f));
			vertexData.push_back(glm::vec4(-2.0f, -1.0f, z, 1.0f));
			vertexData.push_back(glm::vec4(2.0f, -1.0f, z, 1.0f));

		}
	}


}
void GeometryObject::DrawArrays(int mode,int stride){
	vertexBuffer.bind();
	glDrawArrays(mode,stride,vertexData.size());
}

int GeometryObject::BindVBuffer(){
	if (!vertexBuffer.bind()) {
			qWarning() << "Could not bind vertex buffer";
			return -1;
	}
	return 0;

}

void GeometryObject::CreateVertexData(){

}

void GeometryObject::DataPushback(glm::vec4 data){
	vertexData.push_back(data);
}
