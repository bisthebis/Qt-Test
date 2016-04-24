#include "mainwindow.h"

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
    cout << sizeof(QObject) << endl;
    MainWindow mainWin;
    mainWin.show();



    return app.exec();
}

