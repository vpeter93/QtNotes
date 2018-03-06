#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    QCoreApplication::setOrganizationDomain("OrgDomain");
    QCoreApplication::setOrganizationName("MyCompany");
    QCoreApplication::setApplicationName("MyApp");
    QCoreApplication::setApplicationVersion("1.0.0");
    w.readSettings();
    w.loadNotes();
    w.show();

    return a.exec();
}
