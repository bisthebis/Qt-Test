#include "widgetopengl.h"
#include "basicsurface.h"

#include <QtGui/QGuiApplication>
#include <QApplication>
#include <QtGui/QMatrix4x4>
#include <QtGui/QOpenGLShaderProgram>
#include <QtGui/QScreen>
#include <QWidget>
#include <QBoxLayout>
#include <QtGui>
#include <QtWidgets>
#include <QFile>

#include <QtCore/qmath.h>

#include <iostream>

using std::cerr;
using std::cout;
using std::endl;


int main(int argc, char **argv)
{
    QApplication app(argc, argv);

    QWidget window;
    window.resize(1000,800);
    auto layout = new QBoxLayout(QBoxLayout::TopToBottom);
    window.setLayout(layout);

    auto GL = new BasicSurface(nullptr);

    QSurfaceFormat format;
    format.setDepthBufferSize(24);
    format.setStencilBufferSize(8);
    format.setVersion(3, 3);
    format.setRenderableType(QSurfaceFormat::RenderableType::OpenGL);
    format.setProfile(QSurfaceFormat::CoreProfile);
    GL->setFormat(format);



    GL->resize(500,500);
    layout->addWidget(GL);

    auto slider = new QSlider(Qt::Orientation::Horizontal);
    slider->setMinimum(0);
    slider->setMaximum(255);
    slider->setObjectName("redSlider");
    layout->addWidget(slider);

    slider = new QSlider(Qt::Orientation::Horizontal);
    slider->setMinimum(0);
    slider->setMaximum(255);
    slider->setObjectName("greenSlider");
    layout->addWidget(slider);

    slider = new QSlider(Qt::Orientation::Horizontal);
    slider->setMinimum(0);
    slider->setMaximum(255);
    slider->setObjectName("blueSlider");
    layout->addWidget(slider);

    QTextEdit* block = new QTextEdit();
    QString frag;
    {
        QFile file("base.frag");
        file.open(QIODevice::ReadOnly | QIODevice::Text);
        frag = file.readAll();
    }


    block->setText(frag);
    block->setFixedHeight(200);
    block->setObjectName("fragText");
    layout->addWidget(block);


    GL->init();

    window.show();

    //GL->show();

    return app.exec();
}

