#ifndef FILE_DIALOG_H
#define FILE_DIALOG_H

#include <QFileDialog>

#include "happah/HappahTypes.h"

class FileDialog : public QFileDialog {
Q_OBJECT

public:
	enum ContentTypes {
		WAVEFRONT_TRIANGLE_MESH_3D = 0x00000001
	};
	static hpuint getContentType(QString& path);

	FileDialog(const char* title, QWidget* parent = 0);
	~FileDialog();

	void setNameFilters(hpuint contentTypes);

private:
	static const char* WAVEFRONT_TRIANGLE_MESH_3D_FILTER;

};

#endif //FILE_DIALOG_H
