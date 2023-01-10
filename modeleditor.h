#ifndef MODELEDITOR_H
#define MODELEDITOR_H

#include <QWidget>
#include <QAction>
#include <QButtonGroup>
#include <QComboBox>
#include <QHBoxLayout>
#include <QGridLayout>
#include <QHeaderView>
#include <QLabel>
#include <QMenuBar>
#include <QToolBar>
#include <QStatusBar>
#include <QProgressBar>
#include <QTabWidget>
#include <QToolBar>
#include <QToolTip>
#include <QVBoxLayout>
#include <QVariant>
#include <QScrollArea>
// spread sheet stuff
#include <QList>
#include <QTableView>
#include <QStandardItemModel>
#include <QStandardItem>
// spread sheet stuff
#include <QGroupBox>

#include <QPushButton>
#include <QRadioButton>
#include <QSpinBox>
#include <QLineEdit>

#include <QFileDialog>
#include <QMessageBox>
#include <QMatrix4x4>
#include <vector>
#include <map>

//image stuff
#include <QColor>

// new stuff
#include <QtEndian>

#include <QMainWindow>
#include "renderer/mainwidget.h"

class ModelEditor : public QMainWindow
{
    Q_OBJECT

public:
    explicit ModelEditor(QMainWindow *parent = 0);
    ~ModelEditor();

private:
    QStatusBar * mStatusbar;
    QProgressBar * mProgressbar;
    QMenu *viewMenu;

    std::map<quint32,const char*> blocktype;
    std::map<quint32,int> unknownblocktypes;
    int unktypesfound;

    QGroupBox *groupBox;
    QWidget *layoutWidget;
    QHBoxLayout *verticalLayout;
    QVBoxLayout *outerLayout;
    QVBoxLayout *insideboxLayout;

    QRadioButton *rdoSingle;
    QRadioButton *rdoPooled;
    QRadioButton *rdoTheaded;
    QLineEdit *spinBox;
    QLabel *label;
    QLabel *label_3;
    QLabel *difflabel;
    QLabel *speclabel;
    QLabel *normlabel;
    QLabel *litelabel;

    QScrollArea *diffscroll;
    QScrollArea *specscroll;
    QScrollArea *normscroll;
    QScrollArea *litescroll;

    QComboBox *cmbAddress;
    QLineEdit *spinboxIdle;

    QLabel *label_meshcount;
    QLineEdit *meshcount;
    QLabel *label_materialcount;
    QLineEdit *materialcount;
    QLabel *label_vertexcount;
    QLineEdit *vertexcount;

    QLabel *label_facecount;
    QLineEdit *facecount;
    QLabel *label_vertexids;
    QLineEdit *vertexids;
    QLabel *label_vertexbuffersize;
    QLineEdit *vertexbuffersize;

    QLabel *label_secondbuffersize;
    QLineEdit *secondbuffersize;
    QLabel *label_groupcount;
    QLineEdit *groupcount;
    QLabel *label_bonesoffset;
    QLineEdit *bonesoffset;

    QLabel *label_groupoffset;
    QLineEdit *groupoffset;
    QLabel *label_textureoffset;
    QLineEdit *textureoffset;
    QLabel *label_meshoffset;
    QLineEdit *meshoffset;

    QLabel *label_vertexoffset;
    QLineEdit *vertexoffset;
    QLabel *label_facesoffset;
    QLineEdit *facesoffset;
    QLabel *label_unkoffset;
    QLineEdit *unkoffset;

    QLabel* label_bounding_sphere;
    QLineEdit* bounding_spherex;
    QLineEdit* bounding_spherey;
    QLineEdit* bounding_spherez;
    QLineEdit* bounding_spherew;

    QHBoxLayout* boundingspherehLayout;

    QLabel* label_bounding_boxmin;
    QLineEdit* bounding_boxminx;
    QLineEdit* bounding_boxminy;
    QLineEdit* bounding_boxminz;
    QLineEdit* bounding_boxminw;

    QHBoxLayout* boundingboxminhLayout;

    QLabel* label_bounding_boxmax;
    QLineEdit* bounding_boxmaxx;
    QLineEdit* bounding_boxmaxy;
    QLineEdit* bounding_boxmaxz;
    QLineEdit* bounding_boxmaxw;

    QHBoxLayout* boundingboxmaxhLayout;

    QLabel* label_h_unkn02;
    QLineEdit* h_unkn02;

    QLabel* label_h_unkn03;
    QLineEdit* h_unkn03;

    QLabel* label_h_unkn04;
    QLineEdit* h_unkn04;

    QLabel* label_h_unkn05;
    QLineEdit* h_unkn05;

    QLabel* label_h_unkn06;
    QLineEdit* h_unkn06;

    QLabel *label_4;
    QWidget *layoutWidget1;
    QHBoxLayout *horizontalLayout_0;
    QHBoxLayout *horizontalLayout_1;
    QHBoxLayout *horizontalLayout_2;
    QHBoxLayout *horizontalLayout_3;
    QHBoxLayout *horizontalLayout_4;
    QHBoxLayout *horizontalLayout_5;
    QHBoxLayout *horizontalLayout_6;
    QHBoxLayout *horizontalLayout_7;
    QPushButton *btnListen;
    QPushButton *btnClose;

    QTabWidget * bonetabs;

    QTableView*  bonemaptv;
    QStandardItemModel*  bonemapmodel;

    QTabWidget *Groupstabs;

    QTabWidget *Materialstabs;

    QTabWidget *MeshPartstabs;

    QTabWidget *Texturestabs;

    QTabWidget *MeshDatatabs;

    QTabWidget *Weightstabs;

    struct Vector3
    {
        float x,y,z;
    };

    struct Vector4
    {
        float x,y,z,w;
    };

    struct Matrix
    {
        float m[16];
    };

    struct Sphere
    {
        Vector3 pos;
        float r;
    };

    struct AABB
    {
        Vector4 min;
        Vector4 max;
    };

    struct OBB
    {
        Matrix coord;
        Vector4 extent;
    };

    struct MOD_Header
    {
        quint32 magic;
        quint16 version;
        quint16 bonecount;
        quint16 meshcount;
        quint16 materialcount;
        quint32 vertexcount;
        quint32 facecount;
        quint32 vertexids;
        quint32 vertexbuffersize;
        quint32 secondbuffersize;
        quint32 groupcount;
        quint32 bonesoffset;
        quint32 groupoffset;
        quint32 textureoffset;
        quint32 meshoffset;
        quint32 vertexoffset;
        quint32 facesoffset;
        quint32 unkoffset;
        Sphere bsphere;
        AABB bbox;
        struct {
            qint32 middist;
            qint32 lowdist;
            quint32 lightgroup;
            quint16 memory;
            quint16 reserved;
        } info;
        quint32 boundarycount;
    } Mheader;

    struct MOD_Bone_Info
    {
        quint16 id;
        quint8 parent;
        quint8 child;
        quint8 unk;
        float radius;
        float length;
        Vector3 offset;
    };

    struct MOD_bones
    {
        std::vector<MOD_Bone_Info> boneinfo;
        std::vector<Matrix> lmatrices;
        std::vector<Matrix> amatrices;
        std::vector<qint8> remaptable;
    } Mbones;

    struct MOD_Group_Info
    {
        quint32 id;
        quint32 h1;
        quint32 h2;
        quint32 h3;
        Sphere bsphere;
    };

    struct MOD_Groups
    {
        std::vector<MOD_Group_Info> groupinfo;
    } Mgroups;

    struct MOD_Materials
    {
        std::vector<QByteArray> name;
    } Mmats;

    union MOD_Value
    {
        quint32 u32;
        quint16 u16;
        quint8 u8;
        quint32 s32;
        qint16 s16;
        qint8 s8;
        float f32;
    };

    struct MOD_Mesh_Info
    {
        quint16 drawmode;
        quint16 vertexcount;

        quint16 id;        // 12 bits
        quint16 material;  // 12 bits
        quint8 lod;        //  8 bits

        quint8 disp;         // 1 bit
        quint8 shape;        // 1 bit
        quint8 sort;         // 1 bit
        quint8 weightcount;  // 5 bits
        quint8 alphapri;     // 8 bits
        quint8 blocksize;    // 8 bits
        quint8 topology;     // 6 bits
        quint8 binormalflip; // 1 bit
        quint8 bridge;       // 1 bit

        quint32 vertexsub;
        quint32 vertexoffset;
        quint32 blocktype;
        quint32 faceoffset;
        quint32 facecount;
        quint32 facebase;
        quint8 envelope;
        quint8 boneremapid;
        quint16 connectid;
        quint16 minindex;
        quint16 maxindex;
        quint32 unklong;

        std::vector< std::vector<MOD_Value> > vertices;
        std::vector<quint16> faces;
        quint32 newfaceoffset;
        quint32 newfacecount;
    };

    struct MOD_Boundary_Info
    {
        quint32 bone;
        quint32 un2; // on pc dd;da it is "CDCDCDCD" on ps3 it's all 0's
        quint32 un3; // on pc dd;da it is "CDCDCDCD" on ps3 it's all 0's
        quint32 un4; // on pc dd;da it is "CDCDCDCD" on ps3 it's all 0's
        Sphere sphere;
        AABB aabb;
        OBB obb;
    };

    struct MOD_Mesh_Parts
    {
        std::vector<MOD_Mesh_Info> parts;
        std::vector<MOD_Boundary_Info> chunks;
    } Mparts;

    uint as_uint(const float x);
    float as_float(const uint x);
    float half_to_float(const ushort x);
    ushort float_to_half(const float x);
    void entervaluestogui();
    void Make_VBO_Data();
    void open_file(QString fileName);
    void read_file_le(char* buffer);
    void read_file_be(char* buffer);
    void write_file_le(FILE *f, uint version);
    void write_file_be(FILE *f, uint version);

    quint8 read_u8(char *buffer, uint &offset);
    quint16 read_u16le(char *buffer, uint &offset);
    quint16 read_u16be(char *buffer, uint &offset);
    quint32 read_u32le(char *buffer, uint &offset);
    quint32 read_u32be(char *buffer, uint &offset);
    float read_f32le(char *buffer, uint &offset);
    float read_f32be(char *buffer, uint &offset);
    void read_vec3le(char *buffer, uint &offset, Vector3 &vec);
    void read_vec3be(char *buffer, uint &offset, Vector3 &vec);
    void read_vec4le(char *buffer, uint &offset, Vector4 &vec);
    void read_vec4be(char *buffer, uint &offset, Vector4 &vec);
    void read_matrix_le(char *buffer, uint &offset, Matrix &mtx);
    void read_matrix_be(char *buffer, uint &offset, Matrix &mtx);
    void read_sphere_le(char *buffer, uint &offset, Sphere &sphere);
    void read_sphere_be(char *buffer, uint &offset, Sphere &sphere);
    void read_aabb_le(char *buffer, uint &offset, AABB &aabb);
    void read_aabb_be(char *buffer, uint &offset, AABB &aabb);
    void read_obb_le(char *buffer, uint &offset, OBB &obb);
    void read_obb_be(char *buffer, uint &offset, OBB &obb);
    QByteArray read_material(char *buffer, uint &offset);

    static void write_u8(FILE *f, quint8 val) { fputc(val,f); }
    static void write_u16le(FILE *f, quint16 val);
    static void write_u16be(FILE *f, quint16 val);
    static void write_u32le(FILE *f, quint32 val);
    static void write_u32be(FILE *f, quint32 val);
    static void write_f32le(FILE *f, float val);
    static void write_f32be(FILE *f, float val);
    static void write_vec3le(FILE *f, Vector3 &vec);
    static void write_vec3be(FILE *f, Vector3 &vec);
    static void write_vec4le(FILE *f, Vector4 &vec);
    static void write_vec4be(FILE *f, Vector4 &vec);
    static void write_matrix_le(FILE *f, Matrix &mtx);
    static void write_matrix_be(FILE *f, Matrix &mtx);
    static void write_sphere_le(FILE *f, Sphere &sphere);
    static void write_sphere_be(FILE *f, Sphere &sphere);
    static void write_aabb_le(FILE *f, AABB &aabb);
    static void write_aabb_be(FILE *f, AABB &aabb);
    static void write_obb_le(FILE *f, OBB &obb);
    static void write_obb_be(FILE *f, OBB &obb);
    static void write_material(FILE *f, QByteArray &mat);

    qint32 read_s8(char *buffer, uint &offset) { return read_u8(buffer, offset); }
    qint16 read_s16le(char *buffer, uint &offset) { return read_u16le(buffer, offset); }
    qint16 read_s16be(char *buffer, uint &offset) { return read_u16be(buffer, offset); }
    qint32 read_s32le(char *buffer, uint &offset) { return read_u32le(buffer, offset); }
    qint32 read_s32be(char *buffer, uint &offset) { return read_u32be(buffer, offset); }
    static void write_s8(FILE *f, quint32 v) { write_u8(f, v); }
    static void write_s16le(FILE *f, quint16 v) { write_u16le(f, v); }
    static void write_s16be(FILE *f, quint16 v) { write_u16be(f, v); }
    static void write_s32le(FILE *f, quint32 v) { write_u32le(f, v); }
    static void write_s32be(FILE *f, quint32 v) { write_u32be(f, v); }

    std::vector<int> selection;
    std::map<int,int> sel;

signals:
    void newTextures(QString fileName);
    // void newMesh(MOD_Mesh_Parts &mesh, std::vector<Matrix> &lmatrices, std::vector<Matrix> &amatrices);//decipated
    void newDAPCMesh(MOD_Mesh_Parts &mesh); //decipated
    void NewMeshData(std::vector<int> &rmodes, std::vector< std::vector< VertexData > > &arrverts, std::vector< std::vector<unsigned int> > &arrfaces);
    void newMeshPartSelection(std::vector<int> &selected);

public slots:

private slots:
    void about();

    void on_Open_clicked();
    void on_File_changed(QString fileName);
    void on_Save_clicked();
    // face / mesh part info / vertex
    void on_data_changed(QStandardItem* itm);
    // mesh part info selection
    void on_mesh_part_selectionChanged(QItemSelection selected,QItemSelection deselected);
};

#endif // MODELEDITOR_H
