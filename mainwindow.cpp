#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    saveNotes();
    delete ui;
}
void MainWindow::closeEvent(QCloseEvent *event)
{

    QSettings settings("MyCompany", "MyApp");
    settings.setValue("geometry", saveGeometry());
    settings.setValue("windowState", saveState());
    QMainWindow::closeEvent(event);
}
void MainWindow::readSettings()
{
    QSettings settings("MyCompany", "MyApp");
    restoreGeometry(settings.value("geometry").toByteArray());
    restoreState(settings.value("windowState").toByteArray());
    this->setGeometry(this->geometry());
}

void MainWindow::loadNotes()
{
    QFile file("1");

    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        return;
    }
    QTextStream in(&file);
    in.setCodec("UTF-8");
    QString html="";
    while(!in.atEnd())
    {
        html.append(in.readLine());
    }
    ui->textEdit->setHtml(html);
    file.close();
}

void MainWindow::saveNotes()
{
    QFile file("1");
    file.open(QIODevice::WriteOnly | QIODevice::Text);
    QTextStream out(&file);
    out.setCodec("UTF-8");

    out.setGenerateByteOrderMark(false);
    out << ui->textEdit->toHtml();
    file.close();
}
