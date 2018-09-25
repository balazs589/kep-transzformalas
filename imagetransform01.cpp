#include "imagetransform01.h"
#include <QFileDialog>

ImageTransform01::ImageTransform01(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);

	scene = new QGraphicsScene(this);
	ui.graphicsView->setScene(scene);

	picture_eredeti=nullptr;
	picture_szerkesztett=nullptr;
	
	connect( ui.pushButton_beolvas, SIGNAL(clicked()), this, SLOT(beolvas()) );
	connect( ui.pushButton_transform, SIGNAL(clicked()), this, SLOT(transzformal()) );
	connect( ui.checkBox_eredeti, SIGNAL(clicked()), this, SLOT(eredetit_megjelenit()) );
}

ImageTransform01::~ImageTransform01()
{

}

void ImageTransform01::beolvas()
{
	ui.checkBox_eredeti->setChecked(false);
	ui.checkBox_eredeti->setEnabled(false);

	if(picture_eredeti!=nullptr)
	{
		scene->removeItem(picture_eredeti);
		delete picture_eredeti;
		picture_eredeti = nullptr;
	}

	if(picture_szerkesztett!=nullptr)
	{
		scene->removeItem(picture_szerkesztett);
		delete picture_szerkesztett;
		picture_szerkesztett = nullptr;
	}
	
	QPixmap pixmap(QFileDialog::getOpenFileName());
	//QPixmap pixmap(":/ImageTransform01/Resources/picture01.jpg");
	picture_eredeti = scene->addPixmap(pixmap);
	picture_eredeti->setZValue(2);
	picture_eredeti->hide();
	
	picture_szerkesztett = scene->addPixmap(pixmap);
	picture_szerkesztett->setZValue(1);
	picture_szerkesztett->show();	

	ui.pushButton_transform->setEnabled(true);
}

void ImageTransform01::transzformal()
{
	if(picture_szerkesztett!=nullptr)
	{
		QImage image_1 = picture_szerkesztett->pixmap().toImage();
		
		QImage* p_image_2 = kiegeszitett_kep(&image_1);
		QImage* p_image_3 = transzformalt_kep(p_image_2);

		QPixmap pixmap = QPixmap::fromImage(*p_image_3);

		picture_szerkesztett->setPixmap(pixmap);

		ui.checkBox_eredeti->setEnabled(true);

		delete p_image_2;
		delete p_image_3;
	}
}




void ImageTransform01::eredetit_megjelenit()
{
	if(ui.checkBox_eredeti->isChecked()) picture_eredeti->show();
	if(!ui.checkBox_eredeti->isChecked()) picture_eredeti->hide();
}

QImage* ImageTransform01::kiegeszitett_kep(QImage* p_image_1)
{
	QImage* p_image_2 = new QImage(p_image_1->size().width()+2, p_image_1->size().height()+2, p_image_1->format());
	
	for(int y=1;y<p_image_2->size().height()-1;y++)
	{
		for(int x=1;x<p_image_2->size().width()-1;x++)
		{
			p_image_2->setPixel(x,y,p_image_1->pixel(x-1,y-1));
		}
	}

	for(int x=0;x<p_image_2->size().width();x++)
	{
		p_image_2->setPixel(x,0, qRgb(0,0,0));
		p_image_2->setPixel(x,p_image_2->size().height()-1, qRgb(0,0,0));
	}


	for(int y=0;y<p_image_2->size().height();y++)
	{
		p_image_2->setPixel(0,y, qRgb(0,0,0));
		p_image_2->setPixel(p_image_2->size().width()-1,y, qRgb(0,0,0));
	}


	for(int x=1;x<p_image_2->size().width()-1;x++)
	{
		p_image_2->setPixel(x,0,p_image_1->pixel(x-1,0));
		p_image_2->setPixel(x,p_image_2->size().height()-1,p_image_1->pixel(x-1,p_image_1->size().height()-1));
	}

	for(int y=1;y<p_image_2->size().height()-1;y++)
	{
		p_image_2->setPixel(0,y,p_image_1->pixel(0,y-1));
		p_image_2->setPixel(p_image_2->size().width()-1,y,p_image_1->pixel(p_image_1->size().width()-1,y-1));
	}

	p_image_2->setPixel(0,0,p_image_1->pixel(0,0));
	p_image_2->setPixel(p_image_2->size().width()-1,0,p_image_1->pixel(p_image_1->size().width()-1,0));
	p_image_2->setPixel(0,p_image_2->size().height()-1,p_image_1->pixel(0,p_image_1->size().height()-1));
	p_image_2->setPixel(p_image_2->size().width()-1,p_image_2->size().height()-1,p_image_1->pixel(p_image_1->size().width()-1,p_image_1->size().height()-1));
	
	return p_image_2;
}



QImage* ImageTransform01::transzformalt_kep(QImage* p_image_2)
{
	double matrix[3][3];
	matrix[0][0]=ui.lineEdit_11->text().toDouble();
	matrix[0][1]=ui.lineEdit_12->text().toDouble();
	matrix[0][2]=ui.lineEdit_13->text().toDouble();
	
	matrix[1][0]=ui.lineEdit_21->text().toDouble();
	matrix[1][1]=ui.lineEdit_22->text().toDouble();
	matrix[1][2]=ui.lineEdit_23->text().toDouble();
	
	matrix[2][0]=ui.lineEdit_31->text().toDouble();
	matrix[2][1]=ui.lineEdit_32->text().toDouble();
	matrix[2][2]=ui.lineEdit_33->text().toDouble();

	QImage* p_image_3 = new QImage(p_image_2->size().width()-2, p_image_2->size().height()-2, p_image_2->format());

	for(int y=0;y<p_image_3->size().height();y++)
	{
		for(int x=0;x<p_image_3->size().width();x++)
		{
			int red, green, blue;

			double RED=0.0, GREEN=0.0, BLUE=0.0;


			QRgb szin[3][3];
			
			szin[0][0] = p_image_2->pixel(x,y);
			szin[0][1] = p_image_2->pixel(x+1,y);
			szin[0][2] = p_image_2->pixel(x+2,y);

			szin[1][0] = p_image_2->pixel(x,y+1);
			szin[1][1] = p_image_2->pixel(x+1,y+1);
			szin[1][2] = p_image_2->pixel(x+2,y+1);

			szin[2][0] = p_image_2->pixel(x,y+2);
			szin[2][1] = p_image_2->pixel(x+1,y+2);
			szin[2][2] = p_image_2->pixel(x+2,y+2);


			for(int iii=0;iii<3;iii++)
			{
				for(int jjj=0;jjj<3;jjj++)
				{
					RED += qRed(szin[iii][jjj])*matrix[iii][jjj];
				}
			}

			if(RED<0) RED=0;
			if(RED>255) RED=255;
			red = static_cast<int>(RED+0.5);


			for(int iii=0;iii<3;iii++)
			{
				for(int jjj=0;jjj<3;jjj++)
				{
					GREEN += qGreen(szin[iii][jjj])*matrix[iii][jjj];
				}
			}

			if(GREEN<0) GREEN=0;
			if(GREEN>255) GREEN=255;
			green = static_cast<int>(GREEN+0.5);


			for(int iii=0;iii<3;iii++)
			{
				for(int jjj=0;jjj<3;jjj++)
				{
					BLUE += qBlue(szin[iii][jjj])*matrix[iii][jjj];
				}
			}

			if(BLUE<0) BLUE=0;
			if(BLUE>255) BLUE=255;
			blue = static_cast<int>(BLUE+0.5);

			
			p_image_3->setPixel(x,y,qRgb(red, green, blue));
		}
	}
	
	return p_image_3;
}
