#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFile>
#include <QDebug>
#include <QSettings>
#include <QColorDialog>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    QColor backgroundColor;
public:
    explicit MainWindow(QWidget *parent = 0);
    void loadNotes();
    void saveNotes();
    void loadConfig();
    void saveConfig();
    void closeEvent(QCloseEvent *event);
    void readSettings();

    ~MainWindow();

private:
    Ui::MainWindow *ui;
private slots:
    void h2ActionSlot();
    void lineThroutActionSlot();
    void boldActionSlot();
    void normalActionSlot();
    void colorChooseActionSlot();
};

#endif // MAINWINDOW_H
