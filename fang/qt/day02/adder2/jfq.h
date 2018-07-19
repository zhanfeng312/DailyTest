/********************************************************************************
** Form generated from reading UI file 'jfq.ui'
**
** Created: Sun Mar 29 15:20:56 2015
**      by: Qt User Interface Compiler version 4.8.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef JFQ_H
#define JFQ_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_Dialog
{
public:
    QLineEdit *line1;
    QLineEdit *line2;
    QLineEdit *line3;
    QLabel *label;
    QPushButton *button;

    void setupUi(QDialog *Dialog)
    {
        if (Dialog->objectName().isEmpty())
            Dialog->setObjectName(QString::fromUtf8("Dialog"));
        Dialog->resize(578, 300);
        line1 = new QLineEdit(Dialog);
        line1->setObjectName(QString::fromUtf8("line1"));
        line1->setGeometry(QRect(10, 128, 113, 27));
        line2 = new QLineEdit(Dialog);
        line2->setObjectName(QString::fromUtf8("line2"));
        line2->setGeometry(QRect(190, 130, 113, 27));
        line3 = new QLineEdit(Dialog);
        line3->setObjectName(QString::fromUtf8("line3"));
        line3->setGeometry(QRect(440, 130, 113, 27));
        label = new QLabel(Dialog);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(130, 130, 66, 17));
        button = new QPushButton(Dialog);
        button->setObjectName(QString::fromUtf8("button"));
        button->setGeometry(QRect(320, 130, 98, 27));

        retranslateUi(Dialog);

        QMetaObject::connectSlotsByName(Dialog);
    } // setupUi

    void retranslateUi(QDialog *Dialog)
    {
        Dialog->setWindowTitle(QApplication::translate("Dialog", "Dialog", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("Dialog", "       +", 0, QApplication::UnicodeUTF8));
        button->setText(QApplication::translate("Dialog", "=", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class Dialog: public Ui_Dialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // JFQ_H
