#include "basicsurface.h"
#include <iostream>

using std::cerr;
using std::cout;
using std::endl;



BasicSurface::BasicSurface(QWidget* parent) : WidgetOpenGL(parent)
{


}

void BasicSurface::init()
{
    QSlider* curSlider = parent()->findChild<QSlider*>("redSlider");
    QObject::connect(curSlider, SIGNAL(valueChanged(int)), this, SLOT(setRed(int)));
    QObject::connect(curSlider, SIGNAL(valueChanged(int)), this, SLOT(update(void)));

    curSlider = parent()->findChild<QSlider*>("greenSlider");
    QObject::connect(curSlider, SIGNAL(valueChanged(int)), this, SLOT(setGreen(int)));
    QObject::connect(curSlider, SIGNAL(valueChanged(int)), this, SLOT(update(void)));

    curSlider = parent()->findChild<QSlider*>("blueSlider");
    QObject::connect(curSlider, SIGNAL(valueChanged(int)), this, SLOT(setBlue(int)));
    QObject::connect(curSlider, SIGNAL(valueChanged(int)), this, SLOT(update(void)));

}

void BasicSurface::initializeGL()
{
    initializeOpenGLFunctions();
    glClearColor(0.0f, 0.5f, 1.0f, 1.0f);

    float vertices[] = {0.0, 0.5,  -0.5, -0.5,  0.5, -0.5,   0, -1};

    VAO.create();
    VAO.bind();

    VBO.create();
    VBO.bind();
    VBO.allocate(&vertices, sizeof(vertices));


    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);

    VAO.release();



    if(!program.addShaderFromSourceCode(QOpenGLShader::Vertex, "#version 330 core \n in vec2 pos; void main() {gl_Position = vec4(pos, 0.0, 1.0);}"))
        exit(EXIT_FAILURE);

    if(!program.addShaderFromSourceCode(QOpenGLShader::Fragment, "#version 330 core \n  uniform vec3 Color; out vec4 outColor; void main() {outColor = vec4(Color,1);}"))
        exit(EXIT_FAILURE);


    ///glBindFragDataLocation(program.programId(), 0, "outColor");
    program.link();
    program.bind();


    glEnable(GL_DEPTH_TEST);

}

void BasicSurface::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);






    // On affiche le triangle
    program.setUniformValue("Color", QVector3D((float)red/255, (float)green/255, (float)blue/255));

    VAO.bind();
    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
    VAO.release();

    GLenum err;
        while ((err = glGetError()) != GL_NO_ERROR) {
            cerr << "OpenGL error: " << err << endl;
        }




}

void BasicSurface::resizeGL(int width, int height)
{
    int side = qMin(width, height);
    glViewport((width - side) / 2, (height - side) / 2, side, side);


}

BasicSurface::~BasicSurface()
{
}
