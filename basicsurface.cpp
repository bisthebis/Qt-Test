#include "basicsurface.h"
#include <iostream>
#include <QtWidgets>

using std::cerr;
using std::cout;
using std::endl;



BasicSurface::BasicSurface(QWidget* parent) : QOpenGLWidget(parent)
{


}

void BasicSurface::init()
{
    QSlider* curSlider = window()->findChild<QSlider*>("redSlider");
    if(!curSlider)
        cout << "No red";
    else
    {
        connect(curSlider, SIGNAL(valueChanged(int)), this, SLOT(setRed(int)));
        connect(curSlider, SIGNAL(valueChanged(int)), this, SLOT(update(void)));
        curSlider->setValue(127);
    }

    curSlider = window()->findChild<QSlider*>("greenSlider");
    if(!curSlider)
        cout << "No green";
    else
    {
        connect(curSlider, SIGNAL(valueChanged(int)), this, SLOT(setGreen(int)));
        connect(curSlider, SIGNAL(valueChanged(int)), this, SLOT(update(void)));
        curSlider->setValue(127);
    }


    curSlider = window()->findChild<QSlider*>("blueSlider");
    if(!curSlider)
        cout << "No blue";
    else
    {
        connect(curSlider, SIGNAL(valueChanged(int)), this, SLOT(setBlue(int)));
        connect(curSlider, SIGNAL(valueChanged(int)), this, SLOT(update(void)));
        curSlider->setValue(127);
    }

    curSlider = window()->findChild<QSlider*>("frustrumSlider");
    if(!curSlider)
        cout << "No frustrum slider";
    else
    {
        connect(curSlider, SIGNAL(valueChanged(int)), this, SLOT(setFrustrumSize(int)));
        connect(curSlider, SIGNAL(valueChanged(int)), this, SLOT(update(void)));
        curSlider->setValue(10);
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
    connect(text, SIGNAL(textChanged()), this, SLOT(updateShader()));
    text = window()->findChild<QTextEdit*>("vertText");
    connect(text, SIGNAL(textChanged()), this, SLOT(updateShader()));

    connect(window()->findChild<QPushButton*>("shaderLoadButton"), SIGNAL(clicked(bool)), this, SLOT(reloadShader())); ///Reload shaders forme files




    updateShader();




}

void BasicSurface::updateShader()
{
    QTextEdit* text = window()->findChild<QTextEdit*>("fragText");
    QString frag = text->toPlainText();
    text = window()->findChild<QTextEdit*>("vertText");
    QString vert = text->toPlainText();
    program.removeAllShaders();
    program.addShaderFromSourceCode(QOpenGLShader::Vertex, vert);
    program.addShaderFromSourceCode(QOpenGLShader::Fragment, frag);
    program.link();
    program.bind();

    update();
}

void BasicSurface::reloadShader()
{
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

}

void BasicSurface::initializeGL()
{

    initializeOpenGLFunctions();
    init();
    glClearColor(0.0f, 0.5f, 1.0f, 1.0f);



    float vertices[] = {0.0, 0.5, 0,  -0.5, -0.5, 0,  0.5, -0.5, 0,    /*colors*/ 1.0, 0.0, 0.0,  0.0, 1.0, 0.0,  0.0, 0.0, 1.0};

    VAO.create();
    VAO.bind();

    VBO.create();
    VBO.bind();
    VBO.allocate(&vertices, sizeof(vertices));


    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, (void*)(9*sizeof(float)));
    glEnableVertexAttribArray(1);

    glBindBuffer(GL_ARRAY_BUFFER, 0);

    VAO.release();



    glEnable(GL_DEPTH_TEST);

}

void BasicSurface::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);






    // On affiche le triangle
    program.bind();
    program.setUniformValue("Color", QVector3D((float)red/255, (float)green/255, (float)blue/255));
    program.setUniformValue("projection", projection);

    VAO.bind();
    glDrawArrays(GL_TRIANGLES, 0, 3);
    VAO.release();

    program.release();

    GLenum err;
        while ((err = glGetError()) != GL_NO_ERROR) {
            cerr << "OpenGL error: " << err << endl;
        }




}

void BasicSurface::resizeGL(int width, int height)
{
    int side = qMin(width, height);
    glViewport((width - side) / 2, (height - side) / 2, side, side);
    recomputeProjection();


}

void BasicSurface::recomputeProjection()
{
    projection.setToIdentity();
    projection.ortho(-frustrumSize, frustrumSize, -frustrumSize, frustrumSize, -1.0f, 10.0f);
}

BasicSurface::~BasicSurface()
{
}
