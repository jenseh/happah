/********************************************************************************
** Form generated from reading UI file 'happah.ui'
**
** Created: Fri Sep 14 10:41:14 2012
**      by: Qt User Interface Compiler version 4.8.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_HAPPAH_H
#define UI_HAPPAH_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QHeaderView>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_HappahClass
{
public:

    void setupUi(QWidget *HappahClass)
    {
        if (HappahClass->objectName().isEmpty())
            HappahClass->setObjectName(QString::fromUtf8("HappahClass"));
        HappahClass->resize(400, 300);

        retranslateUi(HappahClass);

        QMetaObject::connectSlotsByName(HappahClass);
    } // setupUi

    void retranslateUi(QWidget *HappahClass)
    {
        HappahClass->setWindowTitle(QApplication::translate("HappahClass", "Happah", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class HappahClass: public Ui_HappahClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_HAPPAH_H
