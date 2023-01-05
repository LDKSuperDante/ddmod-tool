/****************************************************************************
**
** Copyright (C) 2014 Digia Plc and/or its subsidiary(-ies).
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

#include "geometryengine.h"

#include <QVector2D>
#include <QVector3D>



//! [0]
GeometryEngine::GeometryEngine()
    : indexBuf(QOpenGLBuffer::IndexBuffer)
{
    initializeOpenGLFunctions();
    rendermode = 0;
    // Generate 2 VBOs
    arrayBuf.create();
    indexBuf.create();

    // Initializes cube geometry and transfers it to VBOs
    initCubeGeometry();
}

GeometryEngine::~GeometryEngine()
{
    arrayBuf.destroy();
    indexBuf.destroy();
    for(int i=0; i<arrbuff.size();i++){
        arrbuff.at(i).destroy();
    }
    for(int i=0; i<idxbuff.size();i++){
        idxbuff.at(i).destroy();
    }
}
//! [0]

void GeometryEngine::initCubeGeometry()
{
    arrayBuf.destroy();
    indexBuf.destroy();
    for(int i=0; i<arrbuff.size();i++){
        arrbuff.at(i).destroy();
    }
    for(int i=0; i<idxbuff.size();i++){
        idxbuff.at(i).destroy();
    }
    arrayBuf.create();
    indexBuf.create();

arrbuff.clear();
idxbuff.clear();

    for(int i=0; i<rendermodes.size();i++){
        QOpenGLBuffer buff;
        buff.create();
        arrbuff.push_back(buff);
        QOpenGLBuffer idx(QOpenGLBuffer::IndexBuffer);
        idx.create();
        idxbuff.push_back(idx);


        // Transfer vertex data to VBO
        buff.bind();
        buff.allocate(vertices.at(i).data(), vertices.at(i).size() * sizeof(VertexData));

        // Transfer index data to VBO
        idx.bind();
        idx.allocate(faces.at(i).data(), faces.at(i).size() * sizeof(unsigned int));
    }


//! [1]
    // Transfer vertex data to VBO 0
    arrayBuf.bind();
    arrayBuf.allocate(mesh.data(), mesh.size() * sizeof(VertexData));

    // Transfer index data to VBO 1
    indexBuf.bind();
    indexBuf.allocate(indecies.data(), indecies.size() * sizeof(unsigned int));
//! [1]
}

//! [2]
void GeometryEngine::drawCubeGeometry(QOpenGLShaderProgram *program)
{
    // Tell OpenGL which VBOs to use
   // arrayBuf.bind();
   // indexBuf.bind();

    if(rendermodes.size() >0){

    glActiveTexture(GL_TEXTURE0+1);
    glBindTexture(GL_TEXTURE_2D,difftex); //diff


     glUniform1i(glGetUniformLocation(program->programId(), "diffusetx"), 1);
     program->setUniformValue("diffusetx", 1);
     glActiveTexture(GL_TEXTURE0+2);
     glBindTexture(GL_TEXTURE_2D,spectex); // spe
glUniform1i(glGetUniformLocation(program->programId(), "speculartx"), 2);
    program->setUniformValue("speculartx", 2);
     glActiveTexture(GL_TEXTURE0+4);
    glBindTexture(GL_TEXTURE_2D,lighttex); // lite
    glUniform1i(glGetUniformLocation(program->programId(), "lighttx"), 4);
    program->setUniformValue("lighttx", 4);
    glActiveTexture(GL_TEXTURE0+3);
    glBindTexture(GL_TEXTURE_2D,normtex); // norm
    glUniform1i(glGetUniformLocation(program->programId(), "normaltx"), 3);
    program->setUniformValue("normaltx", 3);


    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D,0); //diff
for(int i =0;i<rendermodes.size();i++){
    // Tell OpenGL which VBOs to use
  //  arrayBuf.bind();
   // indexBuf.bind();
      arrbuff.at(i).bind();
      idxbuff.at(i).bind();


    // Offset for position
    quintptr offset = 0;

    // end messsing with stuff
    //glPointSize(5.0f);
    // Tell OpenGL programmable pipeline how to locate vertex position data
    int vertexLocation = program->attributeLocation("a_position");
    program->enableAttributeArray(vertexLocation);
    glVertexAttribPointer(vertexLocation, 4, GL_FLOAT, GL_FALSE, sizeof(VertexData), (const void *)offset);


    // Offset for texture coordinate
    offset += sizeof(QVector4D);

    // Tell OpenGL programmable pipeline how to locate vertex normal coordinate data
    int normals = program->attributeLocation("a_normals");
    program->enableAttributeArray(normals);
    glVertexAttribPointer(normals, 4, GL_FLOAT, GL_FALSE, sizeof(VertexData), (const void *)offset);




    offset += sizeof(QVector4D);

    // end messsing with stuff
    //glPointSize(5.0f);
    // Tell OpenGL programmable pipeline how to locate vertex texture data
    int texcoordLocation = program->attributeLocation("a_texcoord");
    program->enableAttributeArray(texcoordLocation);
    glVertexAttribPointer(texcoordLocation,  4, GL_FLOAT, GL_FALSE, sizeof(VertexData), (const void *)offset);

// Draw cube geometry using indices from VBO 1
    switch(rendermode){
      case 0:
        glDrawElements(GL_TRIANGLES, faces.at(i).size(), GL_UNSIGNED_INT, 0);
        break;
      case 1:
        glDrawElements(GL_TRIANGLE_STRIP, faces.at(i).size(), GL_UNSIGNED_INT, 0);
        break;
      default:
    glDrawElements(GL_TRIANGLE_STRIP, faces.at(i).size(), GL_UNSIGNED_INT, 0);

    }

  }

    }
}
//! [2]
