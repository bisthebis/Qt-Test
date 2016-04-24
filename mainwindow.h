#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWidget>

class BasicSurface;
class QLineEdit;

namespace Ui {
class MainWindow;
}

class MainWindow : public QWidget
{
    Q_OBJECT

    public:
        explicit MainWindow(QWidget *parent = 0);
        ~MainWindow();

    private:
        void initConnections();
        BasicSurface* GL_Handle;
        Ui::MainWindow *ui;
        QLineEdit *eyeX, *eyeY, *eyeZ;
        QLineEdit *targetX, *targetY, *targetZ;


    private slots:
        void updateCamera();
};

#endif // MAINWINDOW_H
