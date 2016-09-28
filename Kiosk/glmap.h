#ifndef GLMAP_H
#define GLMAP_H





// GLMap.cpp


#include <QtWidgets>
#include <QtOpenGL>

#include "GLMap.h"


#include <QGLWidget>

class GLMap : public QGLWidget
{
    Q_OBJECT
public:
    explicit GLMap(QWidget *parent = 0);
    ~GLMap();
signals:

public slots:

protected:
    void initializeGL();
    void paintGL();
    void resizeGL(int width, int height);

    QSize minimumSizeHint() const;
    QSize sizeHint() const;
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);

public slots:
    // slots for xyz-rotation slider
    void setXRotation(int angle);
    void setYRotation(int angle);
    void setZRotation(int angle);

signals:
    // signaling rotation from mouse movement
    void xRotationChanged(int angle);
    void yRotationChanged(int angle);
    void zRotationChanged(int angle);

private:
    void draw();

    int xRot;
    int yRot;
    int zRot;

    QPoint lastPos;
};



#endif // GLMAP_H
