#include "pywindow.h"
#include <QApplication>
//#include <QFileInfo>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    a.addLibraryPath(a.applicationDirPath()+"/plugins");

    PyWindow w;
    w.show();

    return a.exec();
}
