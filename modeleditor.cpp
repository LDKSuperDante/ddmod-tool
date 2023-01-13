#include "modeleditor.h"

ModelEditor::ModelEditor(QMainWindow *parent) : QMainWindow(parent)
{
    if (this->objectName().isEmpty())
        this->setObjectName(QStringLiteral("Model Editor"));

    this->resize(700, 280);

    //setup menu
    QMenu *fileMenu = menuBar()->addMenu(tr("&File"));
    QToolBar *fileToolBar = addToolBar(tr("File"));

    const QIcon newIcon(":/resources/Resource/icon_lot.png");
    QAction *newOpenMod = new QAction(newIcon, tr("&Open"), this);
    newOpenMod->setShortcuts(QKeySequence::Open);
    newOpenMod->setStatusTip(tr("Open a .mod File.."));
    // connect(newLetterAct, &QAction::triggered, this, &MainWindow::newLetter);

    connect(newOpenMod,SIGNAL(triggered(bool)),this,SLOT(on_Open_clicked()));

    fileMenu->addAction(newOpenMod);
    fileToolBar->addAction(newOpenMod);

    const QIcon saveIcon = QIcon(":/resources/Resource/icon_stone.png");
    QAction *saveAct = new QAction(saveIcon, tr("&Save..."), this);
    saveAct->setShortcuts(QKeySequence::Save);
    saveAct->setStatusTip(tr("Save the current Model"));
    // connect(saveAct, &QAction::triggered, this, &MainWindow::save);
    connect(saveAct,SIGNAL(triggered(bool)),this,SLOT(on_Save_clicked()));
    fileMenu->addAction(saveAct);
    fileToolBar->addAction(saveAct);

    fileMenu->addSeparator();

    QAction *quitAct = fileMenu->addAction(tr("&Quit"), this, SLOT(close()));
    quitAct->setShortcuts(QKeySequence::Quit);
    quitAct->setStatusTip(tr("Quit the Model Editor"));
    /*
        QMenu *editMenu = menuBar()->addMenu(tr("&Edit"));
        QToolBar *editToolBar = addToolBar(tr("Edit"));
        const QIcon undoIcon = QIcon::fromTheme("edit-undo", QIcon(":/images/undo.png"));
        QAction *undoAct = new QAction(undoIcon, tr("&Undo"), this);
        undoAct->setShortcuts(QKeySequence::Undo);
        undoAct->setStatusTip(tr("Undo the last editing action"));
        connect(undoAct, &QAction::triggered, this, &MainWindow::undo);
        editMenu->addAction(undoAct);
        editToolBar->addAction(undoAct);
    */
    viewMenu = menuBar()->addMenu(tr("&View"));

    QMenu *renderMenu = menuBar()->addMenu(tr("&Render"));

    menuBar()->addSeparator();

    QMenu *helpMenu = menuBar()->addMenu(tr("&Help"));

    QAction *aboutAct = helpMenu->addAction(tr("&About"), this, SLOT(about()));
    aboutAct->setStatusTip(tr("what do you want? go away"));

    //setup menu

    outerLayout = new QVBoxLayout;

    insideboxLayout = new QVBoxLayout;

    groupBox = new QGroupBox(this);

    groupBox->setLayout(insideboxLayout);

    groupBox->setObjectName(QStringLiteral("groupBox"));
    // groupBox->setGeometry(QRect(10, 20, 385, 201));
    // layoutWidget = new QWidget(groupBox);
    // layoutWidget->setObjectName(QStringLiteral("layoutWidget"));
    // layoutWidget->setGeometry(QRect(10, 110, 397, 92));
    verticalLayout = new QHBoxLayout;
    // verticalLayout->setSpacing(6);
    // verticalLayout->setContentsMargins(11, 11, 11, 11);
    // verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
    // verticalLayout->setContentsMargins(0, 0, 0, 0);

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

    spinBox = new QLineEdit(groupBox);
    spinBox->setObjectName(QStringLiteral("spinBox"));
    // spinBox->setGeometry(QRect(58, 78, 70, 23));
    // spinBox->setMaximum(64000);
    // spinBox->setValue(52100);
    label = new QLabel(groupBox);
    label->setObjectName(QStringLiteral("label"));
    // label->setGeometry(QRect(20, 80, 29, 16));
    label_3 = new QLabel(groupBox);
    label_3->setObjectName(QStringLiteral("label_3"));
    //label_3->setGeometry(QRect(20, 40, 59, 14));
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
    // spinboxIdle->setValue(30000);
    label_4 = new QLabel(groupBox);
    label_4->setObjectName(QStringLiteral("label_4"));
    // label_4->setGeometry(QRect(240, 80, 31, 16));
    // layoutWidget1 = new QWidget(this);
    // layoutWidget1->setObjectName(QStringLiteral("layoutWidget1"));
    // layoutWidget1->setGeometry(QRect(180, 240, 239, 38));
    horizontalLayout_2 = new QHBoxLayout;
    // horizontalLayout_2->setSpacing(6);
    // horizontalLayout_2->setContentsMargins(11, 11, 11, 11);
    horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
    // horizontalLayout_2->setContentsMargins(0, 0, 0, 0);
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

    secondbuffersize = new QLineEdit(groupBox);
    label_secondbuffersize = new QLabel(groupBox);
    groupcount = new QLineEdit(groupBox);
    label_groupcount = new QLabel(groupBox);
    bonesoffset = new QLineEdit(groupBox);
    label_bonesoffset = new QLabel(groupBox);

    horizontalLayout_5 = new QHBoxLayout;
    horizontalLayout_5->addWidget(label_secondbuffersize);
    horizontalLayout_5->addWidget(secondbuffersize);
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
    spinBox->setToolTip("Mt Framework Version? ddon:210 dd;da:212");

    horizontalLayout_1->addWidget(label_4);
    horizontalLayout_1->addWidget(spinboxIdle);
    horizontalLayout_1->addWidget(label_meshcount);
    horizontalLayout_1->addWidget(meshcount);

// new lazy stuff

    label_bounding_boxmin = new QLabel(groupBox);
    bounding_boxminx = new QLineEdit(groupBox);
    bounding_boxminx->setToolTip("Bounding Box Min X");
    bounding_boxminy = new QLineEdit(groupBox);
    bounding_boxminy->setToolTip("Bounding Box Min Y");
    bounding_boxminz = new QLineEdit(groupBox);
    bounding_boxminz->setToolTip("Bounding Box Min Z");
    bounding_boxminw = new QLineEdit(groupBox);

    boundingboxminhLayout = new QHBoxLayout;
    boundingboxminhLayout->addWidget(label_bounding_boxmin);
    boundingboxminhLayout->addWidget(bounding_boxminx);
    boundingboxminhLayout->addWidget(bounding_boxminy);
    boundingboxminhLayout->addWidget(bounding_boxminz);
    boundingboxminhLayout->addWidget(bounding_boxminw);

    label_bounding_boxmax = new QLabel(groupBox);
    bounding_boxmaxx = new QLineEdit(groupBox);
    bounding_boxmaxx->setToolTip("Bounding Box Max X");
    bounding_boxmaxy = new QLineEdit(groupBox);
    bounding_boxmaxy->setToolTip("Bounding Box Max Y");
    bounding_boxmaxz = new QLineEdit(groupBox);
    bounding_boxmaxz->setToolTip("Bounding Box Max Z");
    bounding_boxmaxw = new QLineEdit(groupBox);

    boundingboxmaxhLayout = new QHBoxLayout;
    boundingboxmaxhLayout->addWidget(label_bounding_boxmax);
    boundingboxmaxhLayout->addWidget(bounding_boxmaxx);
    boundingboxmaxhLayout->addWidget(bounding_boxmaxy);
    boundingboxmaxhLayout->addWidget(bounding_boxmaxz);
    boundingboxmaxhLayout->addWidget(bounding_boxmaxw);

    label_bounding_sphere = new QLabel(groupBox);
    bounding_spherex = new QLineEdit(groupBox);
    bounding_spherex->setToolTip("Center X");
    bounding_spherey = new QLineEdit(groupBox);
    bounding_spherey->setToolTip("Center Y");
    bounding_spherez = new QLineEdit(groupBox);
    bounding_spherez->setToolTip("Center Z");
    bounding_spherew = new QLineEdit(groupBox);
    bounding_spherew->setToolTip("Radius");

    boundingspherehLayout = new QHBoxLayout;
    boundingspherehLayout->addWidget(label_bounding_sphere);
    boundingspherehLayout->addWidget(bounding_spherex);
    boundingspherehLayout->addWidget(bounding_spherey);
    boundingspherehLayout->addWidget(bounding_spherez);
    boundingspherehLayout->addWidget(bounding_spherew);

    QHBoxLayout* unkchunk1hLayout = new QHBoxLayout;

    label_h_unkn02 = new QLabel(groupBox);
    h_unkn02 = new QLineEdit(groupBox);
    h_unkn02->setToolTip("1000, relates to an id system.");
    label_h_unkn03 = new QLabel(groupBox);
    h_unkn03 = new QLineEdit(groupBox);
    h_unkn03->setToolTip("3000 unkown.");
    label_h_unkn04 = new QLabel(groupBox);
    h_unkn04 = new QLineEdit(groupBox);
    h_unkn04->setToolTip("layering info, usually 1");
    label_h_unkn05 = new QLabel(groupBox);
    h_unkn05 = new QLineEdit(groupBox);

    label_h_unkn06 = new QLabel(groupBox);
    h_unkn06 = new QLineEdit(groupBox);

    unkchunk1hLayout->addWidget(label_h_unkn02);
    unkchunk1hLayout->addWidget(h_unkn02);
    unkchunk1hLayout->addWidget(label_h_unkn03);
    unkchunk1hLayout->addWidget(h_unkn03);
    unkchunk1hLayout->addWidget(label_h_unkn04);
    unkchunk1hLayout->addWidget(h_unkn04);

    QHBoxLayout* unkchunk2hLayout = new QHBoxLayout;
    unkchunk2hLayout->addWidget(label_h_unkn05);
    unkchunk2hLayout->addWidget(h_unkn05);
    unkchunk2hLayout->addWidget(label_h_unkn06);
    unkchunk2hLayout->addWidget(h_unkn06);

//new lazy stuff
    insideboxLayout->addLayout(horizontalLayout_0);
    insideboxLayout->addLayout(horizontalLayout_1);
    insideboxLayout->addLayout(horizontalLayout_3);
    insideboxLayout->addLayout(horizontalLayout_4);
    insideboxLayout->addLayout(horizontalLayout_5);
    insideboxLayout->addLayout(horizontalLayout_6);
    insideboxLayout->addLayout(horizontalLayout_7);

    insideboxLayout->addLayout(boundingspherehLayout);
    insideboxLayout->addLayout(boundingboxminhLayout);
    insideboxLayout->addLayout(boundingboxmaxhLayout);
    insideboxLayout->addLayout(unkchunk1hLayout);
    insideboxLayout->addLayout(unkchunk2hLayout);

    insideboxLayout->addLayout(verticalLayout);

    outerLayout->addWidget(groupBox);
    outerLayout->addLayout(horizontalLayout_2);

    // QVBoxLayout *textures = new QVBoxLayout(groupBox);
    difflabel = new QLabel;
    speclabel = new QLabel;
    normlabel = new QLabel;
    litelabel = new QLabel;

    diffscroll = new QScrollArea;
    specscroll = new QScrollArea;
    normscroll = new QScrollArea;
    litescroll = new QScrollArea;

    diffscroll->setWidgetResizable(true);
    specscroll->setWidgetResizable(true);
    normscroll->setWidgetResizable(true);
    litescroll->setWidgetResizable(true);

    diffscroll->setWidget(difflabel);
    specscroll->setWidget(speclabel);
    normscroll->setWidget(normlabel);
    litescroll->setWidget(litelabel);

    // textures->addWidget(difflabel);
    // textures->addWidget(speclabel);
    // textures->addWidget(normlabel);
    // textures->addWidget(litelabel);

    // outerLayout->addLayout(textures);

    this->setWindowTitle(QApplication::translate("ModelEditor", "Model Editor", 0));
    // groupBox->setTitle(QApplication::translate("ModelEditor", "Headers", 0));
    rdoSingle->setText(QApplication::translate("ModelEditor", "DDON", 0));
    rdoPooled->setText(QApplication::translate("ModelEditor", "DD;DA", 0));
    rdoTheaded->setText(QApplication::translate("ModelEditor", "DD;DA (PS3)", 0));
    label->setText(QApplication::translate("ModelEditor", "Version:", 0));
    label_3->setText(QApplication::translate("ModelEditor", "File:", 0));
    label_4->setText(QApplication::translate("ModelEditor", "Bone Count:", 0));
    btnListen->setText(QApplication::translate("ModelEditor", "Open", 0));
    btnClose->setText(QApplication::translate("ModelEditor", "Save", 0));

    label_meshcount->setText(QApplication::translate("ModelEditor", "Mesh Count: ", 0));
    label_materialcount->setText(QApplication::translate("ModelEditor", "Material Count: ", 0));
    label_vertexcount->setText(QApplication::translate("ModelEditor", "Vertex Count: ", 0));
    label_facecount->setText(QApplication::translate("ModelEditor", "Face Count: ", 0));
    label_vertexids->setText(QApplication::translate("ModelEditor", "Vertex Ids: ", 0));
    label_vertexbuffersize->setText(QApplication::translate("ModelEditor", "Vertex Buffer Size: ", 0));
    label_secondbuffersize->setText(QApplication::translate("ModelEditor", "Second Buffer Size: ", 0));
    label_groupcount->setText(QApplication::translate("ModelEditor", "Group Count: ", 0));
    label_bonesoffset->setText(QApplication::translate("ModelEditor", "Bones Offset: ", 0));
    label_groupoffset->setText(QApplication::translate("ModelEditor", "Group Offset: ", 0));
    label_textureoffset->setText(QApplication::translate("ModelEditor", "Texture Offset: ", 0));
    label_meshoffset->setText(QApplication::translate("ModelEditor", "Mesh Offset: ", 0));
    label_vertexoffset->setText(QApplication::translate("ModelEditor", "Vertex Offset: ", 0));
    label_facesoffset->setText(QApplication::translate("ModelEditor", "Faces Offset: ", 0));
    label_unkoffset->setText(QApplication::translate("ModelEditor", "Unknown Offset: ", 0));

    label_bounding_sphere->setText(QApplication::translate("ModelEditor", "Bounding Sphere: ", 0));
    label_bounding_boxmin->setText(QApplication::translate("ModelEditor", "Bounding Box Min: ", 0));
    label_bounding_boxmax->setText(QApplication::translate("ModelEditor", "Bounding Box Max: ", 0));

    label_h_unkn02->setText(QApplication::translate("ModelEditor", "Mid Dist: ", 0));
    label_h_unkn03->setText(QApplication::translate("ModelEditor", "Low Dist: ", 0));
    label_h_unkn04->setText(QApplication::translate("ModelEditor", "Light Group: ", 0));
    label_h_unkn05->setText(QApplication::translate("ModelEditor", "Memory: ", 0));
    label_h_unkn06->setText(QApplication::translate("ModelEditor", "Boundy Count: ", 0));

// renderer
    MainWidget *r = new MainWidget;
    r->addMainMenu(renderMenu);
    r->setWindowTitle(QApplication::translate("Renderer", "Model Viewer", 0));
    // r->show();

    /* buttons
    connect(btnListen,SIGNAL(clicked(bool)),this,SLOT(on_btnListen_clicked()));
    connect(btnClose,SIGNAL(clicked(bool)),this,SLOT(on_btnClose_clicked()));
    connect(cmbAddress,SIGNAL(activated(QString)),this,SLOT(on_addr_changed(QString)));
    */

    // this->setLayout(outerLayout);
    QDockWidget *dock = new QDockWidget(tr("Headers"),this);
    dock->setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea | Qt::TopDockWidgetArea | Qt::BottomDockWidgetArea);
    QScrollArea *scroll = new QScrollArea;
    scroll->setWidgetResizable(true);
    scroll->setWidget(groupBox);
    dock->setWidget(scroll);
    // dock->setFloating(true);
    addDockWidget(Qt::LeftDockWidgetArea,dock);
    viewMenu->addAction(dock->toggleViewAction());

    // r->showNormal();
/*
dock = new QDockWidget(tr("Model Viewer"),this);
dock->setWidget(r);
//dock->setFloating(true);
addDockWidget(Qt::RightDockWidgetArea,dock);
*/

    // outerLayout->addWidget(r);
    // this->setLayout(outerLayout);
    this->setCentralWidget(r);
// bones
    dock = new QDockWidget(tr("Bones"),this);
    QGroupBox * bonesbox = new QGroupBox(dock);
    bonesbox->setObjectName(QStringLiteral("Bones"));
    bonetabs = new QTabWidget(bonesbox);
    QVBoxLayout * boneboxlayout = new QVBoxLayout;
    bonesbox->setLayout(boneboxlayout);
    boneboxlayout->addWidget(bonetabs);
    dock->setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea | Qt::TopDockWidgetArea | Qt::BottomDockWidgetArea);
    dock->setWidget(bonesbox);

    addDockWidget(Qt::LeftDockWidgetArea,dock);
    viewMenu->addAction(dock->toggleViewAction());

// bone remaptable
    dock = new QDockWidget(tr("Bone Remap Table"),this);
    QGroupBox * bonesmbox = new QGroupBox(dock);
    bonesmbox->setObjectName(QStringLiteral("Bone Remap Table"));
    bonemaptv = new QTableView;
    bonemapmodel = new QStandardItemModel;
    bonemaptv->setModel(bonemapmodel);
    bonemaptv->setWindowTitle(QString("Bone Remap Table"));

    QVBoxLayout * bonemboxlayout = new QVBoxLayout;
    bonesmbox->setLayout(bonemboxlayout);
    bonemboxlayout->addWidget(bonemaptv);
    dock->setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea | Qt::TopDockWidgetArea | Qt::BottomDockWidgetArea);
    dock->setWidget(bonesmbox);
    addDockWidget(Qt::LeftDockWidgetArea,dock);
    viewMenu->addAction(dock->toggleViewAction());

// groups
    dock = new QDockWidget(tr("Groups"),this);
    QGroupBox * Groupsbox = new QGroupBox(dock);
    Groupsbox->setObjectName(QStringLiteral("Groups"));
    Groupstabs = new QTabWidget(Groupsbox);
    QVBoxLayout * Groupsboxlayout = new QVBoxLayout;
    Groupsbox->setLayout(Groupsboxlayout);
    Groupsboxlayout->addWidget(Groupstabs);
    dock->setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea | Qt::TopDockWidgetArea | Qt::BottomDockWidgetArea);
    dock->setWidget(Groupsbox);

    addDockWidget(Qt::LeftDockWidgetArea,dock);
    viewMenu->addAction(dock->toggleViewAction());

// Materials
    dock = new QDockWidget(tr("Materials"),this);
    QGroupBox * Materialsbox = new QGroupBox(dock);
    Materialsbox->setObjectName(QStringLiteral("Materials"));
    Materialstabs = new QTabWidget(Materialsbox);
    QVBoxLayout * Materialsboxlayout = new QVBoxLayout;
    Materialsbox->setLayout(Materialsboxlayout);
    Materialsboxlayout->addWidget(Materialstabs);
    dock->setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea | Qt::TopDockWidgetArea | Qt::BottomDockWidgetArea);
    dock->setWidget(Materialsbox);

    addDockWidget(Qt::LeftDockWidgetArea,dock);
    viewMenu->addAction(dock->toggleViewAction());

// Mesh Parts
    dock = new QDockWidget(tr("Mesh Parts"),this);
    QGroupBox * MeshPartsbox = new QGroupBox(dock);
    MeshPartsbox->setObjectName(QStringLiteral("Mesh Parts"));
    MeshPartstabs = new QTabWidget(MeshPartsbox);
    QVBoxLayout * MeshPartsboxlayout = new QVBoxLayout;
    MeshPartsbox->setLayout(MeshPartsboxlayout);
    MeshPartsboxlayout->addWidget(MeshPartstabs);
    dock->setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea | Qt::TopDockWidgetArea | Qt::BottomDockWidgetArea);
    dock->setWidget(MeshPartsbox);

    addDockWidget(Qt::RightDockWidgetArea,dock);
    viewMenu->addAction(dock->toggleViewAction());

// Weights
    dock = new QDockWidget(tr("Weights"),this);
    QGroupBox * Weightsbox = new QGroupBox(dock);
    Weightsbox->setObjectName(QStringLiteral("Weights"));
    Weightstabs = new QTabWidget(Weightsbox);
    QVBoxLayout * Weightsboxlayout = new QVBoxLayout;
    Weightsbox->setLayout(Weightsboxlayout);
    Weightsboxlayout->addWidget(Weightstabs);
    dock->setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea | Qt::TopDockWidgetArea | Qt::BottomDockWidgetArea);
    dock->setWidget(Weightsbox);

    addDockWidget(Qt::RightDockWidgetArea,dock);
    viewMenu->addAction(dock->toggleViewAction());

// Textures
    dock = new QDockWidget(tr("Textures"),this);
    QGroupBox * Texturesbox = new QGroupBox(dock);
    Texturesbox->setObjectName(QStringLiteral("Textures"));
    Texturestabs = new QTabWidget(Texturesbox);
    QVBoxLayout * Texturesboxlayout = new QVBoxLayout;
    Texturesbox->setLayout(Texturesboxlayout);
    Texturesboxlayout->addWidget(Texturestabs);
    dock->setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea | Qt::TopDockWidgetArea | Qt::BottomDockWidgetArea);
    dock->setWidget(Texturesbox);

    addDockWidget(Qt::RightDockWidgetArea,dock);
    viewMenu->addAction(dock->toggleViewAction());

// VBOs
    dock = new QDockWidget(tr("Mesh Data"),this);
    QGroupBox * MeshDatabox = new QGroupBox(dock);
    MeshDatabox->setObjectName(QStringLiteral("Mesh Data"));
    MeshDatatabs = new QTabWidget(MeshDatabox);
    QVBoxLayout * MeshDataboxlayout = new QVBoxLayout;
    MeshDatabox->setLayout(MeshDataboxlayout);
    MeshDataboxlayout->addWidget(MeshDatatabs);
    dock->setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea | Qt::TopDockWidgetArea | Qt::BottomDockWidgetArea);
    dock->setWidget(MeshDatabox);

    addDockWidget(Qt::BottomDockWidgetArea,dock);
    viewMenu->addAction(dock->toggleViewAction());

// progress bar (for loading or saving)
    mProgressbar = new QProgressBar(this);
    mProgressbar->setMaximum(100);
    mProgressbar->setMinimum(0);
    mProgressbar->setTextVisible(true);
    mProgressbar->setValue(0);

    mProgressbar->setVisible(false);

// status bar
    mStatusbar = new QStatusBar(this);
    mStatusbar->addPermanentWidget(mProgressbar);

    mStatusbar->showMessage(tr("Ready."));
    this->setStatusBar(mStatusbar);

// renderer connections
    connect(this,SIGNAL(newTextures(const QImage&,const QImage&,const QImage&,const QImage&)),r,SLOT(onNewTextures(const QImage&,const QImage&,const QImage&,const QImage&)));
    connect(this,SIGNAL(NewMeshData(std::vector<int>&,std::vector<std::vector<VertexData> >&,std::vector<std::vector<uint> >&)),r,SLOT(onNewMesh(std::vector<int>&,std::vector<std::vector<VertexData> >&,std::vector<std::vector<uint> >&)));
    connect(this,SIGNAL(newMeshPartSelection(std::vector<int>&)),r,SLOT(onNewMeshselect(std::vector<int>&)));

// file change shit connections
    connect(cmbAddress,SIGNAL(activated(QString)),this,SLOT(on_File_changed(QString)));

    QIcon icon(":/resources/Resource/icon.png");
    this->setWindowIcon(icon);

    // QStringList lst = server.getAddresses();
    // ui->
    //  cmbAddress->insertItems(0,lst);
    //  ui->
    //  cmbAddress->insertItem(0,"Any");
    // ui->
    //   cmbAddress->setCurrentIndex(0);

    // establish known blocktypes
    blocktype[0x0CB68015]="4s4c4c2s";
    blocktype[0x14D40020]="3s1s4c4c4c2h2h";
    blocktype[0x5E7F202C]="3f4c4c2h2h";
    blocktype[0xA320C016]="4s8c8c4c";
    blocktype[0xA7D7D036]="3f4c2h";
    blocktype[0xA8FAB018]="3s1s4c4c2h";
    blocktype[0xB0983013]="3s1s4c";
    blocktype[0xBB424024]="3s1s4c4c8c2h2h4c";
    blocktype[0xC31F201C]="3s1s4c4c2h2h";
    blocktype[0xD8297028]="3f4c4c2h";
    blocktype[0xDB7DA014]="3s1s4c2s";

    unktypesfound = 0; //initalize me
}

ModelEditor::~ModelEditor()
{
    // cleanup
}

void ModelEditor::open_file(QString fileName)
{
    Texturestabs->clear();

// try to open textures as well
    int txcheck = fileName.lastIndexOf(QChar('.'));
    QString tx = txcheck > 0 ? fileName.left(txcheck) : fileName;

    // qDebug() <<tx;
    QPixmap pixmap(tx + "_BM.dds");
    if (pixmap.isNull())
        pixmap.load(tx + "_NUKI.dds");

    difflabel->setPixmap(pixmap);
    // difflabel->show();
    Texturestabs->addTab(diffscroll,"Diffuse");

    QPixmap pixmap2(tx + "_CMM.dds");
    speclabel->setPixmap(pixmap2);
    // speclabel->show();
    Texturestabs->addTab(specscroll,"Specular");

    QPixmap pixmap3(tx + "_NM.dds");
    if (pixmap3.isNull())
        pixmap3.load(tx + "_NM_HQ.dds");

    normlabel->setPixmap(pixmap3);
    // normlabel->show();
    Texturestabs->addTab(normscroll,"Normal");

    QPixmap pixmap4(tx + "_TM.dds");
    litelabel->setPixmap(pixmap4);
    // litelabel->show();
    Texturestabs->addTab(litescroll,"Light");

// clear old selection
    selection.clear();
    sel.clear();
    emit this->newMeshPartSelection(selection);

    FILE *Filep;

    Filep = fopen(fileName.toLocal8Bit().constData(), "rb");
    if (Filep == NULL) {
        QMessageBox msgBox;
        msgBox.setText(QString("Error Reading File: \n").append(fileName.toLocal8Bit().constData()));
        msgBox.exec();
        return;
    }

    size_t Fsize;
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
        // exit(2);
    }

// copy the file into the buffer:
    result = fread(buffer, 1, Fsize, Filep);
    if (result != Fsize) {
        // fputs("Reading error", stderr);
        QMessageBox msgBox;
        msgBox.setText("Read Error: unable to read file: \n" +fileName);
        msgBox.exec();
        return;
        // exit(3);
    }

// file should have been opened emit file to renderer
    emit this->newTextures(pixmap.toImage(), pixmap2.toImage(), pixmap3.toImage(), pixmap4.toImage());

    mProgressbar->setVisible(true);
    mProgressbar->setMaximum(Fsize);
    mProgressbar->setMinimum(0);
    mProgressbar->setValue(0);

// copy value into readable
//long test;
//memcpy(&test,&id.data()[0],4);
    unknownblocktypes.clear();
    unktypesfound =0;
////////////////////////// reading header
    uint offset = 0;
    quint32 id = read_u32le(buffer,offset);
    if (id == 0x00444F4D) {
        read_file_le(buffer); //pc

        spinBox->setText(QString::number(Mheader.version)); // version
    
        spinboxIdle->setText(QString::number(Mheader.bonecount));  //bone count

        meshcount->setText(QString::number(Mheader.meshcount));
        materialcount->setText(QString::number(Mheader.materialcount));
        vertexcount->setText(QString::number(Mheader.vertexcount));
        facecount->setText(QString::number(Mheader.facecount));
        vertexids->setText(QString::number(Mheader.vertexids));
        vertexbuffersize->setText(QString::number(Mheader.vertexbuffersize));
        secondbuffersize->setText(QString::number(Mheader.secondbuffersize));

        groupcount->setText(QString::number(Mheader.groupcount));
        bonesoffset->setText(QString::number(Mheader.bonesoffset));
        groupoffset->setText(QString::number(Mheader.groupoffset));
        textureoffset->setText(QString::number(Mheader.textureoffset));
        meshoffset->setText(QString::number(Mheader.meshoffset));
        vertexoffset->setText(QString::number(Mheader.vertexoffset));
        facesoffset->setText(QString::number(Mheader.facesoffset));
        unkoffset->setText(QString::number(Mheader.unkoffset));

        entervaluestogui();

        switch (Mheader.version) {
          case 212:
            rdoPooled->click();
            break;
          case 210:
            rdoSingle->click();
            break;
        }

        if (unktypesfound>0) {
            QString msg = "Unknown VBO Format(s): \n";
            for (auto const& x : unknownblocktypes) {
                msg.append(QString::number(x.first,16));
                msg.append("\n");
            }
            msg.append("\n!!!DATA SKIPPED!!!! \n Please report this along with the file you used.");
            QMessageBox msgBox;
            msgBox.setText(msg);
            msgBox.exec();
            mProgressbar->setValue(Fsize);
            mProgressbar->setVisible(false);
            mStatusbar->showMessage("File NOT Loaded: Unknown VBO formats");
        }
        else {
            mProgressbar->setValue(Fsize);
            mProgressbar->setVisible(false);
            mStatusbar->showMessage("File Loaded.");
        }
    }
    else if (id == 0x4D4F4400) {
        read_file_be(buffer); //ps3?

        spinBox->setText(QString::number(Mheader.version)); // version

        spinboxIdle->setText(QString::number(Mheader.bonecount));  //bone count
        meshcount->setText(QString::number(Mheader.meshcount));
        materialcount->setText(QString::number(Mheader.materialcount));
        vertexcount->setText(QString::number(Mheader.vertexcount));
        facecount->setText(QString::number(Mheader.facecount));
        vertexids->setText(QString::number(Mheader.vertexids));
        vertexbuffersize->setText(QString::number(Mheader.vertexbuffersize));
        secondbuffersize->setText(QString::number(Mheader.secondbuffersize));

        groupcount->setText(QString::number(Mheader.groupcount));
        bonesoffset->setText(QString::number(Mheader.bonesoffset));
        groupoffset->setText(QString::number(Mheader.groupoffset));
        textureoffset->setText(QString::number(Mheader.textureoffset));
        meshoffset->setText(QString::number(Mheader.meshoffset));
        vertexoffset->setText(QString::number(Mheader.vertexoffset));
        facesoffset->setText(QString::number(Mheader.facesoffset));
        unkoffset->setText(QString::number(Mheader.unkoffset));

        entervaluestogui();

        switch (Mheader.version) {
          case 212:
            rdoTheaded->click();
            break;
          case 210:
            rdoSingle->click();
            break;
        }

        if (unktypesfound>0) {
            QString msg = "Unknown VBO Format(s): \n";
            for (auto const& x : unknownblocktypes) {
                msg.append(QString::number(x.first,16));
                msg.append("\n");
            }
            msg.append("\n!!!DATA SKIPPED!!!! \n Please report this along with the file you used.");
            QMessageBox msgBox;
            msgBox.setText(msg);
            msgBox.exec();
            mProgressbar->setValue(Fsize);
            mProgressbar->setVisible(false);
            mStatusbar->showMessage("File NOT Loaded: Unknown VBO formats");
        }
        else {
            mProgressbar->setValue(Fsize);
            mProgressbar->setVisible(false);
            mStatusbar->showMessage("File Loaded.");
        }
    }
    else {
        QMessageBox msgBox;
        msgBox.setText(QString("Unknown Mod File Header: %1").arg(Mheader.magic,8,16,QChar('0')));
        msgBox.exec();
        mProgressbar->setValue(0);
        mProgressbar->setVisible(false);
        mStatusbar->showMessage("File NOT Loaded.");
    }

//file is done
    fclose(Filep);
    free(buffer);
}

void ModelEditor::read_file_le(char *buffer)
{
    uint offset = 0;

////////////////////////// reading header
    Mheader.magic = read_u32le(buffer,offset);
    Mheader.version = read_u16le(buffer,offset);
    Mheader.bonecount = read_u16le(buffer,offset);
    Mheader.meshcount = read_u16le(buffer,offset);
    Mheader.materialcount = read_u16le(buffer,offset);
    Mheader.vertexcount = read_u32le(buffer,offset);
    Mheader.facecount = read_u32le(buffer,offset);
    Mheader.vertexids = read_u32le(buffer,offset);
    Mheader.vertexbuffersize = read_u32le(buffer,offset);
    Mheader.secondbuffersize = read_u32le(buffer,offset);
    Mheader.groupcount = read_u32le(buffer,offset);
    Mheader.bonesoffset = read_u32le(buffer,offset);
    Mheader.groupoffset = read_u32le(buffer,offset);
    Mheader.textureoffset = read_u32le(buffer,offset);
    Mheader.meshoffset = read_u32le(buffer,offset);
    Mheader.vertexoffset = read_u32le(buffer,offset);
    Mheader.facesoffset = read_u32le(buffer,offset);
    Mheader.unkoffset = read_u32le(buffer,offset);
    read_sphere_le(buffer,offset,Mheader.bsphere);
    read_aabb_le(buffer,offset,Mheader.bbox);
    Mheader.info.middist = read_s32le(buffer,offset);
    Mheader.info.lowdist = read_s32le(buffer,offset);
    Mheader.info.lightgroup = read_u32le(buffer,offset);
    Mheader.info.memory = read_u16le(buffer,offset);
    Mheader.info.reserved = read_u16le(buffer,offset);
    Mheader.boundarycount = read_u32le(buffer,offset);

//////////////////////  reading bone data
    offset = Mheader.bonesoffset;

    Mbones.boneinfo.clear();
    for (uint i=0;i<Mheader.bonecount;i++) {
        MOD_Bone_Info binf;
        //if version == 237 -> boneinfo2
        if (Mheader.version == 237) {
            binf.id = read_u16le(buffer,offset);
            binf.parent = read_u8(buffer,offset);
            binf.child = read_u8(buffer,offset);
            binf.unk = 0;
        }
        else {
            binf.id = read_u8(buffer,offset);
            binf.parent = read_u8(buffer,offset);
            binf.child = read_u8(buffer,offset);
            binf.unk = read_u8(buffer,offset);
        }
        binf.radius = read_f32le(buffer,offset);
        binf.length = read_f32le(buffer,offset);
        read_vec3le(buffer,offset,binf.offset);
        Mbones.boneinfo.push_back(binf);
    }

    Mbones.lmatrices.clear();
    for (uint i=0;i<Mheader.bonecount;i++) {
        Matrix mtx;
        read_matrix_le(buffer,offset,mtx);
        Mbones.lmatrices.push_back(mtx);
    }

    Mbones.amatrices.clear();
    for (uint i=0;i<Mheader.bonecount;i++) {
        Matrix mtx;
        read_matrix_le(buffer,offset,mtx);
        Mbones.amatrices.push_back(mtx);
    }

    uint remaptablesize = (Mheader.bonecount + 0xFF) & 0xFFFFFF00;
    Mbones.remaptable.clear();
    for (uint i=0;i<remaptablesize;i++) {
        Mbones.remaptable.push_back(read_u8(buffer,offset));
    }

//////////////////////  reading group data
    offset = Mheader.groupoffset;

    Mgroups.groupinfo.clear();
    for (uint i=0;i<Mheader.groupcount;i++) {
        MOD_Group_Info ginf;
        ginf.id = read_u32le(buffer,offset);
        ginf.h1 = read_u32le(buffer,offset);
        ginf.h2 = read_u32le(buffer,offset);
        ginf.h3 = read_u32le(buffer,offset);
        read_sphere_le(buffer,offset,ginf.bsphere);
        Mgroups.groupinfo.push_back(ginf);
    }

//////////////////////  reading material data
    offset = Mheader.textureoffset;

    Mmats.name.clear();
    for (uint i=0;i<Mheader.materialcount;i++) {
        Mmats.name.push_back(read_material(buffer,offset));
    }

/////////////////////  reading mesh data
    offset = Mheader.meshoffset;

    Mparts.parts.clear();
    for (uint i=0;i<Mheader.meshcount;i++) {
        MOD_Mesh_Info mp;
        mp.drawmode = read_u16le(buffer,offset);
        mp.vertexcount = read_u16le(buffer,offset);

        quint32 v = read_u32le(buffer,offset);
        mp.id = v & 0xFFF; v >>= 12;
        mp.material = v & 0xFFF; v >>= 12;
        mp.lod = v;

        v = read_u32le(buffer,offset);
        mp.disp = v & 1; v >>= 1;
        mp.shape = v & 1; v >>= 1;
        mp.sort = v & 1; v >>= 1;
        mp.weightcount = v & 0x1F; v >>= 5;
        mp.alphapri = v & 0xFF; v >>= 8;
        mp.blocksize = v & 0xFF; v >>= 8;
        mp.topology = v & 0x3F; v >>= 6;
        mp.binormalflip = v & 1; v >>= 1;
        mp.bridge = v & 1;

        mp.vertexsub = read_u32le(buffer,offset);
        mp.vertexoffset = read_u32le(buffer,offset);
        mp.blocktype = read_u32le(buffer,offset);
        mp.faceoffset = read_u32le(buffer,offset);
        mp.facecount = read_u32le(buffer,offset);
        mp.facebase = read_u32le(buffer,offset);
        mp.envelope = read_u8(buffer,offset);
        mp.boneremapid = read_u8(buffer,offset);
        mp.connectid = read_u16le(buffer,offset);
        mp.minindex = read_u16le(buffer,offset);
        mp.maxindex = read_u16le(buffer,offset);
        mp.unklong = read_u32le(buffer,offset);
        Mparts.parts.push_back(mp);
    }

    Mparts.chunks.clear();
    for (uint i=0;i<Mheader.boundarycount;i++) {
        MOD_Boundary_Info chunk;
        chunk.bone = read_u32le(buffer,offset);
        chunk.un2 = read_u32le(buffer,offset);
        chunk.un3 = read_u32le(buffer,offset);
        chunk.un4 = read_u32le(buffer,offset);
        read_sphere_le(buffer,offset,chunk.sphere);
        read_aabb_le(buffer,offset,chunk.aabb);
        read_obb_le(buffer,offset,chunk.obb);
        Mparts.chunks.push_back(chunk);
    }

/////////////////  reading vbo permesh part data
    offset = Mheader.vertexoffset;

    for (uint i=0;i<Mheader.meshcount;i++) {
        MOD_Mesh_Info &mp = Mparts.parts[i];

        auto it = blocktype.find(mp.blocktype);
        if (it != blocktype.end())
        {
            const char *fmt = it->second;

            for (uint j=0;j<mp.vertexcount;j++) {
                std::vector<MOD_Value> vtx;
                const char *s = fmt;
                char c;

                while ((c = *s) != 0)
                {
                    s++;
                    uint n = c - '0';
                    if (n <= 9 && (c = *s) != 0)
                    {
                        s++;

                        for (uint k=0;k<n;k++)
                        {
                            MOD_Value val = {};

                            switch (c)
                            {
                              case 'c':
                                val.u8 = read_u8(buffer,offset);
                                break;
                              case 's':
                              case 'h':
                                val.u16 = read_u16le(buffer,offset);
                                break;
                              case 'l':
                                val.u32 = read_u32le(buffer,offset);
                                break;
                              case 'f':
                                val.f32 = read_f32le(buffer,offset);
                                break;
                            }

                            vtx.push_back(val);
                        }
                    }
                }

                mp.vertices.push_back(vtx);
            }
        }
        else
        {
            if (unknownblocktypes.find(mp.blocktype) == unknownblocktypes.end()) {
                unknownblocktypes[mp.blocktype] = unktypesfound;
                unktypesfound++;
            }

            for (uint j=0;j<mp.vertexcount;j++) {
                std::vector<MOD_Value> vtx;
                for (uint k=0;k<mp.blocksize;k++)
                {
                    MOD_Value val = {};
                    val.u8 = read_u8(buffer,offset);
                    vtx.push_back(val);
                }
                mp.vertices.push_back(vtx);
            }
        }
    }

/////////////////  reading faces permesh part data
    offset = Mheader.facesoffset;

    std::vector<quint16> faces;
    for (uint i=0;i<Mheader.facecount;i++) {
        faces.push_back(read_u16le(buffer,offset));
    }

    for (uint i=0;i<Mheader.meshcount;i++) {
        MOD_Mesh_Info &mp = Mparts.parts[i];
        quint16 *data = faces.data() + mp.faceoffset;

        for (uint j=0;j<mp.facecount;j++)
        {
            mp.faces.push_back(data[j]);
        }
    };
}

void ModelEditor::read_file_be(char *buffer)
{
    uint offset = 0;

////////////////////////// reading header

    Mheader.magic = read_u32be(buffer,offset);
    Mheader.version = read_u16be(buffer,offset);
    Mheader.bonecount = read_u16be(buffer,offset);
    Mheader.meshcount = read_u16be(buffer,offset);
    Mheader.materialcount = read_u16be(buffer,offset);
    Mheader.vertexcount = read_u32be(buffer,offset);
    Mheader.facecount = read_u32be(buffer,offset);
    Mheader.vertexids = read_u32be(buffer,offset);
    Mheader.vertexbuffersize = read_u32be(buffer,offset);
    Mheader.secondbuffersize = read_u32be(buffer,offset);
    Mheader.groupcount = read_u32be(buffer,offset);
    Mheader.bonesoffset = read_u32be(buffer,offset);
    Mheader.groupoffset = read_u32be(buffer,offset);
    Mheader.textureoffset = read_u32be(buffer,offset);
    Mheader.meshoffset = read_u32be(buffer,offset);
    Mheader.vertexoffset = read_u32be(buffer,offset);
    Mheader.facesoffset = read_u32be(buffer,offset);
    Mheader.unkoffset = read_u32be(buffer,offset);
    read_sphere_be(buffer,offset,Mheader.bsphere);
    read_aabb_be(buffer,offset,Mheader.bbox);
    Mheader.info.middist = read_s32be(buffer,offset);
    Mheader.info.lowdist = read_s32be(buffer,offset);
    Mheader.info.lightgroup = read_u32be(buffer,offset);
    Mheader.info.memory = read_u16be(buffer,offset);
    Mheader.info.reserved = read_u16be(buffer,offset);
    Mheader.boundarycount = read_u32be(buffer,offset);

//////////////////////  reading bone data
    offset = Mheader.bonesoffset;

    Mbones.boneinfo.clear();
    for (uint i=0;i<Mheader.bonecount;i++) {
        MOD_Bone_Info binf;
        //if version == 237 -> boneinfo2
        if (Mheader.version == 237) {
            binf.id = read_u16be(buffer,offset);
            binf.parent = read_u8(buffer,offset);
            binf.child = read_u8(buffer,offset);
            binf.unk = 0;
        }
        else {
            binf.id = read_u8(buffer,offset);
            binf.parent = read_u8(buffer,offset);
            binf.child = read_u8(buffer,offset);
            binf.unk = read_u8(buffer,offset);
        }
        binf.radius = read_f32be(buffer,offset);
        binf.length = read_f32be(buffer,offset);
        read_vec3be(buffer,offset,binf.offset);
        Mbones.boneinfo.push_back(binf);
    }

    Mbones.lmatrices.clear();
    for (uint i=0;i<Mheader.bonecount;i++) {
        Matrix mtx;
        read_matrix_be(buffer,offset,mtx);
        Mbones.lmatrices.push_back(mtx);
    }

    Mbones.amatrices.clear();
    for (uint i=0;i<Mheader.bonecount;i++) {
        Matrix mtx;
        read_matrix_be(buffer,offset,mtx);
        Mbones.amatrices.push_back(mtx);
    }

    uint remaptablesize = (Mheader.bonecount + 0xFF) & 0xFFFFFF00;
    Mbones.remaptable.clear();
    for (uint i=0; i<remaptablesize;i++) {
        Mbones.remaptable.push_back(read_u8(buffer,offset));
    }

//////////////////////  reading group data
    offset = Mheader.groupoffset;

    Mgroups.groupinfo.clear();
    for (uint i=0;i<Mheader.groupcount;i++) {
        MOD_Group_Info ginf;
        ginf.id = read_u32be(buffer,offset);
        ginf.h1 = read_u32be(buffer,offset);
        ginf.h2 = read_u32be(buffer,offset);
        ginf.h3 = read_u32be(buffer,offset);
        read_sphere_be(buffer,offset,ginf.bsphere);
        Mgroups.groupinfo.push_back(ginf);
    }

//////////////////////  reading material data
    offset = Mheader.textureoffset;

    Mmats.name.clear();
    for (uint i=0;i<Mheader.materialcount;i++) {
        Mmats.name.push_back(read_material(buffer,offset));
    }

/////////////////////  reading mesh data
    offset = Mheader.meshoffset;

    Mparts.parts.clear();
    for (uint i=0;i<Mheader.meshcount;i++) {
        MOD_Mesh_Info mp;
        mp.drawmode = read_u16be(buffer,offset);
        mp.vertexcount = read_u16be(buffer,offset);

        quint32 v = read_u32be(buffer,offset);
        mp.lod = v & 0xFF; v >>= 8;
        mp.material = v & 0xFFF; v >>= 12;
        mp.id = v;

        v = read_u32be(buffer,offset);
        mp.bridge = v & 1; v >>= 1;
        mp.binormalflip = v & 1; v >>= 1;
        mp.topology = v & 0x3F; v >>= 6;
        mp.blocksize = v & 0xFF; v >>= 8;
        mp.alphapri = v & 0xFF; v >>= 8;
        mp.weightcount = v & 0x1F; v >>= 5;
        mp.sort = v & 1; v >>= 1;
        mp.shape = v & 1; v >>= 1;
        mp.disp = v & 1;

        mp.vertexsub = read_u32be(buffer,offset);
        mp.vertexoffset = read_u32be(buffer,offset);
        mp.blocktype = read_u32be(buffer,offset);
        mp.faceoffset = read_u32be(buffer,offset);
        mp.facecount = read_u32be(buffer,offset);
        mp.facebase = read_u32be(buffer,offset);
        mp.envelope = read_u8(buffer,offset);
        mp.boneremapid = read_u8(buffer,offset);
        mp.connectid = read_u16be(buffer,offset);
        mp.minindex = read_u16be(buffer,offset);
        mp.maxindex = read_u16be(buffer,offset);
        mp.unklong = read_u32be(buffer,offset);
        offset+=8;//skip read in 00000000 x2 longs spacers
        Mparts.parts.push_back(mp);
    }

    Mparts.chunks.clear();
    for (uint i=0;i<Mheader.boundarycount;i++) {
        MOD_Boundary_Info chunk;
        chunk.bone = read_u32be(buffer,offset);
        chunk.un2 = read_u32be(buffer,offset);
        chunk.un3 = read_u32be(buffer,offset);
        chunk.un4 = read_u32be(buffer,offset);
        read_sphere_be(buffer,offset,chunk.sphere);
        read_aabb_be(buffer,offset,chunk.aabb);
        read_obb_be(buffer,offset,chunk.obb);
        Mparts.chunks.push_back(chunk);
    }

/////////////////  reading vbo permesh part data
    offset = Mheader.vertexoffset;

    for (uint i=0;i<Mheader.meshcount;i++) {
        MOD_Mesh_Info &mp = Mparts.parts[i];

        auto it = blocktype.find(mp.blocktype);
        if (it != blocktype.end())
        {
            const char *fmt = it->second;

            for (uint j=0;j<mp.vertexcount;j++) {
                std::vector<MOD_Value> vtx;
                const char *s = fmt;
                char c;

                while ((c = *s) != 0)
                {
                    s++;
                    uint n = c - '0';
                    if (n <= 9 && (c = *s) != 0)
                    {
                        s++;

                        for (uint k=0;k<n;k++)
                        {
                            MOD_Value val = {};

                            switch (c)
                            {
                              case 'c':
                                val.u8 = read_u8(buffer,offset);
                                break;
                              case 's':
                              case 'h':
                                val.u16 = read_u16be(buffer,offset);
                                break;
                              case 'l':
                                val.u16 = read_u32be(buffer,offset);
                                break;
                              case 'f':
                                val.f32 = read_f32be(buffer,offset);
                                break;
                            }

                            vtx.push_back(val);
                        }
                    }
                }

                mp.vertices.push_back(vtx);
            }
        }
        else
        {
            if (unknownblocktypes.find(mp.blocktype) == unknownblocktypes.end()) {
                unknownblocktypes[mp.blocktype] = unktypesfound;
                unktypesfound++;
            }

            for (uint j=0;j<mp.vertexcount;j++) {
                std::vector<MOD_Value> vtx;
                for (uint k=0;k<mp.blocksize;k++)
                {
                    MOD_Value val = {};
                    val.u8 = read_u8(buffer,offset);
                    vtx.push_back(val);
                }
                mp.vertices.push_back(vtx);
            }
        }
    }

/////////////////  reading faces permesh part data
    offset = Mheader.facesoffset;

    std::vector<quint16> faces;
    for (uint i=0;i<Mheader.facecount;i++) {
        faces.push_back(read_u16be(buffer,offset));
    }

    for (uint i=0;i<Mheader.meshcount;i++) {
        MOD_Mesh_Info &mp = Mparts.parts[i];
        quint16 *data = faces.data() + mp.faceoffset;

        for (uint j=0;j<mp.facecount;j++)
        {
            mp.faces.push_back(data[j]);
        }
    };
}

void ModelEditor::about()
{
    QMessageBox::about(this, tr("About Dragon's Dogma Mod Tool"),
        tr("The <b>Dragon's Dogma Mod Tool</b> blah blah "
            "use it to view and edit .mod files, "
            "yada yada yada, "
            "use at your own risk."));
}

void ModelEditor::on_Open_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this,
          tr("Load Mod File"), "./",tr("MOD (*.mod)"));
    if (fileName.isNull()) return;
    cmbAddress->insertItem(0,fileName);
    label_3->setText("File: " + fileName.section("/",-1,-1)); // just the file name
    open_file(fileName);
}

void ModelEditor::on_File_changed(QString fileName)
{
    label_3->setText("File: " + fileName.section("/",-1,-1)); // just the file name
    open_file(fileName);
}

void ModelEditor::on_Save_clicked()
{
    QString fileName = QFileDialog::getSaveFileName(this, tr("Save Mod File"),"./",tr("MOD (*.mod)"));
    if (fileName.isNull()) return;

    FILE *f = fopen(fileName.toLocal8Bit().constData(), "wb");
    if (f == NULL) {
        QMessageBox msgBox;
        msgBox.setText(QString("Error Saving File: \n").append(fileName.toLocal8Bit().constData()));
        msgBox.exec();
    }
    else {
        if (rdoPooled->isChecked()) { //pc
            write_file_le(f, 212);
        }
        else if (rdoTheaded->isChecked()) { //ps3
            write_file_be(f, 212);
        }
        else {
            write_file_be(f, 210);
        }

        fclose(f);
    }
}

void ModelEditor::write_file_le(FILE *f, uint version)
{
    ulong pos;

    std::vector<quint16> faces;
    for (uint i=0;i<Mparts.parts.size();i++) {
        MOD_Mesh_Info &mp = Mparts.parts[i];

        if (mp.topology == 4) // strips
        {
            quint16 last = 0;
            if (faces.size() & 1)
                faces.push_back(last);

            mp.newfaceoffset = faces.size();

            for (uint j=0;j<mp.faces.size();j++)
            {
                if (mp.faces[j] == 0xFFFF)
                {
                    if (faces.size() & 1)
                        faces.push_back(last);
                    faces.push_back(last);
                    last = mp.faces[j+1];
                    faces.push_back(last);
                }
                else
                {
                    last = mp.faces[j];
                    faces.push_back(last);
                }
            }

            mp.newfacecount = faces.size() - mp.faceoffset;

            if (mp.faces.size())
            {
                if (faces.size() & 1)
                    faces.push_back(last);
                faces.push_back(last);
                faces.push_back(mp.faces[0]);
            }
        }
        else
        {
            mp.newfaceoffset = faces.size();
            mp.newfacecount = mp.faces.size();
            for (uint j=0;j<mp.faces.size();j++)
            {
                faces.push_back(mp.faces[j]);
            }
        }
    }

////////////////////////// writing header

    write_u32le(f,0x444F4D);
    write_u16le(f,version);
    write_u16le(f,Mheader.bonecount);
    write_u16le(f,Mheader.meshcount);
    write_u16le(f,Mheader.materialcount);
    write_u32le(f,Mheader.vertexcount);
    write_u32le(f,faces.size());
    write_u32le(f,Mheader.vertexids);
    write_u32le(f,Mheader.vertexbuffersize);
    write_u32le(f,Mheader.secondbuffersize);
    write_u32le(f,Mheader.groupcount);
    write_u32le(f,Mheader.bonesoffset);
    write_u32le(f,Mheader.groupoffset);
    write_u32le(f,Mheader.textureoffset);
    write_u32le(f,Mheader.meshoffset);
    write_u32le(f,Mheader.vertexoffset);
    write_u32le(f,Mheader.facesoffset);
    write_u32le(f,Mheader.unkoffset);
    write_sphere_le(f,Mheader.bsphere);
    write_aabb_le(f,Mheader.bbox);
    write_s32le(f,Mheader.info.middist);
    write_s32le(f,Mheader.info.lowdist);
    write_u32le(f,Mheader.info.lightgroup);
    write_u16le(f,Mheader.info.memory);
    write_u16le(f,Mheader.info.reserved);
    write_u32le(f,Mheader.boundarycount);

////////////////////////// writing bone data

    pos = ftell(f);
    if (pos != Mheader.bonesoffset) {
        fseek(f,36,SEEK_SET);
        write_u32le(f,pos);
        fseek(f,pos,SEEK_SET);
    }

    for (uint i=0;i<Mheader.bonecount;i++) {
        MOD_Bone_Info &binf = Mbones.boneinfo[i];
        //if version == 237 -> boneinfo2
        if (version == 237) {
            write_u16le(f,binf.id);
            write_u8(f,binf.parent);
            write_u8(f,binf.child);
        }
        else {
            write_u8(f,binf.id);
            write_u8(f,binf.parent);
            write_u8(f,binf.child);
            write_u8(f,binf.unk);
        }
        write_f32le(f,binf.radius);
        write_f32le(f,binf.length);
        write_vec3le(f,binf.offset);
    }

    for (uint i=0;i<Mheader.bonecount;i++) {
        write_matrix_le(f,Mbones.lmatrices[i]);
    }

    for (uint i=0;i<Mheader.bonecount;i++) {
        write_matrix_le(f,Mbones.amatrices[i]);
    }

    for (uint i =0; i<Mbones.remaptable.size();i++) {
        write_u8(f,Mbones.remaptable[i]);
    }

//////////////////////  writing group data

    pos = ftell(f);
    if (pos != Mheader.groupoffset) {
        fseek(f,40,SEEK_SET);
        write_u32le(f,pos);
        fseek(f,pos,SEEK_SET);
    }

    for (uint i=0;i<Mheader.groupcount;i++) {
        MOD_Group_Info &ginf = Mgroups.groupinfo[i];
        write_u32le(f,ginf.id);
        write_u32le(f,ginf.h1);
        write_u32le(f,ginf.h2);
        write_u32le(f,ginf.h3);
        write_sphere_le(f,ginf.bsphere);
    }

//////////////////////  writing material data

    pos = ftell(f);
    if (pos != Mheader.textureoffset) {
        fseek(f,44,SEEK_SET);
        write_u32le(f,pos);
        fseek(f,pos,SEEK_SET);
    }

    for (uint i=0;i<Mheader.materialcount;i++) {
        write_material(f, Mmats.name[i]);
    }

/////////////////////  writing mesh data

    pos = ftell(f);
    if (pos != Mheader.meshoffset) {
        fseek(f,48,SEEK_SET);
        write_u32le(f,pos);
        fseek(f,pos,SEEK_SET);
    }

    for (uint i=0;i<Mheader.meshcount;i++) {
        MOD_Mesh_Info &mp = Mparts.parts[i];

        write_u16le(f,mp.drawmode);
        write_u16le(f,mp.vertexcount);

        uint32_t v = mp.lod & 0xFF;
        v <<= 12; v |= mp.material & 0xFFF;
        v <<= 12; v |= mp.id & 0xFFF;
        write_u32le(f,v);

        v = mp.bridge & 1;
        v <<= 1; v |= mp.binormalflip & 1;
        v <<= 6; v |= mp.topology & 0x3F;
        v <<= 8; v |= mp.blocksize & 0xFF;
        v <<= 8; v |= mp.alphapri & 0xFF;
        v <<= 5; v |= mp.weightcount & 0x1F;
        v <<= 1; v |= mp.sort & 1;
        v <<= 1; v |= mp.shape & 1;
        v <<= 1; v |= mp.disp & 1;
        write_u32le(f,v);        

        write_u32le(f,mp.vertexsub);
        write_u32le(f,mp.vertexoffset);
        write_u32le(f,mp.blocktype);
        write_u32le(f,mp.newfaceoffset);
        write_u32le(f,mp.newfacecount);
        write_u32le(f,mp.facebase);
        write_u8(f,mp.envelope);
        write_u8(f,mp.boneremapid);
        write_u16le(f,mp.connectid);
        write_u16le(f,mp.minindex);
        write_u16le(f,mp.maxindex);
        write_u32le(f,mp.unklong);
    }

    for (uint i=0;i<Mheader.boundarycount;i++) {
        MOD_Boundary_Info &chunk = Mparts.chunks[i];
        write_u32le(f,chunk.bone);
        write_u32le(f,chunk.un2);
        write_u32le(f,chunk.un3);
        write_u32le(f,chunk.un4);
        write_sphere_le(f,chunk.sphere);
        write_aabb_le(f,chunk.aabb);
        write_obb_le(f,chunk.obb);
    }

/////////////////  writing vbo permesh part data

    pos = ftell(f);
    if (pos != Mheader.vertexoffset) {
        fseek(f,52,SEEK_SET);
        write_u32le(f,pos);
        fseek(f,pos,SEEK_SET);
    }

    for (uint i=0;i<Mheader.meshcount;i++) {
        MOD_Mesh_Info &mp = Mparts.parts[i];

        auto it = blocktype.find(mp.blocktype);
        if (it != blocktype.end())
        {
            const char *fmt = it->second;

            for (uint j=0;j<mp.vertexcount;j++) {
                std::vector<MOD_Value> &vtx = mp.vertices[j];
                uint l = 0;
                const char *s = fmt;
                char c;

                while ((c = *s) != 0)
                {
                    s++;
                    uint n = c - '0';
                    if (n <= 9 && (c = *s) != 0)
                    {
                        s++;

                        for (uint k=0;k<n;k++)
                        {
                            switch (c)
                            {
                              case 'c':
                                write_u8(f, vtx[l++].u8);
                                break;
                              case 's':
                              case 'h':
                                write_u16le(f, vtx[l++].u16);
                                break;
                              case 'l':
                                write_u32le(f, vtx[l++].u32);
                                break;
                              case 'f':
                                write_f32le(f, vtx[l++].f32);
                                break;
                            }
                        }
                    }
                }
            }
        }
        else
        {
            if (unknownblocktypes.find(mp.blocktype) == unknownblocktypes.end()) {
                unknownblocktypes[mp.blocktype] = unktypesfound;
                unktypesfound++;
            }

            for (uint j=0;j<mp.vertexcount;j++) {
                std::vector<MOD_Value> &vtx = mp.vertices[j];
                for (uint k=0;k<mp.blocksize;k++)
                {
                    write_u8(f, vtx[k++].u8);
                }
            }
        }
    }

/////////////// write faces data

    pos = ftell(f);
    if (pos != Mheader.facesoffset) {
        fseek(f,56,SEEK_SET);
        write_u32le(f,pos);
        fseek(f,pos,SEEK_SET);
    }

    for (uint i=0;i<faces.size();i++)
    {
        write_u16le(f,faces[i]);
    }

///////////////

    pos = ftell(f);
    if (pos != Mheader.unkoffset) {
        fseek(f,60,SEEK_SET);
        write_u32le(f,pos);
        fseek(f,pos,SEEK_SET);
    }

    write_u32le(f,0);
}

void ModelEditor::write_file_be(FILE *f,uint version)
{
    ulong pos;

    std::vector<quint16> faces;
    for (uint i=0;i<Mparts.parts.size();i++) {
        MOD_Mesh_Info &mp = Mparts.parts[i];
        mp.newfaceoffset = faces.size();
        mp.newfacecount = mp.faces.size();
        for (uint j=0;j<mp.faces.size();j++)
        {
            faces.push_back(mp.faces[j]);
        }
    }

////////////////////////// writing header

    write_u32be(f,0x444F4D);
    write_u16be(f,version);
    write_u16be(f,Mheader.bonecount);
    write_u16be(f,Mheader.meshcount);
    write_u16be(f,Mheader.materialcount);
    write_u32be(f,Mheader.vertexcount);
    write_u32be(f,faces.size());
    write_u32be(f,Mheader.vertexids);
    write_u32be(f,Mheader.vertexbuffersize);
    write_u32be(f,Mheader.secondbuffersize);
    write_u32be(f,Mheader.groupcount);
    write_u32be(f,Mheader.bonesoffset);
    write_u32be(f,Mheader.groupoffset);
    write_u32be(f,Mheader.textureoffset);
    write_u32be(f,Mheader.meshoffset);
    write_u32be(f,Mheader.vertexoffset);
    write_u32be(f,Mheader.facesoffset);
    write_u32be(f,Mheader.unkoffset);
    write_sphere_be(f,Mheader.bsphere);
    write_aabb_be(f,Mheader.bbox);
    write_s32be(f,Mheader.info.middist);
    write_s32be(f,Mheader.info.lowdist);
    write_u32be(f,Mheader.info.lightgroup);
    write_u16be(f,Mheader.info.memory);
    write_u16be(f,Mheader.info.reserved);
    write_u32be(f,Mheader.boundarycount);

////////////////////////// writing bone data

    pos = ftell(f);
    if (pos != Mheader.bonesoffset) {
        fseek(f,36,SEEK_SET);
        write_u32be(f,pos);
        fseek(f,pos,SEEK_SET);
    }

    for (uint i=0;i<Mheader.bonecount;i++) {
        MOD_Bone_Info &binf = Mbones.boneinfo[i];
        //if version == 237 -> boneinfo2
        if (version == 237) {
            write_u16be(f,binf.id);
            write_u8(f,binf.parent);
            write_u8(f,binf.child);
        }
        else {
            write_u8(f,binf.id);
            write_u8(f,binf.parent);
            write_u8(f,binf.child);
            write_u8(f,binf.unk);
        }
        write_f32be(f,binf.radius);
        write_f32be(f,binf.length);
        write_vec3be(f,binf.offset);
    }

    for (uint i=0;i<Mheader.bonecount;i++) {
        write_matrix_be(f,Mbones.lmatrices[i]);
    }

    for (uint i=0;i<Mheader.bonecount;i++) {
        write_matrix_be(f,Mbones.amatrices[i]);
    }

    for (uint i =0; i<Mbones.remaptable.size();i++) {
        write_u8(f,Mbones.remaptable[i]);
    }

//////////////////////  writing group data

    pos = ftell(f);
    if (pos != Mheader.groupoffset) {
        fseek(f,40,SEEK_SET);
        write_u32be(f,pos);
        fseek(f,pos,SEEK_SET);
    }

    for (uint i=0;i<Mheader.groupcount;i++) {
        MOD_Group_Info &ginf = Mgroups.groupinfo[i];
        write_u32be(f,ginf.id);
        write_u32be(f,ginf.h1);
        write_u32be(f,ginf.h2);
        write_u32be(f,ginf.h3);
        write_sphere_be(f,ginf.bsphere);
    }

//////////////////////  writing material data

    pos = ftell(f);
    if (pos != Mheader.textureoffset) {
        fseek(f,44,SEEK_SET);
        write_u32be(f,pos);
        fseek(f,pos,SEEK_SET);
    }

    for (uint i=0;i<Mheader.materialcount;i++) {
        write_material(f, Mmats.name[i]);
    }

/////////////////////  writing mesh data

    pos = ftell(f);
    if (pos != Mheader.meshoffset) {
        fseek(f,48,SEEK_SET);
        write_u32be(f,pos);
        fseek(f,pos,SEEK_SET);
    }

    for (uint i=0;i<Mheader.meshcount;i++) {
        MOD_Mesh_Info &mp = Mparts.parts[i];

        write_u16be(f,mp.drawmode);
        write_u16be(f,mp.vertexcount);

        quint32 v = mp.id & 0xFFF; 
        v <<= 12; v |= mp.material & 0xFFF;
        v <<= 8; v |= mp.lod & 0xFF; 
        write_u32be(f,v);

        v = mp.disp & 1;
        v <<= 1; v |= mp.shape & 1;
        v <<= 1; v |= mp.sort & 1;
        v <<= 5; v |= mp.weightcount & 0x1F;
        v <<= 8; v |= mp.alphapri & 0xFF;
        v <<= 8; v |= mp.blocksize & 0xFF;
        v <<= 6; v |= mp.topology & 0x3F;
        v <<= 1; v |= mp.binormalflip & 1;
        v <<= 1; v |= mp.bridge & 1;
        write_u32be(f,v);

        write_u32be(f,mp.vertexsub);
        write_u32be(f,mp.vertexoffset);
        write_u32be(f,mp.blocktype);
        write_u32be(f,mp.newfaceoffset);
        write_u32be(f,mp.newfacecount);
        write_u32be(f,mp.facebase);
        write_u8(f,mp.envelope);
        write_u8(f,mp.boneremapid);
        write_u16be(f,mp.connectid);
        write_u16be(f,mp.minindex);
        write_u16be(f,mp.maxindex);
        write_u32be(f,mp.unklong);
        write_u32be(f,0);
        write_u32be(f,0);
    }

    for (uint i=0;i<Mheader.boundarycount;i++) {
        MOD_Boundary_Info &chunk = Mparts.chunks[i];
        write_u32be(f,chunk.bone);
        write_u32be(f,chunk.un2);
        write_u32be(f,chunk.un3);
        write_u32be(f,chunk.un4);
        write_sphere_be(f,chunk.sphere);
        write_aabb_be(f,chunk.aabb);
        write_obb_be(f,chunk.obb);
    }

/////////////////  writing vbo permesh part data

    pos = ftell(f);
    if (pos != Mheader.vertexoffset) {
        fseek(f,52,SEEK_SET);
        write_u32be(f,pos);
        fseek(f,pos,SEEK_SET);
    }

    for (uint i=0;i<Mheader.meshcount;i++) {
        MOD_Mesh_Info &mp = Mparts.parts[i];

        auto it = blocktype.find(mp.blocktype);
        if (it != blocktype.end())
        {
            const char *fmt = it->second;

            for (uint j=0;j<mp.vertexcount;j++) {
                std::vector<MOD_Value> &vtx = mp.vertices[j];
                uint l = 0;
                const char *s = fmt;
                char c;

                while ((c = *s) != 0)
                {
                    s++;
                    uint n = c - '0';
                    if (n <= 9 && (c = *s) != 0)
                    {
                        s++;

                        for (uint k=0;k<n;k++)
                        {
                            switch (c)
                            {
                              case 'c':
                                write_u8(f, vtx[l++].u8);
                                break;
                              case 's':
                              case 'h':
                                write_u16be(f, vtx[l++].u16);
                                break;
                              case 'l':
                                write_u32be(f, vtx[l++].u32);
                                break;
                              case 'f':
                                write_f32be(f, vtx[l++].f32);
                                break;
                            }
                        }
                    }
                }
            }
        }
        else
        {
            if (unknownblocktypes.find(mp.blocktype) == unknownblocktypes.end()) {
                unknownblocktypes[mp.blocktype] = unktypesfound;
                unktypesfound++;
            }

            for (uint j=0;j<mp.vertexcount;j++) {
                std::vector<MOD_Value> &vtx = mp.vertices[j];
                for (uint k=0;k<mp.blocksize;k++)
                {
                    write_u8(f, vtx[k++].u8);
                }
            }
        }
    }

/////////////// write faces data

    pos = ftell(f);
    if (pos != Mheader.facesoffset) {
        fseek(f,56,SEEK_SET);
        write_u32be(f,pos);
        fseek(f,pos,SEEK_SET);
    }

    for (uint i=0;i<faces.size();i++)
    {
        write_u16be(f,faces[i]);
    }

///////////////

    pos = ftell(f);

    if (pos != Mheader.unkoffset) {
        fseek(f,60,SEEK_SET);
        write_u32be(f,pos);
        fseek(f,pos,SEEK_SET);
    }

    write_u32be(f,0);
}

void ModelEditor::on_data_changed(QStandardItem */* itm */)
{
    Make_VBO_Data();
}

void ModelEditor::on_mesh_part_selectionChanged(QItemSelection selected, QItemSelection deselected)
{
    QModelIndexList indexes = selected.indexes();
    QModelIndexList indexes2 = deselected.indexes();
    QModelIndex index;

    foreach(index, indexes) {
        if (sel.find(index.row()) == sel.end()) { // not found enter
            sel[index.row()]= index.row();
        }
    }

    foreach(index, indexes2) {
        if (sel.find(index.row()) != sel.end()) { //  found delete
            sel.erase(index.row());
        }
    }

    QStandardItemModel* meshpartmodel = (QStandardItemModel*)((QTableView*)MeshPartstabs->widget(0))->model();

    selection.clear();
    selection.resize(meshpartmodel->rowCount(), 0);

    for (const auto &entry: sel) {
        selection[entry.first]=1;
    }

    emit this->newMeshPartSelection(selection);
}

//helper functions

quint8 ModelEditor::read_u8(char *buffer, uint &offset)
{
    quint8 val = buffer[offset];
    mProgressbar->setValue(offset += 1);
    return val;
}

quint16 ModelEditor::read_u16le(char *buffer, uint &offset)
{
    quint16 val = qFromLittleEndian<quint16>(buffer + offset);
    mProgressbar->setValue(offset += 2);
    return val;
}

quint16 ModelEditor::read_u16be(char *buffer, uint &offset)
{
    quint16 val = qFromBigEndian<quint16>(buffer + offset);
    mProgressbar->setValue(offset += 2);
    return val;
}

quint32 ModelEditor::read_u32le(char *buffer, uint &offset)
{
    quint32 val = qFromLittleEndian<quint32>(buffer + offset);
    mProgressbar->setValue(offset += 4);
    return val;
}

quint32 ModelEditor::read_u32be(char *buffer, uint &offset)
{
    quint32 val = qFromBigEndian<quint32>(buffer + offset);
    mProgressbar->setValue(offset += 4);
    return val;
}

float ModelEditor::read_f32le(char *buffer, uint &offset)
{
    float val = qFromLittleEndian<float>(buffer + offset);
    mProgressbar->setValue(offset += 4);
    return val;
}

float ModelEditor::read_f32be(char *buffer, uint &offset)
{
    float val = qFromBigEndian<float>(buffer + offset);
    mProgressbar->setValue(offset += 4);
    return val;
}

void ModelEditor::read_vec3le(char *buffer, uint &offset, Vector3 &vec)
{
    vec.x = read_f32le(buffer,offset);
    vec.y = read_f32le(buffer,offset);
    vec.z = read_f32le(buffer,offset);
}

void ModelEditor::read_vec3be(char *buffer, uint &offset, Vector3 &vec)
{
    vec.x = read_f32be(buffer,offset);
    vec.y = read_f32be(buffer,offset);
    vec.z = read_f32be(buffer,offset);
}

void ModelEditor::read_vec4le(char *buffer, uint &offset, Vector4 &vec)
{
    vec.x = read_f32le(buffer,offset);
    vec.y = read_f32le(buffer,offset);
    vec.z = read_f32le(buffer,offset);
    vec.w = read_f32le(buffer,offset);
}

void ModelEditor::read_vec4be(char *buffer, uint &offset, Vector4 &vec)
{
    vec.x = read_f32be(buffer,offset);
    vec.y = read_f32be(buffer,offset);
    vec.z = read_f32be(buffer,offset);
    vec.w = read_f32be(buffer,offset);
}

void ModelEditor::read_matrix_le(char *buffer, uint &offset, Matrix &mtx)
{
    for (uint i=0;i<16;i++)
    {
        mtx.m[i] = read_f32le(buffer,offset);
    }
}

void ModelEditor::read_matrix_be(char *buffer, uint &offset, Matrix &mtx)
{
    for (uint i=0;i<16;i++)
    {
        mtx.m[i] = read_f32be(buffer,offset);
    }
}

void ModelEditor::read_sphere_le(char *buffer, uint &offset, Sphere &sphere)
{
    read_vec3le(buffer,offset,sphere.pos);
    sphere.r = read_f32le(buffer,offset);
}

void ModelEditor::read_sphere_be(char *buffer, uint &offset, Sphere &sphere)
{
    read_vec3be(buffer,offset,sphere.pos);
    sphere.r = read_f32be(buffer,offset);
}

void ModelEditor::read_aabb_le(char *buffer, uint &offset, AABB &aabb)
{
    read_vec4le(buffer,offset,aabb.min);
    read_vec4le(buffer,offset,aabb.max);
}

void ModelEditor::read_aabb_be(char *buffer, uint &offset, AABB &aabb)
{
    read_vec4be(buffer,offset,aabb.min);
    read_vec4be(buffer,offset,aabb.max);
}

void ModelEditor::read_obb_le(char *buffer, uint &offset, OBB &obb)
{
    read_matrix_le(buffer,offset,obb.coord);
    read_vec4le(buffer,offset,obb.extent);
}

void ModelEditor::read_obb_be(char *buffer, uint &offset, OBB &obb)
{
    read_matrix_be(buffer,offset,obb.coord);
    read_vec4be(buffer,offset,obb.extent);
}

QByteArray ModelEditor::read_material(char *buffer, uint &offset)
{
    QByteArray val(buffer + offset, 128);
    mProgressbar->setValue(offset+=128);
    return val;
}

void ModelEditor::write_u16le(FILE *f, quint16 val)
{
    quint16 v = qToLittleEndian<quint16>(val);
    fwrite(&v, 2, 1, f);
}

void ModelEditor::write_u16be(FILE *f, quint16 val)
{
    quint16 v = qToBigEndian<quint16>(val);
    fwrite(&v, 2, 1, f);
}

void ModelEditor::write_u32le(FILE *f, quint32 val)
{
    quint32 v = qToLittleEndian<quint32>(val);
    fwrite(&v, 4, 1, f);
}

void ModelEditor::write_u32be(FILE *f, quint32 val)
{
    quint32 v = qToBigEndian<quint32>(val);
    fwrite(&v, 4, 1, f);
}

void ModelEditor::write_f32le(FILE *f, float val)
{
    quint32 v;
    qToLittleEndian<float>(val, &v);
    fwrite(&v, 4, 1, f);
}

void ModelEditor::write_f32be(FILE *f, float val)
{
    quint32 v;
    qToBigEndian<float>(val, &v);
    fwrite(&v, 4, 1, f);
}

void ModelEditor::write_vec3le(FILE *f, Vector3 &vec)
{
    write_f32le(f,vec.x);
    write_f32le(f,vec.y);
    write_f32le(f,vec.z);
}

void ModelEditor::write_vec3be(FILE *f, Vector3 &vec)
{
    write_f32be(f,vec.x);
    write_f32be(f,vec.y);
    write_f32be(f,vec.z);
}

void ModelEditor::write_vec4le(FILE *f, Vector4 &vec)
{
    write_f32le(f,vec.x);
    write_f32le(f,vec.y);
    write_f32le(f,vec.z);
    write_f32le(f,vec.w);
}

void ModelEditor::write_vec4be(FILE *f, Vector4 &vec)
{
    write_f32be(f,vec.x);
    write_f32be(f,vec.y);
    write_f32be(f,vec.z);
    write_f32be(f,vec.w);
}

void ModelEditor::write_matrix_le(FILE *f, Matrix &mtx)
{
    for (uint i=0;i<16;i++)
    {
        write_f32le(f,mtx.m[i]);
    }
}

void ModelEditor::write_matrix_be(FILE *f, Matrix &mtx)
{
    for (uint i=0;i<16;i++)
    {
        write_f32be(f,mtx.m[i]);
    }
}

void ModelEditor::write_sphere_le(FILE *f, Sphere &sphere)
{
    write_vec3le(f,sphere.pos);
    write_f32le(f,sphere.r);
}

void ModelEditor::write_sphere_be(FILE *f, Sphere &sphere)
{
    write_vec3be(f,sphere.pos);
    write_f32be(f,sphere.r);
}

void ModelEditor::write_aabb_le(FILE *f, AABB &aabb)
{
    write_vec4le(f,aabb.min);
    write_vec4le(f,aabb.max);
}

void ModelEditor::write_aabb_be(FILE *f, AABB &aabb)
{
    write_vec4be(f,aabb.min);
    write_vec4be(f,aabb.max);
}

void ModelEditor::write_obb_le(FILE *f, OBB &obb)
{
    write_matrix_le(f,obb.coord);
    write_vec4le(f,obb.extent);
}

void ModelEditor::write_obb_be(FILE *f, OBB &obb)
{
    write_matrix_be(f,obb.coord);
    write_vec4be(f,obb.extent);
}

void ModelEditor::write_material(FILE *f, QByteArray &mat)
{
    fwrite(mat.data(), 128, 1, f);
}

uint ModelEditor::as_uint(const float x)
{
      return *(uint*)&x;
}

float ModelEditor::as_float(const uint x)
{
      return *(float*)&x;
}

float ModelEditor::half_to_float(const ushort x)
{
    const uint e = (x&0x7C00)>>10; // exponent
    const uint m = (x&0x03FF)<<13; // mantissa
    const uint v = as_uint((float)m)>>23; // evil log2 bit hack to count leading zeros in denormalized format
    return as_float((x&0x8000)<<16 | (e!=0)*((e+112)<<23|m) | ((e==0)&(m!=0))*((v-37)<<23|((m<<(150-v))&0x007FE000))); // sign : normalized : denormalized
}

ushort ModelEditor::float_to_half(const float x)
{
    const uint b = as_uint(x)+0x00001000; // round-to-nearest-even: add last bit after truncated mantissa
    const uint e = (b&0x7F800000)>>23; // exponent
    const uint m = b&0x007FFFFF; // mantissa; in line below: 0x007FF000 = 0x00800000-0x00001000 = decimal indicator flag - initial rounding
    return (b&0x80000000)>>16 | (e>112)*((((e-112)<<10)&0x7C00)|m>>13) | ((e<113)&(e>101))*((((0x007FF000+m)>>(125-e))+1)>>1) | (e>143)*0x7FFF; // sign : normalized : denormalized : saturate
}

void ModelEditor::entervaluestogui()
{
    //bounding sphere
    bounding_spherex->setText(QString::number(Mheader.bsphere.pos.x,'f'));
    bounding_spherey->setText(QString::number(Mheader.bsphere.pos.y,'f'));
    bounding_spherez->setText(QString::number(Mheader.bsphere.pos.z,'f'));
    bounding_spherew->setText(QString::number(Mheader.bsphere.r,'f'));

    //bounding box min
    bounding_boxminx->setText(QString::number(Mheader.bbox.min.x,'f'));
    bounding_boxminy->setText(QString::number(Mheader.bbox.min.y,'f'));
    bounding_boxminz->setText(QString::number(Mheader.bbox.min.z,'f'));
    bounding_boxminw->setText(QString::number(Mheader.bbox.min.w,'f'));

    //bounding box max
    bounding_boxmaxx->setText(QString::number(Mheader.bbox.max.x,'f'));
    bounding_boxmaxy->setText(QString::number(Mheader.bbox.max.y,'f'));
    bounding_boxmaxz->setText(QString::number(Mheader.bbox.max.z,'f'));
    bounding_boxmaxw->setText(QString::number(Mheader.bbox.max.w,'f'));

    //model info
    h_unkn02->setText(QString::number(Mheader.info.middist));
    h_unkn03->setText(QString::number(Mheader.info.lowdist));
    h_unkn04->setText(QString::number(Mheader.info.lightgroup));
    h_unkn05->setText(QString::number(Mheader.info.memory));

    h_unkn06->setText(QString::number(Mheader.boundarycount));

    QTableView *areastv = new QTableView(this);
    QStandardItemModel *areasmodel = new QStandardItemModel(this);
    areastv->setModel(areasmodel);
    areastv->setWindowTitle(QString("Bone Data"));

    areasmodel->setHorizontalHeaderLabels(QStringList()
        << "Index" << "Parent" << "Bone Mirror" << "Unknown1" << "Child Distance?" << "Parent Distance" << "Position x" << "Position y" << "Position z"
        << "WTM 1" << "WTM 2"<< "WTM 3"<< "WTM 4"
        << "WTM 5" << "WTM 6"<< "WTM 7"<< "WTM 8"
        << "WTM 9" << "WTM 10"<< "WTM 11"<< "WTM 12"
        << "WTM 13" << "WTM 14"<< "WTM 15"<< "WTM 16"

        << "MTM 1" << "MTM 2"<< "MTM 3"<< "MTM 4"
        << "MTM 5" << "MTM 6"<< "MTM 7"<< "MTM 8"
        << "MTM 9" << "MTM 10"<< "MTM 11"<< "MTM 12"
        << "MTM 13" << "MTM 14"<< "MTM 15"<< "MTM 16"  ); //<< "Short 1??" << "Long 1??" << "Short 1.5??" << "Short 2"<< "Short 3??"<< "Short 4??"<< "Short 5??");

    //connect(areastv,SIGNAL(clicked(QModelIndex)),this,SLOT(on_areacell_clicked(QModelIndex)));

    // fill bone data

    bonetabs->clear();

    for (uint i=0;i<Mbones.boneinfo.size();i++) {
        MOD_Bone_Info &binf = Mbones.boneinfo[i];
        QList<QStandardItem*> row;

        QStandardItem *ffid = new QStandardItem(QString::number(binf.id));
        ffid->setToolTip("Index of the bone");
        row.append(ffid);

        QStandardItem *fparent = new QStandardItem(QString::number(binf.parent));
        fparent->setToolTip("Index of the parent bone");
        row.append(fparent);

        QStandardItem *fmirro = new QStandardItem(QString::number(binf.child));
        fmirro->setToolTip("Index of the bone mirror(opposite bone) or is it child?");
        row.append(fmirro);

        QStandardItem *funk = new QStandardItem(QString::number(binf.unk));
        funk->setToolTip("always 0x00 ?");
        row.append(funk);

        QStandardItem *funk1 = new QStandardItem(QString::number(binf.radius,'f'));
        funk1->setToolTip("child distance ?");
        row.append(funk1);

        QStandardItem *funk2 = new QStandardItem(QString::number(binf.length,'f'));
        funk2->setToolTip("Distance to the parent bone");
        row.append(funk2);

        QStandardItem *funk3 = new QStandardItem(QString::number(binf.offset.x,'f'));
        funk3->setToolTip("Position x relative to it's parent");
        row.append(funk3);

        QStandardItem *funk4 = new QStandardItem(QString::number(binf.offset.y,'f'));
        funk4->setToolTip("Position y relative to it's parent");
        row.append(funk4);

        QStandardItem *funk5 = new QStandardItem(QString::number(binf.offset.z,'f'));
        funk5->setToolTip("Position z relative to it's parent");
        row.append(funk5);

        for (uint j=0;j<16;j++) {
            QStandardItem *WTM01 = new QStandardItem(QString::number(Mbones.lmatrices.at(i).m[j],'f'));
            WTM01->setToolTip("World transform, skeleton forms with mesh");
            row.append(WTM01);
        }

        for (uint j=0;j<16;j++) {
            QStandardItem *MTM01 = new QStandardItem(QString::number(Mbones.amatrices.at(i).m[j],'f'));
            MTM01->setToolTip("Transform relative to it's parent");
            row.append(MTM01);
        }

        areasmodel->appendRow(row);
    }

    bonetabs->addTab(areastv,"Bones Information");

    // bone map table...

    bonemapmodel->clear();
    bonemapmodel->setHorizontalHeaderLabels(QStringList() <<"Slot ID");

    for (uint i=0;i<Mbones.remaptable.size();i++) {
        QList<QStandardItem*> row;
   /*
       QStandardItem *ffidx = new QStandardItem(QString::number(i));
       ffidx->setToolTip("Index of the array");
       row.append(ffidx);
   */
        QStandardItem *ffid = new QStandardItem(QString::number(Mbones.remaptable.at(i)));
        ffid->setToolTip("Bone lookup table used for animation");
        row.append(ffid);

        bonemapmodel->appendRow(row);
    }

    Groupstabs->clear();

    QTableView *groupstv = new QTableView(this);
    QStandardItemModel *groupsmodel = new QStandardItemModel(this);
    groupstv->setModel(groupsmodel);
    groupstv->setWindowTitle(QString("Group Data"));

    groupsmodel->setHorizontalHeaderLabels(QStringList()
        << "Group ID" << "padding?"<< "padding?"<< "padding?" << "Bounding Sphere Ceneter x"
        << "Bounding Sphere Ceneter y"
        << "Bounding Sphere Ceneter z"
        << "Bounding Sphere Radius"
    ); //<< "Short 1??" << "Long 1??" << "Short 1.5??" << "Short 2"<< "Short 3??"<< "Short 4??"<< "Short 5??");

    for (uint i=0;i<Mgroups.groupinfo.size();i++) {
        MOD_Group_Info &ginf = Mgroups.groupinfo[i];
        QList<QStandardItem*> row;

        QStandardItem *ffid = new QStandardItem(QString::number(ginf.id));
        ffid->setToolTip("Relates to the group ids in the mesh info");
        row.append(ffid);

        QStandardItem *funk = new QStandardItem(QString::number(ginf.h1,16));
        funk->setToolTip("0xCD used as a dummy byte");
        row.append(funk);
        QStandardItem *funkh2 = new QStandardItem(QString::number(ginf.h2,16));
        funkh2->setToolTip("0xCD used as a dummy byte");
        row.append(funkh2);
        QStandardItem *funkh3 = new QStandardItem(QString::number(ginf.h3,16));
        funkh3->setToolTip("0xCD used as a dummy byte");
        row.append(funkh3);

        QStandardItem *funk1 = new QStandardItem(QString::number(ginf.bsphere.pos.x,'f'));
        funk1->setToolTip("???bounding sphere for meshes within the group");
        row.append(funk1);

        QStandardItem *funk2 = new QStandardItem(QString::number(ginf.bsphere.pos.y,'f'));
        funk2->setToolTip("???bounding sphere for meshes within the group");
        row.append(funk2);

        QStandardItem *funk3 = new QStandardItem(QString::number(ginf.bsphere.pos.z,'f'));
        funk3->setToolTip("???bounding sphere for meshes within the group");
        row.append(funk3);

        QStandardItem *funk4 = new QStandardItem(QString::number(ginf.bsphere.r,'f'));
        funk4->setToolTip("???bounding sphere for meshes within the group");
        row.append(funk4);

        groupsmodel->appendRow(row);
    }

    Groupstabs->addTab(groupstv,"Group Information");

    Materialstabs->clear();

    QTableView *Materialstv = new QTableView(this);
    QStandardItemModel *Materialsmodel = new QStandardItemModel(this);
    Materialstv->setModel(Materialsmodel);
    Materialstv->setWindowTitle(QString("Material Data"));

    Materialsmodel->setHorizontalHeaderLabels(QStringList() << "ID Hash");
    // << "Short 1??" << "Long 1??" << "Short 1.5??" << "Short 2"<< "Short 3??"<< "Short 4??"<< "Short 5??");

    for (uint i=0;i<Mmats.name.size();i++) {
        QList<QStandardItem*> row;

        QStandardItem *funk = new QStandardItem(QString(Mmats.name.at(i)));
        funk->setToolTip("hash code gets looked up in MRL (128 characters MAXIMUM)");
        row.append(funk);

        Materialsmodel->appendRow(row);
    }

    Materialstabs->addTab(Materialstv,"Material Names");

    MeshPartstabs->clear();

    QTableView *meshpartstv = new QTableView(this);
    QStandardItemModel *meshpartsmodel = new QStandardItemModel(this);
    meshpartstv->setModel(meshpartsmodel);
    meshpartstv->setWindowTitle(QString("Mesh Part Information"));

    meshpartsmodel->setHorizontalHeaderLabels(QStringList()
        << "Mesh Type"
        << "Vertex Count"
        << "Group Index"
        << "Material Index"
        << "LOD Index"
        << "Class"
        << "Mesh Class"
        << "Block Size"
        << "Render Mode"
        << "Vertex Position"
        << "Vertex Offset"
        << "Block Type"
        << "Faces Position"
        << "Faces Count"
        << "Faces Offset"
        << "Bone ID Start"
        << "Remap Bone ID"
        << "Mesh Index"
        << "Min Index"
        << "Max Index"
        << "Hash"
    ); //<< "Short 1??" << "Long 1??" << "Short 1.5??" << "Short 2"<< "Short 3??"<< "Short 4??"<< "Short 5??");
    
    for (uint i=0;i<Mparts.parts.size();i++) {
        MOD_Mesh_Info &mp = Mparts.parts[i];
        QList<QStandardItem*> row;

        QStandardItem *ffid = new QStandardItem(QString::number(mp.drawmode));
        ffid->setToolTip("Mesh Type");
        row.append(ffid);

        QStandardItem *fvertc = new QStandardItem(QString::number(mp.vertexcount));
        fvertc->setToolTip("Number of Vertecies in this Mesh Part");
        row.append(fvertc);

        QStandardItem *fgidx = new QStandardItem(QString::number(mp.id));
        fgidx->setToolTip("Group Index that this Mesh part belongs to");
        row.append(fgidx);

        QStandardItem *fmidx = new QStandardItem(QString::number(mp.material));
        fmidx->setToolTip("Material Index of this Mesh part");
        row.append(fmidx);

        QStandardItem *fLOD = new QStandardItem(QString::number(mp.lod));
        fLOD->setToolTip("Level Of Detail Index:  0x00 = Null | 0x01 = HightPoly | 0x02 = MidPoly | 0x03 = LowPoly | 0xFF(255) = Shadow");
        row.append(fLOD);

        QStandardItem *fclass = new QStandardItem(QString::number(mp.weightcount));
        fclass->setToolTip("0x09 = Hidden? | 0x11(17) = Hands | 0x21(33) = Visible");
        row.append(fclass);

        QStandardItem *fmclass = new QStandardItem(QString::number(mp.alphapri));
        fmclass->setToolTip("??either body mesh, or hand mesh");
        row.append(fmclass);

        QStandardItem *fblocksize = new QStandardItem(QString::number(mp.blocksize));
        fblocksize->setToolTip("Size of VBO block / Vertex Stride");
        row.append(fblocksize);

        QStandardItem *frmode = new QStandardItem(QString::number(mp.topology));
        frmode->setToolTip("Render Mode, triangels, triangle strips, etc.");
        row.append(frmode);

        QStandardItem *fvertp = new QStandardItem(QString::number(mp.vertexsub));
        fvertp->setToolTip("Vertex Position in this mesh part auto generated");
        row.append(fvertp);

        QStandardItem *fvertoff = new QStandardItem(QString::number(mp.vertexoffset));
        fvertoff->setToolTip("Vertex Offset in this mesh part auto generated");
        row.append(fvertoff);

        QStandardItem *funk = new QStandardItem(QString::number(mp.blocktype,16));
        funk->setToolTip("This Is the VBO format / Block type Idenfitication, Determains how each vertex info is stored");
        row.append(funk);

        QStandardItem *ffacep = new QStandardItem(QString::number(mp.faceoffset));
        ffacep->setToolTip("Faces Offset in this mesh part auto generated");
        row.append(ffacep);

        QStandardItem *ffacec = new QStandardItem(QString::number(mp.facecount));
        ffacec->setToolTip("Faces Count in this mesh part auto generated");
        row.append(ffacec);

        QStandardItem *ffaceoff = new QStandardItem(QString::number(mp.facebase));
        ffaceoff->setToolTip("Faces Position? in this mesh part auto generated");
        row.append(ffaceoff);

        QStandardItem *fbsidx = new QStandardItem(QString::number(mp.envelope));
        fbsidx->setToolTip("Bone Id Start?");
        row.append(fbsidx);

        QStandardItem *fbrmidx = new QStandardItem(QString::number(mp.boneremapid));
        fbrmidx->setToolTip("Bone Remap table ID");
        row.append(fbrmidx);

        QStandardItem *fmeshidx= new QStandardItem(QString::number(mp.connectid));
        fmeshidx->setToolTip("Mesh Index?");
        row.append(fmeshidx);

        QStandardItem *fminidx= new QStandardItem(QString::number(mp.minindex));
        fminidx->setToolTip("Min Index?");
        row.append(fminidx);

        QStandardItem *fmaxidx= new QStandardItem(QString::number(mp.maxindex));
        fmaxidx->setToolTip("Max Index?");
        row.append(fmaxidx);

        QStandardItem *funkh2 = new QStandardItem(QString::number(mp.unklong,16));
        funkh2->setToolTip("?unique ID give to distinguish each mesh? ixion-saga leaves this data blank");
        row.append(funkh2);

        meshpartsmodel->appendRow(row);
   }

    MeshPartstabs->addTab(meshpartstv,"Mesh Part Information");

    connect(meshpartsmodel,SIGNAL(itemChanged(QStandardItem*)),this,SLOT(on_data_changed(QStandardItem*)));

    // connect(meshpartstv,SIGNAL(clicked(QModelIndex)),this,SLOT(on_cell_clicked(QModelIndex)));

    connect(meshpartstv->selectionModel(),SIGNAL(selectionChanged(QItemSelection,QItemSelection)),this,SLOT(on_mesh_part_selectionChanged(QItemSelection,QItemSelection)));

    Weightstabs->clear();

    QTableView *Weightstv = new QTableView(this);
    QStandardItemModel *Weightsmodel = new QStandardItemModel(this);
    Weightstv->setModel(Weightsmodel);
    Weightstv->setWindowTitle(QString("Weights Bounding"));

    Weightsmodel->setHorizontalHeaderLabels(QStringList()
        << "Bone Index"
        << "padding?"
        << "padding?"
        << "padding?"
        << "Bounding Sphere Ceneter x"
        << "Bounding Sphere Ceneter y"
        << "Bounding Sphere Ceneter z"
        << "Bounding Sphere Radius"

        << "Min x"
        << "Min y"
        << "Min z"
        << "Min w"

        << "Max x"
        << "Max y"
        << "Max z"
        << "Max w"

        << "Matrix 1" << "Matrix 2"<< "Matrix 3"<< "Matrix 4"
        << "Matrix 5" << "Matrix 6"<< "Matrix 7"<< "Matrix 8"
        << "Matrix 9" << "Matrix 10"<< "Matrix 11"<< "Matrix 12"
        << "Matrix 13" << "Matrix 14"<< "Matrix 15"<< "Matrix 16"

        << "Unknown x"
        << "Unknown y"
        << "Unknown z"
        << "Unknown w"
    );

    for (uint i=0;i<Mparts.chunks.size();i++) {
        MOD_Boundary_Info &chunk = Mparts.chunks[i];
        QList<QStandardItem*> row;

        QStandardItem *ffid = new QStandardItem(QString::number(chunk.bone));
        ffid->setToolTip("Bounding area for vertices effected by a boneid");
        row.append(ffid);

        QStandardItem *funk = new QStandardItem(QString::number(chunk.un2,16));
        funk->setToolTip("0xCD used as a dummy byte / 0x00 on ps3");
        row.append(funk);
        QStandardItem *funkh2 = new QStandardItem(QString::number(chunk.un3,16));
        funkh2->setToolTip("0xCD used as a dummy byte / 0x00 on ps3");
        row.append(funkh2);
        QStandardItem *funkh3 = new QStandardItem(QString::number(chunk.un4,16));
        funkh3->setToolTip("0xCD used as a dummy byte / 0x00 on ps3");
        row.append(funkh3);

        QStandardItem *funk1 = new QStandardItem(QString::number(chunk.sphere.pos.x,'f'));
        funk1->setToolTip("???bounding sphere for bone within the meshe");
        row.append(funk1);

        QStandardItem *funk2 = new QStandardItem(QString::number(chunk.sphere.pos.y,'f'));
        funk2->setToolTip("???bounding sphere for bone within the meshe");
        row.append(funk2);

        QStandardItem *funk3 = new QStandardItem(QString::number(chunk.sphere.pos.z,'f'));
        funk3->setToolTip("???bounding sphere for bone within the meshe");
        row.append(funk3);

        QStandardItem *funk4 = new QStandardItem(QString::number(chunk.sphere.r,'f'));
        funk4->setToolTip("???bounding sphere for bone within the meshe");
        row.append(funk4);

        QStandardItem *fminx = new QStandardItem(QString::number(chunk.aabb.min.x,'f'));
        fminx->setToolTip("???bounding box MIN for bone within the meshe");
        row.append(fminx);
        QStandardItem *fminy = new QStandardItem(QString::number(chunk.aabb.min.y,'f'));
        fminy->setToolTip("???bounding box MIN for bone within the meshe");
        row.append(fminy);
        QStandardItem *fminz = new QStandardItem(QString::number(chunk.aabb.min.z,'f'));
        fminz->setToolTip("???bounding box MIN for bone within the meshe");
        row.append(fminz);
        QStandardItem *fminw = new QStandardItem(QString::number(chunk.aabb.min.w,'f'));
        fminw->setToolTip("???bounding box MIN for bone within the meshe");
        row.append(fminw);

        QStandardItem *fmaxx = new QStandardItem(QString::number(chunk.aabb.max.x,'f'));
        fmaxx->setToolTip("???bounding box MAX for bone within the meshe");
        row.append(fmaxx);
        QStandardItem *fmaxy = new QStandardItem(QString::number(chunk.aabb.max.y,'f'));
        fmaxy->setToolTip("???bounding box MAX for bone within the meshe");
        row.append(fmaxy);
        QStandardItem *fmaxz = new QStandardItem(QString::number(chunk.aabb.max.z,'f'));
        fmaxz->setToolTip("???bounding box MAX for bone within the meshe");
        row.append(fmaxz);
        QStandardItem *fmaxw = new QStandardItem(QString::number(chunk.aabb.max.w,'f'));
        fmaxw->setToolTip("???bounding box MAX for bone within the meshe");
        row.append(fmaxw);

        QStandardItem *fmat01 = new QStandardItem(QString::number(chunk.obb.coord.m[0],'f'));
        fmat01->setToolTip("???relative to bone position");
        row.append(fmat01);
        QStandardItem *fmat02 = new QStandardItem(QString::number(chunk.obb.coord.m[1],'f'));
        fmat02->setToolTip("???relative to bone position");
        row.append(fmat02);
        QStandardItem *fmat03 = new QStandardItem(QString::number(chunk.obb.coord.m[2],'f'));
        fmat03->setToolTip("???relative to bone position");
        row.append(fmat03);
        QStandardItem *fmat04 = new QStandardItem(QString::number(chunk.obb.coord.m[3],'f'));
        fmat04->setToolTip("???relative to bone position");
        row.append(fmat04);
        QStandardItem *fmat05 = new QStandardItem(QString::number(chunk.obb.coord.m[4],'f'));
        fmat05->setToolTip("???relative to bone position");
        row.append(fmat05);
        QStandardItem *fmat06 = new QStandardItem(QString::number(chunk.obb.coord.m[5],'f'));
        fmat06->setToolTip("???relative to bone position");
        row.append(fmat06);
        QStandardItem *fmat07 = new QStandardItem(QString::number(chunk.obb.coord.m[6],'f'));
        fmat07->setToolTip("???relative to bone position");
        row.append(fmat07);
        QStandardItem *fmat08 = new QStandardItem(QString::number(chunk.obb.coord.m[7],'f'));
        fmat08->setToolTip("???relative to bone position");
        row.append(fmat08);
        QStandardItem *fmat09 = new QStandardItem(QString::number(chunk.obb.coord.m[8],'f'));
        fmat09->setToolTip("???relative to bone position");
        row.append(fmat09);
        QStandardItem *fmat10 = new QStandardItem(QString::number(chunk.obb.coord.m[9],'f'));
        fmat10->setToolTip("???relative to bone position");
        row.append(fmat10);
        QStandardItem *fmat11 = new QStandardItem(QString::number(chunk.obb.coord.m[10],'f'));
        fmat11->setToolTip("???relative to bone position");
        row.append(fmat11);
        QStandardItem *fmat12 = new QStandardItem(QString::number(chunk.obb.coord.m[11],'f'));
        fmat12->setToolTip("???relative to bone position");
        row.append(fmat12);
        QStandardItem *fmat13 = new QStandardItem(QString::number(chunk.obb.coord.m[12],'f'));
        fmat13->setToolTip("???relative to bone position");
        row.append(fmat13);
        QStandardItem *fmat14 = new QStandardItem(QString::number(chunk.obb.coord.m[13],'f'));
        fmat14->setToolTip("???relative to bone position");
        row.append(fmat14);
        QStandardItem *fmat15 = new QStandardItem(QString::number(chunk.obb.coord.m[14],'f'));
        fmat15->setToolTip("???relative to bone position");
        row.append(fmat15);
        QStandardItem *fmat16 = new QStandardItem(QString::number(chunk.obb.coord.m[15],'f'));
        fmat16->setToolTip("???relative to bone position");
        row.append(fmat16);

        QStandardItem *funkx = new QStandardItem(QString::number(chunk.obb.extent.x,'f'));
        funkx->setToolTip("?unknown x");
        row.append(funkx);
        QStandardItem *funky = new QStandardItem(QString::number(chunk.obb.extent.y,'f'));
        funky->setToolTip("?unknown y");
        row.append(funky);
        QStandardItem *funkz = new QStandardItem(QString::number(chunk.obb.extent.z,'f'));
        funkz->setToolTip("?unknown z");
        row.append(funkz);
        QStandardItem *funkw = new QStandardItem(QString::number(chunk.obb.extent.w,'f'));
        funkw->setToolTip("?unknown w");
        row.append(funkw);

        Weightsmodel->appendRow(row);
    }

    Weightstabs->addTab(Weightstv,"Weights Bounding");

    MeshDatatabs->clear();

/////////////////  writing vbo permesh part data
//std::vector<VertexData> meshdat;

    QMatrix4x4 mtx;

    if (Mheader.bonecount)
        mtx = QMatrix4x4(Mbones.amatrices[0].m) *
            QMatrix4x4(Mbones.lmatrices[0].m);

    for (uint i=0;i<Mparts.parts.size();i++) {
        MOD_Mesh_Info &mp = Mparts.parts[i];

        //spread sheet stuff memory leak fix later<
        QTableView*  tv = new QTableView;
        QStandardItemModel*  model = new QStandardItemModel;
        tv->setModel(model);
        tv->setWindowTitle(QString("Vertecies Mesh Part: ").append(QString::number(i)));
        model->setHorizontalHeaderLabels(QStringList()
            << "Position X" 
            << "Position Y"
            << "Position Z"
            << "Normal X"
            << "Normal Y"
            << "Normal Z"
            << "Texture U"
            << "Texture V"
        );

        for (uint j=0;j<mp.vertices.size();j++) {
            std::vector<MOD_Value> &vtx = mp.vertices[j];

            QVector3D vert, norm;
            float txu = 0.0f, txv = 0.0f;

            switch (mp.blocktype) {
              case 0x0CB68015:
                vert.setX(vtx[0].s16);
                vert.setY(vtx[1].s16);
                vert.setZ(vtx[2].s16);
                vert /= 32767;
                break;

              case 0x14D40020:
                vert.setX(vtx[0].s16);
                vert.setY(vtx[1].s16);
                vert.setZ(vtx[2].s16);
                vert /= 32767;
                norm.setX(vtx[4].u8-127);
                norm.setY(vtx[5].u8-127);
                norm.setZ(vtx[6].u8-127);
                norm /= 127;
                txu = half_to_float(vtx[16].u16);
                txv = half_to_float(vtx[17].u16);
                break;

              case 0x5E7F202C:
                vert.setX(vtx[0].f32);
                vert.setY(vtx[1].f32);
                vert.setZ(vtx[2].f32);
                norm.setX(vtx[3].u8-127);
                norm.setY(vtx[4].u8-127);
                norm.setZ(vtx[5].u8-127);
                norm /= 127;
                txu = half_to_float(vtx[11].u16);
                txv = half_to_float(vtx[12].u16);
                break;

              case 0xA320C016:
                vert.setX(vtx[0].s16);
                vert.setY(vtx[1].s16);
                vert.setZ(vtx[2].s16);
                vert /= 32767;
                norm.setX(vtx[12].u8-127);
                norm.setY(vtx[13].u8-127);
                norm.setZ(vtx[14].u8-127);
                norm /= 127;
                break;

              case 0xA7D7D036:
                vert.setX(vtx[0].f32);
                vert.setY(vtx[1].f32);
                vert.setZ(vtx[2].f32);
                norm.setX(vtx[3].u8-127);
                norm.setY(vtx[4].u8-127);
                norm.setZ(vtx[5].u8-127);
                norm /= 127;
                txu = half_to_float(vtx[7].u16);
                txv = half_to_float(vtx[8].u16);
                break;

              case 0xA8FAB018:
                vert.setX(vtx[0].s16);
                vert.setY(vtx[1].s16);
                vert.setZ(vtx[2].s16);
                vert /= 32767;
                norm.setX(vtx[4].u8-127);
                norm.setY(vtx[5].u8-127);
                norm.setZ(vtx[6].u8-127);
                norm /= 127;
                txu = half_to_float(vtx[12].u16);
                txv = half_to_float(vtx[13].u16);
                break;

              case 0xB0983013:
                vert.setX(vtx[0].s16);
                vert.setY(vtx[1].s16);
                vert.setZ(vtx[2].s16);
                vert /= 32767;
                norm.setX(vtx[4].u8-127);
                norm.setY(vtx[5].u8-127);
                norm.setZ(vtx[6].u8-127);
                norm /= 127;
                break;

              case 0xBB424024:
                vert.setX(vtx[0].s16);
                vert.setY(vtx[1].s16);
                vert.setZ(vtx[2].s16);
                vert /= 32767;
                norm.setX(vtx[4].u8-127);
                norm.setY(vtx[5].u8-127);
                norm.setZ(vtx[6].u8-127);
                norm /= 127;
                txu = half_to_float(vtx[20].u16);
                txv = half_to_float(vtx[21].u16);
                break;

              case 0xC31F201C:
                vert.setX(vtx[0].s16);
                vert.setY(vtx[1].s16);
                vert.setZ(vtx[2].s16);
                vert /= 32767;
                norm.setX(vtx[4].u8-127);
                norm.setY(vtx[5].u8-127);
                norm.setZ(vtx[6].u8-127);
                norm /= 127;
                txu = half_to_float(vtx[12].u16);
                txv = half_to_float(vtx[13].u16);
                break;

              case 0xD8297028:
                vert.setX(vtx[0].f32);
                vert.setY(vtx[1].f32);
                vert.setZ(vtx[2].f32);
                norm.setX(vtx[3].u8-127);
                norm.setY(vtx[4].u8-127);
                norm.setZ(vtx[5].u8-127);
                norm /= 127;
                txu = half_to_float(vtx[7].u16);
                txv = half_to_float(vtx[8].u16);
                break;

              case 0xDB7DA014:
                vert.setX(vtx[0].s16);
                vert.setY(vtx[1].s16);
                vert.setZ(vtx[2].s16);
                vert /= 32767;
                norm.setX(vtx[4].u8-127);
                norm.setY(vtx[5].u8-127);
                norm.setZ(vtx[6].u8-127);
                norm /= 127;
                break;
            }

            if (Mheader.bonecount)
                vert = (QVector4D(vert, 1.0f) * mtx).toVector3D();

            QList<QStandardItem*> row;

            QStandardItem *itmvx = new QStandardItem(QString::number(vert.x(),'f'));
            itmvx->setToolTip("Position X");
            row.append(itmvx);
            QStandardItem *itmvy = new QStandardItem(QString::number(vert.y(),'f'));
            itmvy->setToolTip("Position Y");
            row.append(itmvy);
            QStandardItem *itmvz = new QStandardItem(QString::number(vert.z(),'f'));
            itmvz->setToolTip("Position Z");
            row.append(itmvz);
            QStandardItem *itmnx = new QStandardItem(QString::number(norm.x(),'f'));
            itmnx->setToolTip("Normal X");
            row.append(itmnx);
            QStandardItem *itmny = new QStandardItem(QString::number(norm.y(),'f'));
            itmny->setToolTip("Normal Y");
            row.append(itmny);
            QStandardItem *itmnz = new QStandardItem(QString::number(norm.z(),'f'));
            itmnz->setToolTip("Normal Z");
            row.append(itmnz);
            QStandardItem *itmtxu = new QStandardItem(QString::number(txu,'f'));
            itmtxu->setToolTip("Texture U");
            row.append(itmtxu);
            QStandardItem *itmtxv = new QStandardItem(QString::number(txv,'f'));
            itmtxv->setToolTip("Texture V");
            row.append(itmtxv);
            model->appendRow(row);
        }

        // add tv
        MeshDatatabs->addTab(tv,QString("Vertecies Mesh Part: ").append(QString::number(i)));
        tv->resizeColumnsToContents();

        connect(model,SIGNAL(itemChanged(QStandardItem*)),this,SLOT(on_data_changed(QStandardItem*)));
    }

    // start writing faces

    // std::vector< unsigned int > faces;
    // unsigned int meshpartcount = 0;
    for (uint i=0;i<Mparts.parts.size();i++) {
        MOD_Mesh_Info &mp = Mparts.parts[i];
        //spread sheet stuff memory leak fix later<
        QTableView*  tv = new QTableView;
        QStandardItemModel*  model = new QStandardItemModel;
        tv->setModel(model);
        tv->setWindowTitle(QString("Faces Mesh Part: ").append(QString::number(i)));

        QList<QStandardItem*> strip;
        quint16 last = 0;

        for (uint j=0;j<mp.faces.size();j++)
        {
            if (mp.faces[j] == 0xFFFF)
            {
                if (strip.size() & 1)
                    strip.append(new QStandardItem(QString::number(last)));
                strip.append(new QStandardItem(QString::number(last)));
                last = mp.faces[j+1] - mp.minindex;
                strip.append(new QStandardItem(QString::number(last)));
            }
            else
            {
                last = mp.faces[j] - mp.minindex;
                strip.append(new QStandardItem(QString::number(last)));
            }
        }
        model->appendRow(strip);

        //meshpartcount += mp.vertexcount.toHex().toUInt(&ok,16);
        // add tv
        MeshDatatabs->addTab(tv,QString("Faces Mesh Part: ").append(QString::number(i)));
        tv->resizeColumnsToContents();
        connect(model,SIGNAL(itemChanged(QStandardItem*)),this,SLOT(on_data_changed(QStandardItem*)));
    }

    areastv->resizeColumnsToContents();
    bonemaptv->resizeColumnsToContents();
    groupstv->resizeColumnsToContents();
    Materialstv->resizeColumnsToContents();
    meshpartstv->resizeColumnsToContents();
    Weightstv->resizeColumnsToContents();

    Make_VBO_Data();
}

void ModelEditor::Make_VBO_Data()
{
    std::vector<int> rendermodes;
    std::vector< std::vector< VertexData > > vertices;
    std::vector< std::vector<unsigned int> > faces;

    // mesh part info

    QStandardItemModel* meshpartmodel = (QStandardItemModel*)((QTableView*)MeshPartstabs->widget(0))->model();
    int rows = meshpartmodel->rowCount();

    float scale = 100.0f;
    if (Mheader.bsphere.r > 1.0f) scale /= Mheader.bsphere.r;

    for (int i =  0; i<rows; i++) {  // for each mesh part

        rendermodes.push_back(meshpartmodel->index(i,8).data().toInt()); // set render mode
        // fill mesh part vertcies and faces from ui
        std::vector< VertexData > vert;
        QStandardItemModel* vertmodel = (QStandardItemModel*)((QTableView*)MeshDatatabs->widget(i))->model();
        int vertcount = vertmodel->rowCount();
        for (int j = 0; j<vertcount;j++) {
            VertexData vertex = {
                QVector4D(
                    (vertmodel->index(j,0).data().toFloat() - Mheader.bsphere.pos.x) * scale,
                    (vertmodel->index(j,1).data().toFloat() - Mheader.bsphere.pos.y) * scale,
                    (vertmodel->index(j,2).data().toFloat() - Mheader.bsphere.pos.z) * scale,
                    0.0f),
                QVector4D(vertmodel->index(j,3).data().toFloat(),
                    vertmodel->index(j,4).data().toFloat(),
                    vertmodel->index(j,5).data().toFloat(),
                    0),
                QVector4D(vertmodel->index(j,6).data().toFloat(),
                    vertmodel->index(j,7).data().toFloat(),
                    0.0,i)
            };
            vert.push_back(vertex);
        }

        std::vector<unsigned int> face;
        QStandardItemModel* facemodel = (QStandardItemModel*)((QTableView*)MeshDatatabs->widget(rows+i))->model();
        int facecount = facemodel->rowCount();
        int colcount = facemodel->columnCount();
        for (int j = 0; j<facecount;j++) {
            for (int k = 0; k<colcount;k++) {
                if (!facemodel->index(j,k).data().isNull()) {
                    face.push_back(facemodel->index(j,k).data().toUInt());
                    // qDebug() << "j " << j << "k " << k  << "val " << facemodel->index(j,k).data().toUInt();
                }
                else {
                    k = colcount; // jump.
                    continue; // to optimize?
                }
            }
        }

        faces.push_back(face);
        vertices.push_back(vert);
    }

    emit this->NewMeshData(rendermodes,vertices,faces);
}
