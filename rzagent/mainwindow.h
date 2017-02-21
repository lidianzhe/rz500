#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStackedWidget>
#include "statusform.h"

//For 90' rotation(size : 854 X 480)
#define UMX_DEVICE_HEIGHT 40
#define UMX_DEVICE_WIDTH 520

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void initUI(QWidget *parent);
private slots:
    void setTop();
private:
    Ui::MainWindow *ui;
    QStackedWidget *_pQStackedWidget;
    StatusForm *_pStatusForm;
    QTimer *_timer;
};

#endif // MAINWINDOW_H
