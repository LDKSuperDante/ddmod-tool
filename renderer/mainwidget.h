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
#include <vector>

#include <QOpenGLFunctions_4_3_Core>

class GeometryEngine;

class MainWidget :  public QOpenGLWidget//, protected QOpenGLFunctions
{
    Q_OBJECT

public:
    explicit MainWidget(QWidget *parent = 0);

    ~MainWidget();

private:
    std::vector<int> selectedmeshes;
    std::vector<int> rendermodes;

    // QTextEdit *console;

    int shadingmode;
    int rendermode;

    QOpenGLFunctions_4_3_Core * m_pFunctions = nullptr;
    float mousex, mousey;
    int m_distExp;

    QBasicTimer timer;

    QOpenGLShaderProgram *program;
    GeometryEngine * geometries;
    GLuint tex[4];
    TrackBall m_trackBall;

    QMatrix4x4 projection;

    QAction *cv1;
    QAction *cv2;
    QAction *cv3;
    QAction *cv4;
    QAction *cv5;

    void DeleteFunctions() {
        delete(m_pFunctions);
        m_pFunctions = nullptr;
        // qDebug() << "goodbye context!";
    }

    QPointF pixelPosToViewPos(const QPointF& p);

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

signals:
    void uptime(int t);

public slots:
    void gldebugmsg(const QOpenGLDebugMessage &debugMessage);
    void addMainMenu(QMenu *menu);
    void onNewTextures(const QImage &diff, const QImage &spec, const QImage &norm, const QImage &light);

    void onNewMesh(std::vector<int> &rmodes, std::vector< std::vector< VertexData > > &arrverts, std::vector< std::vector<unsigned int> > &arrfaces);
    void onNewMeshselect(std::vector<int> &selection);

    void setSmoothShading();
    void setWireframeShading();
    void setVertexShading();
    void setTriangleRendering();
    void setTriangleStripRendering();
};

#endif // MAINWIDGET_H
