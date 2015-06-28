﻿
#include "GLWidget.h"
#include <QKeyEvent>
#include <QTimer>



GLWidget::GLWidget(QWidget *parent)
	: QOpenGLWidget(parent)
{
	// loop call update
	QTimer *timer = new QTimer(this);
	connect(timer, SIGNAL(timeout()), this, SLOT(update()));
	timer->start(33);
}


GLWidget::~GLWidget()
{
	cleanup();
}


void GLWidget::cleanup()
{
	this->makeCurrent();
	//delete image_texture;
	this->doneCurrent();
}


void GLWidget::initializeGL()
{
	this->initializeOpenGLFunctions();

	// the default is /shaders from your running dir
	string shaders_dir("../../effects/shaders/");

	rendertexture.setShadersDir(shaders_dir);
	rendertexture.initialize();

	//// initialize texture with given image
	QImage image(":/images/camelo.jpg");

	for (int x = 0; x < image.width(); ++x)
	{
		for (int y = 0; y < image.height(); ++y)
		{
			QRgb orig = image.pixel(x, y);
			QRgb inv = qRgb(qBlue(orig), qGreen(orig), qRed(orig));
			image.setPixel(x, y, inv);
		}
	}

	image_texture.create(image.width(), image.height(), image.mirrored().bits());
}





void GLWidget::paintGL()
{
	makeCurrent();
	
	glClearColor(0.0, 0.2, 0.3, 0.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// renders the given image, not that we are setting a fixed viewport that follows the widgets size
	// so it may not be scaled correctly with the image's size (just to keep the example simple)
	Eigen::Vector2i viewport(this->width(), this->height());
	rendertexture.renderTexture(image_texture, viewport);
}



void GLWidget::resizeGL(int w, int h)
{
	QOpenGLFunctions *f = context()->functions();
	f->glViewport(0, 0, this->width(), this->height());
}




void GLWidget::keyReleaseEvent(QKeyEvent *event)
{
	switch (event->key())
	{
	case Qt::Key_Q:
		close();
		break;


	default:
		QWidget::keyReleaseEvent(event);
	}
}