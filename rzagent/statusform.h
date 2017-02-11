#ifndef STATUSFORM_H
#define STATUSFORM_H

#include <QDialog>
#include <QStackedWidget>

namespace Ui {
class StatusForm;
}

class StatusForm : public QDialog
{
    Q_OBJECT

public:
    explicit StatusForm(QStackedWidget *pQStackedWidget,QWidget *parent = 0);
    ~StatusForm();

private:
    Ui::StatusForm *ui;
};

#endif // STATUSFORM_H
