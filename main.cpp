#include "imagetransform01.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	ImageTransform01 w;
	w.show();
	return a.exec();
}
