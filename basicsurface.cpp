#include "basicsurface.h"
#include <iostream>
#include <QtWidgets>

using std::cerr;
using std::cout;
using std::endl;



BasicSurface::BasicSurface(QWidget* parent) : QOpenGLWidget(parent), camera(this){
    camera.setObjectName("Camera");
    camera.setEye(QVector3D(3,3,3));
    camera.setTarget(QVector3D(0,0,0));

    connect(&camera, SIGNAL(valueChanged()), this, SLOT(update()));


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
    glClearColor(0.0f, 0.5f, 1.0f, 1.0f);


    updateShader();
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
    program.setUniformValue("view", camera.get());



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
    if(window()->findChild<QCheckBox*>("isOrthographic")->isChecked())
        projection.ortho(-frustrumSize, frustrumSize, -frustrumSize, frustrumSize, 1.0f, 10.0f);
    else
        projection.perspective(FoV, 1.0, 1.0f, 100.0f);
}

BasicSurface::~BasicSurface()
{
}
