/********************************************************************************
** Form generated from reading UI file 'qq.ui'
**
** Created: Mon Mar 30 17:56:34 2015
**      by: Qt User Interface Compiler version 4.8.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef QQ_H
#define QQ_H

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

class Ui_calculator
{
public:
    QLineEdit *uname;
    QLineEdit *upasswd;
    QPushButton *login;
    QPushButton *cancel;
    QLabel *label;
    QLabel *label_2;

    void setupUi(QDialog *calculator)
    {
        if (calculator->objectName().isEmpty())
            calculator->setObjectName(QString::fromUtf8("calculator"));
        calculator->resize(401, 300);
        uname = new QLineEdit(calculator);
        uname->setObjectName(QString::fromUtf8("uname"));
        uname->setGeometry(QRect(140, 70, 113, 27));
        upasswd = new QLineEdit(calculator);
        upasswd->setObjectName(QString::fromUtf8("upasswd"));
        upasswd->setGeometry(QRect(140, 120, 113, 27));
        upasswd->setEchoMode(QLineEdit::Password);
        login = new QPushButton(calculator);
        login->setObjectName(QString::fromUtf8("login"));
        login->setGeometry(QRect(70, 189, 98, 30));
        cancel = new QPushButton(calculator);
        cancel->setObjectName(QString::fromUtf8("cancel"));
        cancel->setGeometry(QRect(210, 190, 98, 30));
        label = new QLabel(calculator);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(70, 75, 66, 17));
        QFont font;
        font.setPointSize(13);
        font.setBold(false);
        font.setWeight(50);
        label->setFont(font);
        label_2 = new QLabel(calculator);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(77, 125, 66, 17));
        QFont font1;
        font1.setPointSize(13);
        label_2->setFont(font1);

        retranslateUi(calculator);

        QMetaObject::connectSlotsByName(calculator);
    } // setupUi

    void retranslateUi(QDialog *calculator)
    {
        calculator->setWindowTitle(QApplication::translate("calculator", "Dialog", 0, QApplication::UnicodeUTF8));
        uname->setText(QString());
        upasswd->setText(QString());
        login->setText(QApplication::translate("calculator", "login", 0, QApplication::UnicodeUTF8));
        cancel->setText(QApplication::translate("calculator", "cancel", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("calculator", "QQ\345\217\267", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("calculator", "\345\257\206\347\240\201", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class calculator: public Ui_calculator {};
} // namespace Ui

QT_END_NAMESPACE

#endif // QQ_H
