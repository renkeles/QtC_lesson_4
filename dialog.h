#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include <QTranslator>

namespace Ui {
class Dialog;
}

class Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog(QWidget *parent = nullptr);
    ~Dialog();
    bool getCheckOpen();
    bool getCheckSave();
    bool getCheckNew();
    bool getCheckQuit();

    void setLanguage(int);

private:
    Ui::Dialog *ui;
    QTranslator qTranslator;
};

#endif // DIALOG_H
