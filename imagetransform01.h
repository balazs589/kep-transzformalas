#ifndef IMAGETRANSFORM01_H
#define IMAGETRANSFORM01_H

#include <QtWidgets/QMainWindow>
#include "ui_imagetransform01.h"

#include <QtCore>
#include <QtGui>
//project properties -> C/C++ -> General -> Additional include directories -> $(QTDIR)\include\QtANGLE

#include <QPixmap>
#include <QGraphicsItem>


class ImageTransform01 : public QMainWindow
{
	Q_OBJECT


public:
	ImageTransform01(QWidget *parent = 0);
	~ImageTransform01();

public slots:
	void beolvas();
	void transzformal();
	void eredetit_megjelenit();

private:
	
	QImage* kiegeszitett_kep(QImage* p_image_1);
	QImage* transzformalt_kep(QImage* p_image_2);
	
	Ui::ImageTransform01Class ui;

	QGraphicsScene *scene;
	QGraphicsPixmapItem *picture_eredeti;
	QGraphicsPixmapItem *picture_szerkesztett;

	
};

#endif // IMAGETRANSFORM01_H
