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

#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include "geometryengine.h"

#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <QMatrix4x4>
#include <QQuaternion>
#include <QVector2D>
#include <QBasicTimer>
#include <QOpenGLShaderProgram>
#include <QOpenGLTexture>
#include <QMenu>
// spread sheet stuff
#include <QList>
#include <QTableView>
#include <QStandardItemModel>
#include <QStandardItem>
// spread sheet stuff
#include "trackball.h"
#include "Mat.h"
#include "Vec.h"
#include <vector>


#include <QOpenGLFunctions_4_3_Core>




class GeometryEngine;

class MainWidget :  public QOpenGLWidget//, protected QOpenGLFunctions
{
    Q_OBJECT

public:
    explicit MainWidget(QWidget *parent = 0);

           std::vector<float> weights;

    ~MainWidget();
 QOpenGLTexture *texture;
 QOpenGLTexture *diffuse;
 QOpenGLTexture *specular;
 QOpenGLTexture *normal;
 QOpenGLTexture *light;
           struct MOD_Mesh_Data
           {
               std::vector<QByteArray> verticies;
               std::vector<QByteArray> texturemap;
               std::vector<QByteArray> normals;
               std::vector<QByteArray> weights;
               std::vector< std::vector<QByteArray> > faces; //array of triangle strips as qbytearray per int val
               std::vector<QByteArray> bns;
               std::vector<QByteArray> unkbyte1;
               std::vector<QByteArray> unklong2;
               std::vector<QByteArray> unksh1;
               std::vector<QByteArray> unksh2;
               std::vector<QByteArray> unksh3;
               std::vector<QByteArray> unksh4;

               std::vector<QByteArray> unklong1;
               std::vector<QByteArray> unklong3;

               std::vector<QByteArray> unklong4;
               std::vector<QByteArray> unklong5;


           };

           struct MOD_Mesh_Part2
           {
               QByteArray unksh1;
               QByteArray vertexcount;
               QByteArray id;
               QByteArray material;
               QByteArray LOD;
               QByteArray unkbyte20;
               QByteArray unkbyte21;
               QByteArray blocksize;
               QByteArray unkbtye3;
               QByteArray vertexsub;
               QByteArray vertexoffset;
               QByteArray blocktype;
               QByteArray faceoffset;
               QByteArray facecount;
               QByteArray unklong4;
               QByteArray unkbyte5;
               QByteArray boneremapid;
               QByteArray unksh6;
               QByteArray unksh7;
               QByteArray unksh8;
               QByteArray unklong; /// pc E0,00,??,1D   ps3.... gibberish?
               std::vector<MOD_Mesh_Data> meshdata; // why is this a vector? it only ever does this once
           };
           struct MOD_unk2_chunk
           {
               QByteArray un1;
               QByteArray un2; // on pc dd;da it is "CDCDCDCD" on ps3 it's all 0's
               QByteArray un3; // on pc dd;da it is "CDCDCDCD" on ps3 it's all 0's
               QByteArray un4; // on pc dd;da it is "CDCDCDCD" on ps3 it's all 0's
               QByteArray un5;
               QByteArray un6;
               QByteArray un7; //body begin
               QByteArray un8;
               QByteArray un9;
               QByteArray un10;
               QByteArray un11;
               QByteArray un12;
               QByteArray un13;
               QByteArray un14;
               QByteArray un15;
               QByteArray un16;
               QByteArray un17;
               QByteArray un18;
               QByteArray un19;
               QByteArray un20;
               QByteArray un21;
               QByteArray un22;
               QByteArray un23;
               QByteArray un24;
               QByteArray un25;
               QByteArray un26;
               QByteArray un27;
               QByteArray un28;
               QByteArray un29;
               QByteArray un30;
               QByteArray un31;
               QByteArray un32;
               QByteArray un33;
               QByteArray un34;
               QByteArray un35;
               QByteArray un36;

           } ;

           struct MOD_Mesh_Parts
           {
               std::vector<MOD_Mesh_Part2> parts;
               std::vector<MOD_unk2_chunk> chunks;
           } Mparts;

uint as_uint(const float x);
float as_float(const uint x);
float half_to_float(const ushort x);
ushort float_to_half(const float x);
quint32 toUint( QByteArray &data, bool bigEndian);
float toFloat( QByteArray &data, bool bigEndian);

protected:
std::vector<int> selectedmeshes;

std::vector<int> rendermodes;

std::vector< std::vector< VertexData > > vertices;
std::vector< std::vector<unsigned int> > faces;

QTextEdit *console;

int shadingmode;
void DeleteFunctions() {delete(m_pFunctions); m_pFunctions = nullptr; qDebug() << "goodbye context!";  }

QOpenGLFunctions_4_3_Core * m_pFunctions = nullptr;
//QOpenGLFunctions* m_pFunctions = nullptr;
float mousex, mousey;
           float tp;
           float dur;
           int time,time2,time3;
           int st,et,st2,et2,s1,s2,t1,t2;
    QPointF pixelPosToViewPos(const QPointF& p);
    int m_lastTime;
    int m_mouseEventTime;
    int m_distExp;
    int m_frame;
    int dir;
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void wheelEvent(QWheelEvent *event);
    void timerEvent(QTimerEvent *e);

    void initializeGL();
    void resizeGL(int w, int h);
    void paintGL();

    void initShaders();
    void initTextures();

    QPointF mousePos;
  //  Mat3f rotation;
        QQuaternion rotation;
    Vec3f translation;
    Mat4f modelViewMatrix;
    Mat4f projectionMatrix;

signals:

    void uptime(int t);


public slots:
    void gldebugmsg(const QOpenGLDebugMessage &debugMessage);
void ShowContextMenu(const QPoint& pos);
    void onNewTextures(QString fileName);


    void onNewMeshdata(MOD_Mesh_Parts &mesh, std::vector<QByteArray> &lmatrices, std::vector<QByteArray> &amatrices); // decipated
    void onNewDAPCMeshdata(MOD_Mesh_Parts &mesh); // decipated

    void onNewMesh(std::vector<int> &rmodes, std::vector< std::vector< VertexData > > &arrverts, std::vector< std::vector<unsigned int> > &arrfaces);
   void onNewMeshselect(std::vector<int> &selection);

void setSmoothShading();
void setWireframeShading();
void setVertexShading();
void setTriangleRendering();
void setTriangleStripRendering();


        void updatetimer();


private:
            std::map<QByteArray,long int> blocktype;
    QTimer* timer2;
    QBasicTimer timer;

    QOpenGLShaderProgram *program;
    GeometryEngine * geometries;
   float lh;
    GLuint htex,btex,b2tex,hantex,legtex,ftex;
    TrackBall m_trackBalls[3];

    QMatrix4x4 projection;

    QVector2D mousePressPosition;
    QVector3D rotationAxis;
    qreal angularSpeed;
    //QQuaternion rotation;
    QRgb *m_color;
        QRgb cl_color;
            QRgb cm_color;
};

#endif // MAINWIDGET_H
