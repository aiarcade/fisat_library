#include <QtGui>
 #include <QtOpenGL>
 #include <stdlib.h>

 #include <math.h>

 #include "bubble.h"

 #include "glwidget.h"

 #ifndef GL_MULTISAMPLE
 #define GL_MULTISAMPLE  0x809D
 #endif

 GLWidget::GLWidget(QWidget *parent)
     : QGLWidget(QGLFormat(QGL::SampleBuffers), parent)
 {
     QTime midnight(0, 0, 0);
     qsrand(midnight.secsTo(QTime::currentTime()));

     //logo = 0;
     xRot = 0;
     yRot = 0;
     zRot = 0;

     qtGreen = QColor::fromCmykF(0.40, 0.0, 1.0, 0.0);
     qtPurple = QColor::fromCmykF(0.39, 0.39, 0.0, 0.0);

     animationTimer.setSingleShot(false);
     connect(&animationTimer, SIGNAL(timeout()), this, SLOT(animate()));
     animationTimer.start(25);

     setAutoFillBackground(false);
     setMinimumSize(200, 200);
     setWindowTitle(tr("Overpainting a Scene"));

     campusData=new DbHelper();
 }

 GLWidget::~GLWidget()
 {
 }

 static void qNormalizeAngle(int &angle)
 {
     while (angle < 0)
         angle += 360 * 16;
     while (angle > 360 * 16)
         angle -= 360 * 16;
 }

 void GLWidget::setXRotation(int angle)
 {
     qNormalizeAngle(angle);
     if (angle != xRot)
         xRot = angle;
 }

 void GLWidget::setYRotation(int angle)
 {
     qNormalizeAngle(angle);
     if (angle != yRot)
         yRot = angle;
 }

 void GLWidget::setZRotation(int angle)
 {
     qNormalizeAngle(angle);
     if (angle != zRot)
         zRot = angle;
 }

 void GLWidget::initializeGL()
 {
     glEnable(GL_MULTISAMPLE);

     //logo = new QtLogo(this);
     //logo->setColor(qtGreen.dark());
 }

 void GLWidget::mousePressEvent(QMouseEvent *event)
 {
     lastPos = event->pos();
 }

 void GLWidget::mouseMoveEvent(QMouseEvent *event)
 {
     int dx = event->x() - lastPos.x();
     int dy = event->y() - lastPos.y();

     if (event->buttons() & Qt::LeftButton) {
         setXRotation(xRot + 8 * dy);
         setYRotation(yRot + 8 * dx);
     } else if (event->buttons() & Qt::RightButton) {
         setXRotation(xRot + 8 * dy);
         setZRotation(zRot + 8 * dx);
     }
     lastPos = event->pos();
 }

 void GLWidget::paintEvent(QPaintEvent *event)
 {
     makeCurrent();
     glMatrixMode(GL_MODELVIEW);
     glPushMatrix();

     qglClearColor(qtPurple.dark());
     glShadeModel(GL_SMOOTH);
     glEnable(GL_DEPTH_TEST);
     glEnable(GL_CULL_FACE);
     glEnable(GL_LIGHTING);
     glEnable(GL_LIGHT0);
     glEnable(GL_MULTISAMPLE);
     static GLfloat lightPosition[4] = { 0.5, 5.0, 7.0, 1.0 };
     glLightfv(GL_LIGHT0, GL_POSITION, lightPosition);

     setupViewport(width(), height());

     glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
     glLoadIdentity();
     glTranslatef(0.0, 0.0, -10.0);
     glRotatef(xRot / 16.0, 1.0, 0.0, 0.0);
     glRotatef(yRot / 16.0, 0.0, 1.0, 0.0);
     glRotatef(zRot / 16.0, 0.0, 0.0, 1.0);

     glColor3f(.1,.1,.4);
     glBegin(GL_LINES);
     glVertex2d(0,.0);
     glVertex2d(.5,.5);
     glEnd();


     glShadeModel(GL_FLAT);
     glDisable(GL_CULL_FACE);
     glDisable(GL_DEPTH_TEST);
     glDisable(GL_LIGHTING);

     glMatrixMode(GL_MODELVIEW);
     glPopMatrix();

     QPainter painter(this);
     painter.setRenderHint(QPainter::Antialiasing);
     foreach (Bubble *bubble, bubbles) {
         if (bubble->rect().intersects(event->rect()))
             bubble->drawBubble(&painter);
     }
     drawInstructions(&painter);
     painter.end();
 }

 void GLWidget::resizeGL(int width, int height)
 {
     setupViewport(width, height);
 }

 void GLWidget::showEvent(QShowEvent *event)
 {
     Q_UNUSED(event);
     createBubbles(20 - bubbles.count());
 }

 QSize GLWidget::sizeHint() const
 {
     return QSize(400, 400);
 }

 void GLWidget::createBubbles(int number)
 {
     for (int i = 0; i < number; ++i) {
         QPointF position(width()*(0.1 + (0.8*qrand()/(RAND_MAX+1.0))),
                         height()*(0.1 + (0.8*qrand()/(RAND_MAX+1.0))));
         qreal radius = qMin(width(), height())*(0.0125 + 0.0875*qrand()/(RAND_MAX+1.0));
         QPointF velocity(width()*0.0125*(-0.5 + qrand()/(RAND_MAX+1.0)),
                         height()*0.0125*(-0.5 + qrand()/(RAND_MAX+1.0)));

         bubbles.append(new Bubble(position, radius, velocity));
     }
 }

 void GLWidget::animate()
 {
     QMutableListIterator<Bubble*> iter(bubbles);

     while (iter.hasNext()) {
         Bubble *bubble = iter.next();
         bubble->move(rect());
     }
     update();
 }

 void GLWidget::setupViewport(int width, int height)
 {
     int side = qMin(width, height);
     glViewport((width - side) / 2, (height - side) / 2, side, side);

     glMatrixMode(GL_PROJECTION);
     glLoadIdentity();
 #ifdef QT_OPENGL_ES
     glOrthof(-0.5, +0.5, -0.5, 0.5, 4.0, 15.0);
 #else
     glOrtho(-0.5, +0.5, -0.5, 0.5, 4.0, 15.0);
 #endif
     glMatrixMode(GL_MODELVIEW);
 }

 void GLWidget::drawInstructions(QPainter *painter)
 {
     QStringList  highlights;
     QString text("hello");
     QFontMetrics metrics = QFontMetrics(font());
     int border = qMax(4, metrics.leading());
     int fontsize=22;

     highlights = campusData->getHighlights((width()-2*width()/5+2)/(fontsize/2));

     painter->fillRect(QRect((this->width()/5)-2, (this->height()/5)+2, (width()-2*width()/5)+20,highlights.length()*30),
                     QBrush(QColor(128, 128, 255, 128)));

     painter->setFont(QFont("goodtimes",22));
     for(int i=0;i<highlights.length();i++ )
     {

         QRect rect = metrics.boundingRect(0, 0, width() - 2*border, int(height()*0.125),
                                           Qt::AlignCenter | Qt::TextWordWrap, text);


         painter->setRenderHint(QPainter::TextAntialiasing);

         painter->fillRect(QRect(0, 0, width(), rect.height() + 2*border),
                          QColor(0, 0, 0, 127));

         painter->setPen(Qt::white);

         QStringList pdata=highlights[i].split('+');
         painter->drawText(this->width()/5+40, (this->height()/5)+(i+1)*40,
                            width()-2*width()/5, rect.height()+2*border,
                           Qt::AlignJustify ,pdata[0]);
         painter->drawText(this->width()/5+300, (this->height()/5)+(i+1)*40,
                            width()-2*width()/5, rect.height()+2*border,
                           Qt::AlignJustify ,pdata[1]);

         //qDebug()<<highlights[i].length();

      }
}
