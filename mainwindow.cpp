#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "camera.h"

#include <iostream>
#include <QtWidgets>

MainWindow::MainWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    /* Init OpenGL Widget */
    GL_Handle = findChild<BasicSurface*>("OpenGL");
    QSurfaceFormat format;
    format.setDepthBufferSize(24);
    format.setStencilBufferSize(8);
    format.setVersion(3, 3);
    format.setRenderableType(QSurfaceFormat::RenderableType::OpenGL);
    format.setProfile(QSurfaceFormat::CoreProfile);
    GL_Handle->setFormat(format);


    eyeX = findChild<QLineEdit*>("EyeX");
    eyeY = findChild<QLineEdit*>("EyeY");
    eyeZ = findChild<QLineEdit*>("EyeZ");

    targetX = findChild<QLineEdit*>("TargetX");
    targetY = findChild<QLineEdit*>("TargetY");
    targetZ = findChild<QLineEdit*>("TargetZ");

    initConnections();

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::initConnections()
{
    using std::cout;
    using std::endl;
    using std::cerr;

    QSlider* curSlider = window()->findChild<QSlider*>("redSlider");
    if(!curSlider)
        cout << "No red";
    else
    {
        connect(curSlider, SIGNAL(valueChanged(int)), GL_Handle, SLOT(setRed(int)));
        connect(curSlider, SIGNAL(valueChanged(int)), GL_Handle, SLOT(update(void)));
        curSlider->setValue(127);
    }

    curSlider = window()->findChild<QSlider*>("greenSlider");
    if(!curSlider)
        cout << "No green";
    else
    {
        connect(curSlider, SIGNAL(valueChanged(int)), GL_Handle, SLOT(setGreen(int)));
        connect(curSlider, SIGNAL(valueChanged(int)), GL_Handle, SLOT(update(void)));
        curSlider->setValue(127);
    }


    curSlider = window()->findChild<QSlider*>("blueSlider");
    if(!curSlider)
        cout << "No blue";
    else
    {
        connect(curSlider, SIGNAL(valueChanged(int)), GL_Handle, SLOT(setBlue(int)));
        connect(curSlider, SIGNAL(valueChanged(int)), GL_Handle, SLOT(update(void)));
        curSlider->setValue(127);
    }

    curSlider = window()->findChild<QSlider*>("frustrumSlider");
    if(!curSlider)
        cout << "No frustrum slider";
    else
    {
        connect(curSlider, SIGNAL(valueChanged(int)), GL_Handle, SLOT(setFrustrumSize(int)));
        connect(curSlider, SIGNAL(valueChanged(int)), GL_Handle, SLOT(update(void)));
        curSlider->setValue(10);
    }

    curSlider = window()->findChild<QSlider*>("FoV");
    if(!curSlider)
        cout << "No FOV slider";
    else
    {
        connect(curSlider, SIGNAL(valueChanged(int)), GL_Handle, SLOT(setFieldOfView(int)));
        connect(curSlider, SIGNAL(valueChanged(int)), GL_Handle, SLOT(update(void)));
    }

    //Initializing shaders texboxes BEFORE connecting
    //*
    {
        QString frag;
        QFile file("../Qt-Test/base.frag");
        file.open(QIODevice::ReadOnly | QIODevice::Text);
        frag = file.readAll();
        window()->findChild<QTextEdit*>("fragText")->setText(frag);
    }
    {
        QString vert;
        QFile file("../Qt-Test/base.vert");
        file.open(QIODevice::ReadOnly | QIODevice::Text);
        vert = file.readAll();
        window()->findChild<QTextEdit*>("vertText")->setText(vert);
    }

    //Now, connect
    QTextEdit* text = window()->findChild<QTextEdit*>("fragText");
    connect(text, SIGNAL(textChanged()), GL_Handle, SLOT(updateShader()));
    text = window()->findChild<QTextEdit*>("vertText");
    connect(text, SIGNAL(textChanged()), GL_Handle, SLOT(updateShader()));

    connect(window()->findChild<QPushButton*>("shaderLoadButton"), SIGNAL(clicked(bool)), GL_Handle, SLOT(reloadShader())); ///Reload shaders forme files



    /* Connecting text edits to camera */
    connect(eyeX, SIGNAL(textChanged(QString)), this, SLOT(updateCamera()));
    connect(eyeY, SIGNAL(textChanged(QString)), this, SLOT(updateCamera()));
    connect(eyeZ, SIGNAL(textChanged(QString)), this, SLOT(updateCamera()));

    connect(targetX, SIGNAL(textChanged(QString)), this, SLOT(updateCamera()));
    connect(targetY, SIGNAL(textChanged(QString)), this, SLOT(updateCamera()));
    connect(targetZ, SIGNAL(textChanged(QString)), this, SLOT(updateCamera()));
}

void MainWindow::updateCamera()
{
    auto camera = window()->findChild<Camera*>("Camera");
    QVector3D eye = QVector3D(eyeX->text().toDouble(), eyeY->text().toDouble(), eyeZ->text().toDouble());
    camera->setEye(eye);
    QVector3D target = QVector3D(targetX->text().toDouble(), targetY->text().toDouble(), targetZ->text().toDouble());
    camera->setTarget(target);
}
