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
    m_distExp(-400)
{
     setMinimumSize(400, 400);

    m_trackBalls[0] = TrackBall(0.05f, QVector3D(0, 1, 0), TrackBall::Sphere);
    m_trackBalls[1] = TrackBall(0.005f, QVector3D(0, 0, 1), TrackBall::Sphere);
    m_trackBalls[2] = TrackBall(0.0f, QVector3D(0, 1, 0), TrackBall::Plane);

/*
console = new QTextEdit;
console->clear();
console->setWindowTitle("OpenGL Logger");
console->show();
*/
//this->showFullScreen();

    shadingmode = 0;
    rendermode = 1;

    cl_color = QColor(0,0,0.5*255).rgba();
    cm_color = QColor(255,255,0).rgba();
    lh = 0.0f;

    dur = 1;
    tp = 0.1;
    st = 0;
    et = tp;
    st2 = 0;
    et2 = tp;
    s1 = 0;
    s2 = 0;
    t1 = 0;
    t2 = 1;

    mousex = 0.5;
    mousey = 0.5;
}

MainWidget::~MainWidget()
{
    /*
    deleteTexture(htex);
    deleteTexture(btex);
    deleteTexture(b2tex);
    deleteTexture(hantex);
    */
}

QPointF MainWidget::pixelPosToViewPos(const QPointF& p)
{
    return QPointF(2.0 * float(p.x()) / width() - 1.0,
                   1.0 - 2.0 * float(p.y()) / height());
}

//! [0]

void MainWidget::mousePressEvent(QMouseEvent *event)
{
    // Save mouse press position
    mousePressPosition = QVector2D(event->localPos());

    if (event->buttons() & Qt::LeftButton) {
        m_trackBalls[2].push(pixelPosToViewPos(event->localPos()), QQuaternion());
        event->accept();
    }
}

void MainWidget::mouseMoveEvent(QMouseEvent *event)
{
    if (event->buttons() & Qt::RightButton){ //Qt::MidButton) {
        this->mousex = float(event->x())/float(width());
        this->mousey = float(event->y())/float(height());
    }

    if (event->buttons() & Qt::LeftButton){ //Qt::MidButton) {
        m_trackBalls[2].move(pixelPosToViewPos(event->localPos()), QQuaternion());
        event->accept();
    } else {
        m_trackBalls[2].release(pixelPosToViewPos(event->localPos()), QQuaternion());
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

           m_trackBalls[2].release(pixelPosToViewPos(event->localPos()), QQuaternion());
        event->accept();
    }
}
//! [0]

//! [1]
void MainWidget::timerEvent(QTimerEvent *)
{
    update();
}

void MainWidget::initializeGL()
{
    makeCurrent();
    connect(context(), &QOpenGLContext::aboutToBeDestroyed, this, &MainWidget::DeleteFunctions);
    m_pFunctions = new QOpenGLFunctions_4_3_Core();

    m_pFunctions->initializeOpenGLFunctions();
    program = new QOpenGLShaderProgram(context());
    m_pFunctions->initializeOpenGLFunctions();
    if(!context()->isValid()){
        QMessageBox msgBox1;
        msgBox1.setText("gl context not valid! ");
        msgBox1.exec();
    }

    if(!m_pFunctions->initializeOpenGLFunctions()) {
        QMessageBox msgBox;
        msgBox.setText("Failed to initialize the OpenGL functions.");
        msgBox.exec();
    } //qFatal("Failed to initialize the OpenGL functions.");
/*
        const QString vendor = reinterpret_cast<const char*>(m_pFunctions->glGetString(GL_VENDOR));
        const QString renderer = reinterpret_cast<const char*>(m_pFunctions->glGetString(GL_RENDERER));
        const QString version = reinterpret_cast<const char*>(m_pFunctions->glGetString(GL_VERSION));

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

//glClearColor(0, 0, 0, 0.5f);

    // initializeOpenGLFunctions();
    QColor bg = QColor(Qt::darkGray);
    this->context()->functions()->glClearColor(bg.redF(),bg.greenF(),bg.blueF(),bg.alphaF());
    //qglClearColor(QColor(m_color));
    this->context()->functions()->glEnable(GL_LINE_SMOOTH);
    this->context()->functions()->glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);
    this->context()->functions()->glEnable(GL_BLEND);
    this->context()->functions()->glBlendEquation(GL_FUNC_ADD);
    this->context()->functions()->glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    geometries = new GeometryEngine;
    geometries->rendermode = rendermode;
    //qglClearColor(QColor(m_color));
    initShaders();
    initTextures();

//! [2]
    // Enable depth buffer
    this->context()->functions()->glEnable(GL_DEPTH_TEST);

    // Enable back face culling
    this->context()->functions()->glEnable(GL_CULL_FACE);
//! [2]

    // Use QBasicTimer because its faster than QTimer
    timer.start(33, this);
}

//! [3]
void MainWidget::initShaders()
{
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
//! [3]

//! [4]
void MainWidget::initTextures()
{
    this->context()->functions()->glGenTextures(1, &htex);
    this->context()->functions()->glGenTextures(1, &btex);
    this->context()->functions()->glGenTextures(1, &legtex);
    this->context()->functions()->glGenTextures(1, &hantex);
}

void MainWidget::gldebugmsg(const QOpenGLDebugMessage &/* debugMessage */)
{
    //  if (debugMessage.message()== "GL_INVALID_VALUE error generated. Index out of range.") return;
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

void MainWidget::onNewTextures(QString fileName)
{
    // Load filename

    // try to open textures
    int txcheck = fileName.lastIndexOf(QChar('.'));
    if( txcheck > 0 ){
        QString tx= fileName.left(txcheck);
        tx.append("_BM.dds");

        const QPixmap pixmap(tx);

        const QImage image = pixmap.toImage();
        // qDebug() << (image.isNull() ? "QImage error" : "QImage ok");

        tx= fileName.left(txcheck);
        tx.append("_CMM.dds");

        const QPixmap pixmap2(tx);

        const QImage image2 = pixmap2.toImage();
        // qDebug() << (image2.isNull() ? "QImage error" : "QImage ok");

        tx= fileName.left(txcheck);
        tx.append("_NM.dds");

        const QPixmap pixmap3(tx);

        const QImage image3 = pixmap3.toImage();
        // qDebug() << (image3.isNull() ? "QImage error" : "QImage ok");

        tx= fileName.left(txcheck);
        tx.append("_TM.dds");

        const QPixmap pixmap4(tx);

        const QImage image4 = pixmap4.toImage();
        // qDebug() << (image4.isNull() ? "QImage error" : "QImage ok");

// fuck sakes

        this->context()->functions()->glEnable(GL_TEXTURE_2D);

        // htex =     bindTexture(image); //diffuse
        this->context()->functions()->glActiveTexture(GL_TEXTURE0 + 1);
        this->context()->functions()->glBindTexture(GL_TEXTURE_2D, htex);

        QImage image0 = image.convertToFormat(QImage::Format_RGBA8888);

        // Set nearest filtering mode for texture minification
        this->context()->functions()->glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

        // Set bilinear filtering mode for texture magnification
        this->context()->functions()->glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        // Wrap texture coordinates by repeating
        // f.ex. texture coordinate (1.1, 1.2) is same as (0.1, 0.2)
        this->context()->functions()->glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        this->context()->functions()->glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

        this->context()->functions()->glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, image0.width(), image0.height(), 0, GL_RGBA, GL_UNSIGNED_BYTE, image0.constBits());

        this->context()->functions()->glBindTexture(GL_TEXTURE_2D, 0);
        this->context()->functions()->glActiveTexture(GL_TEXTURE0);

        //btex =  bindTexture(image2); //specular
        this->context()->functions()->glActiveTexture(GL_TEXTURE0 + 2);
        this->context()->functions()->glBindTexture(GL_TEXTURE_2D, btex);

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

        //legtex = bindTexture(image3); //normal
        this->context()->functions()->glBindTexture(GL_TEXTURE_2D, 0);
        this->context()->functions()->glActiveTexture(GL_TEXTURE0);

        this->context()->functions()->glActiveTexture(GL_TEXTURE0 +3);
        this->context()->functions()->glBindTexture(GL_TEXTURE_2D, legtex);

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

        //  hantex =     bindTexture(image4); //light
        this->context()->functions()->glActiveTexture(GL_TEXTURE0+4);
        this->context()->functions()->glBindTexture(GL_TEXTURE_2D, hantex);

        QImage image04 =  image4.convertToFormat(QImage::Format_RGBA8888);
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

        geometries->difftex = htex;
        geometries->spectex = btex;
        geometries->lighttex = hantex;
        geometries->normtex = legtex;
    }
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

//    for(int i=0;i<selectedmeshes.size();i++){
//        qDebug() << selectedmeshes.at(i);
//    }
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

//! [4]

//! [5]
void MainWidget::resizeGL(int w, int h)
{
    this->context()->functions()->glViewport(0, 0, w, h);
 //   projectionMatrix = Mat4f::perspective(Math::pi<float>() * 0.25f, float(w) / float(h), 0.01f, 1000.0f);

/*
    // Calculate aspect ratio
    qreal aspect = qreal(w) / qreal(h ? h : 1);

    // Set near plane to 3.0, far plane to 7.0, field of view 45 degrees
    const qreal zNear = 1.0, zFar = 70000.0, fov = 45.0;

    // Reset projection
    projection.setToIdentity();

    // Set perspective projection
    projection.perspective(fov, aspect, zNear, zFar);*/

    qreal aspect = qreal(w) / qreal(h ? h : 1);
    //  const qreal zNear = 0.0, zFar = 1000.0, fov = 120.0;
    const qreal zNear = 1.0, zFar = 7000.0, fov = 45.0;
    // Reset projection
    projection.setToIdentity();

    // Set perspective projection
    projection.perspective(fov, aspect, zNear, zFar);
}
//! [5]

void MainWidget::paintGL()
{
    //if(!(series.size() > 0)) return;

    // Clear color and depth buffer
    this->context()->functions()->glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    this->context()->functions()->glEnable(GL_DEPTH_TEST);
    this->context()->functions()->glDepthMask(GL_TRUE);
    //geometries->init();
//! [6]
    // Calculate model view transformation

/*
QMatrix4x4 matrix;


//QMatrix4x4 matrix2;
    matrix.translate(0.0, -50.0, -1000.0);
   // matrix.rotate(QQuaternion(90,0,0,1));
    matrix.rotate(90,0,1,0);
      // matrix.scale(.05,.05,.05);
       matrix.rotate(rotation);
       matrix.lookAt(QVector3D(1,0,0),QVector3D(0,0,0),QVector3D(0,1,0));
*/

    QMatrix4x4 matrix;
    matrix.translate(0.0, 0.0, m_distExp);
    matrix.rotate(m_trackBalls[2].rotation());

    program->setUniformValue("mousex",mousex);
    program->setUniformValue("mousey",mousey);

    float DEFAULT_LIGHT_Z = 0.075f;
// light pos
    QVector3D lightpos(mousex, 1 -mousey, DEFAULT_LIGHT_Z);

    QVector2D res(this->width(),this->height());

//Light RGB and intensity (alpha)
    QVector4D LIGHT_COLOR(0.8f, 0.8f, 0.8f, 2.0f);

//Ambient RGB and intensity (alpha)
    QVector4D AMBIENT_COLOR(0.6f, 0.6f, 1.0f, 0.2f);

//Attenuation coefficients for light falloff
    QVector3D FALLOFF(.4f, 3.0f, 20.0f);

    program->setUniformValue("Resolution",res);
    program->setUniformValue("LightPos",lightpos);
    program->setUniformValue("LightColor",LIGHT_COLOR);
    program->setUniformValue("AmbientColor",AMBIENT_COLOR);
    program->setUniformValue("Falloff",FALLOFF);

    // Set modelview-projection matrix
    program->setUniformValue("mvp_matrix",projection * matrix);
    // GLint location = glGetUniformLocation(program.programId(), "mvp_matrix");
    //glProgramUniformMatrix4fv(program.programId(), location, 1, true, &modelViewMatrix.elem[0][0]);
//! [6]

    if(selectedmeshes.size()>0){
        program->setUniformValue("selsize",(int)selectedmeshes.size());
        program->setUniformValueArray("selected_mesh_part",selectedmeshes.data(),selectedmeshes.size());
    }

    float timer = (QTime::currentTime().msec() % 500) / 250.0f;
    if (timer > 1.0f) timer = 2.0f - timer;
    program->setUniformValue("timer", timer);

    program->setUniformValue("lh", lh);
    // Draw  geometry
//glUseProgram(0);
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

    // this->context()->functions()->glEnable(GL_PRIMITIVE_RESTART);
    geometries->drawCubeGeometry(program);
    // this->context()->functions()->glDisable(GL_PRIMITIVE_RESTART);
    // geometries->drawCubeGeometry(&program);
    // emit this->newText(geometries->p1,geometries->p2,geometries->p3,geometries->p4,geometries->v1,geometries->v2,geometries->v3,geometries->v4);
    // glMultMatrixf(matrix2.data());
    glPolygonMode(GL_FRONT, GL_FILL);
    glPolygonMode(GL_BACK, GL_FILL);

    this->context()->functions()->glDisable(GL_DEPTH_TEST);

    // We need to flush the contents to the FBO before posting
    // the texture to the other thread, otherwise, we might
    // get unexpected results.
    this->context()->functions()->glFlush();

    // QMessageBox msgBox2;
    // msgBox2.setText("check gl error: " +QString(m_pFunctions->glGetError()));
    // msgBox2.exec();
}
