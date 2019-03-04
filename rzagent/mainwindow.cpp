#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsProxyWidget>
#include <QTimer>
#include "statusform.h"
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    //ui->setupUi(this);
    _pQStackedWidget = NULL;
    _pStatusForm = NULL;

    initUI(parent);

    _timer = new QTimer(this);
    connect(_timer,SIGNAL(timeout()),this,SLOT(setTop()));
    _timer->start(1000*5);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::initUI(QWidget *parent)
{
    setFixedSize(UMX_DEVICE_HEIGHT,UMX_DEVICE_WIDTH);
    this->setGeometry(0,167,80,60);
    _pQStackedWidget = new QStackedWidget();
    _pQStackedWidget->setFixedSize(UMX_DEVICE_WIDTH, UMX_DEVICE_HEIGHT);
    _pStatusForm= new StatusForm(_pQStackedWidget);

    _pQStackedWidget->addWidget(_pStatusForm);
    _pQStackedWidget->setCurrentIndex(0);

    QGraphicsScene *scene = new QGraphicsScene();
    QGraphicsView *view = new QGraphicsView(this);
    QGraphicsProxyWidget *proxy = scene->addWidget(_pQStackedWidget);
    view->setScene(scene);
    view->setFrameStyle(QFrame::NoFrame);
    view->setAutoFillBackground(true);
    view->setFixedWidth(UMX_DEVICE_HEIGHT);
    view->setFixedHeight(UMX_DEVICE_WIDTH);
    view->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view->rotate(90);
    view->show();

}

void MainWindow::setTop()
{
    hide();
    if(_pStatusForm->getDebugMode()==1){
        setWindowFlags(Qt::WindowStaysOnTopHint);
        show();
    }else
    {
        hide();
    }
    //_timer->stop();
}


