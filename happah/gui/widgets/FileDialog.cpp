#include "happah/gui/widgets/FileDialog.h"

const char* FileDialog::WAVEFRONT_TRIANGLE_MESH_3D_FILTER = "Wavefront Triangle Mesh 3D (*.triangle.mesh.3d.obj)";

FileDialog::FileDialog(const char* title, QWidget* parent) : QFileDialog(parent) {
	setWindowTitle(tr(title));
}

FileDialog::~FileDialog() {}

hpuint FileDialog::getContentType(QString& path) {
	QFileInfo pathInfo(path);
	if(!pathInfo.isDir()) {
		QString completeSuffix = pathInfo.completeSuffix();
		if(completeSuffix.compare("triangle.mesh.3d.obj", Qt::CaseInsensitive) == 0)
			return WAVEFRONT_TRIANGLE_MESH_3D;
	}
	return 0;
}

void FileDialog::setNameFilters(hpuint contentTypes) {
	QStringList filters;
	if(contentTypes && FileDialog::WAVEFRONT_TRIANGLE_MESH_3D)
		filters << FileDialog::WAVEFRONT_TRIANGLE_MESH_3D_FILTER;
	QFileDialog::setNameFilters(filters);
}
