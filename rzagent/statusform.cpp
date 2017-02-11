#include "statusform.h"
#include "ui_statusform.h"

StatusForm::StatusForm(QStackedWidget *pQStackedWidget,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::StatusForm)
{
    ui->setupUi(this);
    //ui->mainpanel->setStyleSheet("QWidget#mainpanel{background-color: rgba(36, 36, 36, 255);}");
    ui->mainpanel->setStyleSheet("background-color: rgba(46, 52, 54, 255);");
    this->setStyleSheet("background-color: rgba(36, 36, 36, 255);");
    this->setStyleSheet("background-color:transparent;");
}

StatusForm::~StatusForm()
{
    delete ui;
}
