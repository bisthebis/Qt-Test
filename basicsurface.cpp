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
    QSlider* curSlider = window()->findChild<QSlider*>("redSlider");
    if(!curSlider)
        cout << "No red";
    else
    {
        QObject::connect(curSlider, SIGNAL(valueChanged(int)), this, SLOT(setRed(int)));
        QObject::connect(curSlider, SIGNAL(valueChanged(int)), this, SLOT(update(void)));
        curSlider->setValue(127);
    }

    curSlider = window()->findChild<QSlider*>("greenSlider");
    if(!curSlider)
        cout << "No green";
    else
    {
        QObject::connect(curSlider, SIGNAL(valueChanged(int)), this, SLOT(setGreen(int)));
        QObject::connect(curSlider, SIGNAL(valueChanged(int)), this, SLOT(update(void)));
        curSlider->setValue(127);
    }


    curSlider = window()->findChild<QSlider*>("blueSlider");
    if(!curSlider)
        cout << "No blue";
    else
    {
        QObject::connect(curSlider, SIGNAL(valueChanged(int)), this, SLOT(setBlue(int)));
        QObject::connect(curSlider, SIGNAL(valueChanged(int)), this, SLOT(update(void)));
        curSlider->setValue(127);
    }

    //Initializing shaders texboxes BEFORE connecting
    //*
    {
        QString frag;
        QFile file("base.frag");
        file.open(QIODevice::ReadOnly | QIODevice::Text);
        frag = file.readAll();
        window()->findChild<QTextEdit*>("fragText")->setText(frag);
    }
    {
        QString vert;
        QFile file("base.vert");
        file.open(QIODevice::ReadOnly | QIODevice::Text);
        vert = file.readAll();
        window()->findChild<QTextEdit*>("vertText")->setText(vert);
    }

    //Now, connect
    QTextEdit* text = window()->findChild<QTextEdit*>("fragText");
    QObject::connect(text, SIGNAL(textChanged()), this, SLOT(updateShader()));
    text = window()->findChild<QTextEdit*>("vertText");
    QObject::connect(text, SIGNAL(textChanged()), this, SLOT(updateShader()));




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
    /*
    if(!program.addShaderFromSourceCode(QOpenGLShader::Fragment, "#version 330 core \n  uniform vec3 Color; out vec4 outColor; void main() {outColor = vec4(Color,1);}"))
        exit(EXIT_FAILURE);*/
    if(!program.addShaderFromSourceFile(QOpenGLShader::Fragment, "base.frag"))


    ///glBindFragDataLocation(program.programId(), 0, "outColor");
    program.link();
    program.bind();


    glEnable(GL_DEPTH_TEST);

}

void BasicSurface::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);






    // On affiche le triangle
    program.bind();
    program.setUniformValue("Color", QVector3D((float)red/255, (float)green/255, (float)blue/255));

    VAO.bind();
    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
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


}

BasicSurface::~BasicSurface()
{
}
