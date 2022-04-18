#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QFileDialog"
#include "QTextStream"
#include "QVBoxLayout"
#include "QLabel"

QWidget* pWindow;
QDialog* childDialog;



MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{

    pWindow = new QWidget();
    childDialog = new QDialog(pWindow);
    childDialog->setMinimumWidth(200);
    childDialog->setMinimumHeight(100);
    childDialog->setWindowTitle("Справка");
    QVBoxLayout *vlayout = new QVBoxLayout;
    QLabel *label = new QLabel("Ver 0.02 \nby Renkeles");
    vlayout->addWidget(label);
    childDialog->setLayout(vlayout);



    ui->setupUi(this);

    ui->menu->setTitle(tr("Файл"));
    ui->action->setText(tr("Открыть"));
    ui->action_2->setText(tr("Сохранить"));
    ui->action_3->setText(tr("Открыть для чтения"));
    ui->action_4->setText(tr("Справка"));
    ui->menu_2->setTitle(tr("Язык"));


}

MainWindow::~MainWindow()
{
    delete ui;
    delete pWindow;
    delete childDialog;
}

void MainWindow::on_action_triggered()
{
    QString filename = QFileDialog::getOpenFileName();
    if(filename.length())
    {
        QFile file(filename);
        if(file.open(QFile::ReadOnly | QFile::ExistingOnly))
        {
            QTextStream stream(&file);
            ui->plainTextEdit->setPlainText(stream.readAll());
            ui->plainTextEdit->setReadOnly(false);
            file.close();
        }
    }
}


void MainWindow::on_action_2_triggered()
{
    QString filename = QFileDialog::getSaveFileName();
    if(filename.length())
    {
        QFile file(filename);
        if(file.open(QFile::WriteOnly | QFile::NewOnly))
        {
            QTextStream stream(&file);
            stream << ui->plainTextEdit->toPlainText();
            file.close();
        }
    }
}


void MainWindow::on_action_4_triggered()
{
    childDialog->show();
}


void MainWindow::on_action_3_triggered()
{
    QString filename = QFileDialog::getOpenFileName();
    if(filename.length())
    {
        QFile file(filename);
        if(file.open(QFile::ReadOnly))
        {
            QTextStream stream(&file);
            ui->plainTextEdit->setPlainText(stream.readAll());
            ui->plainTextEdit->setReadOnly(true);
            file.close();
        }
    }
}


void MainWindow::on_actionEnglish_triggered()
{

}

