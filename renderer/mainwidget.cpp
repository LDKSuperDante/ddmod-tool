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
    QOpenGLWidget(parent,0),//QGLFormat::defaultFormat(),this,shared),
    texture(0),
    diffuse(0),
    specular(0),
    normal(0),
    light(0),
    m_distExp(-200000),
    angularSpeed(0)
{
     setMinimumSize(400, 400);

    m_trackBalls[0] = TrackBall(0.05f, QVector3D(0, 1, 0), TrackBall::Sphere);
    m_trackBalls[1] = TrackBall(0.005f, QVector3D(0, 0, 1), TrackBall::Sphere);
    m_trackBalls[2] = TrackBall(0.0f, QVector3D(0, 1, 0), TrackBall::Plane);

    m_timer = new QTimer(this);
    m_timer->setInterval(1);
    connect(m_timer, SIGNAL(timeout()), this, SLOT(update()));
    m_timer->start();

    m_time.start();
/*
console = new QTextEdit;
console->clear();
console->setWindowTitle("OpenGL Logger");
console->show();
*/
//this->showFullScreen();
 rightmousedown = 0;
 this->setContextMenuPolicy(Qt::CustomContextMenu);
 connect(this, SIGNAL(customContextMenuRequested(const QPoint &)),
         this, SLOT(ShowContextMenu(const QPoint &)));
 shadingmode = 0;

    cl_color = QColor(0,0,0.5*255).rgba();
    cm_color = QColor(255,255,0).rgba();
    lh = 0.0f;

   time = 100;
   time2 = 0;
   time3 = 0;

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

    timer2 = new QTimer(this);
    timer2->start(1);
    connect(timer2,SIGNAL(timeout()),this,SLOT(updatetimer()));

    // establish known blocktypes
    blocktype[QByteArray::fromHex("14D40020")]= 349437984;
    // redirect to ^
    blocktype[QByteArray::fromHex("14D40019")]= 349437977;
    blocktype[QByteArray::fromHex("BB424024")]= 3141681188;
    // redirect to ^
    blocktype[QByteArray::fromHex("1273701e")]= 309555230;
    // redirect to ^
    blocktype[QByteArray::fromHex("BB42401D")]= 3141681181;
    blocktype[QByteArray::fromHex("0CB68015")]= 213286933;
    blocktype[QByteArray::fromHex("A320C016")]= 2736832534;



}

MainWidget::~MainWidget()
{
    /*
    deleteTexture(htex);
        deleteTexture(btex);
            deleteTexture(b2tex);
                deleteTexture(hantex);
               deleteTexture(ftex);
                */
}

uint MainWidget::as_uint(const float x)
{
    return *(uint*)&x;
}

float MainWidget::as_float(const uint x)
{
    return *(float*)&x;
}

float MainWidget::half_to_float(const ushort x)
{
    const uint e = (x&0x7C00)>>10; // exponent
       const uint m = (x&0x03FF)<<13; // mantissa
       const uint v = as_uint((float)m)>>23; // evil log2 bit hack to count leading zeros in denormalized format
       return as_float((x&0x8000)<<16 | (e!=0)*((e+112)<<23|m) | ((e==0)&(m!=0))*((v-37)<<23|((m<<(150-v))&0x007FE000))); // sign : normalized : denormalized
}

ushort MainWidget::float_to_half(const float x)
{
    const uint b = as_uint(x)+0x00001000; // round-to-nearest-even: add last bit after truncated mantissa
     const uint e = (b&0x7F800000)>>23; // exponent
     const uint m = b&0x007FFFFF; // mantissa; in line below: 0x007FF000 = 0x00800000-0x00001000 = decimal indicator flag - initial rounding
     return (b&0x80000000)>>16 | (e>112)*((((e-112)<<10)&0x7C00)|m>>13) | ((e<113)&(e>101))*((((0x007FF000+m)>>(125-e))+1)>>1) | (e>143)*0x7FFF; // sign : normalized : denormalized : saturate

}

quint32 MainWidget::toUint(QByteArray &data, bool bigEndian)
{
    if (data.size() != 4)
        return 0;

    quint32 word = 0;

    if (bigEndian) {
        word = quint32((quint8(data.at(0)) << 24) |
                       (quint8(data.at(1)) << 16) |
                       (quint8(data.at(2)) <<  8) |
                       (quint8(data.at(3)) <<  0));
    } else {
        word = quint32((quint8(data.at(0)) <<  0) |
                       (quint8(data.at(1)) <<  8) |
                       (quint8(data.at(2)) << 16) |
                       (quint8(data.at(3)) << 24));

    }
    return word;
}

float MainWidget::toFloat(QByteArray &data, bool bigEndian)
{

    quint32 word = toUint(data, bigEndian);

     float *f = reinterpret_cast< float *>(&word);

    return *f;
}

/*
static void loadMatrix(const QMatrix4x4& m)
{
    // static to prevent glLoadMatrixf to fail on certain drivers
    static GLfloat mat[16];
    const float *data = m.constData();
    for (int index = 0; index < 16; ++index)
        mat[index] = data[index];
    glLoadMatrixf(mat);
}
*/

void MainWidget::updatetimer(){

    if(time == 100){
       dir = -1;
    }
    if( time == 0){
        dir = 1;
    }



time += dir;
//time = time % 100;

//qDebug() << time;
}



QPointF MainWidget::pixelPosToViewPos(const QPointF& p)
{
    return QPointF(2.0 * float(p.x()) / width() - 1.0,
                   1.0 - 2.0 * float(p.y()) / height());
}

//! [0]

void MainWidget::mousePressEvent(QMouseEvent *event)
{
    if (event->button() & Qt::RightButton) { // for double right click menu
        if(event->type() == QEvent::MouseButtonDblClick)
            rightmousedown = 1;
    }

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

        m_distExp += event->delta();

       // qDebug() << m_distExp;

}

void MainWidget::mouseReleaseEvent(QMouseEvent *event)
{



    // Mouse release position - mouse press position
    QVector2D diff = QVector2D(event->localPos()) - mousePressPosition;

    // Rotation axis is perpendicular to the mouse position difference
    // vector
    QVector3D n = QVector3D(diff.y(), diff.x(), 0.0).normalized();

    // Accelerate angular speed relative to the length of the mouse sweep
    qreal acc = diff.length() / 100.0;

    // Calculate new rotation axis as weighted sum
    rotationAxis = (rotationAxis * angularSpeed + n * acc).normalized();

    // Increase angular speed
    angularSpeed += acc;


    if (event->button() == Qt::LeftButton){ //Qt::MidButton) {

           m_trackBalls[2].release(pixelPosToViewPos(event->localPos()), QQuaternion());
        event->accept();
    }
}
//! [0]

//! [1]
void MainWidget::timerEvent(QTimerEvent *)
{
    // Decrease angular speed (friction)
    angularSpeed *= 0.99;

    // Stop rotation when speed goes below threshold
    if (angularSpeed < 0.01) {
        angularSpeed = 0.0;
    } else {
        // Update rotation
        rotation = QQuaternion::fromAxisAndAngle(rotationAxis, angularSpeed) * rotation;

        // Update scene
//        updateGL();
        paintGL();
    }
}

void MainWidget::initializeGL()
{

makeCurrent();
connect(context(), &QOpenGLContext::aboutToBeDestroyed, this, &MainWidget::DeleteFunctions);
m_pFunctions = new QOpenGLFunctions_4_3_Core();
//m_pFunctions = new QOpenGLFunctions();



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
    timer.start(12, this);
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


}

void MainWidget::gldebugmsg(const QOpenGLDebugMessage &/* debugMessage */)
{
  //  if (debugMessage.message()== "GL_INVALID_VALUE error generated. Index out of range.") return;
  // console->append( debugMessage.message());
  // console->append("\n");
}

void MainWidget::ShowContextMenu(const QPoint & pos)
{
    // right click menu items

    QPoint globalPos = this->mapToGlobal(pos);

    QMenu myMenu;


    QMenu *shading = myMenu.addMenu("Shading Mode");

    QAction *cv1 = shading->addAction("Smooth");
    cv1->setData(0);
    cv1->setCheckable(true);
    if(shadingmode == 0)
        cv1->setChecked(true);
    connect(cv1, SIGNAL(triggered()), this, SLOT(setSmoothShading()));

    QAction *cv2 = shading->addAction("Wireframe");
    cv2->setData(1);
    cv2->setCheckable(true);
    if(shadingmode == 1)
        cv2->setChecked(true);
    connect(cv2, SIGNAL(triggered()), this, SLOT(setWireframeShading()));

    QAction *cv3 = shading->addAction("Vertex");
    cv3->setCheckable(true);
    if(shadingmode == 2)
        cv3->setChecked(true);
    connect(cv3, SIGNAL(triggered()), this, SLOT(setVertexShading()));


    QMenu *rendering = myMenu.addMenu("Render Mode");

    QAction *cv4 = rendering->addAction("Triangles");
    cv4->setCheckable(true);
    if( geometries->rendermode  == 0)
        cv4->setChecked(true);
    connect(cv4, SIGNAL(triggered()), this, SLOT(setTriangleRendering()));

    QAction *cv5 = rendering->addAction("Triangle Strips");
    cv5->setCheckable(true);
    if(geometries->rendermode == 1)
        cv5->setChecked(true);
    connect(cv5, SIGNAL(triggered()), this, SLOT(setTriangleStripRendering()));




    myMenu.addAction("Cancel");

    // ...
    if(rightmousedown) { // double right click
        myMenu.exec(globalPos);
        rightmousedown = 0;
    }
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
    qDebug() << (image.isNull() ? "QImage error" : "QImage ok");


    tx= fileName.left(txcheck);
        tx.append("_CMM.dds");

        const QPixmap pixmap2(tx);


        const QImage image2 = pixmap2.toImage();
        qDebug() << (image2.isNull() ? "QImage error" : "QImage ok");



        tx= fileName.left(txcheck);
            tx.append("_NM.dds");

            const QPixmap pixmap3(tx);


            const QImage image3 = pixmap3.toImage();
            qDebug() << (image3.isNull() ? "QImage error" : "QImage ok");

            tx= fileName.left(txcheck);
                tx.append("_TM.dds");

                const QPixmap pixmap4(tx);


                const QImage image4 = pixmap4.toImage();
                qDebug() << (image4.isNull() ? "QImage error" : "QImage ok");


// fuck sakes

    this->context()->functions()->glEnable(GL_TEXTURE_2D);


  //  htex =     bindTexture(image); //diffuse
    this->context()->functions()->glGenTextures(1, &htex);
   this->context()->functions()->glActiveTexture(GL_TEXTURE0 + 1);
    this->context()->functions()->glBindTexture(GL_TEXTURE_2D, htex);

   QImage image0 =  image.convertToFormat(QImage::Format_RGBA8888);

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

    //btex =     bindTexture(image2); //specular
    this->context()->functions()->glGenTextures(1, &btex);
    this->context()->functions()->glActiveTexture(GL_TEXTURE0 + 2);
    this->context()->functions()->glBindTexture(GL_TEXTURE_2D, btex);

    QImage image02 =  image2.convertToFormat(QImage::Format_RGBA8888);

    // Set nearest filtering mode for texture minification
    this->context()->functions()->glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

    // Set bilinear filtering mode for texture magnification
    this->context()->functions()->glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    // Wrap texture coordinates by repeating
    // f.ex. texture coordinate (1.1, 1.2) is same as (0.1, 0.2)
    this->context()->functions()->glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    this->context()->functions()->glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    this->context()->functions()->glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, image02.width(), image02.height(), 0, GL_RGBA, GL_UNSIGNED_BYTE, image02.constBits());

    //legtex =     bindTexture(image3); //normal
    this->context()->functions()->glBindTexture(GL_TEXTURE_2D, 0);
    this->context()->functions()->glActiveTexture(GL_TEXTURE0);

    this->context()->functions()->glGenTextures(1, &legtex);
    this->context()->functions()->glActiveTexture(GL_TEXTURE0 +3);
    this->context()->functions()->glBindTexture(GL_TEXTURE_2D, legtex);

    QImage image03 =  image3.convertToFormat(QImage::Format_RGBA8888);

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
this->context()->functions()->glGenTextures(1, &hantex);
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
   // geometries->ftex = ftex;
    //updateGL();
                paintGL();
}

}

void MainWidget::onNewMeshdata(MainWidget::MOD_Mesh_Parts &mesh, std::vector<QByteArray> &lmatrices, std::vector<QByteArray> &amatrices)
{

    //spread sheet stuff memory leak fix later<
  QTableView*  tv = new QTableView;
  QStandardItemModel*  model = new QStandardItemModel;
    tv->setModel(model);
    tv->setWindowTitle(QString("PS3 FACES"));

    //spread sheet stuff

    Mparts = mesh;
    //geometries->Mparts = mesh;

    /////////////////  writing vbo permesh part data
    /// clear stuff check for mem leak later
    std::vector<VertexData> meshdat;
bool ok;
int skip = 0;
//qDebug() << amatrices.size();
//qDebug() << "test " << toFloat(amatrices[0],true);//.toHex().toLong(&ok,16);
QVector3D vbuffscale = QVector3D(toFloat(amatrices[0],true),toFloat(amatrices[5],true),toFloat(amatrices[10],true));
QVector4D bbmin = QVector4D(toFloat(amatrices[12],true)+toFloat(lmatrices[12],true),toFloat(amatrices[13],true)+toFloat(lmatrices[13],true),toFloat(amatrices[14],true)+toFloat(lmatrices[14],true),toFloat(amatrices[15],true)+toFloat(lmatrices[15],true));
                      for (int i=0;i<Mparts.parts.size();i++){


                        for(int j=0;j<Mparts.parts[i].vertexcount.toHex().toUInt(&ok,16);j++){
                            float vertexx,
                            vertexy,
                            vertexz,
                            nx,
                            ny,
                            nz,
                            txu,
                            txv ;
                            ushort shx,shy,shz;

                            if(blocktype.find(Mparts.parts[i].blocktype) != blocktype.end()){
                                switch(blocktype[Mparts.parts[i].blocktype]){
                                  case 2736832534: //unknown

                                    skip = -1;
                                    vertexx =  (float)Mparts.parts[i].meshdata[0].unksh1[j].toHex().toShort(&ok,16) / 32767.0f;
                                    vertexy =  (float)Mparts.parts[i].meshdata[0].unksh2[j].toHex().toShort(&ok,16) / 32767.0f;
                                    vertexz =  (float)Mparts.parts[i].meshdata[0].unksh3[j].toHex().toShort(&ok,16)  / 32767.0f;
                                    nx = 0.0f;
                                    ny = 0.0f;
                                    nz = 0.0f;
                                    txu = 0.0f;
                                    txv =   0.0f;
//                                   Writeshort(f, Mparts.parts[i].meshdata[0].unksh1[j]);
//                                   Writeshort(f, Mparts.parts[i].meshdata[0].unksh2[j]);
//                                   Writeshort(f, Mparts.parts[i].meshdata[0].unksh3[j]);
//                                   Writeshort(f, Mparts.parts[i].meshdata[0].unksh4[j]);
//                                   WriteBElong(f, Mparts.parts[i].meshdata[0].unklong1[j]);
//                                   WriteBElong(f, Mparts.parts[i].meshdata[0].unklong2[j]);
//                                   WriteBElong(f, Mparts.parts[i].meshdata[0].unklong3[j]);
//                                   WriteBElong(f, Mparts.parts[i].meshdata[0].unklong4[j]);
//                                   WriteBElong(f, Mparts.parts[i].meshdata[0].unklong5[j]);

                                    break;
                                  case 213286933: //unkown

                                    skip = -1;
//                                   Writeshort(f, Mparts.parts[i].meshdata[0].unksh1[j]);
//                                   Writeshort(f, Mparts.parts[i].meshdata[0].unksh2[j]);
//                                   Writeshort(f, Mparts.parts[i].meshdata[0].unksh3[j]);
//                                   Writeshort(f, Mparts.parts[i].meshdata[0].unksh4[j]);
//                                   WriteBElong(f, Mparts.parts[i].meshdata[0].unklong1[j]);
//                                   WriteBElong(f, Mparts.parts[i].meshdata[0].unklong2[j]);
//                                   WriteBElong(f, Mparts.parts[i].meshdata[0].unklong3[j]);
                                    vertexx =  (float)Mparts.parts[i].meshdata[0].unksh1[j].toHex().toShort(&ok,16) / 32767.0f;
                                    vertexy =  (float)Mparts.parts[i].meshdata[0].unksh2[j].toHex().toShort(&ok,16)  / 32767.0f;
                                    vertexz =  (float)Mparts.parts[i].meshdata[0].unksh3[j].toHex().toShort(&ok,16)  / 32767.0f;
                                    nx = 0.0f;
                                    ny = 0.0f;
                                    nz = 0.0f;
                                    txu = 0.0f;
                                    txv =   0.0f;
                                    break;
                                  case 349437977:
                                  case 349437984: //appears in dd;da weapons?

//                                   Writeshort(f, Mparts.parts[i].meshdata[0].verticies[(j*3)+0]);
//                                   Writeshort(f, Mparts.parts[i].meshdata[0].verticies[(j*3)+1]);
//                                   Writeshort(f, Mparts.parts[i].meshdata[0].verticies[(j*3)+2]);
//                                   Writeshort(f, Mparts.parts[i].meshdata[0].weights[(j*3)]);
//                                   Writebyte(f, Mparts.parts[i].meshdata[0].normals[(j*3)+0]);
//                                   Writebyte(f, Mparts.parts[i].meshdata[0].normals[(j*3)+1]);
//                                   Writebyte(f, Mparts.parts[i].meshdata[0].normals[(j*3)+2]);
//                                   Writebyte(f, Mparts.parts[i].meshdata[0].unkbyte1[j]);
//                                   WriteBElong(f, Mparts.parts[i].meshdata[0].unklong1[j]);
//                                   Writebyte(f, Mparts.parts[i].meshdata[0].bns[(j*4)+0]);
//                                   Writebyte(f, Mparts.parts[i].meshdata[0].bns[(j*4)+1]);
//                                   Writebyte(f, Mparts.parts[i].meshdata[0].bns[(j*4)+2]);
//                                   Writebyte(f, Mparts.parts[i].meshdata[0].bns[(j*4)+3]);
//                                   Writeshort(f, Mparts.parts[i].meshdata[0].texturemap[(j*2)+0]);
//                                   Writeshort(f, Mparts.parts[i].meshdata[0].texturemap[(j*2)+1]);
//                                   Writeshort(f, Mparts.parts[i].meshdata[0].weights[(j*3)+1]);
//                                   Writeshort(f, Mparts.parts[i].meshdata[0].weights[(j*3)+2]);

                                     shx = Mparts.parts[i].meshdata[0].verticies[(j*3)+0].toHex().toUShort(&ok,16);
                                    if (shx > 32767 ){
                                       vertexx =  -1 -(shx ^ 0xFFFF);
                                       vertexx /= 32767.0f;
                                    }
                                    else{
                                        vertexx = shx / 32767.0f;
                                    }

                                     shy = Mparts.parts[i].meshdata[0].verticies[(j*3)+1].toHex().toUShort(&ok,16);
                                    if (shy > 32767 ){
                                       vertexy =  -1 -(shy ^ 0xFFFF);
                                       vertexy /= 32767.0f;
                                    }
                                    else{
                                        vertexy = shy / 32767.0f;
                                    }

                                     shz = Mparts.parts[i].meshdata[0].verticies[(j*3)+2].toHex().toUShort(&ok,16);
                                    if (shz > 32767 ){
                                       vertexz =  -1 -(shz ^ 0xFFFF);
                                       vertexz /= 32767.0f;
                                    }
                                    else{
                                      vertexz = shz / 32767.0f;
                                    }

//                                    qDebug() << "x: " << Mparts.parts[i].meshdata[0].verticies[(j*3)+0].toHex() << "x: " << Mparts.parts[i].meshdata[0].verticies[(j*3)+0].toHex().toShort(&ok,16);
//                                    qDebug() << "y: " << Mparts.parts[i].meshdata[0].verticies[(j*3)+1].toHex() << "y: " << Mparts.parts[i].meshdata[0].verticies[(j*3)+1].toHex().toShort(&ok,16);
//                                    qDebug() << "z: " << Mparts.parts[i].meshdata[0].verticies[(j*3)+2].toHex() << "z: " << Mparts.parts[i].meshdata[0].verticies[(j*3)+2].toHex().toShort(&ok,16);

                                    nx = (toFloat(Mparts.parts[i].meshdata[0].normals[(j*3)+0],true)); // -127 ) *0.0078125; // -127 ) *0.0078125
                                    ny = (toFloat(Mparts.parts[i].meshdata[0].normals[(j*3)+1],true)); // -127 ) *0.0078125;
                                    nz = (toFloat(Mparts.parts[i].meshdata[0].normals[(j*3)+2],true)); // -127 ) *0.0078125;
                                    txu = half_to_float(Mparts.parts[i].meshdata[0].texturemap[(j*2)+0].toHex().toUShort(&ok,16) );
                                    txv =   half_to_float(Mparts.parts[i].meshdata[0].texturemap[(j*2)+1].toHex().toUShort(&ok,16) );     // 1 - ??
                                    break;
                                   case 3141681188:
                                   case 309555230:
                                   case 3141681181:

//                                    Writeshort(f, Mparts.parts[i].meshdata[0].verticies[(j*3)+0]);
//                                    Writeshort(f, Mparts.parts[i].meshdata[0].verticies[(j*3)+1]);
//                                    Writeshort(f, Mparts.parts[i].meshdata[0].verticies[(j*3)+2]);
//                                    Writeshort(f, Mparts.parts[i].meshdata[0].weights[(j*7)]);
//                                    Writebyte(f, Mparts.parts[i].meshdata[0].normals[(j*3)+0]);
//                                    Writebyte(f, Mparts.parts[i].meshdata[0].normals[(j*3)+1]);
//                                    Writebyte(f, Mparts.parts[i].meshdata[0].normals[(j*3)+2]);
//                                    Writebyte(f, Mparts.parts[i].meshdata[0].unkbyte1[j]);

//                                    Writebyte(f, Mparts.parts[i].meshdata[0].weights[(j*7)+1]);
//                                    Writebyte(f, Mparts.parts[i].meshdata[0].weights[(j*7)+2]);
//                                    Writebyte(f, Mparts.parts[i].meshdata[0].weights[(j*7)+3]);
//                                    Writebyte(f, Mparts.parts[i].meshdata[0].weights[(j*7)+4]);

//                                    Writebyte(f, Mparts.parts[i].meshdata[0].bns[(j*8)+0]);
//                                    Writebyte(f, Mparts.parts[i].meshdata[0].bns[(j*8)+1]);
//                                    Writebyte(f, Mparts.parts[i].meshdata[0].bns[(j*8)+2]);
//                                    Writebyte(f, Mparts.parts[i].meshdata[0].bns[(j*8)+3]);
//                                    Writebyte(f, Mparts.parts[i].meshdata[0].bns[(j*8)+4]);
//                                    Writebyte(f, Mparts.parts[i].meshdata[0].bns[(j*8)+5]);
//                                    Writebyte(f, Mparts.parts[i].meshdata[0].bns[(j*8)+6]);
//                                    Writebyte(f, Mparts.parts[i].meshdata[0].bns[(j*8)+7]);

//                                    Writeshort(f, Mparts.parts[i].meshdata[0].texturemap[(j*2)+0]);
//                                    Writeshort(f, Mparts.parts[i].meshdata[0].texturemap[(j*2)+1]);
//                                    Writeshort(f, Mparts.parts[i].meshdata[0].weights[(j*7)+5]);
//                                    Writeshort(f, Mparts.parts[i].meshdata[0].weights[(j*7)+6]);
//                                    WriteBElong(f, Mparts.parts[i].meshdata[0].unklong1[j]);
                                    shx = Mparts.parts[i].meshdata[0].verticies[(j*3)+0].toHex().toUShort(&ok,16);
                                   if (shx > 32767 ){
                                      vertexx =  -1 -(shx ^ 0xFFFF);
                                      vertexx /= 32767.0f;
                                   }
                                   else{
                                       vertexx = shx / 32767.0f;
                                   }

                                    shy = Mparts.parts[i].meshdata[0].verticies[(j*3)+1].toHex().toUShort(&ok,16);
                                   if (shy > 32767 ){
                                      vertexy =  -1 -(shy ^ 0xFFFF);
                                      vertexy /= 32767.0f;
                                   }
                                   else{
                                       vertexy = shy / 32767.0f;
                                   }

                                    shz = Mparts.parts[i].meshdata[0].verticies[(j*3)+2].toHex().toUShort(&ok,16);
                                   if (shz > 32767 ){
                                      vertexz =  -1 -(shz ^ 0xFFFF);
                                      vertexz /= 32767.0f;
                                   }
                                   else{
                                     vertexz = shz / 32767.0f;
                                   }

//                                    qDebug() << "x: " << Mparts.parts[i].meshdata[0].verticies[(j*3)+0].toHex() << "x: " << Mparts.parts[i].meshdata[0].verticies[(j*3)+0].toHex().toShort(&ok,16);
//                                    qDebug() << "y: " << Mparts.parts[i].meshdata[0].verticies[(j*3)+1].toHex() << "y: " << Mparts.parts[i].meshdata[0].verticies[(j*3)+1].toHex().toShort(&ok,16);
//                                    qDebug() << "z: " << Mparts.parts[i].meshdata[0].verticies[(j*3)+2].toHex() << "z: " << Mparts.parts[i].meshdata[0].verticies[(j*3)+2].toHex().toShort(&ok,16);

                                    nx = (toFloat(Mparts.parts[i].meshdata[0].normals[(j*3)+0],true)); //-127 ) *0.0078125; // -127 ) *0.0078125
                                    ny = (toFloat(Mparts.parts[i].meshdata[0].normals[(j*3)+1],true)); //-127 ) *0.0078125;
                                    nz = (toFloat(Mparts.parts[i].meshdata[0].normals[(j*3)+2],true)); //-127 ) *0.0078125;
                                    txu = half_to_float(Mparts.parts[i].meshdata[0].texturemap[(j*2)+0].toHex().toUShort(&ok,16) );
                                    txv =  half_to_float(Mparts.parts[i].meshdata[0].texturemap[(j*2)+1].toHex().toUShort(&ok,16) );     // 1 - ??

                                    break;
                                  }

                                //QVector3D(vertexx,vertexy,vertexz) * QMatrix3x4()
                                float mtdat[]={
                                    1.0f,0.0f,0.0f,
                                                                                        0.0f,0.0f,1.0f,
                                                                                        0.0f,-1.0f,0.0f,
                                                                                        0.0f,0.0f,0.0f

                                };
                                QMatrix3x4 MTFormat(mtdat);
                                float vecdat[] ={ vertexx*vbuffscale.x()+bbmin.x(),vertexy*vbuffscale.y()+bbmin.y(),vertexz*vbuffscale.z()+bbmin.z() } ;
                               QGenericMatrix< 1, 3, float > vec3d(vecdat);
                               QGenericMatrix< 1, 4, float > vec4d =  MTFormat *vec3d;//vec3d *MTFormat; // <-logical but qt has it flipped why?

                                VertexData vertex = { QVector4D(vec4d.data()[0],vec4d.data()[1],vec4d.data()[2],vec4d.data()[3]) ,
                                                  QVector4D(nx,ny,nz,0),
                                                 QVector4D(txu,txv,0.0,i)
                                                };
                                if(skip !=-1){
                                meshdat.push_back(vertex);
                                              }
                                else{
                                    //do not add vertex

                                    skip = 0;
                                    continue;
                                }

//                                qDebug() << "x: " <<  vertexx << "y: " << vertexy <<"z: " << vertexz ;
//                                                                qDebug() << "mtx: " << vec4d.data()[0] << "mty: " << vec4d.data()[1] << "mtz: " << vec4d.data()[2] << "mtw: " << vec4d.data()[3];
//                                qDebug() << "bbx: " <<  bbmin.x() << "bby: " << bbmin.y() <<"bbz: " << bbmin.z() ;
//                                                                qDebug() << "vbx: " <<  vbuffscale.x() << "vby: " << vbuffscale.y() <<"vbz: " << vbuffscale.z() ;
//                             //    qDebug() << "u: " <<  txu << "v: " << txv ;
                             //   qDebug() << blocktype[Mparts.parts[i].blocktype];
                            }

                       }

                    }
                      geometries->mesh = meshdat;
                      // start writing faces

                      std::vector< unsigned int > faces;
                      unsigned int meshpartcount = 0;
                      QByteArray last = QByteArray::fromHex("FFFF");
                      QByteArray first = QByteArray::fromHex("FFFF");
                       long int facescounter =0;
                      for (int i=0;i<Mparts.parts.size();i++){

                        QList<QStandardItem*> header;
                        header.append(new QStandardItem(QString("Mesh Part:")));
                        header.append(new QStandardItem(QString::number(i)));
                        header[0]->setBackground(Qt::black);
                        header[1]->setBackground(Qt::black);
                        model->appendRow(header);
                      if( blocktype[Mparts.parts[i].blocktype] == 2736832534 || blocktype[Mparts.parts[i].blocktype] == 213286933 ){
                      //skip?
                          continue;
                      }


                              for(int j=0;j<Mparts.parts[i].meshdata[0].faces.size();j++){ // per strip
                                 QList<QStandardItem*> strip;
                                  for(int k=0;k<Mparts.parts[i].meshdata[0].faces[j].size();k++){
                                     /* if (k == 0){
                                          first = Mparts.parts[i].meshdata[0].faces[j][k];
                                          if( i != 0 ){ // write double if not first mesh part and first strip
                                              faces.push_back(first.toHex().toInt(&ok,16));
                                             strip.append(new QStandardItem(QString::number(first.toHex().toInt(&ok,16))));
                                              facescounter++;
                                          }
                                          else if (j !=0 ){
                                              faces.push_back(first.toHex().toInt(&ok,16));
                                              strip.append(new QStandardItem(QString::number(first.toHex().toInt(&ok,16))));
                                              facescounter++;
                                          }

                                      }
                                   */
                                      if (j !=0 && k == 0){
                                          first = Mparts.parts[i].meshdata[0].faces[j][k];
                                          faces.push_back(first.toHex().toInt(&ok,16)+meshpartcount);
                                          strip.append(new QStandardItem(QString::number(first.toHex().toInt(&ok,16))));
                                          facescounter++;
                                          if(!(Mparts.parts[i].meshdata[0].faces[j-1].size() % 2 == 0)){
                                              // check last strip was odd
                                              faces.push_back(first.toHex().toInt(&ok,16)+meshpartcount);
                                              strip.append(new QStandardItem(QString::number(first.toHex().toInt(&ok,16))));
                                              facescounter++;
                                          }

                                        }

                                      last = Mparts.parts[i].meshdata[0].faces[j][k];

                                      faces.push_back(last.toHex().toInt(&ok,16)+meshpartcount);
                                       strip.append(new QStandardItem(QString::number(last.toHex().toInt(&ok,16))));
                                      facescounter++;
                                    }
                                   // write double
                                      faces.push_back(last.toHex().toInt(&ok,16)+meshpartcount);
                                       strip.append(new QStandardItem(QString::number(last.toHex().toInt(&ok,16))));
                                      facescounter++;


                                   model->appendRow(strip);
                              }
meshpartcount += Mparts.parts[i].vertexcount.toHex().toUInt(&ok,16);
                      }

                      geometries->indecies= faces;

//tv->show();

                          // For cube we would need only 8 vertices but we have to
                          // duplicate vertex for each face because texture coordinate
                          // is different.
                          std::vector< VertexData > vertices = {
                              // Vertex data for face 0
                              {QVector4D(-1.0f, -1.0f,  1.0f,1.0f), QVector4D(0.0f, 0.0f,1.0f,1.0f), QVector4D(0.0f, 0.0f,1.0f,1.0f)},  // v0
                              {QVector4D( 1.0f, -1.0f,  1.0f,1.0f), QVector4D(0.0f, 0.0f,1.0f,1.0f), QVector4D(0.33f, 0.0f,1.0f,1.0f)}, // v1
                              {QVector4D(-1.0f,  1.0f,  1.0f,1.0f), QVector4D(0.0f, 0.0f,1.0f,1.0f), QVector4D(0.0f, 0.5f,1.0f,1.0f)},  // v2
                              {QVector4D( 1.0f,  1.0f,  1.0f,1.0f), QVector4D(0.0f, 0.0f,1.0f,1.0f), QVector4D(0.33f, 0.5f,1.0f,1.0f)}, // v3

                              // Vertex data for face 1
                              {QVector4D( 1.0f, -1.0f,  1.0f,1.0f), QVector4D(0.0f, 0.0f,1.0f,1.0f), QVector4D( 0.0f, 0.5f,1.0f,1.0f)}, // v4
                              {QVector4D( 1.0f, -1.0f, -1.0f,1.0f), QVector4D(0.0f, 0.0f,1.0f,1.0f), QVector4D(0.33f, 0.5f,1.0f,1.0f)}, // v5
                              {QVector4D( 1.0f,  1.0f,  1.0f,1.0f), QVector4D(0.0f, 0.0f,1.0f,1.0f), QVector4D(0.0f, 1.0f,1.0f,1.0f)},  // v6
                              {QVector4D( 1.0f,  1.0f, -1.0f,1.0f), QVector4D(0.0f, 0.0f,1.0f,1.0f), QVector4D(0.33f, 1.0f,1.0f,1.0f)}, // v7

                              // Vertex data for face 2
                              {QVector4D( 1.0f, -1.0f, -1.0f,1.0f), QVector4D(0.0f, 0.0f,1.0f,1.0f), QVector4D(0.66f, 0.5f,1.0f,1.0f)}, // v8
                              {QVector4D(-1.0f, -1.0f, -1.0f,1.0f), QVector4D(0.0f, 0.0f,1.0f,1.0f), QVector4D(1.0f, 0.5f,1.0f,1.0f)},  // v9
                              {QVector4D( 1.0f,  1.0f, -1.0f,1.0f), QVector4D(0.0f, 0.0f,1.0f,1.0f), QVector4D(0.66f, 1.0f,1.0f,1.0f)}, // v10
                              {QVector4D(-1.0f,  1.0f, -1.0f,1.0f), QVector4D(0.0f, 0.0f,1.0f,1.0f), QVector4D(1.0f, 1.0f,1.0f,1.0f)},  // v11

                              // Vertex data for face 3
                              {QVector4D(-1.0f, -1.0f, -1.0f,1.0f), QVector4D(0.0f, 0.0f,1.0f,1.0f), QVector4D(0.66f, 0.0f,1.0f,1.0f)}, // v12
                              {QVector4D(-1.0f, -1.0f,  1.0f,1.0f), QVector4D(0.0f, 0.0f,1.0f,1.0f), QVector4D(1.0f, 0.0f,1.0f,1.0f)},  // v13
                              {QVector4D(-1.0f,  1.0f, -1.0f,1.0f), QVector4D(0.0f, 0.0f,1.0f,1.0f), QVector4D(0.66f, 0.5f,1.0f,1.0f)}, // v14
                              {QVector4D(-1.0f,  1.0f,  1.0f,1.0f), QVector4D(0.0f, 0.0f,1.0f,1.0f), QVector4D(1.0f, 0.5f,1.0f,1.0f)},  // v15

                              // Vertex data for face 4
                              {QVector4D(-1.0f, -1.0f, -1.0f,1.0f), QVector4D(0.0f, 0.0f,1.0f,1.0f), QVector4D(0.33f, 0.0f,1.0f,1.0f)}, // v16
                              {QVector4D( 1.0f, -1.0f, -1.0f,1.0f), QVector4D(0.0f, 0.0f,1.0f,1.0f), QVector4D(0.66f, 0.0f,1.0f,1.0f)}, // v17
                              {QVector4D(-1.0f, -1.0f,  1.0f,1.0f), QVector4D(0.0f, 0.0f,1.0f,1.0f), QVector4D(0.33f, 0.5f,1.0f,1.0f)}, // v18
                              {QVector4D( 1.0f, -1.0f,  1.0f,1.0f), QVector4D(0.0f, 0.0f,1.0f,1.0f), QVector4D(0.66f, 0.5f,1.0f,1.0f)}, // v19

                              // Vertex data for face 5
                              {QVector4D(-1.0f,  1.0f,  1.0f,1.0f), QVector4D(0.0f, 0.0f,1.0f,1.0f), QVector4D(0.33f, 0.5f,1.0f,1.0f)}, // v20
                              {QVector4D( 1.0f,  1.0f,  1.0f,1.0f), QVector4D(0.0f, 0.0f,1.0f,1.0f), QVector4D(0.66f, 0.5f,1.0f,1.0f)}, // v21
                              {QVector4D(-1.0f,  1.0f, -1.0f,1.0f), QVector4D(0.0f, 0.0f,1.0f,1.0f), QVector4D(0.33f, 1.0f,1.0f,1.0f)}, // v22
                              {QVector4D( 1.0f,  1.0f, -1.0f,1.0f), QVector4D(0.0f, 0.0f,1.0f,1.0f), QVector4D(0.66f, 1.0f,1.0f,1.0f)}  // v23
                          };
                  //    geometries->mesh = vertices;
                          // Indices for drawing cube faces using triangle strips.
                          // Triangle strips can be connected by duplicating indices
                          // between the strips. If connecting strips have opposite
                          // vertex order then last index of the first strip and first
                          // index of the second strip needs to be duplicated. If
                          // connecting strips have same vertex order then only last
                          // index of the first strip needs to be duplicated.
                          std::vector< unsigned int > indices = {
                               0,  1,  2,  3,  3,     // Face 0 - triangle strip ( v0,  v1,  v2,  v3)
                               4,  4,  5,  6,  7,  7, // Face 1 - triangle strip ( v4,  v5,  v6,  v7)
                               8,  8,  9, 10, 11, 11, // Face 2 - triangle strip ( v8,  v9, v10, v11)
                              12, 12, 13, 14, 15, 15, // Face 3 - triangle strip (v12, v13, v14, v15)
                              16, 16, 17, 18, 19, 19, // Face 4 - triangle strip (v16, v17, v18, v19)
                              20, 20, 21, 22, 23      // Face 5 - triangle strip (v20, v21, v22, v23)
                          };
                  //    geometries->indecies = indices;

                     geometries->initCubeGeometry();
//    updateGL();
                     paintGL();
}

void MainWidget::onNewDAPCMeshdata(MainWidget::MOD_Mesh_Parts &mesh)
{


    //spread sheet stuff memory leak fix later<
  QTableView*  tv = new QTableView;
  QStandardItemModel*  model = new QStandardItemModel;
    tv->setModel(model);
    tv->setWindowTitle(QString("PC FACES"));

    //spread sheet stuff

    Mparts = mesh;
    //geometries->Mparts = mesh;

    /////////////////  writing vbo permesh part data
    /// clear stuff check for mem leak later
    std::vector<VertexData> meshdat;
bool ok;
                      for (int i=0;i<Mparts.parts.size();i++){


                        for(int j=0;j<Mparts.parts[i].vertexcount.toHex().toUInt(&ok,16);j++){
                            float vertexx,
                            vertexy,
                            vertexz,
                            nx,
                            ny,
                            nz,
                            txu,
                            txv ;

                            if(blocktype.find(Mparts.parts[i].blocktype) != blocktype.end()){
                                switch(blocktype[Mparts.parts[i].blocktype]){
                                  case 2736832534: //unknown

                                    vertexx =  (float)Mparts.parts[i].meshdata[0].unksh1[j].toHex().toShort(&ok,16) / 32767.0f;
                                    vertexy =  (float)Mparts.parts[i].meshdata[0].unksh2[j].toHex().toShort(&ok,16)  / 32767.0f;
                                    vertexz =  (float)Mparts.parts[i].meshdata[0].unksh3[j].toHex().toShort(&ok,16)  / 32767.0f;
                                    nx = 0.0f;
                                    ny = 0.0f;
                                    nz = 0.0f;
                                    txu = 0.0f;
                                    txv =   0.0f;
//                                   Writeshort(f, Mparts.parts[i].meshdata[0].unksh1[j]);
//                                   Writeshort(f, Mparts.parts[i].meshdata[0].unksh2[j]);
//                                   Writeshort(f, Mparts.parts[i].meshdata[0].unksh3[j]);
//                                   Writeshort(f, Mparts.parts[i].meshdata[0].unksh4[j]);
//                                   WriteBElong(f, Mparts.parts[i].meshdata[0].unklong1[j]);
//                                   WriteBElong(f, Mparts.parts[i].meshdata[0].unklong2[j]);
//                                   WriteBElong(f, Mparts.parts[i].meshdata[0].unklong3[j]);
//                                   WriteBElong(f, Mparts.parts[i].meshdata[0].unklong4[j]);
//                                   WriteBElong(f, Mparts.parts[i].meshdata[0].unklong5[j]);

                                    break;
                                  case 213286933: //unkown

//                                   Writeshort(f, Mparts.parts[i].meshdata[0].unksh1[j]);
//                                   Writeshort(f, Mparts.parts[i].meshdata[0].unksh2[j]);
//                                   Writeshort(f, Mparts.parts[i].meshdata[0].unksh3[j]);
//                                   Writeshort(f, Mparts.parts[i].meshdata[0].unksh4[j]);
//                                   WriteBElong(f, Mparts.parts[i].meshdata[0].unklong1[j]);
//                                   WriteBElong(f, Mparts.parts[i].meshdata[0].unklong2[j]);
//                                   WriteBElong(f, Mparts.parts[i].meshdata[0].unklong3[j]);
                                    vertexx =  (float)Mparts.parts[i].meshdata[0].unksh1[j].toHex().toShort(&ok,16)  / 32767.0f;
                                    vertexy =  (float)Mparts.parts[i].meshdata[0].unksh2[j].toHex().toShort(&ok,16)  / 32767.0f;
                                    vertexz =  (float)Mparts.parts[i].meshdata[0].unksh3[j].toHex().toShort(&ok,16)  / 32767.0f;
                                    nx = 0.0f;
                                    ny = 0.0f;
                                    nz = 0.0f;
                                    txu = 0.0f;
                                    txv =   0.0f;
                                    break;
                                  case 349437977:
                                  case 349437984: //appears in dd;da weapons?

//                                   Writeshort(f, Mparts.parts[i].meshdata[0].verticies[(j*3)+0]);
//                                   Writeshort(f, Mparts.parts[i].meshdata[0].verticies[(j*3)+1]);
//                                   Writeshort(f, Mparts.parts[i].meshdata[0].verticies[(j*3)+2]);
//                                   Writeshort(f, Mparts.parts[i].meshdata[0].weights[(j*3)]);
//                                   Writebyte(f, Mparts.parts[i].meshdata[0].normals[(j*3)+0]);
//                                   Writebyte(f, Mparts.parts[i].meshdata[0].normals[(j*3)+1]);
//                                   Writebyte(f, Mparts.parts[i].meshdata[0].normals[(j*3)+2]);
//                                   Writebyte(f, Mparts.parts[i].meshdata[0].unkbyte1[j]);
//                                   WriteBElong(f, Mparts.parts[i].meshdata[0].unklong1[j]);
//                                   Writebyte(f, Mparts.parts[i].meshdata[0].bns[(j*4)+0]);
//                                   Writebyte(f, Mparts.parts[i].meshdata[0].bns[(j*4)+1]);
//                                   Writebyte(f, Mparts.parts[i].meshdata[0].bns[(j*4)+2]);
//                                   Writebyte(f, Mparts.parts[i].meshdata[0].bns[(j*4)+3]);
//                                   Writeshort(f, Mparts.parts[i].meshdata[0].texturemap[(j*2)+0]);
//                                   Writeshort(f, Mparts.parts[i].meshdata[0].texturemap[(j*2)+1]);
//                                   Writeshort(f, Mparts.parts[i].meshdata[0].weights[(j*3)+1]);
//                                   Writeshort(f, Mparts.parts[i].meshdata[0].weights[(j*3)+2]);

                                    vertexx = (float)Mparts.parts[i].meshdata[0].verticies[(j*3)+0].toHex().toShort(&ok,16) / 32767.0f; // / 32767.0f
                                    vertexy = (float)Mparts.parts[i].meshdata[0].verticies[(j*3)+1].toHex().toShort(&ok,16) / 32767.0f;
                                    vertexz = (float)Mparts.parts[i].meshdata[0].verticies[(j*3)+2].toHex().toShort(&ok,16) / 32767.0f;
                                    nx = (Mparts.parts[i].meshdata[0].normals[(j*3)+0].toHex().toFloat(&ok) -127 ) *0.0078125; // -127 ) *0.0078125
                                    ny = (Mparts.parts[i].meshdata[0].normals[(j*3)+1].toHex().toFloat(&ok) -127 ) *0.0078125;
                                    nz = (Mparts.parts[i].meshdata[0].normals[(j*3)+2].toHex().toFloat(&ok) -127 ) *0.0078125;
                                    txu = half_to_float(Mparts.parts[i].meshdata[0].texturemap[(j*2)+0].toHex().toUShort(&ok,16) );
                                    txv =   half_to_float(Mparts.parts[i].meshdata[0].texturemap[(j*2)+1].toHex().toUShort(&ok,16) );     // 1 - ??
                                    break;
                                   case 3141681188:
                                   case 309555230:
                                   case 3141681181:

//                                    Writeshort(f, Mparts.parts[i].meshdata[0].verticies[(j*3)+0]);
//                                    Writeshort(f, Mparts.parts[i].meshdata[0].verticies[(j*3)+1]);
//                                    Writeshort(f, Mparts.parts[i].meshdata[0].verticies[(j*3)+2]);
//                                    Writeshort(f, Mparts.parts[i].meshdata[0].weights[(j*7)]);
//                                    Writebyte(f, Mparts.parts[i].meshdata[0].normals[(j*3)+0]);
//                                    Writebyte(f, Mparts.parts[i].meshdata[0].normals[(j*3)+1]);
//                                    Writebyte(f, Mparts.parts[i].meshdata[0].normals[(j*3)+2]);
//                                    Writebyte(f, Mparts.parts[i].meshdata[0].unkbyte1[j]);

//                                    Writebyte(f, Mparts.parts[i].meshdata[0].weights[(j*7)+1]);
//                                    Writebyte(f, Mparts.parts[i].meshdata[0].weights[(j*7)+2]);
//                                    Writebyte(f, Mparts.parts[i].meshdata[0].weights[(j*7)+3]);
//                                    Writebyte(f, Mparts.parts[i].meshdata[0].weights[(j*7)+4]);

//                                    Writebyte(f, Mparts.parts[i].meshdata[0].bns[(j*8)+0]);
//                                    Writebyte(f, Mparts.parts[i].meshdata[0].bns[(j*8)+1]);
//                                    Writebyte(f, Mparts.parts[i].meshdata[0].bns[(j*8)+2]);
//                                    Writebyte(f, Mparts.parts[i].meshdata[0].bns[(j*8)+3]);
//                                    Writebyte(f, Mparts.parts[i].meshdata[0].bns[(j*8)+4]);
//                                    Writebyte(f, Mparts.parts[i].meshdata[0].bns[(j*8)+5]);
//                                    Writebyte(f, Mparts.parts[i].meshdata[0].bns[(j*8)+6]);
//                                    Writebyte(f, Mparts.parts[i].meshdata[0].bns[(j*8)+7]);

//                                    Writeshort(f, Mparts.parts[i].meshdata[0].texturemap[(j*2)+0]);
//                                    Writeshort(f, Mparts.parts[i].meshdata[0].texturemap[(j*2)+1]);
//                                    Writeshort(f, Mparts.parts[i].meshdata[0].weights[(j*7)+5]);
//                                    Writeshort(f, Mparts.parts[i].meshdata[0].weights[(j*7)+6]);
//                                    WriteBElong(f, Mparts.parts[i].meshdata[0].unklong1[j]);
                                    vertexx = (float)Mparts.parts[i].meshdata[0].verticies[(j*3)+0].toHex().toShort(&ok,16) / 32767.0f; // / 32767.0f
                                    vertexy = (float)Mparts.parts[i].meshdata[0].verticies[(j*3)+1].toHex().toShort(&ok,16) / 32767.0f;
                                    vertexz = (float)Mparts.parts[i].meshdata[0].verticies[(j*3)+2].toHex().toShort(&ok,16) / 32767.0f;
                                    nx = (Mparts.parts[i].meshdata[0].normals[(j*3)+0].toHex().toFloat(&ok)-127 ) *0.0078125; // -127 ) *0.0078125
                                    ny = (Mparts.parts[i].meshdata[0].normals[(j*3)+1].toHex().toFloat(&ok)-127 ) *0.0078125;
                                    nz = (Mparts.parts[i].meshdata[0].normals[(j*3)+2].toHex().toFloat(&ok)-127 ) *0.0078125;
                                    txu = half_to_float(Mparts.parts[i].meshdata[0].texturemap[(j*2)+0].toHex().toUShort(&ok,16) );
                                    txv =   half_to_float(Mparts.parts[i].meshdata[0].texturemap[(j*2)+1].toHex().toUShort(&ok,16) );     // 1 - ??

                                    break;
                                  }

                                /*
                                VertexData vertex = { QVector4D(vertexx,vertexy,vertexz,0.0),
                                                  QVector4D(nx,ny,nz,1.0),
                                                 QVector4D(txu,txv,0.0,i)
                                                };
                                                */
                                //QVector3D(vertexx,vertexy,vertexz) * QMatrix3x4()
                                float mtdat[]={
                                    1.0f,0.0f,0.0f,
                                                                                        0.0f,0.0f,1.0f,
                                                                                        0.0f,-1.0f,0.0f,
                                                                                        0.0f,0.0f,0.0f

                                };
                                QMatrix3x4 MTFormat(mtdat);
                                float vecdat[] ={ vertexx,vertexy,vertexz } ;
                               QGenericMatrix< 1, 3, float > vec3d(vecdat);
                               QGenericMatrix< 1, 4, float > vec4d =  MTFormat *vec3d;//vec3d *MTFormat; // <-logical but qt has it flipped why?

                                VertexData vertex = { QVector4D(vec4d.data()[0],vec4d.data()[1],vec4d.data()[2],vec4d.data()[3]) ,
                                                  QVector4D(nx,ny,nz,1.0),
                                                 QVector4D(txu,txv,0.0,i)
                                                };
                                meshdat.push_back(vertex);
//                                qDebug() << "x: " <<  vertexx << "y: " << vertexy <<"z: " << vertexz ;
//                                qDebug() << "mtx: " << vec4d.data()[0] << "mty: " << vec4d.data()[1] << "mtz: " << vec4d.data()[2] << "mtw: " << vec4d.data()[3];
                             //    qDebug() << "u: " <<  txu << "v: " << txv ;
                             //   qDebug() << blocktype[Mparts.parts[i].blocktype];
                            }

                       }

                    }
                      geometries->mesh = meshdat;
                      // start writing faces

                      std::vector< unsigned int > faces;

                      QByteArray last = QByteArray::fromHex("FFFF");
                      QByteArray first = QByteArray::fromHex("FFFF");
                       long int facescounter =0;
                      for (int i=0;i<Mparts.parts.size();i++){

                          QList<QStandardItem*> header;
                          header.append(new QStandardItem(QString("Mesh Part:")));
                          header.append(new QStandardItem(QString::number(i)));
                          header[0]->setBackground(Qt::black);
                          header[1]->setBackground(Qt::black);
                          model->appendRow(header);


                              for(int j=0;j<Mparts.parts[i].meshdata[0].faces.size();j++){ // per strip
                                  QList<QStandardItem*> strip;
                                  for(int k=0;k<Mparts.parts[i].meshdata[0].faces[j].size();k++){
                                      if (k == 0){
                                          first = Mparts.parts[i].meshdata[0].faces[j][k];
                                          if( i != 0 ){ // write double if not first mesh part and first strip
                                           //   faces.push_back(first.toHex().toInt(&ok,16));

                                              facescounter++;
                                          }
                                          else if (j !=0 ){
                                              faces.push_back(first.toHex().toInt(&ok,16));
                                              strip.append(new QStandardItem(QString::number(first.toHex().toInt(&ok,16))));
                                              facescounter++;
                                          }

                                      }


                                      last = Mparts.parts[i].meshdata[0].faces[j][k];

                                      faces.push_back(last.toHex().toInt(&ok,16));
                                      strip.append(new QStandardItem(QString::number(last.toHex().toInt(&ok,16))));

                                      facescounter++;
                                    }
                                   // write double
                                    //  faces.push_back(last.toHex().toInt(&ok,16));

                                      facescounter++;
                                   model->appendRow(strip);
                              }

                      }
//tv->show();
                      geometries->indecies= faces;



                          // For cube we would need only 8 vertices but we have to
                          // duplicate vertex for each face because texture coordinate
                          // is different.
                          std::vector< VertexData > vertices = {
                              // Vertex data for face 0
                              {QVector4D(-1.0f, -1.0f,  1.0f,1.0f), QVector4D(0.0f, 0.0f,1.0f,1.0f), QVector4D(0.0f, 0.0f,1.0f,1.0f)},  // v0
                              {QVector4D( 1.0f, -1.0f,  1.0f,1.0f), QVector4D(0.0f, 0.0f,1.0f,1.0f), QVector4D(0.33f, 0.0f,1.0f,1.0f)}, // v1
                              {QVector4D(-1.0f,  1.0f,  1.0f,1.0f), QVector4D(0.0f, 0.0f,1.0f,1.0f), QVector4D(0.0f, 0.5f,1.0f,1.0f)},  // v2
                              {QVector4D( 1.0f,  1.0f,  1.0f,1.0f), QVector4D(0.0f, 0.0f,1.0f,1.0f), QVector4D(0.33f, 0.5f,1.0f,1.0f)}, // v3

                              // Vertex data for face 1
                              {QVector4D( 1.0f, -1.0f,  1.0f,1.0f), QVector4D(0.0f, 0.0f,1.0f,1.0f), QVector4D( 0.0f, 0.5f,1.0f,1.0f)}, // v4
                              {QVector4D( 1.0f, -1.0f, -1.0f,1.0f), QVector4D(0.0f, 0.0f,1.0f,1.0f), QVector4D(0.33f, 0.5f,1.0f,1.0f)}, // v5
                              {QVector4D( 1.0f,  1.0f,  1.0f,1.0f), QVector4D(0.0f, 0.0f,1.0f,1.0f), QVector4D(0.0f, 1.0f,1.0f,1.0f)},  // v6
                              {QVector4D( 1.0f,  1.0f, -1.0f,1.0f), QVector4D(0.0f, 0.0f,1.0f,1.0f), QVector4D(0.33f, 1.0f,1.0f,1.0f)}, // v7

                              // Vertex data for face 2
                              {QVector4D( 1.0f, -1.0f, -1.0f,1.0f), QVector4D(0.0f, 0.0f,1.0f,1.0f), QVector4D(0.66f, 0.5f,1.0f,1.0f)}, // v8
                              {QVector4D(-1.0f, -1.0f, -1.0f,1.0f), QVector4D(0.0f, 0.0f,1.0f,1.0f), QVector4D(1.0f, 0.5f,1.0f,1.0f)},  // v9
                              {QVector4D( 1.0f,  1.0f, -1.0f,1.0f), QVector4D(0.0f, 0.0f,1.0f,1.0f), QVector4D(0.66f, 1.0f,1.0f,1.0f)}, // v10
                              {QVector4D(-1.0f,  1.0f, -1.0f,1.0f), QVector4D(0.0f, 0.0f,1.0f,1.0f), QVector4D(1.0f, 1.0f,1.0f,1.0f)},  // v11

                              // Vertex data for face 3
                              {QVector4D(-1.0f, -1.0f, -1.0f,1.0f), QVector4D(0.0f, 0.0f,1.0f,1.0f), QVector4D(0.66f, 0.0f,1.0f,1.0f)}, // v12
                              {QVector4D(-1.0f, -1.0f,  1.0f,1.0f), QVector4D(0.0f, 0.0f,1.0f,1.0f), QVector4D(1.0f, 0.0f,1.0f,1.0f)},  // v13
                              {QVector4D(-1.0f,  1.0f, -1.0f,1.0f), QVector4D(0.0f, 0.0f,1.0f,1.0f), QVector4D(0.66f, 0.5f,1.0f,1.0f)}, // v14
                              {QVector4D(-1.0f,  1.0f,  1.0f,1.0f), QVector4D(0.0f, 0.0f,1.0f,1.0f), QVector4D(1.0f, 0.5f,1.0f,1.0f)},  // v15

                              // Vertex data for face 4
                              {QVector4D(-1.0f, -1.0f, -1.0f,1.0f), QVector4D(0.0f, 0.0f,1.0f,1.0f), QVector4D(0.33f, 0.0f,1.0f,1.0f)}, // v16
                              {QVector4D( 1.0f, -1.0f, -1.0f,1.0f), QVector4D(0.0f, 0.0f,1.0f,1.0f), QVector4D(0.66f, 0.0f,1.0f,1.0f)}, // v17
                              {QVector4D(-1.0f, -1.0f,  1.0f,1.0f), QVector4D(0.0f, 0.0f,1.0f,1.0f), QVector4D(0.33f, 0.5f,1.0f,1.0f)}, // v18
                              {QVector4D( 1.0f, -1.0f,  1.0f,1.0f), QVector4D(0.0f, 0.0f,1.0f,1.0f), QVector4D(0.66f, 0.5f,1.0f,1.0f)}, // v19

                              // Vertex data for face 5
                              {QVector4D(-1.0f,  1.0f,  1.0f,1.0f), QVector4D(0.0f, 0.0f,1.0f,1.0f), QVector4D(0.33f, 0.5f,1.0f,1.0f)}, // v20
                              {QVector4D( 1.0f,  1.0f,  1.0f,1.0f), QVector4D(0.0f, 0.0f,1.0f,1.0f), QVector4D(0.66f, 0.5f,1.0f,1.0f)}, // v21
                              {QVector4D(-1.0f,  1.0f, -1.0f,1.0f), QVector4D(0.0f, 0.0f,1.0f,1.0f), QVector4D(0.33f, 1.0f,1.0f,1.0f)}, // v22
                              {QVector4D( 1.0f,  1.0f, -1.0f,1.0f), QVector4D(0.0f, 0.0f,1.0f,1.0f), QVector4D(0.66f, 1.0f,1.0f,1.0f)}  // v23
                          };
                   //   geometries->mesh = vertices;
                          // Indices for drawing cube faces using triangle strips.
                          // Triangle strips can be connected by duplicating indices
                          // between the strips. If connecting strips have opposite
                          // vertex order then last index of the first strip and first
                          // index of the second strip needs to be duplicated. If
                          // connecting strips have same vertex order then only last
                          // index of the first strip needs to be duplicated.
                          std::vector< unsigned int > indices = {
                               0,  1,  2,  3,  3,     // Face 0 - triangle strip ( v0,  v1,  v2,  v3)
                               4,  4,  5,  6,  7,  7, // Face 1 - triangle strip ( v4,  v5,  v6,  v7)
                               8,  8,  9, 10, 11, 11, // Face 2 - triangle strip ( v8,  v9, v10, v11)
                              12, 12, 13, 14, 15, 15, // Face 3 - triangle strip (v12, v13, v14, v15)
                              16, 16, 17, 18, 19, 19, // Face 4 - triangle strip (v16, v17, v18, v19)
                              20, 20, 21, 22, 23      // Face 5 - triangle strip (v20, v21, v22, v23)
                          };
                    //  geometries->indecies = indices;

                     geometries->initCubeGeometry();
//    updateGL();
                     paintGL();
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

    paintGL();
}

void MainWidget::onNewMeshselect(std::vector<int> &selection)
{
    this->selectedmeshes.clear();
     this->selectedmeshes = selection;

//    for(int i=0;i<selectedmeshes.size();i++){
//        qDebug() << selectedmeshes.at(i);
//    }

    paintGL();
}

void MainWidget::setSmoothShading()
{

    QAction* pAction = qobject_cast<QAction*>(sender());
    Q_ASSERT(pAction);

    qDebug() << pAction->data();
    shadingmode = 0;
     paintGL();
}

void MainWidget::setWireframeShading()
{
    QAction* pAction = qobject_cast<QAction*>(sender());
    Q_ASSERT(pAction);

    qDebug() << pAction->data();
    shadingmode = 1;
    paintGL();
}

void MainWidget::setVertexShading()
{
    shadingmode = 2;
    paintGL();
}

void MainWidget::setTriangleRendering()
{
    geometries->rendermode = 0;
     paintGL();
}

void MainWidget::setTriangleStripRendering()
{
    geometries->rendermode = 1;
     paintGL();
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
  matrix.translate(0.0, 0.0, -1.0);
  matrix.rotate(m_trackBalls[2].rotation());
  matrix(2, 3) -= -m_distExp/600.0f;//-20.0f * exp(m_distExp / 1200.0f);

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
 //  GLint location = glGetUniformLocation(program.programId(), "mvp_matrix");
   //glProgramUniformMatrix4fv(program.programId(), location, 1, true, &modelViewMatrix.elem[0][0]);
//! [6]

if(selectedmeshes.size()>0){
    program->setUniformValue("selsize",(int)selectedmeshes.size());
    program->setUniformValueArray("selected_mesh_part",selectedmeshes.data(),selectedmeshes.size());

}
program->setUniformValue("timer",(float)time/100.0f );

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
  //  geometries->drawCubeGeometry(&program);
   // emit this->newText(geometries->p1,geometries->p2,geometries->p3,geometries->p4,geometries->v1,geometries->v2,geometries->v3,geometries->v4);
 //   glMultMatrixf(matrix2.data());
      glPolygonMode(GL_FRONT, GL_FILL);
      glPolygonMode(GL_BACK, GL_FILL);


      this->context()->functions()->glDisable(GL_DEPTH_TEST);

      // We need to flush the contents to the FBO before posting
      // the texture to the other thread, otherwise, we might
      // get unexpected results.
      this->context()->functions()->glFlush();

  //    QMessageBox msgBox2;
       //                     msgBox2.setText("check gl error: " +QString(m_pFunctions->glGetError()));
         //                    msgBox2.exec();

}
