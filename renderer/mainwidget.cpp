/****************************************************************************
**
** Copyright (C) 2013 Digia Plc and/or its subsidiary(-ies).
** Contact: http://www.qt-project.org/legal
**
** This file is part of the QtCore module of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:BSD$
** You may use this file under the terms of the BSD license as follows:
**
** "Redistribution and use in source and binary forms, with or without
** modification, are permitted provided that the following conditions are
** met:
**   * Redistributions of source code must retain the above copyright
**     notice, this list of conditions and the following disclaimer.
**   * Redistributions in binary form must reproduce the above copyright
**     notice, this list of conditions and the following disclaimer in
**     the documentation and/or other materials provided with the
**     distribution.
**   * Neither the name of Digia Plc and its Subsidiary(-ies) nor the names
**     of its contributors may be used to endorse or promote products derived
**     from this software without specific prior written permission.
**
**
** THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
** "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
** LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
** A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
** OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
** SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
** LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
** DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
** THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
** (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
** OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE."
**
** $QT_END_LICENSE$
**
****************************************************************************/

#include "mainwidget.h"

#include <QMouseEvent>

#include <math.h>

MainWidget::MainWidget(QWidget *parent) :
    QOpenGLWidget(parent),
    m_distExp(-400),
    m_trackBall(0.0f, QVector3D(0, 1, 0), TrackBall::Plane)
{
    setMinimumSize(400, 400);

/*
    console = new QTextEdit;
    console->clear();
    console->setWindowTitle("OpenGL Logger");
    console->show();
*/
     // showFullScreen();

    shadingmode = 0;
    rendermode = 1;

    mousex = 0.5;
    mousey = 0.5;
}

MainWidget::~MainWidget()
{
    /* FIXME */
}

QPointF MainWidget::pixelPosToViewPos(const QPointF& p)
{
    return QPointF(2.0 * float(p.x()) / width() - 1.0,
                   1.0 - 2.0 * float(p.y()) / height());
}

void MainWidget::mousePressEvent(QMouseEvent *event)
{
    if (event->buttons() & Qt::LeftButton) {
        m_trackBall.push(pixelPosToViewPos(event->localPos()), QQuaternion());
        event->accept();
    }
}

void MainWidget::mouseMoveEvent(QMouseEvent *event)
{
    if (event->buttons() & Qt::RightButton){ //Qt::MidButton) {
        mousex = float(event->x())/float(width());
        mousey = float(event->y())/float(height());
    }

    if (event->buttons() & Qt::LeftButton){ //Qt::MidButton) {
        m_trackBall.move(pixelPosToViewPos(event->localPos()), QQuaternion());
        event->accept();
    } else {
        m_trackBall.release(pixelPosToViewPos(event->localPos()), QQuaternion());
    }
}

void MainWidget::wheelEvent(QWheelEvent * event)
{
       m_distExp += event->angleDelta().y() / 12;

       // qDebug() << m_distExp;
}

void MainWidget::mouseReleaseEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton){ //Qt::MidButton) {

           m_trackBall.release(pixelPosToViewPos(event->localPos()), QQuaternion());
        event->accept();
    }
}

void MainWidget::timerEvent(QTimerEvent *)
{
    update();
}

void MainWidget::initializeGL()
{
    makeCurrent();
    connect(context(), &QOpenGLContext::aboutToBeDestroyed, this, &MainWidget::DeleteFunctions);

    if(!context()->isValid()){
        QMessageBox msgBox1;
        msgBox1.setText("gl context not valid! ");
        msgBox1.exec();
    }

    m_pFunctions = new QOpenGLFunctions_4_3_Core();
    if(!m_pFunctions->initializeOpenGLFunctions()) {
        QMessageBox msgBox;
        msgBox.setText("Failed to initialize the OpenGL functions.");
        msgBox.exec();
        // qFatal("Failed to initialize the OpenGL functions.");
    }

    const QString vendor = reinterpret_cast<const char*>(m_pFunctions->glGetString(GL_VENDOR));
    const QString renderer = reinterpret_cast<const char*>(m_pFunctions->glGetString(GL_RENDERER));
    const QString version = reinterpret_cast<const char*>(m_pFunctions->glGetString(GL_VERSION));

/*
    QMessageBox msgBox;
    msgBox.setText("OpenGL vendor: "+ vendor +"\n"
                   +"Renderer: "+ renderer +"\n"
                   +"Version: "+ version +"\n"
                   );
    msgBox.exec();

    QOpenGLDebugLogger *logger = new QOpenGLDebugLogger;
    logger->initialize();
    connect(logger, &QOpenGLDebugLogger::messageLogged,this,&MainWidget::gldebugmsg);

    logger->startLogging(QOpenGLDebugLogger::SynchronousLogging);
*/

    QColor bg = QColor(Qt::darkGray);

    QOpenGLFunctions *functions = this->context()->functions();
    functions->glClearColor(bg.redF(),bg.greenF(),bg.blueF(),bg.alphaF());
    functions->glEnable(GL_LINE_SMOOTH);
    functions->glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);
    functions->glEnable(GL_BLEND);
    functions->glBlendEquation(GL_FUNC_ADD);
    functions->glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    geometries = new GeometryEngine;
    geometries->rendermode = rendermode;
    initShaders();
    initTextures();

    // Enable depth buffer
    functions->glEnable(GL_DEPTH_TEST);

    // Enable back face culling
    functions->glEnable(GL_CULL_FACE);

    // Use QBasicTimer because its faster than QTimer
    timer.start(33, this);
}

void MainWidget::initShaders()
{
    program = new QOpenGLShaderProgram(context());

    // Compile vertex shader
    if (!program->addShaderFromSourceFile(QOpenGLShader::Vertex, ":/resources/renderer/vshader.glsl"))
        close();

    // Compile fragment shader
    if (!program->addShaderFromSourceFile(QOpenGLShader::Fragment, ":/resources/renderer/fshader.glsl"))
        close();

    // Link shader pipeline
    if (!program->link())
        close();

    // Bind shader pipeline for use
    if (!program->bind())
        close();
}

void MainWidget::initTextures()
{
    this->context()->functions()->glGenTextures(4, tex);
}

void MainWidget::gldebugmsg(const QOpenGLDebugMessage &/* debugMessage */)
{
    // if (debugMessage.message()== "GL_INVALID_VALUE error generated. Index out of range.") return;
    // console->append( debugMessage.message());
    // console->append("\n");
}

void MainWidget::addMainMenu(QMenu *menu)
{
    QMenu *shading = menu->addMenu("Shading Mode");

    cv1 = shading->addAction("Smooth");
    cv1->setData(0);
    cv1->setCheckable(true);
    if(shadingmode == 0)
        cv1->setChecked(true);
    connect(cv1, SIGNAL(triggered()), this, SLOT(setSmoothShading()));

    cv2 = shading->addAction("Wireframe");
    cv2->setData(1);
    cv2->setCheckable(true);
    if(shadingmode == 1)
        cv2->setChecked(true);
    connect(cv2, SIGNAL(triggered()), this, SLOT(setWireframeShading()));

    cv3 = shading->addAction("Vertex");
    cv3->setCheckable(true);
    if(shadingmode == 2)
        cv3->setChecked(true);
    connect(cv3, SIGNAL(triggered()), this, SLOT(setVertexShading()));

    QMenu *rendering = menu->addMenu("Render Mode");

    cv4 = rendering->addAction("Triangles");
    cv4->setCheckable(true);
    if(rendermode == 0)
        cv4->setChecked(true);
    connect(cv4, SIGNAL(triggered()), this, SLOT(setTriangleRendering()));

    cv5 = rendering->addAction("Triangle Strips");
    cv5->setCheckable(true);
    if(rendermode == 1)
        cv5->setChecked(true);
    connect(cv5, SIGNAL(triggered()), this, SLOT(setTriangleStripRendering()));
}

void MainWidget::onNewTextures(const QImage &image, const QImage &image2, const QImage &image3, const QImage &image4)
{
    static const uchar data[] = { 0xFF, 0xFF, 0xFF, 0xFF };

    this->context()->functions()->glEnable(GL_TEXTURE_2D);

    this->context()->functions()->glActiveTexture(GL_TEXTURE0 + 1);
    this->context()->functions()->glBindTexture(GL_TEXTURE_2D, tex[0]);

    QImage image0(data, 1, 1, QImage::Format_RGBA8888);
    if (!image.isNull())
        image0 = image.convertToFormat(QImage::Format_RGBA8888);

    // Set nearest filtering mode for texture minification
    this->context()->functions()->glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

    // Set bilinear filtering mode for texture magnification
    this->context()->functions()->glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    // Wrap texture coordinates by repeating
    // f.ex. texture coordinate (1.1, 1.2) is same as (0.1, 0.2)
    this->context()->functions()->glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    this->context()->functions()->glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    this->context()->functions()->glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, image0.width(), image0.height(), 0, GL_RGBA, GL_UNSIGNED_BYTE, image0.constBits());

    this->context()->functions()->glBindTexture(GL_TEXTURE_2D, 0);
    this->context()->functions()->glActiveTexture(GL_TEXTURE0);

    this->context()->functions()->glActiveTexture(GL_TEXTURE0 + 2);
    this->context()->functions()->glBindTexture(GL_TEXTURE_2D, tex[1]);

    QImage image02 = image2.convertToFormat(QImage::Format_RGBA8888);

    // Set nearest filtering mode for texture minification
    this->context()->functions()->glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

    // Set bilinear filtering mode for texture magnification
    this->context()->functions()->glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    // Wrap texture coordinates by repeating
    // f.ex. texture coordinate (1.1, 1.2) is same as (0.1, 0.2)
    this->context()->functions()->glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    this->context()->functions()->glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    this->context()->functions()->glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, image02.width(), image02.height(), 0, GL_RGBA, GL_UNSIGNED_BYTE, image02.constBits());

    this->context()->functions()->glBindTexture(GL_TEXTURE_2D, 0);
    this->context()->functions()->glActiveTexture(GL_TEXTURE0);

    this->context()->functions()->glActiveTexture(GL_TEXTURE0 +3);
    this->context()->functions()->glBindTexture(GL_TEXTURE_2D, tex[2]);

    QImage image03 = image3.convertToFormat(QImage::Format_RGBA8888);

    // Set nearest filtering mode for texture minification
    this->context()->functions()->glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

    // Set bilinear filtering mode for texture magnification
    this->context()->functions()->glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    // Wrap texture coordinates by repeating
    // f.ex. texture coordinate (1.1, 1.2) is same as (0.1, 0.2)
    this->context()->functions()->glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    this->context()->functions()->glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    this->context()->functions()->glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, image03.width(), image03.height(), 0, GL_RGBA, GL_UNSIGNED_BYTE, image03.constBits());

    this->context()->functions()->glBindTexture(GL_TEXTURE_2D, 0);
    this->context()->functions()->glActiveTexture(GL_TEXTURE0);

    this->context()->functions()->glActiveTexture(GL_TEXTURE0+4);
    this->context()->functions()->glBindTexture(GL_TEXTURE_2D, tex[3]);

    QImage image04 = image4.convertToFormat(QImage::Format_RGBA8888);

    // Set nearest filtering mode for texture minification
    this->context()->functions()->glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

    // Set bilinear filtering mode for texture magnification
    this->context()->functions()->glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    // Wrap texture coordinates by repeating
    // f.ex. texture coordinate (1.1, 1.2) is same as (0.1, 0.2)
    this->context()->functions()->glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    this->context()->functions()->glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    this->context()->functions()->glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, image04.width(), image04.height(), 0, GL_RGBA, GL_UNSIGNED_BYTE, image04.constBits());

    this->context()->functions()->glBindTexture(GL_TEXTURE_2D, 0);
    this->context()->functions()->glActiveTexture(GL_TEXTURE0);
    //

    geometries->difftex = tex[0];
    geometries->spectex = tex[1];
    geometries->normtex = tex[2];
    geometries->lighttex = tex[3];
}

void MainWidget::onNewMesh(std::vector<int> &rmodes, std::vector<std::vector<VertexData> > &arrverts, std::vector<std::vector<unsigned int> > &arrfaces)
{
    geometries->rendermodes.clear();
    this->rendermodes.clear();
    geometries->vertices.clear();
    geometries->faces.clear();

    geometries->rendermodes = rmodes;
    this->rendermodes =rmodes;
    geometries->vertices = arrverts;
    geometries->faces = arrfaces;

    geometries->initCubeGeometry();
}

void MainWidget::onNewMeshselect(std::vector<int> &selection)
{
    this->selectedmeshes.clear();
    this->selectedmeshes = selection;

    // for(int i=0;i<selectedmeshes.size();i++){
    //     qDebug() << selectedmeshes.at(i);
    // }
}

void MainWidget::setSmoothShading()
{
    QAction* pAction = qobject_cast<QAction*>(sender());
    Q_ASSERT(pAction);

    qDebug() << pAction->data();
    shadingmode = 0;
    cv1->setChecked(true);
    cv2->setChecked(false);
    cv3->setChecked(false);
}

void MainWidget::setWireframeShading()
{
    QAction* pAction = qobject_cast<QAction*>(sender());
    Q_ASSERT(pAction);

    qDebug() << pAction->data();
    shadingmode = 1;
    cv1->setChecked(false);
    cv2->setChecked(true);
    cv3->setChecked(false);
}

void MainWidget::setVertexShading()
{
    shadingmode = 2;
    cv1->setChecked(false);
    cv2->setChecked(false);
    cv3->setChecked(true);
}

void MainWidget::setTriangleRendering()
{
    rendermode = 0;
    if (geometries) geometries->rendermode = 0;
    cv4->setChecked(true);
    cv5->setChecked(false);
}

void MainWidget::setTriangleStripRendering()
{
    rendermode = 1;
    if (geometries) geometries->rendermode = 1;
    cv4->setChecked(false);
    cv5->setChecked(true);
}

void MainWidget::resizeGL(int w, int h)
{
    this->context()->functions()->glViewport(0, 0, w, h);

    qreal aspect = qreal(w) / qreal(h ? h : 1);
    const qreal zNear = 1.0, zFar = 1000.0, fov = 45.0;
    // Reset projection
    projection.setToIdentity();

    // Set perspective projection
    projection.perspective(fov, aspect, zNear, zFar);
}

void MainWidget::paintGL()
{
    //if(!(series.size() > 0)) return;

    QOpenGLFunctions *functions = this->context()->functions();

    // Clear color and depth buffer
    functions->glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    functions->glEnable(GL_DEPTH_TEST);
    functions->glDepthMask(GL_TRUE);
    //geometries->init();

    // Calculate model view transformation
    QMatrix4x4 matrix;
    matrix.translate(0.0, 0.0, m_distExp);
    matrix.rotate(m_trackBall.rotation());

    // light pos
    QVector3D lightdir(mousex - 0.5f, 0.5f - mousey, 0.5f);
    lightdir.normalize();

    program->setUniformValue("LightDir",lightdir);

    // Set modelview-projection matrix
    program->setUniformValue("mvp_matrix",projection * matrix);
    program->setUniformValue("mv_matrix",matrix);

    if(selectedmeshes.size()>0){
        program->setUniformValue("selsize",(int)selectedmeshes.size());
        program->setUniformValueArray("selected_mesh_part",selectedmeshes.data(),selectedmeshes.size());
    }

    float timer = (QTime::currentTime().msec() % 500) / 250.0f;
    if (timer > 1.0f) timer = 2.0f - timer;
    program->setUniformValue("timer", timer);

    // Draw  geometry
    switch(shadingmode){
      case 0:
        glPolygonMode(GL_FRONT, GL_FILL);
        glPolygonMode(GL_BACK, GL_FILL);
        break;
      case 1:
        glPolygonMode(GL_FRONT, GL_LINE);
        glPolygonMode(GL_BACK, GL_LINE);
        break;
      case 2:
        glPolygonMode(GL_FRONT, GL_POINT);
        glPolygonMode(GL_BACK, GL_POINT);
        break;

      default:
        glPolygonMode(GL_FRONT, GL_FILL);
        glPolygonMode(GL_BACK, GL_FILL);
    }

    geometries->drawCubeGeometry(program);

    glPolygonMode(GL_FRONT, GL_FILL);
    glPolygonMode(GL_BACK, GL_FILL);

    functions->glDisable(GL_DEPTH_TEST);

    // We need to flush the contents to the FBO before posting
    // the texture to the other thread, otherwise, we might
    // get unexpected results.
    functions->glFlush();

    // QMessageBox msgBox2;
    // msgBox2.setText("check gl error: " +QString(m_pFunctions->glGetError()));
    // msgBox2.exec();
}
