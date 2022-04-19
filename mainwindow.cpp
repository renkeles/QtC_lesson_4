#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QFileDialog"
#include "QTextStream"
#include "QVBoxLayout"
#include "QLabel"
#include <QDebug>
#include "dialog.h"

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
    childDialog->setWindowTitle(tr("Справка"));
    QVBoxLayout *vlayout = new QVBoxLayout;
    QLabel *label = new QLabel("Ver 0.05 \nby Renkeles");
    vlayout->addWidget(label);
    childDialog->setLayout(vlayout);

    dialog = new Dialog;



    ui->setupUi(this);

    ui->menu->setTitle(tr("Файл"));
    ui->action->setText(tr("Открыть"));
    ui->action_3->setText(tr("Сохранить"));
    ui->action_2->setText(tr("Открыть для чтения"));
    ui->action_4->setText(tr("Справка"));
    ui->menu_2->setTitle(tr("Язык"));
    ui->menu_3->setTitle(tr("Управление"));
    ui->action_6->setText(tr("Клавиши"));


    qTranslator.load(":/new/laguages/QtLanguage_ru.qm");
    qApp->installTranslator(&qTranslator);
    ui->retranslateUi(this);

}

MainWindow::~MainWindow()
{
    delete ui;
    delete pWindow;
    delete childDialog;
    delete dialog;
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


void MainWindow::on_action_3_triggered()
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


void MainWindow::on_action_2_triggered()
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
    qTranslator.load(":/new/laguages/QtLanguage_en.qm");
    qApp->installTranslator(&qTranslator);
    dialog->setLanguage(1);
    ui->retranslateUi(this);
}


void MainWindow::on_action_5_triggered()
{
    qTranslator.load(":/new/laguages/QtLanguage_ru.qm");
    qApp->installTranslator(&qTranslator);
    dialog->setLanguage(0);
    ui->retranslateUi(this);
}

void MainWindow::keyPressEvent(QKeyEvent *e)
{


    if(dialog->getCheckOpen())
    {
        if (e->modifiers() == Qt::ControlModifier && e->key() == Qt::Key_O)
        {
            MainWindow::on_action_2_triggered();
        }
    }else if(!dialog->getCheckOpen())
    {
        if (e->key() == Qt::Key_F3)
        {
            MainWindow::on_action_2_triggered();
        }
    }

    if(dialog->getCheckSave())
    {
        if (e->modifiers() == Qt::ControlModifier && e->key() == Qt::Key_S)
        {
            MainWindow::on_action_3_triggered();
        }
    }else if(!dialog->getCheckSave())
    {
        if (e->key() == Qt::Key_F6)
        {
            MainWindow::on_action_3_triggered();
        }
    }

    if(dialog->getCheckQuit())
    {
        if (e->modifiers() == Qt::ControlModifier && e->key() == Qt::Key_Q)
        {
            exit(0);
            //qApp->quit();
        }
    }else if(!dialog->getCheckQuit())
    {
        if (e->key() == Qt::Key_F12)
        {
            exit(0);
            //qApp->quit();
        }
    }

    if(dialog->getCheckNew())
    {
        if (e->modifiers() == Qt::ControlModifier && e->key() == Qt::Key_N)
        {
            ui->plainTextEdit->clear();
            ui->plainTextEdit->setReadOnly(false);
        }
    }else if(!dialog->getCheckNew())
    {
        if (e->key() == Qt::Key_F2)
        {
            ui->plainTextEdit->clear();
            ui->plainTextEdit->setReadOnly(false);
        }
    }

}



void MainWindow::on_action_6_triggered()
{
    dialog->show();

}

