#ifndef BASICSURFACE_H
#define BASICSURFACE_H



#include <QOpenGLShader>
#include <QOpenGLShaderProgram>
#include <QOpenGLVertexArrayObject>
#include <QtOpenGL>
#include <QtGui>
#include <QtWidgets>
#include <QtMath>


class BasicSurface : public QOpenGLWidget, protected QOpenGLFunctions
{
    Q_OBJECT
    public:
        BasicSurface(QWidget* parent = nullptr);
        virtual ~BasicSurface();
        void init();

    protected:
        void initializeGL();
        void paintGL();
        void resizeGL(int width, int height);


    signals:


    public slots:
        void setRed(int v) {red = v;}
        void setGreen(int v) {green = v;}
        void setBlue(int v) {blue = v;}
        void setFrustrumSize(int v) {frustrumSize = float(v)/10.0f; recomputeProjection();}
        void updateShader();
        void reloadShader();

    private slots:
        void recomputeProjection();

    private:
        QOpenGLShaderProgram program;
        QOpenGLVertexArrayObject VAO;
        QOpenGLBuffer VBO;
        QMatrix4x4 projection;
        float frustrumSize = 2.0f;
        QMatrix4x4 camera;
        unsigned char red, green, blue;
};

#endif // BASICSURFACE_H
