#ifndef WIDGETOPENGL_H
#define WIDGETOPENGL_H

#include <QWidget>
#include <QOpenGLWidget>
#include <QOpenGLFunctions>

class WidgetOpenGL : public QOpenGLWidget, protected QOpenGLFunctions
{
    Q_OBJECT

    public:
        WidgetOpenGL(QWidget* parent = nullptr);

    protected:
        void initializeGL();
        void paintGL();
        void resizeGL(int width, int height);

    signals:

    public slots:
};

#endif // WIDGETOPENGL_H
