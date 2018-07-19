/********************************************************************************
** Form generated from reading UI file 'qqlogin.ui'
**
** Created: Mon Mar 30 19:29:14 2015
**      by: Qt User Interface Compiler version 4.8.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_QQLOGIN_H
#define UI_QQLOGIN_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QHeaderView>
#include <QtGui/QLineEdit>
#include <QtGui/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_QqLogin
{
public:
    QPushButton *login;
    QPushButton *cancel;
    QLineEdit *uname;
    QLineEdit *upasswd;

    void setupUi(QDialog *QqLogin)
    {
        if (QqLogin->objectName().isEmpty())
            QqLogin->setObjectName(QString::fromUtf8("QqLogin"));
        QqLogin->resize(520, 300);
        login = new QPushButton(QqLogin);
        login->setObjectName(QString::fromUtf8("login"));
        login->setGeometry(QRect(104, 200, 98, 27));
        cancel = new QPushButton(QqLogin);
        cancel->setObjectName(QString::fromUtf8("cancel"));
        cancel->setGeometry(QRect(270, 200, 98, 27));
        uname = new QLineEdit(QqLogin);
        uname->setObjectName(QString::fromUtf8("uname"));
        uname->setGeometry(QRect(190, 70, 113, 27));
        upasswd = new QLineEdit(QqLogin);
        upasswd->setObjectName(QString::fromUtf8("upasswd"));
        upasswd->setGeometry(QRect(190, 130, 113, 27));

        retranslateUi(QqLogin);

        QMetaObject::connectSlotsByName(QqLogin);
    } // setupUi

    void retranslateUi(QDialog *QqLogin)
    {
        QqLogin->setWindowTitle(QApplication::translate("QqLogin", "QqLogin", 0, QApplication::UnicodeUTF8));
        login->setText(QApplication::translate("QqLogin", "login", 0, QApplication::UnicodeUTF8));
        cancel->setText(QApplication::translate("QqLogin", "cancel", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class QqLogin: public Ui_QqLogin {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_QQLOGIN_H
