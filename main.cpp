#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    MainWindow w;
    QCoreApplication::setOrganizationDomain("hu");
    QCoreApplication::setOrganizationName("varga");
    QCoreApplication::setApplicationName("QtNotes");
    QCoreApplication::setApplicationVersion("1.0.1");
    w.readSettings();
    w.loadNotes();
    w.loadConfig();
    w.show();
    return a.exec();
}
