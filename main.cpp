#include "OpenGLWindow.h"
#include "widgetopengl.h"

#include <QtGui/QGuiApplication>
#include <QApplication>
#include <QtGui/QMatrix4x4>
#include <QtGui/QOpenGLShaderProgram>
#include <QtGui/QScreen>
#include <QWidget>
#include <QBoxLayout>
#include <QtGui>
#include <QtWidgets>

#include <QtCore/qmath.h>


int main(int argc, char **argv)
{
    QApplication app(argc, argv);

    QWidget window;
    window.resize(1000,800);
    auto layout = new QBoxLayout(QBoxLayout::TopToBottom);
    window.setLayout(layout);

    WidgetOpenGL* GL = new WidgetOpenGL(nullptr);
    GL->resize(500,500);
    layout->addWidget(GL);

    auto bouton = new QPushButton();
    bouton->setText("Salut !");
    layout->addWidget(bouton);

    window.show();

    //GL->show();

    return app.exec();
}

