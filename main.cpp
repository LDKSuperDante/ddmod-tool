#include "modeleditor.h"
#include <QApplication>
#include <QFile>

int main(int argc, char *argv[])
{
 //Q_INIT_RESOURCE(ddons);
    QApplication a(argc, argv);


// set font
    QFont font;
    font.setFamily("VL PGothic");
    a.setFont(font);
// set style sheet
    QFile file(":/resources/styles/darkgold.qss");
    if(file.open(QFile::ReadOnly)== true){
        QString StyleSheet(file.readAll());
        a.setStyleSheet(StyleSheet);
    }
    else{
        printf("failed to open style sheet");
    }
a.setApplicationName("Dragon's Dogma Mod Tool");
a.setApplicationDisplayName("Dragon's Dogma Mod Tool");
    //Dialog w;
    ModelEditor m;

  //  w.show();
    m.show();


    return a.exec();
}
