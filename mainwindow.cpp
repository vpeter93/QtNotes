#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect (ui->actionh2 , SIGNAL (triggered()), this, SLOT(h2ActionSlot()));
    connect (ui->actionbold , SIGNAL (triggered()), this, SLOT(boldActionSlot()));
    connect (ui->actionlinethrout , SIGNAL (triggered()), this, SLOT(lineThroutActionSlot()));
    connect (ui->actionnormal , SIGNAL (triggered()), this, SLOT(normalActionSlot()));
    connect (ui->actionColor , SIGNAL (triggered()), this, SLOT(colorChooseActionSlot()));
}
void MainWindow::h2ActionSlot()
{
    ui->textEdit->textCursor().insertHtml("<h2>"+ui->textEdit->textCursor().selectedText()+"</h2>");
}
void MainWindow::lineThroutActionSlot()
{
    ui->textEdit->textCursor().insertHtml("<s>"+ui->textEdit->textCursor().selectedText()+"</s>");
}
void MainWindow::normalActionSlot()
{
    QTextCharFormat format;
    format.setFontWeight(QFont::Normal);
    ui->textEdit->textCursor().setCharFormat(format);
}
/**
 * @brief MainWindow::colorChooseActionSlot
 */
void MainWindow::colorChooseActionSlot()
{
    QColor backgroundColorTemp = QColorDialog::getColor(backgroundColor,this);
    if(backgroundColorTemp.isValid())
    {
        backgroundColor = backgroundColorTemp;
    }
    QPalette p = ui->textEdit->palette();
    p.setColor(QPalette::Base, backgroundColor);
    //p.setColor(QPalette::Text, color); // set text color which is selected from color pallete
    ui->textEdit->setPalette(p);
    saveConfig();
}

void MainWindow::boldActionSlot()
{
    QTextCharFormat format;
    format.setFontWeight(QFont::Bold);
    ui->textEdit->textCursor().mergeCharFormat(format);
}

MainWindow::~MainWindow()
{
    saveNotes();
    delete ui;
}
void MainWindow::closeEvent(QCloseEvent *event)
{
    QSettings settings("varga", "QtNotes");
    settings.setValue("geometry", saveGeometry());
    settings.setValue("windowState", saveState());
    QMainWindow::closeEvent(event);
}
void MainWindow::readSettings()
{
    QSettings settings("varga", "QtNotes");
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
    QString html="";
    while(!in.atEnd())
    {
        html.append(in.readLine().toUtf8());
    }
    ui->textEdit->setHtml(html);
    file.close();
}

void MainWindow::saveNotes()
{
    QFile file("1");
    file.open(QIODevice::WriteOnly | QIODevice::Text);
    QTextStream out(&file);
    out.setEncoding(QStringConverter::Utf8);

    out.setGenerateByteOrderMark(false);
    out << ui->textEdit->toHtml();
    file.close();
}
void MainWindow::loadConfig()
{
    QFile file("config");

    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        return;
    }
    QTextStream in(&file);
    QString html="";
    while(!in.atEnd())
    {
        html.append(in.readLine().toUtf8());
    }
    file.close();
    backgroundColor = QColor(html);
    QPalette p = ui->textEdit->palette();
    p.setColor(QPalette::Base, backgroundColor);
    ui->textEdit->setPalette(p);

}

void MainWindow::saveConfig()
{
    QFile file("config");
    file.open(QIODevice::WriteOnly | QIODevice::Text);
    QTextStream out(&file);
    out.setEncoding(QStringConverter::Utf8);

    out.setGenerateByteOrderMark(false);
    out << backgroundColor.name();
    file.close();
}

