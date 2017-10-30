/********************************************************************************
** Form generated from reading UI file 'statusform.ui'
**
** Created by: Qt User Interface Compiler version 4.8.6
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_STATUSFORM_H
#define UI_STATUSFORM_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_StatusForm
{
public:
    QWidget *textBackground;
    QWidget *leftTextbar;
    QWidget *centerTextbar;
    QLabel *infoText;
    QWidget *rightTextbar;

    void setupUi(QDialog *StatusForm)
    {
        if (StatusForm->objectName().isEmpty())
            StatusForm->setObjectName(QString::fromUtf8("StatusForm"));
        StatusForm->resize(520, 40);
        textBackground = new QWidget(StatusForm);
        textBackground->setObjectName(QString::fromUtf8("textBackground"));
        textBackground->setGeometry(QRect(0, 0, 520, 40));
        QFont font;
        font.setFamily(QString::fromUtf8("Noto Sans CJK KR"));
        textBackground->setFont(font);
        leftTextbar = new QWidget(textBackground);
        leftTextbar->setObjectName(QString::fromUtf8("leftTextbar"));
        leftTextbar->setGeometry(QRect(0, 0, 20, 40));
        leftTextbar->setFont(font);
        centerTextbar = new QWidget(textBackground);
        centerTextbar->setObjectName(QString::fromUtf8("centerTextbar"));
        centerTextbar->setGeometry(QRect(20, 0, 480, 40));
        centerTextbar->setFont(font);
        infoText = new QLabel(centerTextbar);
        infoText->setObjectName(QString::fromUtf8("infoText"));
        infoText->setGeometry(QRect(0, 0, 480, 40));
        QFont font1;
        font1.setFamily(QString::fromUtf8("Noto Sans CJK JP"));
        infoText->setFont(font1);
        infoText->setAlignment(Qt::AlignCenter);
        rightTextbar = new QWidget(textBackground);
        rightTextbar->setObjectName(QString::fromUtf8("rightTextbar"));
        rightTextbar->setGeometry(QRect(500, 0, 20, 40));
        rightTextbar->setFont(font);

        retranslateUi(StatusForm);

        QMetaObject::connectSlotsByName(StatusForm);
    } // setupUi

    void retranslateUi(QDialog *StatusForm)
    {
        StatusForm->setWindowTitle(QApplication::translate("StatusForm", "Dialog", 0, QApplication::UnicodeUTF8));
        infoText->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class StatusForm: public Ui_StatusForm {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_STATUSFORM_H
