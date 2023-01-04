#include "dialog.h"
//#include "dirent.h"
//#include "ui_dialog.h"


Dialog::Dialog(QWidget *parent) :
    QDialog(parent)//,
   // ui(new Ui::Dialog)
{
    //ui->setupUi(this);

    if (this->objectName().isEmpty())
        this->setObjectName(QStringLiteral("DDON"));
    this->resize(700, 280);
    outerLayout = new QVBoxLayout;

    insideboxLayout = new QVBoxLayout;

    groupBox = new QGroupBox(this);

    groupBox->setLayout(insideboxLayout);

    groupBox->setObjectName(QStringLiteral("groupBox"));
   // groupBox->setGeometry(QRect(10, 20, 385, 201));
 //   layoutWidget = new QWidget(groupBox);
  //  layoutWidget->setObjectName(QStringLiteral("layoutWidget"));
  //  layoutWidget->setGeometry(QRect(10, 110, 397, 92));
    verticalLayout = new QVBoxLayout;
  //  verticalLayout->setSpacing(6);
  //  verticalLayout->setContentsMargins(11, 11, 11, 11);
  //  verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
  //  verticalLayout->setContentsMargins(0, 0, 0, 0);
    rdoSingle = new QRadioButton;
    rdoSingle->setObjectName(QStringLiteral("rdoSingle"));


    verticalLayout->addWidget(rdoSingle);

    rdoPooled = new QRadioButton;
    rdoPooled->setObjectName(QStringLiteral("rdoPooled"));
    rdoPooled->setChecked(true);

    verticalLayout->addWidget(rdoPooled);

    rdoTheaded = new QRadioButton;
    rdoTheaded->setObjectName(QStringLiteral("rdoTheaded"));

    verticalLayout->addWidget(rdoTheaded);

    label_2 = new QLabel(groupBox);
    label_2->setObjectName(QStringLiteral("label_2"));
  //  label_2->setGeometry(QRect(130, 80, 31, 16));
    spinBoxMax = new QLineEdit(groupBox);
    spinBoxMax->setObjectName(QStringLiteral("spinBoxMax"));
   // spinBoxMax->setGeometry(QRect(160, 80, 70, 23));
   // spinBoxMax->setMaximum(64000);
  //  spinBoxMax->setValue(100);
    spinBox = new QLineEdit(groupBox);
    spinBox->setObjectName(QStringLiteral("spinBox"));
   // spinBox->setGeometry(QRect(58, 78, 70, 23));
   // spinBox->setMaximum(64000);
  //  spinBox->setValue(52100);
    label = new QLabel(groupBox);
    label->setObjectName(QStringLiteral("label"));
  //  label->setGeometry(QRect(20, 80, 29, 16));
    label_3 = new QLabel(groupBox);
    label_3->setObjectName(QStringLiteral("label_3"));
   // label_3->setGeometry(QRect(20, 40, 59, 14));
    cmbAddress = new QComboBox(groupBox);
    cmbAddress->setObjectName(QStringLiteral("cmbAddress"));
   // cmbAddress->setGeometry(QRect(80, 40, 281, 22));

    horizontalLayout_0 = new QHBoxLayout;
    horizontalLayout_0->addWidget(label_3);
    horizontalLayout_0->addWidget(cmbAddress);


    spinboxIdle = new QLineEdit(groupBox);
    spinboxIdle->setObjectName(QStringLiteral("spinboxIdle"));
   // spinboxIdle->setGeometry(QRect(270, 80, 70, 23));
   // spinboxIdle->setMaximum(64000);
  //  spinboxIdle->setValue(30000);
    label_4 = new QLabel(groupBox);
    label_4->setObjectName(QStringLiteral("label_4"));
  //  label_4->setGeometry(QRect(240, 80, 31, 16));
  //  layoutWidget1 = new QWidget(this);
   // layoutWidget1->setObjectName(QStringLiteral("layoutWidget1"));
  //  layoutWidget1->setGeometry(QRect(180, 240, 239, 38));
    horizontalLayout_2 = new QHBoxLayout;
//    horizontalLayout_2->setSpacing(6);
  //  horizontalLayout_2->setContentsMargins(11, 11, 11, 11);
    horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
  //  horizontalLayout_2->setContentsMargins(0, 0, 0, 0);
    btnListen = new QPushButton;
    btnListen->setObjectName(QStringLiteral("btnListen"));

    horizontalLayout_2->addWidget(btnListen);

    btnClose = new QPushButton;
    btnClose->setObjectName(QStringLiteral("btnClose"));

    horizontalLayout_2->addWidget(btnClose);






    meshcount = new QLineEdit(groupBox);
    label_meshcount = new QLabel(groupBox);
    materialcount = new QLineEdit(groupBox);
    label_materialcount = new QLabel(groupBox);
    vertexcount = new QLineEdit(groupBox);
    label_vertexcount = new QLabel(groupBox);

    horizontalLayout_3 = new QHBoxLayout;
    horizontalLayout_3->addWidget(label_meshcount);
    horizontalLayout_3->addWidget(meshcount);
    horizontalLayout_3->addWidget(label_materialcount);
    horizontalLayout_3->addWidget(materialcount);
    horizontalLayout_3->addWidget(label_vertexcount);
    horizontalLayout_3->addWidget(vertexcount);


    facecount = new QLineEdit(groupBox);
    label_facecount = new QLabel(groupBox);
    vertexids = new QLineEdit(groupBox);
    label_vertexids = new QLabel(groupBox);
    vertexbuffersize = new QLineEdit(groupBox);
    label_vertexbuffersize = new QLabel(groupBox);


    horizontalLayout_4 = new QHBoxLayout;
    horizontalLayout_4->addWidget(label_facecount);
    horizontalLayout_4->addWidget(facecount);
    horizontalLayout_4->addWidget(label_vertexids);
    horizontalLayout_4->addWidget(vertexids);
    horizontalLayout_4->addWidget(label_vertexbuffersize);
    horizontalLayout_4->addWidget(vertexbuffersize);

    scondbuffersize = new QLineEdit(groupBox);
    label_scondbuffersize = new QLabel(groupBox);
    groupcount = new QLineEdit(groupBox);
    label_groupcount = new QLabel(groupBox);
    bonesoffset = new QLineEdit(groupBox);
    label_bonesoffset = new QLabel(groupBox);

    horizontalLayout_5 = new QHBoxLayout;
    horizontalLayout_5->addWidget(label_scondbuffersize);
    horizontalLayout_5->addWidget(scondbuffersize);
    horizontalLayout_5->addWidget(label_groupcount);
    horizontalLayout_5->addWidget(groupcount);
    horizontalLayout_5->addWidget(label_bonesoffset);
    horizontalLayout_5->addWidget(bonesoffset);

    groupoffset = new QLineEdit(groupBox);
    label_groupoffset = new QLabel(groupBox);
    textureoffset = new QLineEdit(groupBox);
    label_textureoffset = new QLabel(groupBox);
    meshoffset = new QLineEdit(groupBox);
    label_meshoffset = new QLabel(groupBox);

    horizontalLayout_6 = new QHBoxLayout;
    horizontalLayout_6->addWidget(label_groupoffset);
    horizontalLayout_6->addWidget(groupoffset);
    horizontalLayout_6->addWidget(label_textureoffset);
    horizontalLayout_6->addWidget(textureoffset);
    horizontalLayout_6->addWidget(label_meshoffset);
    horizontalLayout_6->addWidget(meshoffset);

    vertexoffset = new QLineEdit(groupBox);
    label_vertexoffset = new QLabel(groupBox);
    facesoffset = new QLineEdit(groupBox);
    label_facesoffset = new QLabel(groupBox);
    unkoffset = new QLineEdit(groupBox);
    label_unkoffset = new QLabel(groupBox);


    horizontalLayout_7 = new QHBoxLayout;
    horizontalLayout_7->addWidget(label_vertexoffset);
    horizontalLayout_7->addWidget(vertexoffset);
    horizontalLayout_7->addWidget(label_facesoffset);
    horizontalLayout_7->addWidget(facesoffset);
    horizontalLayout_7->addWidget(label_unkoffset);
    horizontalLayout_7->addWidget(unkoffset);



    horizontalLayout_1 = new QHBoxLayout;
    horizontalLayout_1->addWidget(label);
    horizontalLayout_1->addWidget(spinBox);
    horizontalLayout_1->addWidget(label_2);
    horizontalLayout_1->addWidget(spinBoxMax);
    horizontalLayout_1->addWidget(label_4);
    horizontalLayout_1->addWidget(spinboxIdle);



    insideboxLayout->addLayout(horizontalLayout_0);
    insideboxLayout->addLayout(horizontalLayout_1);
    insideboxLayout->addLayout(horizontalLayout_3);
    insideboxLayout->addLayout(horizontalLayout_4);
    insideboxLayout->addLayout(horizontalLayout_5);
    insideboxLayout->addLayout(horizontalLayout_6);
    insideboxLayout->addLayout(horizontalLayout_7);
    insideboxLayout->addLayout(verticalLayout);


        outerLayout->addWidget(groupBox);
        outerLayout->addLayout(horizontalLayout_2);


       // QVBoxLayout *textures = new QVBoxLayout(groupBox);
        difflabel = new QLabel;
        speclabel = new QLabel;
        normlabel = new QLabel;
        litelabel = new QLabel;

//        textures->addWidget(difflabel);
//        textures->addWidget(speclabel);
//        textures->addWidget(normlabel);
//        textures->addWidget(litelabel);

//        outerLayout->addLayout(textures);

    this->setWindowTitle(QApplication::translate("Dialog", "Dragon's Dogma", 0));
    groupBox->setTitle(QApplication::translate("Dialog", "Headers", 0));
    rdoSingle->setText(QApplication::translate("Dialog", "DDON", 0));
    rdoPooled->setText(QApplication::translate("Dialog", "DD;DA", 0));
    rdoTheaded->setText(QApplication::translate("Dialog", "DD;DA (PS3)", 0));
    label_2->setText(QApplication::translate("Dialog", "Version 2:", 0));
    label->setText(QApplication::translate("Dialog", "Version:", 0));
    label_3->setText(QApplication::translate("Dialog", "File:", 0));
    label_4->setText(QApplication::translate("Dialog", "Bone Count:", 0));
    btnListen->setText(QApplication::translate("Dialog", "Open", 0));
    btnClose->setText(QApplication::translate("Dialog", "Save", 0));


    label_meshcount->setText(QApplication::translate("Dialog", "Mesh Count: ", 0));
    label_materialcount->setText(QApplication::translate("Dialog", "Material Count: ", 0));
    label_vertexcount->setText(QApplication::translate("Dialog", "Vertex Count: ", 0));
    label_facecount->setText(QApplication::translate("Dialog", "Face Count: ", 0));
    label_vertexids->setText(QApplication::translate("Dialog", "Vertex Ids: ", 0));
    label_vertexbuffersize->setText(QApplication::translate("Dialog", "Vertex Buffer Size: ", 0));
    label_scondbuffersize->setText(QApplication::translate("Dialog", "Second Buffer Size: ", 0));
    label_groupcount->setText(QApplication::translate("Dialog", "Group Count: ", 0));
    label_bonesoffset->setText(QApplication::translate("Dialog", "Bones Offset: ", 0));
    label_groupoffset->setText(QApplication::translate("Dialog", "Group Offset: ", 0));
    label_textureoffset->setText(QApplication::translate("Dialog", "Texture Offset: ", 0));
    label_meshoffset->setText(QApplication::translate("Dialog", "Mesh Offset: ", 0));
    label_vertexoffset->setText(QApplication::translate("Dialog", "Vertex Offset: ", 0));
    label_facesoffset->setText(QApplication::translate("Dialog", "Faces Offset: ", 0));
    label_unkoffset->setText(QApplication::translate("Dialog", "Unknown Offset: ", 0));

    difflabel->setWindowTitle(QApplication::translate("Diffuse Map", "Diffuse Map", 0));
    speclabel->setWindowTitle(QApplication::translate("Specular Map", "Specular Map", 0));
    normlabel->setWindowTitle(QApplication::translate("Normal Map", "Normal Map", 0));
    litelabel->setWindowTitle(QApplication::translate("Light Map", "Light Map", 0));

    MainWidget *r = new MainWidget;
connect(this,SIGNAL(newTextures(QString)),r,SLOT(onNewTextures(QString)));
connect(this,SIGNAL(newMesh(MOD_Mesh_Parts&,std::vector<QByteArray>&, std::vector<QByteArray>&)),r,SLOT(onNewMeshdata(MOD_Mesh_Parts&,std::vector<QByteArray>&, std::vector<QByteArray>&)));
connect(this,SIGNAL(newDAPCMesh(MOD_Mesh_Parts&)),r,SLOT(onNewDAPCMeshdata(MOD_Mesh_Parts&)));
   r->setWindowTitle(QApplication::translate("Renderer", "Model Viewer", 0));
r->show();

    connect(btnListen,SIGNAL(clicked(bool)),this,SLOT(on_btnListen_clicked()));
    connect(btnClose,SIGNAL(clicked(bool)),this,SLOT(on_btnClose_clicked()));
    connect(cmbAddress,SIGNAL(activated(QString)),this,SLOT(on_addr_changed(QString)));

   this->setLayout(outerLayout);

    QIcon icon = QIcon(":/resources/Resource/icon.png");
    this->setWindowIcon(icon);

  //  QStringList lst = server.getAddresses();
   // ui->
          //  cmbAddress->insertItems(0,lst);
  //  ui->
          //  cmbAddress->insertItem(0,"Any");
   // ui->
         //   cmbAddress->setCurrentIndex(0);

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

    unktypesfound = 0; //initalize me
    byte3map[QByteArray::fromHex("13")] = QByteArray::fromHex("C4");
    byte3map[QByteArray::fromHex("C4")] = QByteArray::fromHex("13");
    byte3map[QByteArray::fromHex("12")] = QByteArray::fromHex("44");
    byte3map[QByteArray::fromHex("44")] = QByteArray::fromHex("12");
    byte3map[QByteArray::fromHex("10")] = QByteArray::fromHex("04");
    byte3map[QByteArray::fromHex("04")] = QByteArray::fromHex("10");
    unkbyte3found =0; //initalize me
}

Dialog::~Dialog()
{
    //  delete ui;
}

QByteArray Dialog::Readbyte(char *buffer, int &offset)
{
    char idx;
    QByteArray val;
    memcpy(&idx, &buffer[offset+0], 1);
    val.append(idx);
    offset++;
    return val;
}

QByteArray Dialog::Readlong(char *buffer, int &offset)
{
    char idx;
    QByteArray val;
    memcpy(&idx, &buffer[offset+0], 1);
    val.append(idx);
    memcpy(&idx, &buffer[offset+1], 1);
    val.append(idx);
    memcpy(&idx, &buffer[offset+2], 1);
    val.append(idx);
    memcpy(&idx, &buffer[offset+3], 1);
    val.append(idx);
    offset +=4;
    return val;
}

QByteArray Dialog::ReadBElong(char *buffer, int &offset)
{
    char idx;
    QByteArray val;
    memcpy(&idx, &buffer[offset+3], 1);
    val.append(idx);
    memcpy(&idx, &buffer[offset+2], 1);
    val.append(idx);
    memcpy(&idx, &buffer[offset+1], 1);
    val.append(idx);
    memcpy(&idx, &buffer[offset+0], 1);
    val.append(idx);
    offset +=4;
    return val;
}

QByteArray Dialog::Readshort(char *buffer, int &offset)
{
    char idx;
    QByteArray val;
    memcpy(&idx, &buffer[offset+0], 1);
    val.append(idx);
    memcpy(&idx, &buffer[offset+1], 1);
    val.append(idx);
    offset +=2;
    return val;
}

QByteArray Dialog::ReadBEshort(char *buffer, int &offset)
{
    char idx;
    QByteArray val;
    memcpy(&idx, &buffer[offset+1], 1);
    val.append(idx);
    memcpy(&idx, &buffer[offset+0], 1);
    val.append(idx);
    offset +=2;
    return val;
}

QByteArray Dialog::ReadBEpointer(char *buffer, int &offset, bool x64)
{
    if(x64){
        offset +=4;
        return ReadBElong(buffer,offset);
    }
    else{
        return ReadBElong(buffer,offset);
    }
}

QByteArray Dialog::Readpointer(char *buffer, int &offset, bool /* x64 */)
{
  return Readlong(buffer,offset);
}

QByteArray Dialog::ReadBEfloat(char *buffer, int &offset, bool /* x64 */)
{
 return ReadBElong(buffer,offset);
}

QByteArray Dialog::Readfloat(char *buffer, int &offset, bool /* x64 */)
{
    return Readlong(buffer,offset);
}

void Dialog::ReadMatrix44(char *buffer, int &offset, std::vector<QByteArray> &dest)
{
    for(int i = 0; i<16;i++){
        dest.push_back(Readlong(buffer,offset));
    }
      return;
}

void Dialog::ReadBEMatrix44(char *buffer, int &offset, std::vector<QByteArray> &dest)
{
    for(int i = 0; i<16;i++){
        dest.push_back(ReadBElong(buffer,offset));
    }
    return;
}

QByteArray Dialog::ReadMaterial(char *buffer, int &offset)
{
    char idx;
    QByteArray val;
    for(int i=0;i<128;i++){
        memcpy(&idx, &buffer[offset+i], 1);
        val.append(idx);
    }
    offset +=128;
    return val;
}

void Dialog::WriteMaterial(FILE *f, QByteArray &bytes)
{
  for(int i=0;i<128;i++){
      fprintf(f,"%c", (uint) bytes[i]);
  }
  goffset +=128;
  return;
}

void Dialog::WriteMatrix44(FILE *f, int offset, std::vector<QByteArray> &dest)
{
    for(int i = offset; i<offset+16;i++){
        Writelong(f,dest[i]);
    }
    return;
}

void Dialog::WriteBEMatrix44(FILE *f, int offset, std::vector<QByteArray> &dest)
{
    for(int i = offset; i<offset+16;i++){
        WriteBElong(f,dest[i]);
    }
    return;
}

void Dialog::Writebyte(FILE *f, QByteArray &bytes)
{
    fprintf(f,"%c", (uint) bytes[0]);
    goffset++;
    return;
}

void Dialog::Writelong(FILE *f, QByteArray &bytes)
{
    fprintf(f,"%c", (uint) bytes[3]);
    fprintf(f,"%c", (uint) bytes[2]);
    fprintf(f,"%c", (uint) bytes[1]);
    fprintf(f,"%c", (uint) bytes[0]);
    goffset+=4;
    return;
}

void Dialog::WriteBElong(FILE *f, QByteArray &bytes)
{
    fprintf(f,"%c", (uint) bytes[0]);
    fprintf(f,"%c", (uint) bytes[1]);
    fprintf(f,"%c", (uint) bytes[2]);
    fprintf(f,"%c", (uint) bytes[3]);
    goffset+=4;
    return;
}

void Dialog::Writeshort(FILE *f, QByteArray &bytes)
{
    fprintf(f,"%c", (uint) bytes[1]);
    fprintf(f,"%c", (uint) bytes[0]);
    goffset+=2;
    return;
}

void Dialog::WriteBEshort(FILE *f, QByteArray &bytes)
{
    fprintf(f,"%c", (uint) bytes[0]);
    fprintf(f,"%c", (uint) bytes[1]);
    goffset+=2;
    return;
}

void Dialog::on_btnListen_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this,
          tr("Load Mod File"), "./",tr("MOD (*.mod)"));
    cmbAddress->insertItem(0,fileName);
    label_3->setText("File: " + fileName.section("/",-1,-1)); // just the file name
    open_file(fileName);
}

void Dialog::on_addr_changed(QString fileName)
{
    label_3->setText("File: " + fileName.section("/",-1,-1)); // just the file name
    open_file(fileName);
}

void Dialog::on_btnClose_clicked()
{
    QString fileName = QFileDialog::getSaveFileName(this, tr("Save Mod File"),"./",tr("MOD (*.mod)"));

    FILE *f = fopen(fileName.toLocal8Bit().constData(), "wb");
    if (f == NULL)
    {
        QMessageBox msgBox;
        msgBox.setText(QString("Error Saving File: \n").append(fileName.toLocal8Bit().constData()));
        msgBox.exec();
    }

else {
//        /// tmp log file
//        FILE *flog = fopen("log.txt", "wb");
//        if (flog == NULL)
//        {
//            QMessageBox msgBox;
//            msgBox.setText(QString("Error creating log File \n"));
//            msgBox.exec();
//        }
//        else{
//            //start writing

//                QByteArray last = QByteArray::fromHex("FFFF");
//                QByteArray next = QByteArray::fromHex("FFFF");

//                for(int i=0;i<faces.size();i++){

//                    for(int j=0;j<faces[i].size();j++){

//                       last = faces[i][j];
//                       WriteBEshort(flog,last);
////                       if(j==0 && i>0){
////                        Writeshort(f,last);
////                       }
//                    }
//                    WriteBEshort(flog,next);
//                }

//                fclose(flog);
//        }


        bool ok ;
        if (rdoPooled->isChecked()){//Mheader.BEndian){ //pc
////////////////////////// writing header
/// //initialize global write offset
            goffset = 0;
            //write header.id
            QByteArray h = QByteArray::fromHex("4D4F4400");
            WriteBElong(f,h);//Mheader.id);
            //write version
            Writebyte(f,Mheader.version);
            //write version2
            Writebyte(f,Mheader.version2);
            // pc is little ending so flip
            //write bonecount
            Writeshort(f,Mheader.bonecount);
            //write meshcount
            Writeshort(f,Mheader.meshcount);
            //write materialcount
            Writeshort(f,Mheader.materialcount);
            //write vertexcount
            Writelong(f,Mheader.vertexcount);
            //write facecount
            Writelong(f,Mheader.facecount);
            //write vertexids
            Writelong(f,Mheader.vertexids);
            //write vertexbuffersize
            Writelong(f,Mheader.vertexbuffersize);
            //write secondbuffersize
            Writelong(f,Mheader.scondbuffersize);
            //write groupcount
            Writelong(f,Mheader.groupcount);
            //write boneoffset
            Writelong(f,Mheader.bonesoffset);
            //write groupoffset
            Writelong(f,Mheader.groupoffset);
            //write textureoffset
            Writelong(f,Mheader.textureoffset);
            //write meshoffset
            Writelong(f,Mheader.meshoffset);
            //write vertexoffset
            Writelong(f,Mheader.vertexoffset);
            //write facesoffset
            Writelong(f,Mheader.facesoffset);
            //write unknoffset
            Writelong(f,Mheader.unkoffset);
////////////////////////// writing unknown chunk 1
            Writelong(f,Mhunk1.un1);
            Writelong(f,Mhunk1.un2);
            Writelong(f,Mhunk1.un3);
            Writelong(f,Mhunk1.un4);
            Writelong(f,Mhunk1.un5);
            Writelong(f,Mhunk1.un6);
            Writelong(f,Mhunk1.un7);
            Writelong(f,Mhunk1.un8);
            Writelong(f,Mhunk1.un9);
            Writelong(f,Mhunk1.un10);
            Writelong(f,Mhunk1.un11);
            Writelong(f,Mhunk1.un12);
            Writelong(f,Mhunk1.un13);
            Writelong(f,Mhunk1.un14);
            Writelong(f,Mhunk1.un15);
         //   Writelong(f,Mhunk1.un16);
            QByteArray un16 = QByteArray::fromHex("0000CDCD"); // dd;da pc is this? (needs varification)
            WriteBElong(f,un16); // output exact ^
            Writelong(f,Mhunk1.un17);

            QByteArray h1 = QByteArray::fromHex("CDCDCDCD"); // dd;da pc is this? (needs varification) for later use

////////////////////////// writing bone data
            for (int i=0;i<Mbones.boneinfo.size();i++){

              //if version == 237 -> boneinfo2
              if (Mheader.version.toHex().toUInt(&ok,16) == 237){
                  Writeshort(f,Mbones.boneinfo[i].id);
                  Writebyte(f,Mbones.boneinfo[i].parentid);
                  Writebyte(f,Mbones.boneinfo[i].child);
              }
              else{
                  Writebyte(f,Mbones.boneinfo[i].id);
                  Writebyte(f,Mbones.boneinfo[i].parentid);
                  Writebyte(f,Mbones.boneinfo[i].child);
                  Writebyte(f,Mbones.boneinfo[i].unk);
              }
              // write 5* 4byte longs of unknown data
              Writelong(f,Mbones.boneinfo[i].unk1);
              Writelong(f,Mbones.boneinfo[i].unk2);
              Writelong(f,Mbones.boneinfo[i].unk3);
              Writelong(f,Mbones.boneinfo[i].unk4);
              Writelong(f,Mbones.boneinfo[i].unk5);
            }

            for (int i=0;i<Mbones.boneinfo.size();i++){
                WriteMatrix44(f,i*16,Mbones.lmatrices);
            }

            for (int i=0;i<Mbones.boneinfo.size();i++){
                WriteMatrix44(f,i*16,Mbones.amatrices);
            }
            //  Mbones.remaptablesize = (Mheader.bonecount.toHex().toUInt(&ok,16) == 137)?512:256;
            for (int i =0; i<Mbones.remaptable.size();i++){
                Writebyte(f,Mbones.remaptable[i]);
            }


//////////////////////  writing group data


            for (int i=0;i<Mgroups.groupinfo.size();i++){

                  Writelong(f,Mgroups.groupinfo[i].h0);
                //  WriteBElong(f,Mgroups.groupinfo[i].h1);
                 // QByteArray h1 = QByteArray::fromHex("CDCDCDCD"); // dd;da pc is this? (needs varification)
                  WriteBElong(f,h1); // write this as exact^
                  Writelong(f,Mgroups.groupinfo[i].h2);
                  Writelong(f,Mgroups.groupinfo[i].h3);
                  Writelong(f,Mgroups.groupinfo[i].b0);
                  Writelong(f,Mgroups.groupinfo[i].b1);
                  Writelong(f,Mgroups.groupinfo[i].b2);
                  Writelong(f,Mgroups.groupinfo[i].b3);

             }

//////////////////////  writing material data


            for (int i=0;i<Mmats.name.size();i++){

                WriteMaterial(f, Mmats.name[i]);
            }


/////////////////////  writing mesh data
///  for i=0; i<mheader.meshcount -> get meshparts

        for (int i=0;i<Mparts.parts.size();i++){
             Writeshort(f,Mparts.parts[i].unksh1);
             Writeshort(f,Mparts.parts[i].vertexcount);

             //compute sh2 value
             if(Mheader.BEndian){//it's pc don't convert
                 Writebyte(f,Mparts.parts[i].id);
                 Writeshort(f,Mparts.parts[i].material);
                 Writebyte(f,Mparts.parts[i].LOD);
                 Writebyte(f,Mparts.parts[i].unkbyte20);
             }
             else{ //convert
//                 Writebyte(f,Mparts.parts[i].id);
//                 Writeshort(f,Mparts.parts[i].material);
                 QByteArray wtf;
                 wtf.append(Mparts.parts[i].id.toHex()[1]);
                 wtf.append(Mparts.parts[i].material.toHex()[0]);
                 wtf = QByteArray::fromHex(wtf);
                 Writebyte(f,wtf);

                 QByteArray wtf2;
                 wtf2.append(Mparts.parts[i].material.toHex()[3]);
                 wtf2.append(Mparts.parts[i].id.toHex()[0]);
                 wtf2.append(Mparts.parts[i].material.toHex()[2]);
                 wtf2.append(Mparts.parts[i].material.toHex()[1]);
                 wtf2 = QByteArray::fromHex(wtf2);
                 WriteBEshort(f,wtf2);

                 Writebyte(f,Mparts.parts[i].LOD);

                uint ps3= Mparts.parts[i].unkbyte20.toHex().toUInt(&ok,16);

                     QString boop = QString("%1").arg(((ps3 - 128)*8) +1,2,16,QChar('0'));
                     QByteArray newunksh2 = QByteArray::fromHex(boop.toLocal8Bit());
                Writebyte(f,newunksh2);


             }
             Writebyte(f,Mparts.parts[i].unkbyte21);
             Writebyte(f,Mparts.parts[i].blocksize);
             // map unkbyte3 value
             if(Mheader.BEndian){//it's pc don't convert
                 Writebyte(f,Mparts.parts[i].unkbtye3);
             }
             else{ //convert byte3

                 if(byte3map.find(Mparts.parts[i].unkbtye3) != byte3map.end()){
                    Writebyte(f,byte3map[Mparts.parts[i].unkbtye3]);
                 }


                 else{
                     if(unknownbyte3.find(Mparts.parts[i].unkbtye3) == unknownbyte3.end()){
                       unknownbyte3[Mparts.parts[i].unkbtye3] = unkbyte3found;
                       unkbyte3found++;
                     }
                     Writebyte(f,Mparts.parts[i].unkbtye3);
                 }

             }

             Writelong(f,Mparts.parts[i].vertexsub);
             Writelong(f,Mparts.parts[i].vertexoffset);
             Writelong(f,Mparts.parts[i].blocktype);
             if(Mheader.BEndian){// it's pc don't convert
             Writelong(f,Mparts.parts[i].faceoffset);
             Writelong(f,Mparts.parts[i].facecount);
             }
             else{ // convert to ps3
                 if( i == 0){
                     Writelong(f,Mparts.parts[i].faceoffset); // offset is the same probably "0"
                 }
                 else{
                      uint newfoff= Mparts.parts[i-1].facecount.toHex().toUInt(&ok,16)+ Mparts.parts[i-1].faceoffset.toHex().toUInt(&ok,16) +2;
                      QString boop = QString("%1").arg(newfoff,8,16,QChar('0'));
                      QByteArray newfacesoffset = QByteArray::fromHex(boop.toLocal8Bit());
                     Writelong(f,newfacesoffset);
                     // update memory
                     Mparts.parts[i].faceoffset = newfacesoffset;
                 }
                 uint newfcount =0;

                 for (int c=0;c<Mparts.parts[i].meshdata[0].faces.size();c++){
                     newfcount +=  Mparts.parts[i].meshdata[0].faces[c].size();
                     // degenerate tirangle odd strip addition
                     if(!(Mparts.parts[i].meshdata[0].faces[c].size() % 2 == 0)){
                         newfcount++; //no?
                     }
                 }
                 // now add denegerate triangle computation
                 newfcount += (Mparts.parts[i].meshdata[0].faces.size() -1 )*2; // number of strips
                 QString boop = QString("%1").arg(newfcount,8,16,QChar('0'));
                 QByteArray newfacescount = QByteArray::fromHex(boop.toLocal8Bit());
                 Writelong(f,newfacescount);
                   // update memory
                   Mparts.parts[i].facecount = newfacescount;
             }
             Writelong(f,Mparts.parts[i].unklong4);
             Writebyte(f,Mparts.parts[i].unkbyte5);
             Writebyte(f,Mparts.parts[i].boneremapid);
             Writeshort(f,Mparts.parts[i].unksh6);
             Writeshort(f,Mparts.parts[i].unksh7);
             Writeshort(f,Mparts.parts[i].unksh8);
             Writelong(f,Mparts.parts[i].unklong);
        }

        ///////////////////////// write unknown chunk between mesh data and vertext offset
        ///     struct MOD_unk2_chunk
        ///
                            for (int i=0;i<Mparts.chunks.size();i++){
                                Writelong(f,Mparts.chunks[i].un1 );
                                WriteBElong(f,h1); // on pc dd;da it is "CDCDCDCD" on ps3 it's all 0's
                                WriteBElong(f,h1 ); // on pc dd;da it is "CDCDCDCD" on ps3 it's all 0's
                                WriteBElong(f,h1 ); // on pc dd;da it is "CDCDCDCD" on ps3 it's all 0's
                                Writelong(f,Mparts.chunks[i].un5 );
                                Writelong(f,Mparts.chunks[i].un6 );
                                Writelong(f,Mparts.chunks[i].un7 ); //body begin
                                Writelong(f,Mparts.chunks[i].un8 );
                                Writelong(f,Mparts.chunks[i].un9 );
                                Writelong(f,Mparts.chunks[i].un10 );
                                Writelong(f,Mparts.chunks[i].un11 );
                                Writelong(f,Mparts.chunks[i].un12 );
                                Writelong(f,Mparts.chunks[i].un13 );
                                Writelong(f,Mparts.chunks[i].un14 );
                                Writelong(f,Mparts.chunks[i].un15 );
                                Writelong(f,Mparts.chunks[i].un16 );
                                Writelong(f,Mparts.chunks[i].un17 );
                                Writelong(f,Mparts.chunks[i].un18 );
                                Writelong(f,Mparts.chunks[i].un19 );
                                Writelong(f,Mparts.chunks[i].un20 );
                                Writelong(f,Mparts.chunks[i].un21 );
                                Writelong(f,Mparts.chunks[i].un22 );
                                Writelong(f,Mparts.chunks[i].un23 );
                                Writelong(f,Mparts.chunks[i].un24 );
                                Writelong(f,Mparts.chunks[i].un25 );
                                Writelong(f,Mparts.chunks[i].un26 );
                                Writelong(f,Mparts.chunks[i].un27 );
                                Writelong(f,Mparts.chunks[i].un28 );
                                Writelong(f,Mparts.chunks[i].un29 );
                                Writelong(f,Mparts.chunks[i].un30 );
                                Writelong(f,Mparts.chunks[i].un31 );
                                Writelong(f,Mparts.chunks[i].un32 );
                                Writelong(f,Mparts.chunks[i].un33 );
                                Writelong(f,Mparts.chunks[i].un34 );
                                Writelong(f,Mparts.chunks[i].un35 );
                                Writelong(f,Mparts.chunks[i].un36 );

                            }
//set new vertex offset
if(goffset != Mheader.vertexoffset.toHex().toUInt(&ok,16) ){
    QMessageBox msgBox;
    QString boop = QString("%1").arg(goffset,8,16,QChar('0'));
    QByteArray newoffset = QByteArray::fromHex(boop.toLocal8Bit());
    msgBox.setText("Vertex offset has changed!! before: " +Mheader.vertexoffset.toHex() + " Current: " +newoffset.toHex());
    msgBox.exec();

    //write new vertex offset
    fseek(f,52,SEEK_SET);
    Writelong(f,newoffset );
    goffset-=4; //this is a rewrite
    fseek(f,goffset,SEEK_SET);
}
/////////////////  writing vbo permesh part data
/// clear stuff check for mem leak later

                  for (int i=0;i<Mparts.parts.size();i++){
                 //  MOD_Mesh_Data *meshdata = &Mparts.parts[i].meshdata;
                    for(int j=0;j<Mparts.parts[i].vertexcount.toHex().toUInt(&ok,16);j++){

                        if(blocktype.find(Mparts.parts[i].blocktype) != blocktype.end()){
                            switch(blocktype[Mparts.parts[i].blocktype]){
                              case 2736832534: //unknown
                               Writeshort(f, Mparts.parts[i].meshdata[0].unksh1[j]);
                               Writeshort(f, Mparts.parts[i].meshdata[0].unksh2[j]);
                               Writeshort(f, Mparts.parts[i].meshdata[0].unksh3[j]);
                               Writeshort(f, Mparts.parts[i].meshdata[0].unksh4[j]);
                               WriteBElong(f, Mparts.parts[i].meshdata[0].unklong1[j]);
                               WriteBElong(f, Mparts.parts[i].meshdata[0].unklong2[j]);
                               WriteBElong(f, Mparts.parts[i].meshdata[0].unklong3[j]);
                               WriteBElong(f, Mparts.parts[i].meshdata[0].unklong4[j]);
                               WriteBElong(f, Mparts.parts[i].meshdata[0].unklong5[j]);

                                break;
                              case 213286933: //unkown
                               Writeshort(f, Mparts.parts[i].meshdata[0].unksh1[j]);
                               Writeshort(f, Mparts.parts[i].meshdata[0].unksh2[j]);
                               Writeshort(f, Mparts.parts[i].meshdata[0].unksh3[j]);
                               Writeshort(f, Mparts.parts[i].meshdata[0].unksh4[j]);
                               WriteBElong(f, Mparts.parts[i].meshdata[0].unklong1[j]);
                               WriteBElong(f, Mparts.parts[i].meshdata[0].unklong2[j]);
                               WriteBElong(f, Mparts.parts[i].meshdata[0].unklong3[j]);
                                break;
                              case 349437977:
                              case 349437984: //appears in dd;da weapons?

                               Writeshort(f, Mparts.parts[i].meshdata[0].verticies[(j*3)+0]);
                               Writeshort(f, Mparts.parts[i].meshdata[0].verticies[(j*3)+1]);
                               Writeshort(f, Mparts.parts[i].meshdata[0].verticies[(j*3)+2]);
                               Writeshort(f, Mparts.parts[i].meshdata[0].weights[(j*3)]);
                               Writebyte(f, Mparts.parts[i].meshdata[0].normals[(j*3)+0]);
                               Writebyte(f, Mparts.parts[i].meshdata[0].normals[(j*3)+1]);
                               Writebyte(f, Mparts.parts[i].meshdata[0].normals[(j*3)+2]);
                               Writebyte(f, Mparts.parts[i].meshdata[0].unkbyte1[j]);
                               WriteBElong(f, Mparts.parts[i].meshdata[0].unklong1[j]);
                               Writebyte(f, Mparts.parts[i].meshdata[0].bns[(j*4)+0]);
                               Writebyte(f, Mparts.parts[i].meshdata[0].bns[(j*4)+1]);
                               Writebyte(f, Mparts.parts[i].meshdata[0].bns[(j*4)+2]);
                               Writebyte(f, Mparts.parts[i].meshdata[0].bns[(j*4)+3]);
                               Writeshort(f, Mparts.parts[i].meshdata[0].texturemap[(j*2)+0]);
                               Writeshort(f, Mparts.parts[i].meshdata[0].texturemap[(j*2)+1]);
                               Writeshort(f, Mparts.parts[i].meshdata[0].weights[(j*3)+1]);
                               Writeshort(f, Mparts.parts[i].meshdata[0].weights[(j*3)+2]);
                                break;
                               case 3141681188:
                               case 309555230:
                               case 3141681181:

                                Writeshort(f, Mparts.parts[i].meshdata[0].verticies[(j*3)+0]);
                                Writeshort(f, Mparts.parts[i].meshdata[0].verticies[(j*3)+1]);
                                Writeshort(f, Mparts.parts[i].meshdata[0].verticies[(j*3)+2]);
                                Writeshort(f, Mparts.parts[i].meshdata[0].weights[(j*7)]);
                                Writebyte(f, Mparts.parts[i].meshdata[0].normals[(j*3)+0]);
                                Writebyte(f, Mparts.parts[i].meshdata[0].normals[(j*3)+1]);
                                Writebyte(f, Mparts.parts[i].meshdata[0].normals[(j*3)+2]);
                                Writebyte(f, Mparts.parts[i].meshdata[0].unkbyte1[j]);

                                Writebyte(f, Mparts.parts[i].meshdata[0].weights[(j*7)+1]);
                                Writebyte(f, Mparts.parts[i].meshdata[0].weights[(j*7)+2]);
                                Writebyte(f, Mparts.parts[i].meshdata[0].weights[(j*7)+3]);
                                Writebyte(f, Mparts.parts[i].meshdata[0].weights[(j*7)+4]);

                                Writebyte(f, Mparts.parts[i].meshdata[0].bns[(j*8)+0]);
                                Writebyte(f, Mparts.parts[i].meshdata[0].bns[(j*8)+1]);
                                Writebyte(f, Mparts.parts[i].meshdata[0].bns[(j*8)+2]);
                                Writebyte(f, Mparts.parts[i].meshdata[0].bns[(j*8)+3]);
                                Writebyte(f, Mparts.parts[i].meshdata[0].bns[(j*8)+4]);
                                Writebyte(f, Mparts.parts[i].meshdata[0].bns[(j*8)+5]);
                                Writebyte(f, Mparts.parts[i].meshdata[0].bns[(j*8)+6]);
                                Writebyte(f, Mparts.parts[i].meshdata[0].bns[(j*8)+7]);

                                Writeshort(f, Mparts.parts[i].meshdata[0].texturemap[(j*2)+0]);
                                Writeshort(f, Mparts.parts[i].meshdata[0].texturemap[(j*2)+1]);
                                Writeshort(f, Mparts.parts[i].meshdata[0].weights[(j*7)+5]);
                                Writeshort(f, Mparts.parts[i].meshdata[0].weights[(j*7)+6]);
                                WriteBElong(f, Mparts.parts[i].meshdata[0].unklong1[j]);

                                break;
                              }
                        }


                        else{
                            if(unknownblocktypes.find(Mparts.parts[i].blocktype) == unknownblocktypes.end()){
                              unknownblocktypes[Mparts.parts[i].blocktype] = unktypesfound;
                              unktypesfound++;
//                              QMessageBox msgBox;
//                              msgBox.setText("Unknown VBO Format: " +Mparts.parts[i].blocktype.toHex() + "\n!!!DATA SKIPPED!!!! \n Please report this along with the file you used." );
//                              msgBox.exec();
                            }
                        }


                   }

                }

                  /////////////// write faces data

                  //set new vertex offset

                  if(goffset != Mheader.facesoffset.toHex().toUInt(&ok,16) ){
                      QMessageBox msgBox;
                      QString boop = QString("%1").arg(goffset,8,16,QChar('0'));
                      QByteArray newoffset = QByteArray::fromHex(boop.toLocal8Bit());
                      msgBox.setText("Faces offset has changed!! before: " +Mheader.facesoffset.toHex() + " Current: " +newoffset.toHex());
                      msgBox.exec();

                      //write new vertex offset
                      fseek(f,56,SEEK_SET);
                      Writelong(f,newoffset );
                      goffset-=4; //this is a rewrite
                      fseek(f,goffset,SEEK_SET);
                  }

                                     //start writing
// ps3 sentinal test?
//                                         QByteArray last = QByteArray::fromHex("FFFF");
//                                         QByteArray next = QByteArray::fromHex("FFFF");

//                                         //start writing
//                                             QByteArray sentinal = QByteArray::fromHex("FFFF");

//                                             for(int i=0;i<faces.size();i++){
//                                                 for(int j=0;j<faces[i].size();j++){
//                                                     Writeshort(f,faces[i][j]);
//                                                 }
//                                                 if ( i+1 <faces.size()){
//                                                 Writeshort(f,sentinal);
//                                                 }
//                                             }
                  // start writing faces
                  QByteArray last = QByteArray::fromHex("AAAA");
                  QByteArray first = QByteArray::fromHex("AAAA");
                   long int facescounter =0;
                   /* old working face data
                  for (int i=0;i<Mparts.parts.size();i++){





                          for(int j=0;j<Mparts.parts[i].meshdata[0].faces.size();j++){ // per strip

                              for(int k=0;k<Mparts.parts[i].meshdata[0].faces[j].size();k++){
                                  if (k == 0){
                                      first = Mparts.parts[i].meshdata[0].faces[j][k];
                                      if( i != 0 ){ // write double if not first mesh part and first strip
                                          Writeshort(f,first);
                                          facescounter++;
                                      }
                                      else if (j !=0 ){
                                          Writeshort(f,first);
                                          facescounter++;
                                      }

                                  }


                                  last = Mparts.parts[i].meshdata[0].faces[j][k];

                                  Writeshort(f,last);
                                  facescounter++;
                                }
                               // write double
                                  Writeshort(f,last);
                                  facescounter++;

                          }
                  } */

                   // start writing faces


                   for (int i=0;i<Mparts.parts.size();i++){


// i = 2, k= 0 , j = 1

                           for(int j=0;j<Mparts.parts[i].meshdata[0].faces.size();j++){ // per strip
                              QList<QStandardItem*> strip;
                               for(int k=0;k<Mparts.parts[i].meshdata[0].faces[j].size();k++){
                                 if( k == 0){
                                       first = Mparts.parts[i].meshdata[0].faces[j][k];

                                       if( i != 0  ){ // write double if not first mesh part and first strip
                                           Writeshort(f,first);
                                           facescounter++;

                                       }
                                       else if (j !=0 ){

                                        Writeshort(f,first);
                                       facescounter++;
//                                       if(!(Mparts.parts[i].meshdata[0].faces[j-1].size() % 2 == 0)  ){
//                                           // check last strip was odd
//                                            Writeshort(f,first);
//                                           facescounter++;
//                                       }

                                     }
                                      else{
                                      // do nothing

                                       }
                                       if (j >0){
                                       if(!(Mparts.parts[i].meshdata[0].faces[j-1].size() % 2 == 0)  ){
                                           // check last strip was odd
                                            Writeshort(f,first);
                                           facescounter++;
                                       }
                                       }

                                  }
                                   last = Mparts.parts[i].meshdata[0].faces[j][k];

                                   Writeshort(f,last);
                                   facescounter++;
                                 }
                                // write double
                               Writeshort(f,last);
                                   facescounter++;

                                   // write tripple if last of mesh part
                                   if(!(Mparts.parts[i].meshdata[0].faces[j].size() % 2 == 0) && j+1 == Mparts.parts[i].meshdata[0].faces.size()){
                                       // check last strip was odd
                                        Writeshort(f,last);
                                       facescounter++;
                                   }

                           }



                   }

/* wtf was i doing here?
                                         for(int i=0;i<faces.size();i++){

                                             for(int j=0;j<faces[i].size();j++){

                                                last = faces[i][j];
//                                                Writeshort(f,last);
                                                if(j==0 && i>0){
//                                                 Writeshort(f,last);
                                                }
                                             }
//                                             Writeshort(f,last);
                                             Writeshort(f,sentinal);
                                        }
*/
        last = QByteArray::fromHex("0000");
        WriteBEshort(f,last);
        //set new face count
        if(facescounter != Mheader.facecount.toHex().toUInt(&ok,16) ){
            QMessageBox msgBox;
            QString boop = QString("%1").arg(facescounter,8,16,QChar('0'));
            QByteArray newoffset = QByteArray::fromHex(boop.toLocal8Bit());
            msgBox.setText("Faces count has changed!! before: " +Mheader.facecount.toHex() + " Current: " +newoffset.toHex());
            msgBox.exec();

            //write new vertex offset
            fseek(f,16,SEEK_SET);
            Writelong(f,newoffset );
            goffset-=4; //this is a rewrite
            fseek(f,goffset,SEEK_SET);
        }

        //set new unknown offset  (EOF?)
        if(goffset != Mheader.unkoffset.toHex().toUInt(&ok,16) ){
            QMessageBox msgBox;
            QString boop = QString("%1").arg(goffset,8,16,QChar('0'));
            QByteArray newoffset = QByteArray::fromHex(boop.toLocal8Bit());
            msgBox.setText("Unknown (EOF?) offset has changed!! before: " +Mheader.unkoffset.toHex() + " Current: " +newoffset.toHex());
            msgBox.exec();

            //write new vertex offset
            fseek(f,60,SEEK_SET);
            Writelong(f,newoffset );
            goffset-=4; //this is a rewrite
            fseek(f,goffset,SEEK_SET);
        }
        last = QByteArray::fromHex("00000000");
        WriteBElong(f,last);
    }
        else if (rdoTheaded->isChecked()){ //ps3
////////////////////////// writing header
//initialize global write offset
            goffset = 0;
            //write header.id
            QByteArray h = QByteArray::fromHex("00444F4D");
            WriteBElong(f,h);//Mheader.id);
            //write version2
            Writebyte(f,Mheader.version2);
            //write version
            Writebyte(f,Mheader.version);
            // ps3 is big ending so don't flip
            //write bonecount
            WriteBEshort(f,Mheader.bonecount);
            //write meshcount
            WriteBEshort(f,Mheader.meshcount);
            //write materialcount
            WriteBEshort(f,Mheader.materialcount);
            //write vertexcount
            WriteBElong(f,Mheader.vertexcount);
            //write facecount
            WriteBElong(f,Mheader.facecount);
            //write vertexids
            WriteBElong(f,Mheader.vertexids);
            //write vertexbuffersize
            WriteBElong(f,Mheader.vertexbuffersize);
            //write secondbuffersize
            WriteBElong(f,Mheader.scondbuffersize);
            //write groupcount
            WriteBElong(f,Mheader.groupcount);
            //write boneoffset
            WriteBElong(f,Mheader.bonesoffset);
            //write groupoffset
            WriteBElong(f,Mheader.groupoffset);
            //write textureoffset
            WriteBElong(f,Mheader.textureoffset);
            //write meshoffset
            WriteBElong(f,Mheader.meshoffset);
            //write vertexoffset
            WriteBElong(f,Mheader.vertexoffset);
            //write facesoffset
            WriteBElong(f,Mheader.facesoffset);
            //write unknoffset
            WriteBElong(f,Mheader.unkoffset);

////////////////////////// writing unknown chunk 1
                        WriteBElong(f,Mhunk1.un1);
                        WriteBElong(f,Mhunk1.un2);
                        WriteBElong(f,Mhunk1.un3);
                        WriteBElong(f,Mhunk1.un4);
                        WriteBElong(f,Mhunk1.un5);
                        WriteBElong(f,Mhunk1.un6);
                        WriteBElong(f,Mhunk1.un7);
                        WriteBElong(f,Mhunk1.un8);
                        WriteBElong(f,Mhunk1.un9);
                        WriteBElong(f,Mhunk1.un10);
                        WriteBElong(f,Mhunk1.un11);
                        WriteBElong(f,Mhunk1.un12);
                        WriteBElong(f,Mhunk1.un13);
                        WriteBElong(f,Mhunk1.un14);
                        WriteBElong(f,Mhunk1.un15);
                     //   Writelong(f,Mhunk1.un16);
                        QByteArray un16 = QByteArray::fromHex("00000000"); // dd;da ps3 is this? (needs varification)
                        WriteBElong(f,un16);
                        WriteBElong(f,Mhunk1.un17);

////////////////////////// writing bone data
                        for (int i=0;i<Mbones.boneinfo.size();i++){

                          //if version == 237 -> boneinfo2
                          if (Mheader.version.toHex().toUInt(&ok,16) == 237){
                              WriteBEshort(f,Mbones.boneinfo[i].id);
                              Writebyte(f,Mbones.boneinfo[i].parentid);
                              Writebyte(f,Mbones.boneinfo[i].child);
                          }
                          else{
                              Writebyte(f,Mbones.boneinfo[i].id);
                              Writebyte(f,Mbones.boneinfo[i].parentid);
                              Writebyte(f,Mbones.boneinfo[i].child);
                              Writebyte(f,Mbones.boneinfo[i].unk);
                          }
                          // write 5* 4byte longs of unknown data
                          WriteBElong(f,Mbones.boneinfo[i].unk1);
                          WriteBElong(f,Mbones.boneinfo[i].unk2);
                          WriteBElong(f,Mbones.boneinfo[i].unk3);
                          WriteBElong(f,Mbones.boneinfo[i].unk4);
                          WriteBElong(f,Mbones.boneinfo[i].unk5);
                        }

                        for (int i=0;i<Mbones.boneinfo.size();i++){
                            WriteBEMatrix44(f,i*16,Mbones.lmatrices);
                        }

                        for (int i=0;i<Mbones.boneinfo.size();i++){
                            WriteBEMatrix44(f,i*16,Mbones.amatrices);
                        }

                      //  Mbones.remaptablesize = (Mheader.bonecount.toHex().toUInt(&ok,16) == 137)?512:256;
                        for (int i =0; i<Mbones.remaptable.size();i++){
                            Writebyte(f,Mbones.remaptable[i]);
                        }

//////////////////////  writing group data


                        for (int i=0;i<Mgroups.groupinfo.size();i++){

                              WriteBElong(f,Mgroups.groupinfo[i].h0);
                            //  WriteBElong(f,Mgroups.groupinfo[i].h1);
                             //  QByteArray h1 = QByteArray::fromHex("00000000"); // dd;da ps3 is this? (needs varification)
                              WriteBElong(f,un16);
                              WriteBElong(f,Mgroups.groupinfo[i].h2);
                              WriteBElong(f,Mgroups.groupinfo[i].h3);
                              WriteBElong(f,Mgroups.groupinfo[i].b0);
                              WriteBElong(f,Mgroups.groupinfo[i].b1);
                              WriteBElong(f,Mgroups.groupinfo[i].b2);
                              WriteBElong(f,Mgroups.groupinfo[i].b3);

                         }

//////////////////////  writing material data


                        for (int i=0;i<Mmats.name.size();i++){

                            WriteMaterial(f, Mmats.name[i]);
                        }

/////////////////////  writing mesh data
///  for i=0; i<mheader.meshcount -> get meshparts

                       for (int i=0;i<Mparts.parts.size();i++){
                           WriteBEshort(f,Mparts.parts[i].unksh1);
                           WriteBEshort(f,Mparts.parts[i].vertexcount);
                           //compute sh2 value
                           if(!Mheader.BEndian){//it's ps3 don't convert
                               Writebyte(f,Mparts.parts[i].id);
                               WriteBEshort(f,Mparts.parts[i].material);
                               Writebyte(f,Mparts.parts[i].LOD);
                               Writebyte(f,Mparts.parts[i].unkbyte20);
                           }
                           else{ //convert
//                               Writebyte(f,Mparts.parts[i].id);
//                               WriteBEshort(f,Mparts.parts[i].material);
                               QByteArray wtf;

                               wtf.append(Mparts.parts[i].material.toHex()[3]);
                               wtf.append(Mparts.parts[i].id.toHex()[0]);
                               wtf = QByteArray::fromHex(wtf);
                               Writebyte(f,wtf);

                               QByteArray wtf2;
                               wtf2.append(Mparts.parts[i].id.toHex()[1]);
                               wtf2.append(Mparts.parts[i].material.toHex()[2]);

                               wtf2.append(Mparts.parts[i].material.toHex()[1]);
                               wtf2.append(Mparts.parts[i].material.toHex()[0]);
                               wtf2 = QByteArray::fromHex(wtf2);
                               WriteBEshort(f,wtf2);
                               Writebyte(f,Mparts.parts[i].LOD);

                              uint ps3= Mparts.parts[i].unkbyte20.toHex().toUInt(&ok,16);

                                   QString boop = QString("%1").arg(((ps3 - 128)*8) +1,2,16,QChar('0'));
                                   QByteArray newunksh2 = QByteArray::fromHex(boop.toLocal8Bit());
                              Writebyte(f,newunksh2);


                           }
                           Writebyte(f,Mparts.parts[i].unkbyte21);
                           Writebyte(f,Mparts.parts[i].blocksize);
                           // map unkbyte3 value
                           if(!Mheader.BEndian){//it's ps3 don't convert
                               Writebyte(f,Mparts.parts[i].unkbtye3);
                           }
                           else{ //convert byte3

                               if(byte3map.find(Mparts.parts[i].unkbtye3) != byte3map.end()){
                                  Writebyte(f,byte3map[Mparts.parts[i].unkbtye3]);
                               }


                               else{
                                   if(unknownbyte3.find(Mparts.parts[i].unkbtye3) == unknownbyte3.end()){
                                     unknownbyte3[Mparts.parts[i].unkbtye3] = unkbyte3found;
                                     unkbyte3found++;
                                   }
                                   Writebyte(f,Mparts.parts[i].unkbtye3);
                               }

                           }
                           WriteBElong(f,Mparts.parts[i].vertexsub);
                           WriteBElong(f,Mparts.parts[i].vertexoffset);
                           WriteBElong(f,Mparts.parts[i].blocktype);
                           // fix me bacon!
                           WriteBElong(f,Mparts.parts[i].faceoffset);
                           WriteBElong(f,Mparts.parts[i].facecount);
                           WriteBElong(f,Mparts.parts[i].unklong4);
                           Writebyte(f,Mparts.parts[i].unkbyte5);
                           Writebyte(f,Mparts.parts[i].boneremapid);
                           WriteBEshort(f,Mparts.parts[i].unksh6);
                           WriteBEshort(f,Mparts.parts[i].unksh7);
                           WriteBEshort(f,Mparts.parts[i].unksh8);
                           WriteBElong(f,Mparts.parts[i].unklong);
                          // QByteArray h1 = QByteArray::fromHex("00000000"); // dd;da ps3 is this
                           WriteBElong(f,un16); // write this as exact^
                           WriteBElong(f,un16); // write this as exact twice^
                        }

///////////////////////// write unknown chunk between mesh data and vertext offset 2
///     struct MOD_unk2_chunk
///
                    for (int i=0;i<Mparts.chunks.size();i++){
                        WriteBElong(f,Mparts.chunks[i].un1 );
                        WriteBElong(f,un16); // on pc dd;da it is "CDCDCDCD" on ps3 it's all 0's
                        WriteBElong(f,un16 ); // on pc dd;da it is "CDCDCDCD" on ps3 it's all 0's
                        WriteBElong(f,un16 ); // on pc dd;da it is "CDCDCDCD" on ps3 it's all 0's
                        WriteBElong(f,Mparts.chunks[i].un5 );
                        WriteBElong(f,Mparts.chunks[i].un6 );
                        WriteBElong(f,Mparts.chunks[i].un7 ); //body begin
                        WriteBElong(f,Mparts.chunks[i].un8 );
                        WriteBElong(f,Mparts.chunks[i].un9 );
                        WriteBElong(f,Mparts.chunks[i].un10 );
                        WriteBElong(f,Mparts.chunks[i].un11 );
                        WriteBElong(f,Mparts.chunks[i].un12 );
                        WriteBElong(f,Mparts.chunks[i].un13 );
                        WriteBElong(f,Mparts.chunks[i].un14 );
                        WriteBElong(f,Mparts.chunks[i].un15 );
                        WriteBElong(f,Mparts.chunks[i].un16 );
                        WriteBElong(f,Mparts.chunks[i].un17 );
                        WriteBElong(f,Mparts.chunks[i].un18 );
                        WriteBElong(f,Mparts.chunks[i].un19 );
                        WriteBElong(f,Mparts.chunks[i].un20 );
                        WriteBElong(f,Mparts.chunks[i].un21 );
                        WriteBElong(f,Mparts.chunks[i].un22 );
                        WriteBElong(f,Mparts.chunks[i].un23 );
                        WriteBElong(f,Mparts.chunks[i].un24 );
                        WriteBElong(f,Mparts.chunks[i].un25 );
                        WriteBElong(f,Mparts.chunks[i].un26 );
                        WriteBElong(f,Mparts.chunks[i].un27 );
                        WriteBElong(f,Mparts.chunks[i].un28 );
                        WriteBElong(f,Mparts.chunks[i].un29 );
                        WriteBElong(f,Mparts.chunks[i].un30 );
                        WriteBElong(f,Mparts.chunks[i].un31 );
                        WriteBElong(f,Mparts.chunks[i].un32 );
                        WriteBElong(f,Mparts.chunks[i].un33 );
                        WriteBElong(f,Mparts.chunks[i].un34 );
                        WriteBElong(f,Mparts.chunks[i].un35 );
                        WriteBElong(f,Mparts.chunks[i].un36 );

                    }
//set new vertex offset
if(goffset != Mheader.vertexoffset.toHex().toUInt(&ok,16) ){
    QMessageBox msgBox;
    QString boop = QString("%1").arg(goffset,8,16,QChar('0'));
    QByteArray newoffset = QByteArray::fromHex(boop.toLocal8Bit());
    msgBox.setText("Vertex offset has changed!! before: " +Mheader.vertexoffset.toHex() + " Current: " +newoffset.toHex());
    msgBox.exec();

    //write new vertex offset
    fseek(f,52,SEEK_SET);
    WriteBElong(f,newoffset );
    goffset-=4; //this is a rewrite
    fseek(f,goffset,SEEK_SET);
}

/////////////////  writing vbo permesh part data
/// clear stuff check for mem leak later

                  for (int i=0;i<Mparts.parts.size();i++){

                    for(int j=0;j<Mparts.parts[i].vertexcount.toHex().toUInt(&ok,16);j++){

                        if(blocktype.find(Mparts.parts[i].blocktype) != blocktype.end()){
                            switch(blocktype[Mparts.parts[i].blocktype]){
                            case 2736832534: //unknown
                             WriteBEshort(f, Mparts.parts[i].meshdata[0].unksh1[j]);
                             WriteBEshort(f, Mparts.parts[i].meshdata[0].unksh2[j]);
                             WriteBEshort(f, Mparts.parts[i].meshdata[0].unksh3[j]);
                             WriteBEshort(f, Mparts.parts[i].meshdata[0].unksh4[j]);
                             WriteBElong(f, Mparts.parts[i].meshdata[0].unklong1[j]);
                             WriteBElong(f, Mparts.parts[i].meshdata[0].unklong2[j]);
                             WriteBElong(f, Mparts.parts[i].meshdata[0].unklong3[j]);
                             WriteBElong(f, Mparts.parts[i].meshdata[0].unklong4[j]);
                             WriteBElong(f, Mparts.parts[i].meshdata[0].unklong5[j]);
                               break;
                              case 213286933: //unkown
                               WriteBEshort(f, Mparts.parts[i].meshdata[0].unksh1[j]);
                               WriteBEshort(f, Mparts.parts[i].meshdata[0].unksh2[j]);
                               WriteBEshort(f, Mparts.parts[i].meshdata[0].unksh3[j]);
                               WriteBEshort(f, Mparts.parts[i].meshdata[0].unksh4[j]);
                               WriteBElong(f, Mparts.parts[i].meshdata[0].unklong1[j]);
                               WriteBElong(f, Mparts.parts[i].meshdata[0].unklong2[j]);
                               WriteBElong(f, Mparts.parts[i].meshdata[0].unklong3[j]);
                                break;
                              case 349437977:
                              case 349437984: //appears in dd;da weapons?

                               WriteBEshort(f, Mparts.parts[i].meshdata[0].verticies[j*3]);
                               WriteBEshort(f, Mparts.parts[i].meshdata[0].verticies[(j*3)+1]);
                               WriteBEshort(f, Mparts.parts[i].meshdata[0].verticies[(j*3)+2]);
                               WriteBEshort(f, Mparts.parts[i].meshdata[0].weights[j*3]);
                               Writebyte(f, Mparts.parts[i].meshdata[0].normals[j*3]);
                               Writebyte(f, Mparts.parts[i].meshdata[0].normals[(j*3)+1]);
                               Writebyte(f, Mparts.parts[i].meshdata[0].normals[(j*3)+2]);
                               Writebyte(f, Mparts.parts[i].meshdata[0].unkbyte1[j]);
                               WriteBElong(f, Mparts.parts[i].meshdata[0].unklong1[j]);
                               Writebyte(f, Mparts.parts[i].meshdata[0].bns[(j*4)]);
                               Writebyte(f, Mparts.parts[i].meshdata[0].bns[(j*4)+1]);
                               Writebyte(f, Mparts.parts[i].meshdata[0].bns[(j*4)+2]);
                               Writebyte(f, Mparts.parts[i].meshdata[0].bns[(j*4)+3]);
                               WriteBEshort(f, Mparts.parts[i].meshdata[0].texturemap[(j*2)]);
                               WriteBEshort(f, Mparts.parts[i].meshdata[0].texturemap[(j*2)+1]);
                               WriteBEshort(f, Mparts.parts[i].meshdata[0].weights[(j*3)+1]);
                               WriteBEshort(f, Mparts.parts[i].meshdata[0].weights[(j*3)+2]);


                                break;
                            case 3141681188:
                            case 309555230:
                            case 3141681181:

                             WriteBEshort(f, Mparts.parts[i].meshdata[0].verticies[(j*3)+0]);
                             WriteBEshort(f, Mparts.parts[i].meshdata[0].verticies[(j*3)+1]);
                             WriteBEshort(f, Mparts.parts[i].meshdata[0].verticies[(j*3)+2]);
                             WriteBEshort(f, Mparts.parts[i].meshdata[0].weights[(j*7)]);
                             Writebyte(f, Mparts.parts[i].meshdata[0].normals[(j*3)+0]);
                             Writebyte(f, Mparts.parts[i].meshdata[0].normals[(j*3)+1]);
                             Writebyte(f, Mparts.parts[i].meshdata[0].normals[(j*3)+2]);
                             Writebyte(f, Mparts.parts[i].meshdata[0].unkbyte1[j]);

                             Writebyte(f, Mparts.parts[i].meshdata[0].weights[(j*7)+1]);
                             Writebyte(f, Mparts.parts[i].meshdata[0].weights[(j*7)+2]);
                             Writebyte(f, Mparts.parts[i].meshdata[0].weights[(j*7)+3]);
                             Writebyte(f, Mparts.parts[i].meshdata[0].weights[(j*7)+4]);

                             Writebyte(f, Mparts.parts[i].meshdata[0].bns[(j*8)+0]);
                             Writebyte(f, Mparts.parts[i].meshdata[0].bns[(j*8)+1]);
                             Writebyte(f, Mparts.parts[i].meshdata[0].bns[(j*8)+2]);
                             Writebyte(f, Mparts.parts[i].meshdata[0].bns[(j*8)+3]);
                             Writebyte(f, Mparts.parts[i].meshdata[0].bns[(j*8)+4]);
                             Writebyte(f, Mparts.parts[i].meshdata[0].bns[(j*8)+5]);
                             Writebyte(f, Mparts.parts[i].meshdata[0].bns[(j*8)+6]);
                             Writebyte(f, Mparts.parts[i].meshdata[0].bns[(j*8)+7]);

                             WriteBEshort(f, Mparts.parts[i].meshdata[0].texturemap[(j*2)+0]);
                             WriteBEshort(f, Mparts.parts[i].meshdata[0].texturemap[(j*2)+1]);
                             WriteBEshort(f, Mparts.parts[i].meshdata[0].weights[(j*7)+5]);
                             WriteBEshort(f, Mparts.parts[i].meshdata[0].weights[(j*7)+6]);
                             WriteBElong(f, Mparts.parts[i].meshdata[0].unklong1[j]);

                             break;

                              }
                        }


                        else{
                            if(unknownblocktypes.find(Mparts.parts[i].blocktype) == unknownblocktypes.end()){
                              unknownblocktypes[Mparts.parts[i].blocktype] = unktypesfound;
                              unktypesfound++;
//                              QMessageBox msgBox;
//                              msgBox.setText("Unknown VBO Format: " +Mparts.parts[i].blocktype.toHex() + "\n!!!DATA SKIPPED!!!! \n Please report this along with the file you used." );
//                              msgBox.exec();
                            }
                        }


                   }

                }

/////////////// write faces data
                  //set new faces offset
                  if(goffset != Mheader.facesoffset.toHex().toUInt(&ok,16) ){
                      QMessageBox msgBox;
                      QString boop = QString("%1").arg(goffset,8,16,QChar('0'));
                      QByteArray newoffset = QByteArray::fromHex(boop.toLocal8Bit());
                      msgBox.setText("Faces offset has changed!! before: " +Mheader.facesoffset.toHex() + " Current: " +newoffset.toHex());
                      msgBox.exec();

                      //write new vertex offset
                      fseek(f,56,SEEK_SET);
                      WriteBElong(f,newoffset );
                      goffset-=4; //this is a rewrite
                      fseek(f,goffset,SEEK_SET);
                  }


                   //start writing
                       QByteArray sentinal = QByteArray::fromHex("FFFF");

                       for(int i=0;i<faces.size();i++){
                           for(int j=0;j<faces[i].size();j++){
                               WriteBEshort(f,faces[i][j]);
                           }
                           if ( i+1 <faces.size()){
                           WriteBEshort(f,sentinal);
                           }
                       }
                       sentinal = QByteArray::fromHex("0000");
                       WriteBEshort(f,sentinal);

                       //set new unknown offset  (EOF?)
                       if(goffset != Mheader.unkoffset.toHex().toUInt(&ok,16) ){
                           QMessageBox msgBox;
                           QString boop = QString("%1").arg(goffset,8,16,QChar('0'));
                           QByteArray newoffset = QByteArray::fromHex(boop.toLocal8Bit());
                           msgBox.setText("Unknown (EOF?) offset has changed!! before: " +Mheader.unkoffset.toHex() + " Current: " +newoffset.toHex());
                           msgBox.exec();

                           //write new vertex offset
                           fseek(f,60,SEEK_SET);
                           WriteBElong(f,newoffset );
                           goffset-=4; //this is a rewrite
                           fseek(f,goffset,SEEK_SET);
                       }
                       sentinal = QByteArray::fromHex("00000000");
                       WriteBElong(f,sentinal);

      }
else{

                                          QMessageBox msgBox;
                                          msgBox.setText("Exporting to DDON not yet implemented." );
                                          msgBox.exec();
    }


    fclose(f);


    if(unkbyte3found>0){
        QString msg = "Unknown Byte3 conversions (left alone will cause mesh to not display): \n";
        for (auto const& x : unknownbyte3)
        {
            msg.append(x.first.toHex());
            msg.append("\n");
        }
        msg.append("\n!!!DATA SKIPPED!!!! \n Please report this along with the file you used.");
                                      QMessageBox msgBox;
                                      msgBox.setText(msg);
                                      msgBox.exec();
        unkbyte3found =0;
        unknownbyte3.clear();
    }

    }

}

void Dialog::open_file(QString fileName)
{

    // try to open textures as well
    int txcheck = fileName.lastIndexOf(QChar('.'));
   if( txcheck > 0 ){
    QString tx= fileName.left(txcheck);
    tx.append("_BM.dds");

    const QPixmap pixmap(tx);
    difflabel->setPixmap(pixmap);
    difflabel->show();
    const QImage image = pixmap.toImage();
    qDebug() << (image.isNull() ? "QImage error" : "QImage ok");


    tx= fileName.left(txcheck);
        tx.append("_CMM.dds");

        const QPixmap pixmap2(tx);
        speclabel->setPixmap(pixmap2);

        const QImage image2 = pixmap2.toImage();
        qDebug() << (image2.isNull() ? "QImage error" : "QImage ok");

speclabel->show();

        tx= fileName.left(txcheck);
            tx.append("_NM.dds");

            const QPixmap pixmap3(tx);
            normlabel->setPixmap(pixmap3);

            const QImage image3 = pixmap3.toImage();
            qDebug() << (image3.isNull() ? "QImage error" : "QImage ok");
normlabel->show();
            tx= fileName.left(txcheck);
                tx.append("_TM.dds");

                const QPixmap pixmap4(tx);
                litelabel->setPixmap(pixmap4);

                const QImage image4 = pixmap4.toImage();
                qDebug() << (image4.isNull() ? "QImage error" : "QImage ok");
           litelabel->show();
   }





    FILE *Filep;

    Filep = fopen(fileName.toLocal8Bit().constData(), "rb");

    long Fsize;
    char *buffer;
    size_t result;

    // get file size
    fseek(Filep, 0, SEEK_END);
    Fsize = ftell(Filep);
    rewind(Filep);

    // allocate memory to contain the whole file:
    buffer = (char *)malloc(sizeof(char)*Fsize);
    if (buffer == NULL) {
        //fputs("Memory error", stderr);
        QMessageBox msgBox;
        msgBox.setText("Memory Error: buffer is NULL. did you select a file? \n" +fileName);
        msgBox.exec();
        return;
      //  exit(2);
    }

    // copy the file into the buffer:
    result = fread(buffer, 1, Fsize, Filep);
    if (result != Fsize) {
       // fputs("Reading error", stderr);
        QMessageBox msgBox;
        msgBox.setText("Read Error: unable to read file: \n" +fileName);
        msgBox.exec();
        return;
      //  exit(3);
    }

// file should have been opened emit file to renderer
emit this->newTextures(fileName);

QByteArray validator = QByteArray::fromHex("4D4F4400");


// copy value into readable
//long test;
//memcpy(&test,&id.data()[0],4);
unknownblocktypes.clear();
unktypesfound =0;
////////////////////////// reading header
int offset = 0;
bool ok = false;
Mheader.id = Readlong(buffer,offset);
Mheader.BEndian = Mheader.id == validator;
if(Mheader.BEndian){   //pc
    Mheader.version = Readbyte(buffer,offset);//unsigned
    Mheader.version2 = Readbyte(buffer,offset);
    Mheader.bonecount = ReadBEshort(buffer,offset);
    Mheader.meshcount = ReadBEshort(buffer,offset);
    Mheader.materialcount = ReadBEshort(buffer,offset);
    Mheader.vertexcount = ReadBElong(buffer,offset);
    Mheader.facecount = ReadBElong(buffer,offset);
    Mheader.vertexids = ReadBElong(buffer,offset);
    Mheader.vertexbuffersize = ReadBElong(buffer,offset);
    Mheader.scondbuffersize = ReadBElong(buffer,offset);

    Mheader.groupcount = ReadBElong(buffer,offset);
    Mheader.bonesoffset = ReadBElong(buffer,offset);
    Mheader.groupoffset = ReadBElong(buffer,offset);
    Mheader.textureoffset = ReadBElong(buffer,offset);
    Mheader.meshoffset = ReadBElong(buffer,offset);
    Mheader.vertexoffset = ReadBElong(buffer,offset);
    Mheader.facesoffset = ReadBElong(buffer,offset);
    Mheader.unkoffset = ReadBElong(buffer,offset);

////////////////////////// reading unknown chucnk 1
    Mhunk1.un1 = ReadBElong(buffer,offset);
    Mhunk1.un2 = ReadBElong(buffer,offset);
    Mhunk1.un3 = ReadBElong(buffer,offset);
    Mhunk1.un4 = ReadBElong(buffer,offset);
    Mhunk1.un5 = ReadBElong(buffer,offset);
    Mhunk1.un6 = ReadBElong(buffer,offset);
    Mhunk1.un7 = ReadBElong(buffer,offset);
    Mhunk1.un8 = ReadBElong(buffer,offset);
    Mhunk1.un9 = ReadBElong(buffer,offset);
    Mhunk1.un10 = ReadBElong(buffer,offset);
    Mhunk1.un11 = ReadBElong(buffer,offset);
    Mhunk1.un12 = ReadBElong(buffer,offset);
    Mhunk1.un13 = ReadBElong(buffer,offset);
    Mhunk1.un14 = ReadBElong(buffer,offset);
    Mhunk1.un15 = ReadBElong(buffer,offset);
    Mhunk1.un16 = ReadBElong(buffer,offset);
    Mhunk1.un17 = ReadBElong(buffer,offset);

//////////////////////  reading bone data
  Mbones.boneinfo.clear(); // check for memleak later

  for (int i=0;i<Mheader.bonecount.toHex().toUInt(&ok,16);i++){
      MOD_Bone_info  binf;
    //if version == 237 -> boneinfo2
    if (Mheader.version.toHex().toUInt(&ok,16) == 237){
        binf.id = ReadBEshort(buffer,offset);
        binf.parentid = Readbyte(buffer,offset);
        binf.child = Readbyte(buffer,offset);
    }
    else {
        binf.id = Readbyte(buffer,offset);
        binf.parentid = Readbyte(buffer,offset);
        binf.child = Readbyte(buffer,offset);
        binf.unk = Readbyte(buffer,offset);
    }
    // read 5* 4byte longs of unknown data
    binf.unk1 = ReadBElong(buffer,offset);
    binf.unk2 = ReadBElong(buffer,offset);
    binf.unk3 = ReadBElong(buffer,offset);
    binf.unk4 = ReadBElong(buffer,offset);
    binf.unk5 = ReadBElong(buffer,offset);
         Mbones.boneinfo.push_back(binf);
  }

 Mbones.lmatrices.clear();

  for (int i=0;i<Mbones.boneinfo.size();i++){
      ReadBEMatrix44(buffer,offset,Mbones.lmatrices);
  }

 Mbones.amatrices.clear();

  for (int i=0;i<Mbones.boneinfo.size();i++){
      ReadBEMatrix44(buffer,offset,Mbones.amatrices);
  }

  Mbones.remaptablesize = (Mheader.bonecount.toHex().toUInt(&ok,16) == 137)?512:256;
  Mbones.remaptable.clear();

          for (int i =0; i<Mbones.remaptablesize;i++){
              Mbones.remaptable.push_back(Readbyte(buffer,offset));
          }
//////////////////////  reading group data

          Mgroups.groupinfo.clear();
                  for (int i=0;i<Mheader.groupcount.toHex().toUInt(&ok,16);i++){
                         MOD_Group_info  ginf;
                        ginf.h0 = ReadBElong(buffer,offset);
                        ginf.h1 = ReadBElong(buffer,offset);
                        ginf.h2 = ReadBElong(buffer,offset);
                        ginf.h3 = ReadBElong(buffer,offset);
                        ginf.b0 = ReadBElong(buffer,offset);
                        ginf.b1 = ReadBElong(buffer,offset);
                        ginf.b2 = ReadBElong(buffer,offset);
                        ginf.b3 = ReadBElong(buffer,offset);
                       Mgroups.groupinfo.push_back(ginf);
                  }

//////////////////////  reading material data

          Mmats.name.clear();
                    for (int i=0;i<Mheader.materialcount.toHex().toUInt(&ok,16);i++){

                        Mmats.name.push_back(ReadMaterial(buffer,offset));
                     }
/////////////////////  reading mesh data
///  for i=0; i<mheader.meshcount -> get meshparts
                    Mparts.parts.clear(); // check for mem leak later

                    for (int i=0;i<Mheader.meshcount.toHex().toUInt(&ok,16);i++){
                        MOD_Mesh_Part2 mp ;
                        mp.unksh1 = ReadBEshort(buffer,offset);
                        mp.vertexcount = ReadBEshort(buffer,offset);
                        mp.id = Readbyte(buffer,offset);
                        mp.material = ReadBEshort(buffer,offset);
                        mp.LOD = Readbyte(buffer,offset);
                        mp.unkbyte20 = Readbyte(buffer,offset);
                        mp.unkbyte21 = Readbyte(buffer,offset);
                        mp.blocksize = Readbyte(buffer,offset);
                        mp.unkbtye3 = Readbyte(buffer,offset);
                        mp.vertexsub = ReadBElong(buffer,offset);
                        mp.vertexoffset = ReadBElong(buffer,offset);
                        mp.blocktype = ReadBElong(buffer,offset);
                        mp.faceoffset = ReadBElong(buffer,offset);
                        mp.facecount = ReadBElong(buffer,offset);
                        mp.unklong4 = ReadBElong(buffer,offset);
                        mp.unkbyte5 = Readbyte(buffer,offset);
                        mp.boneremapid = Readbyte(buffer,offset);
                        mp.unksh6 = ReadBEshort(buffer,offset);
                        mp.unksh7 = ReadBEshort(buffer,offset);
                        mp.unksh8 = ReadBEshort(buffer,offset);
                        mp.unklong = ReadBElong(buffer,offset);
                        Mparts.parts.push_back(mp);
                    }
///////////////////////// reading unknown chunk between mesh data and vertext offset wtf is this
///     struct MOD_unk2_chunk
///
                    Mparts.chunks.clear(); // check for mem leak later
                   // for (int i=0;i<Mheader.meshcount.toHex().toUInt(&ok,16);i++){
                    while(offset < Mheader.vertexoffset.toHex().toUInt(&ok,16)){
                        MOD_unk2_chunk Mchunk2;
                        Mchunk2.un1 = ReadBElong(buffer,offset);
                        Mchunk2.un2 = ReadBElong(buffer,offset); // on pc dd;da it is "CDCDCDCD" on ps3 it's all 0's
                        Mchunk2.un3 = ReadBElong(buffer,offset); // on pc dd;da it is "CDCDCDCD" on ps3 it's all 0's
                        Mchunk2.un4 = ReadBElong(buffer,offset); // on pc dd;da it is "CDCDCDCD" on ps3 it's all 0's
                        Mchunk2.un5 = ReadBElong(buffer,offset);
                        Mchunk2.un6 = ReadBElong(buffer,offset);
                        Mchunk2.un7 = ReadBElong(buffer,offset); //body begin
                        Mchunk2.un8 = ReadBElong(buffer,offset);
                        Mchunk2.un9 = ReadBElong(buffer,offset);
                        Mchunk2.un10 = ReadBElong(buffer,offset);
                        Mchunk2.un11 = ReadBElong(buffer,offset);
                        Mchunk2.un12 = ReadBElong(buffer,offset);
                        Mchunk2.un13 = ReadBElong(buffer,offset);
                        Mchunk2.un14 = ReadBElong(buffer,offset);
                        Mchunk2.un15 = ReadBElong(buffer,offset);
                        Mchunk2.un16 = ReadBElong(buffer,offset);
                        Mchunk2.un17 = ReadBElong(buffer,offset);
                        Mchunk2.un18 = ReadBElong(buffer,offset);
                        Mchunk2.un19 = ReadBElong(buffer,offset);
                        Mchunk2.un20 = ReadBElong(buffer,offset);
                        Mchunk2.un21 = ReadBElong(buffer,offset);
                        Mchunk2.un22 = ReadBElong(buffer,offset);
                        Mchunk2.un23 = ReadBElong(buffer,offset);
                        Mchunk2.un24 = ReadBElong(buffer,offset);
                        Mchunk2.un25 = ReadBElong(buffer,offset);
                        Mchunk2.un26 = ReadBElong(buffer,offset);
                        Mchunk2.un27 = ReadBElong(buffer,offset);
                        Mchunk2.un28 = ReadBElong(buffer,offset);
                        Mchunk2.un29 = ReadBElong(buffer,offset);
                        Mchunk2.un30 = ReadBElong(buffer,offset);
                        Mchunk2.un31 = ReadBElong(buffer,offset);
                        Mchunk2.un32 = ReadBElong(buffer,offset);
                        Mchunk2.un33 = ReadBElong(buffer,offset);
                        Mchunk2.un34 = ReadBElong(buffer,offset);
                        Mchunk2.un35 = ReadBElong(buffer,offset);
                        Mchunk2.un36 = ReadBElong(buffer,offset);
                        Mparts.chunks.push_back(Mchunk2);
                    }
/////////////////  reading vbo permesh part data
/// clear stuff check for mem leak later

                  for (int i=0;i<Mparts.parts.size();i++){
                    MOD_Mesh_Data md ;
                    for(int j=0;j<Mparts.parts[i].vertexcount.toHex().toUInt(&ok,16);j++){

                        if(blocktype.find(Mparts.parts[i].blocktype) != blocktype.end()){
                            switch(blocktype[Mparts.parts[i].blocktype]){
                              case 2736832534: //unknown
                                md.unksh1.push_back(ReadBEshort(buffer,offset));
                                md.unksh2.push_back(ReadBEshort(buffer,offset));
                                md.unksh3.push_back(ReadBEshort(buffer,offset));
                                md.unksh4.push_back(ReadBEshort(buffer,offset));
                                md.unklong1.push_back(Readlong(buffer,offset));
                                md.unklong2.push_back(Readlong(buffer,offset));
                                md.unklong3.push_back(Readlong(buffer,offset));
                                md.unklong4.push_back(Readlong(buffer,offset));
                                md.unklong5.push_back(Readlong(buffer,offset));
                                break;
                              case 213286933: //unkown
                                md.unksh1.push_back(ReadBEshort(buffer,offset));
                                md.unksh2.push_back(ReadBEshort(buffer,offset));
                                md.unksh3.push_back(ReadBEshort(buffer,offset));
                                md.unksh4.push_back(ReadBEshort(buffer,offset));
                                md.unklong1.push_back(Readlong(buffer,offset));
                                md.unklong2.push_back(Readlong(buffer,offset));
                                md.unklong3.push_back(Readlong(buffer,offset));
                                break;
                              case 349437977:
                              case 349437984: //appears in dd;da weapons?

                                md.verticies.push_back(ReadBEshort(buffer,offset));
                                md.verticies.push_back(ReadBEshort(buffer,offset));
                                md.verticies.push_back(ReadBEshort(buffer,offset));
                                md.weights.push_back(ReadBEshort(buffer,offset));
                                md.normals.push_back(Readbyte(buffer,offset));
                                md.normals.push_back(Readbyte(buffer,offset));
                                md.normals.push_back(Readbyte(buffer,offset));
                                md.unkbyte1.push_back(Readbyte(buffer,offset));
                                md.unklong1.push_back(Readlong(buffer,offset));
                                md.bns.push_back(Readbyte(buffer,offset));
                                md.bns.push_back(Readbyte(buffer,offset));
                                md.bns.push_back(Readbyte(buffer,offset));
                                md.bns.push_back(Readbyte(buffer,offset));
                                md.texturemap.push_back(ReadBEshort(buffer,offset));
                                md.texturemap.push_back(ReadBEshort(buffer,offset));
                                md.weights.push_back(ReadBEshort(buffer,offset));
                                md.weights.push_back(ReadBEshort(buffer,offset));


                                break;
                            case 3141681188:
                            case 309555230:
                            case 3141681181:

                                md.verticies.push_back(ReadBEshort(buffer,offset));
                                md.verticies.push_back(ReadBEshort(buffer,offset));
                                md.verticies.push_back(ReadBEshort(buffer,offset));
                                md.weights.push_back(ReadBEshort(buffer,offset));
                                md.normals.push_back(Readbyte(buffer,offset));
                                md.normals.push_back(Readbyte(buffer,offset));
                                md.normals.push_back(Readbyte(buffer,offset));
                                md.unkbyte1.push_back(Readbyte(buffer,offset));

                                md.weights.push_back(Readbyte(buffer,offset));
                                md.weights.push_back(Readbyte(buffer,offset));
                                md.weights.push_back(Readbyte(buffer,offset));
                                md.weights.push_back(Readbyte(buffer,offset));


                                md.bns.push_back(Readbyte(buffer,offset));
                                md.bns.push_back(Readbyte(buffer,offset));
                                md.bns.push_back(Readbyte(buffer,offset));
                                md.bns.push_back(Readbyte(buffer,offset));
                                md.bns.push_back(Readbyte(buffer,offset));
                                md.bns.push_back(Readbyte(buffer,offset));
                                md.bns.push_back(Readbyte(buffer,offset));
                                md.bns.push_back(Readbyte(buffer,offset));

                                md.texturemap.push_back(ReadBEshort(buffer,offset));
                                md.texturemap.push_back(ReadBEshort(buffer,offset));
                                md.weights.push_back(ReadBEshort(buffer,offset));
                                md.weights.push_back(ReadBEshort(buffer,offset));
                                md.unklong1.push_back(Readlong(buffer,offset));

                             break;

                              }
                        }


                        else{
                            if(unknownblocktypes.find(Mparts.parts[i].blocktype) == unknownblocktypes.end()){
                              unknownblocktypes[Mparts.parts[i].blocktype] = unktypesfound;
                              unktypesfound++;

                            }
                        }


                   }
                    Mparts.parts[i].meshdata.push_back(md);
                }

                  if(Mheader.version.toHex().toUInt(&ok,16) == 212){ // only for dd;da ddon is sensable
                   for (int i=0;i<faces.size();i++){
                       faces[i].clear();
                   }
                   faces.clear();

                   //start reading
                   /* //old faces
                        std::vector<QByteArray> first;
                        first.push_back(ReadBEshort(buffer,offset));
                       QByteArray one = first[0];
                       QByteArray two = ReadBEshort(buffer,offset);
                        first.push_back(two);
                       QByteArray three = QByteArray::fromHex("FFFF");
                       QByteArray four = QByteArray::fromHex("FFFF");
//                       bool skipped = true;
                       int stride =2;
                       int idx =0;
                       faces.push_back(first);
                */

//                       while(offset < Mheader.unkoffset.toHex().toUInt(&ok,16)-2){
//                           three = ReadBEshort(buffer,offset);
//                           if( stride % 2 == 1){
//                             offset+=2;
//                             std::vector<QByteArray> vect;
//                             faces.push_back(vect);
//                             idx++;
//                             skipped= true;
//                             stride = 0;
//                           }
//                           else{
//                               faces[idx].push_back(next);
//                               last = next;
//                               if (stride > 1){
//                               skipped= false;
//                               }
//                               stride++;

//                           }
//                       }
                      /* //old faces
                       while(offset < Mheader.unkoffset.toHex().toUInt(&ok,16)-2){


                           three = ReadBEshort(buffer,offset);
                           if( two == three ){ // degenerate triangle detected SKIPPING!
                             //offset+=2; // don't push 3 and 4 and 5 because fuck it
                             four = ReadBEshort(buffer,offset);
                             one = ReadBEshort(buffer,offset);
                             two = ReadBEshort(buffer,offset);
                             std::vector<QByteArray> vect;
                             faces.push_back(vect);
                             idx++;
                             if ( one == two ){  // another type of degenerate entry
                                 faces[idx].push_back(two);
                             }
                             else if (three != four){ // yet another
                                 faces[idx].push_back(one);
                                 faces[idx].push_back(two);
                             }
                             else{

                                 faces[idx].push_back(four);
                                 faces[idx].push_back(one);
                                 faces[idx].push_back(two);
                             }
//                             skipped= true;
//                             stride = 0;
                           }
                           else{
                               faces[idx].push_back(three);
                               two = three;

                           }

                       }
                   */ // old faces


                   /////////////////  reading faces permesh part data
                   /// oh god what in the FUCK is this
                   /// clear stuff if exists
                                    for (int i=0;i<Mparts.parts.size();i++){
                                        if (Mparts.parts[i].meshdata[0].faces.size() >0 ){
                                          for (int j=0;j<Mparts.parts[i].meshdata[0].faces.size();j++){
                                              // not a tripple attray? check for mem leak later
               //                              for(int k=0;k<Mparts.parts[i].meshdata.faces[j].size();k++){
               //                                  Mparts.parts[i].meshdata.faces[j][k].clear();
               //                              }
                                             Mparts.parts[i].meshdata[0].faces[j].clear();
                                          }
                                          Mparts.parts[i].meshdata[0].faces.clear();
                                        }
                                    }
                                    // start reading
                                    for (int i=0;i<Mparts.parts.size();i++){

                                             std::vector<QByteArray> first;
                                             first.push_back(ReadBEshort(buffer,offset));
                                            QByteArray last = first[0];
                                            QByteArray sentinal = QByteArray::fromHex("FFFF");
                                            int idx =0;
                                            Mparts.parts[i].meshdata[0].faces.push_back(first);
                                           // while(offset  < Mheader.unkoffset.toHex().toUInt(&ok,16)-2){
                                            for(int j=1;j<Mparts.parts[i].facecount.toHex().toUInt(&ok,16);j++){
                                                last = ReadBEshort(buffer,offset);
                                                if( last == sentinal){
                                                  std::vector<QByteArray> vect;
                                                  idx++;
                                                  Mparts.parts[i].meshdata[0].faces.push_back(vect);
                                                }
                                                else{
                                                    Mparts.parts[i].meshdata[0].faces[idx].push_back(last);
                                                }
                                            }
                                    }


                  }



 spinBox->setText(QString::number(Mheader.version.toHex().toUInt(&ok,16))); // version

 spinBoxMax->setText(QString::number(Mheader.version2.toHex().toInt(&ok,16)));  //version 2

 spinboxIdle->setText(QString::number(Mheader.bonecount.toHex().toUInt(&ok,16)));  //bone count

meshcount->setText(QString::number(Mheader.meshcount.toHex().toInt(&ok,16)));
materialcount->setText(QString::number(Mheader.materialcount.toHex().toInt(&ok,16)));
vertexcount->setText(QString::number(Mheader.vertexcount.toHex().toInt(&ok,16)));
 facecount->setText(QString::number(Mheader.facecount.toHex().toInt(&ok,16)));
 vertexids->setText(QString::number(Mheader.vertexids.toHex().toInt(&ok,16)));
 vertexbuffersize->setText(QString::number(Mheader.vertexbuffersize.toHex().toInt(&ok,16)));
 scondbuffersize->setText(QString::number(Mheader.scondbuffersize.toHex().toInt(&ok,16)));

 groupcount->setText(QString::number(Mheader.groupcount.toHex().toInt(&ok,16)));
 bonesoffset->setText(QString::number(Mheader.bonesoffset.toHex().toInt(&ok,16)));
 groupoffset->setText(QString::number(Mheader.groupoffset.toHex().toInt(&ok,16)));
 textureoffset->setText(QString::number(Mheader.textureoffset.toHex().toInt(&ok,16)));
 meshoffset->setText(QString::number(Mheader.meshoffset.toHex().toInt(&ok,16)));
 vertexoffset->setText(QString::number(Mheader.vertexoffset.toHex().toInt(&ok,16)));
 facesoffset->setText(QString::number(Mheader.facesoffset.toHex().toInt(&ok,16)));
 unkoffset->setText(QString::number(Mheader.unkoffset.toHex().toInt(&ok,16)));

 switch( Mheader.version.toHex().toUInt(&ok,16) ){

    case 212:
      rdoPooled->click();
     break;
    case 210:
     rdoSingle->click();
     break;

 }

if(unktypesfound>0){
    QString msg = "Unknown VBO Format(s): \n";
    for (auto const& x : unknownblocktypes)
    {
        msg.append(x.first.toHex());
        msg.append("\n");
    }
    msg.append("\n!!!DATA SKIPPED!!!! \n Please report this along with the file you used.");
                                  QMessageBox msgBox;
                                  msgBox.setText(msg);
                                  msgBox.exec();
}

// qDebug() << "version: " << version << " version2: " << version2 << " bonecount: " << bonecount ;
 //qDebug() << "version: " << Mheader.version.toHex() << " version2: " << Mheader.version2.toHex() << " bonecount: " << Mheader.bonecount.toHex();
//we done?
emit this->newDAPCMesh(Mparts);

}
else if( Mheader.id == QByteArray::fromHex("00444f4d")){ //ps3?

////////////////////////// reading header

    Mheader.version2 = Readbyte(buffer,offset);
    Mheader.version = Readbyte(buffer,offset);//unsigned

    Mheader.bonecount = Readshort(buffer,offset);
    Mheader.meshcount = Readshort(buffer,offset);
    Mheader.materialcount = Readshort(buffer,offset);
    Mheader.vertexcount = Readlong(buffer,offset);
    Mheader.facecount = Readlong(buffer,offset);
    Mheader.vertexids = Readlong(buffer,offset);
    Mheader.vertexbuffersize = Readlong(buffer,offset);
    Mheader.scondbuffersize = Readlong(buffer,offset);
  // if(Mheader.version.toHex().toUInt(&ok,16) < 190) Mheader.texturecount = Readlong(buffer,32); // (not for dd so don't care)
    Mheader.groupcount = Readlong(buffer,offset);
    Mheader.bonesoffset = Readlong(buffer,offset);
    Mheader.groupoffset = Readlong(buffer,offset);
    Mheader.textureoffset = Readlong(buffer,offset);
    Mheader.meshoffset = Readlong(buffer,offset);
    Mheader.vertexoffset = Readlong(buffer,offset);
    Mheader.facesoffset = Readlong(buffer,offset);
    Mheader.unkoffset = Readlong(buffer,offset);
    ////////////////////////// reading unknown chucnk 1

        Mhunk1.un1 = Readlong(buffer,offset);
        Mhunk1.un2 = Readlong(buffer,offset);
        Mhunk1.un3 = Readlong(buffer,offset);
        Mhunk1.un4 = Readlong(buffer,offset);
        Mhunk1.un5 = Readlong(buffer,offset);
        Mhunk1.un6 = Readlong(buffer,offset);
        Mhunk1.un7 = Readlong(buffer,offset);
        Mhunk1.un8 = Readlong(buffer,offset);
        Mhunk1.un9 = Readlong(buffer,offset);
        Mhunk1.un10 = Readlong(buffer,offset);
        Mhunk1.un11 = Readlong(buffer,offset);
        Mhunk1.un12 = Readlong(buffer,offset);
        Mhunk1.un13 = Readlong(buffer,offset);
        Mhunk1.un14 = Readlong(buffer,offset);
        Mhunk1.un15 = Readlong(buffer,offset);
        Mhunk1.un16 = Readlong(buffer,offset);
        Mhunk1.un17 = Readlong(buffer,offset);

//////////////////////  reading bone data

        Mbones.boneinfo.clear(); // check for memleak later
        for (int i=0;i<Mheader.bonecount.toHex().toUInt(&ok,16);i++){
            MOD_Bone_info  binf;
          //if version == 237 -> boneinfo2
          if (Mheader.version.toHex().toUInt(&ok,16) == 237){
              binf.id = Readshort(buffer,offset);
              binf.parentid = Readbyte(buffer,offset);
              binf.child = Readbyte(buffer,offset);
          }
          else {
              binf.id = Readbyte(buffer,offset);
              binf.parentid = Readbyte(buffer,offset);
              binf.child = Readbyte(buffer,offset);
              binf.unk = Readbyte(buffer,offset);
          }
          // read 5* 4byte longs of unknown data
          binf.unk1 = Readlong(buffer,offset);
          binf.unk2 = Readlong(buffer,offset);
          binf.unk3 = Readlong(buffer,offset);
          binf.unk4 = Readlong(buffer,offset);
          binf.unk5 = Readlong(buffer,offset);
          Mbones.boneinfo.push_back(binf);
        }
Mbones.lmatrices.clear();

        for (int i=0;i<Mbones.boneinfo.size();i++){
            ReadMatrix44(buffer,offset,Mbones.lmatrices);
        }
Mbones.amatrices.clear();

        for (int i=0;i<Mbones.boneinfo.size();i++){
            ReadMatrix44(buffer,offset,Mbones.amatrices);
        }

Mbones.remaptablesize = (Mheader.bonecount.toHex().toUInt(&ok,16) == 137)?512:256;
Mbones.remaptable.clear();

        for (int i =0; i<Mbones.remaptablesize;i++){
            Mbones.remaptable.push_back(Readbyte(buffer,offset));
        }

//////////////////////  reading group data

Mgroups.groupinfo.clear();
        for (int i=0;i<Mheader.groupcount.toHex().toUInt(&ok,16);i++){
               MOD_Group_info  ginf;
              ginf.h0 = Readlong(buffer,offset);
              ginf.h1 = Readlong(buffer,offset);
              ginf.h2 = Readlong(buffer,offset);
              ginf.h3 = Readlong(buffer,offset);
              ginf.b0 = Readlong(buffer,offset);
              ginf.b1 = Readlong(buffer,offset);
              ginf.b2 = Readlong(buffer,offset);
              ginf.b3 = Readlong(buffer,offset);
             Mgroups.groupinfo.push_back(ginf);
        }

//////////////////////  reading material data

                Mmats.name.clear();
                for (int i=0;i<Mheader.materialcount.toHex().toUInt(&ok,16);i++){

                     Mmats.name.push_back(ReadMaterial(buffer,offset));
                }
/////////////////////  reading mesh data
///  for i=0; i<mheader.meshcount -> get meshparts
                  Mparts.parts.clear(); // check for mem leak later

                    for (int i=0;i<Mheader.meshcount.toHex().toUInt(&ok,16);i++){
                        MOD_Mesh_Part2 mp ;
                        mp.unksh1 = Readshort(buffer,offset);
                        mp.vertexcount = Readshort(buffer,offset);
                        mp.id = Readbyte(buffer,offset);
                        mp.material = Readshort(buffer,offset);
                        mp.LOD = Readbyte(buffer,offset);
                        mp.unkbyte20 = Readbyte(buffer,offset);
                        mp.unkbyte21 = Readbyte(buffer,offset);
                        mp.blocksize = Readbyte(buffer,offset);
                        mp.unkbtye3 = Readbyte(buffer,offset);
                        mp.vertexsub = Readlong(buffer,offset);
                        mp.vertexoffset = Readlong(buffer,offset);
                        mp.blocktype = Readlong(buffer,offset);
                        mp.faceoffset = Readlong(buffer,offset);
                        mp.facecount = Readlong(buffer,offset);
                        mp.unklong4 = Readlong(buffer,offset);
                        mp.unkbyte5 = Readbyte(buffer,offset);
                        mp.boneremapid = Readbyte(buffer,offset);
                        mp.unksh6 = Readshort(buffer,offset);
                        mp.unksh7 = Readshort(buffer,offset);
                        mp.unksh8 = Readshort(buffer,offset);
                        mp.unklong = Readlong(buffer,offset);
                        offset+=8;//skip read in 00000000 x2 longs spacers
                        Mparts.parts.push_back(mp);
                    }
///////////////////////// reading unknown chunk between mesh data and vertext offset what arrrrre you
///     struct MOD_unk2_chunk
///
                Mparts.chunks.clear(); // check for mem leak later
                //for (int i=0;i<Mheader.meshcount.toHex().toUInt(&ok,16);i++){
                while(offset < Mheader.vertexoffset.toHex().toUInt(&ok,16)){
                    MOD_unk2_chunk Mchunk2;
                        Mchunk2.un1 = Readlong(buffer,offset);
                        Mchunk2.un2 = Readlong(buffer,offset); // on pc dd;da it is "CDCDCDCD" on ps3 it's all 0's
                        Mchunk2.un3 = Readlong(buffer,offset); // on pc dd;da it is "CDCDCDCD" on ps3 it's all 0's
                        Mchunk2.un4 = Readlong(buffer,offset); // on pc dd;da it is "CDCDCDCD" on ps3 it's all 0's
                        Mchunk2.un5 = Readlong(buffer,offset);
                        Mchunk2.un6 = Readlong(buffer,offset);
                        Mchunk2.un7 = Readlong(buffer,offset); //body begin
                        Mchunk2.un8 = Readlong(buffer,offset);
                        Mchunk2.un9 = Readlong(buffer,offset);
                        Mchunk2.un10 = Readlong(buffer,offset);
                        Mchunk2.un11 = Readlong(buffer,offset);
                        Mchunk2.un12 = Readlong(buffer,offset);
                        Mchunk2.un13 = Readlong(buffer,offset);
                        Mchunk2.un14 = Readlong(buffer,offset);
                        Mchunk2.un15 = Readlong(buffer,offset);
                        Mchunk2.un16 = Readlong(buffer,offset);
                        Mchunk2.un17 = Readlong(buffer,offset);
                        Mchunk2.un18 = Readlong(buffer,offset);
                        Mchunk2.un19 = Readlong(buffer,offset);
                        Mchunk2.un20 = Readlong(buffer,offset);
                        Mchunk2.un21 = Readlong(buffer,offset);
                        Mchunk2.un22 = Readlong(buffer,offset);
                        Mchunk2.un23 = Readlong(buffer,offset);
                        Mchunk2.un24 = Readlong(buffer,offset);
                        Mchunk2.un25 = Readlong(buffer,offset);
                        Mchunk2.un26 = Readlong(buffer,offset);
                        Mchunk2.un27 = Readlong(buffer,offset);
                        Mchunk2.un28 = Readlong(buffer,offset);
                        Mchunk2.un29 = Readlong(buffer,offset);
                        Mchunk2.un30 = Readlong(buffer,offset);
                        Mchunk2.un31 = Readlong(buffer,offset);
                        Mchunk2.un32 = Readlong(buffer,offset);
                        Mchunk2.un33 = Readlong(buffer,offset);
                        Mchunk2.un34 = Readlong(buffer,offset);
                        Mchunk2.un35 = Readlong(buffer,offset);
                        Mchunk2.un36 = Readlong(buffer,offset);
                        Mparts.chunks.push_back(Mchunk2);
                    }

/////////////////  reading vbo permesh part data
                for (int i=0;i<Mparts.parts.size();i++){
                    MOD_Mesh_Data md ;
                    for(int j=0;j<Mparts.parts[i].vertexcount.toHex().toUInt(&ok,16);j++){

                        if(blocktype.find(Mparts.parts[i].blocktype) != blocktype.end()){
                            switch(blocktype[Mparts.parts[i].blocktype]){
                              case 2736832534: //unknown
                                md.unksh1.push_back(Readshort(buffer,offset));
                                md.unksh2.push_back(Readshort(buffer,offset));
                                md.unksh3.push_back(Readshort(buffer,offset));
                                md.unksh4.push_back(Readshort(buffer,offset));
                                md.unklong1.push_back(Readlong(buffer,offset));
                                md.unklong2.push_back(Readlong(buffer,offset));
                                md.unklong3.push_back(Readlong(buffer,offset));
                                md.unklong4.push_back(Readlong(buffer,offset));
                                md.unklong5.push_back(Readlong(buffer,offset));
                                break;
                              case 213286933: //unkown
                                md.unksh1.push_back(Readshort(buffer,offset));
                                md.unksh2.push_back(Readshort(buffer,offset));
                                md.unksh3.push_back(Readshort(buffer,offset));
                                md.unksh4.push_back(Readshort(buffer,offset));
                                md.unklong1.push_back(Readlong(buffer,offset));
                                md.unklong2.push_back(Readlong(buffer,offset));
                                md.unklong3.push_back(Readlong(buffer,offset));
                                break;
                              case 349437977:
                              case 349437984: //appears in dd;da weapons?

                                md.verticies.push_back(Readshort(buffer,offset));
                                md.verticies.push_back(Readshort(buffer,offset));
                                md.verticies.push_back(Readshort(buffer,offset));
                                md.weights.push_back(Readshort(buffer,offset));
                                md.normals.push_back(Readbyte(buffer,offset));
                                md.normals.push_back(Readbyte(buffer,offset));
                                md.normals.push_back(Readbyte(buffer,offset));
                                md.unkbyte1.push_back(Readbyte(buffer,offset));
                                md.unklong1.push_back(Readlong(buffer,offset));
                                md.bns.push_back(Readbyte(buffer,offset));
                                md.bns.push_back(Readbyte(buffer,offset));
                                md.bns.push_back(Readbyte(buffer,offset));
                                md.bns.push_back(Readbyte(buffer,offset));
                                md.texturemap.push_back(Readshort(buffer,offset));
                                md.texturemap.push_back(Readshort(buffer,offset));
                                md.weights.push_back(Readshort(buffer,offset));
                                md.weights.push_back(Readshort(buffer,offset));


                                break;
                            case 3141681188:
                            case 309555230:
                            case 3141681181:

                                md.verticies.push_back(Readshort(buffer,offset));
                                md.verticies.push_back(Readshort(buffer,offset));
                                md.verticies.push_back(Readshort(buffer,offset));
                                md.weights.push_back(Readshort(buffer,offset));
                                md.normals.push_back(Readbyte(buffer,offset));
                                md.normals.push_back(Readbyte(buffer,offset));
                                md.normals.push_back(Readbyte(buffer,offset));
                                md.unkbyte1.push_back(Readbyte(buffer,offset));

                                md.weights.push_back(Readbyte(buffer,offset));
                                md.weights.push_back(Readbyte(buffer,offset));
                                md.weights.push_back(Readbyte(buffer,offset));
                                md.weights.push_back(Readbyte(buffer,offset));


                                md.bns.push_back(Readbyte(buffer,offset));
                                md.bns.push_back(Readbyte(buffer,offset));
                                md.bns.push_back(Readbyte(buffer,offset));
                                md.bns.push_back(Readbyte(buffer,offset));
                                md.bns.push_back(Readbyte(buffer,offset));
                                md.bns.push_back(Readbyte(buffer,offset));
                                md.bns.push_back(Readbyte(buffer,offset));
                                md.bns.push_back(Readbyte(buffer,offset));

                                md.texturemap.push_back(Readshort(buffer,offset));
                                md.texturemap.push_back(Readshort(buffer,offset));
                                md.weights.push_back(Readshort(buffer,offset));
                                md.weights.push_back(Readshort(buffer,offset));
                                md.unklong1.push_back(Readlong(buffer,offset));

                             break;


                              }
                        }


                        else{
                            if(unknownblocktypes.find(Mparts.parts[i].blocktype) == unknownblocktypes.end()){
                              unknownblocktypes[Mparts.parts[i].blocktype] = unktypesfound;
                              unktypesfound++;
//                              QMessageBox msgBox;
//                              msgBox.setText("Unknown VBO Format: " +Mparts.parts[i].blocktype.toHex() + "\n!!!DATA SKIPPED!!!! \n Please report this along with the file you used." );
//                              msgBox.exec();
                            }
                        }


                   }
                    Mparts.parts[i].meshdata.push_back(md);
                }


if(Mheader.version.toHex().toUInt(&ok,16) == 212){ // only for dd;da ddon is sensable

    /* old method
 for (int i=0;i<faces.size();i++){
     faces[i].clear();
 }
 faces.clear();

 //start reading
      std::vector<QByteArray> first;
      first.push_back(Readshort(buffer,offset));
     QByteArray last = first[0];
     QByteArray sentinal = QByteArray::fromHex("FFFF");
     int idx =0;
     faces.push_back(first);
     while(offset  < Mheader.unkoffset.toHex().toUInt(&ok,16)-2){
         last = Readshort(buffer,offset);
         if( last == sentinal){
           std::vector<QByteArray> vect;
           idx++;
           faces.push_back(vect);
         }
         else{
             faces[idx].push_back(last);
         }
     }
     */

    /////////////////  reading faces permesh part data
    /// oh god what in the FUCK is this
    /// clear stuff if exists
                     for (int i=0;i<Mparts.parts.size();i++){
                         if (Mparts.parts[i].meshdata[0].faces.size() >0 ){
                           for (int j=0;j<Mparts.parts[i].meshdata[0].faces.size();j++){
                               // not a tripple attray? check for mem leak later
//                              for(int k=0;k<Mparts.parts[i].meshdata.faces[j].size();k++){
//                                  Mparts.parts[i].meshdata.faces[j][k].clear();
//                              }
                              Mparts.parts[i].meshdata[0].faces[j].clear();
                           }
                           Mparts.parts[i].meshdata[0].faces.clear();
                         }
                     }
                     // start reading
                     for (int i=0;i<Mparts.parts.size();i++){

                              std::vector<QByteArray> first;
                              first.push_back(Readshort(buffer,offset));
                             QByteArray last = first[0];
                             QByteArray sentinal = QByteArray::fromHex("FFFF");
                             int idx =0;
                             Mparts.parts[i].meshdata[0].faces.push_back(first);
                            // while(offset  < Mheader.unkoffset.toHex().toUInt(&ok,16)-2){
                             for(int j=1;j<Mparts.parts[i].facecount.toHex().toUInt(&ok,16);j++){
                                 last = Readshort(buffer,offset);
                                 if( last == sentinal){
                                   std::vector<QByteArray> vect;
                                   idx++;
                                   Mparts.parts[i].meshdata[0].faces.push_back(vect);
                                 }
                                 else{
                                     Mparts.parts[i].meshdata[0].faces[idx].push_back(last);
                                 }
                             }
                     }

}
     spinBox->setText(QString::number(Mheader.version.toHex().toUInt(&ok,16))); // version

     spinBoxMax->setText(QString::number(Mheader.version2.toHex().toInt(&ok,16)));  //version 2

     spinboxIdle->setText(QString::number(Mheader.bonecount.toHex().toUInt(&ok,16)));  //bone count
     meshcount->setText(QString::number(Mheader.meshcount.toHex().toInt(&ok,16)));
     materialcount->setText(QString::number(Mheader.materialcount.toHex().toInt(&ok,16)));
     vertexcount->setText(QString::number(Mheader.vertexcount.toHex().toInt(&ok,16)));
      facecount->setText(QString::number(Mheader.facecount.toHex().toInt(&ok,16)));
      vertexids->setText(QString::number(Mheader.vertexids.toHex().toInt(&ok,16)));
      vertexbuffersize->setText(QString::number(Mheader.vertexbuffersize.toHex().toInt(&ok,16)));
      scondbuffersize->setText(QString::number(Mheader.scondbuffersize.toHex().toInt(&ok,16)));

      groupcount->setText(QString::number(Mheader.groupcount.toHex().toInt(&ok,16)));
      bonesoffset->setText(QString::number(Mheader.bonesoffset.toHex().toInt(&ok,16)));
      groupoffset->setText(QString::number(Mheader.groupoffset.toHex().toInt(&ok,16)));
      textureoffset->setText(QString::number(Mheader.textureoffset.toHex().toInt(&ok,16)));
      meshoffset->setText(QString::number(Mheader.meshoffset.toHex().toInt(&ok,16)));
      vertexoffset->setText(QString::number(Mheader.vertexoffset.toHex().toInt(&ok,16)));
      facesoffset->setText(QString::number(Mheader.facesoffset.toHex().toInt(&ok,16)));
      unkoffset->setText(QString::number(Mheader.unkoffset.toHex().toInt(&ok,16)));
switch( Mheader.version.toHex().toUInt(&ok,16) ){

   case 212:
     rdoTheaded->click();
    break;
   case 210:
    rdoSingle->click();
    break;

}

if(unktypesfound>0){
    QString msg = "Unknown VBO Format(s): \n";
    for (auto const& x : unknownblocktypes)
    {
        msg.append(x.first.toHex());
        msg.append("\n");
    }
    msg.append("\n!!!DATA SKIPPED!!!! \n Please report this along with the file you used.");
                                  QMessageBox msgBox;
                                  msgBox.setText(msg);
                                  msgBox.exec();
}

 //qDebug() << "version: " << version << " version2: " << version2 << " bonecount: " << bonecount ;
 //qDebug() << "version: " << Mheader.version.toHex() << " version2: " << Mheader.version2.toHex() << " bonecount: " << Mheader.bonecount.toHex();
// we done? emit signal

emit this->newMesh(Mparts,Mbones.lmatrices,Mbones.amatrices);
}
else {

    QMessageBox msgBox;
    msgBox.setText("Unknown Mod File Header: "+Mheader.id.toHex());
    msgBox.exec();
}

//qDebug() << Mheader.id[0] << Mheader.id[1] << Mheader.id[2] << Mheader.id[3] ;

/*QString sValue = "FF";
bool bStatus = false;
uint nHex = Mheader.bonecount.toHex().toUInt(&bStatus,16);
qDebug() << nHex;
//QString test = QString::number(id,16);
qDebug() << (int) Mheader.version.at(0) + 0xFF;
*/

//file is done
fclose(Filep);
free(buffer);
}

