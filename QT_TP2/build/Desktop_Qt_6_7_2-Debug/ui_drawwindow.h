/********************************************************************************
** Form generated from reading UI file 'drawwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.7.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DRAWWINDOW_H
#define UI_DRAWWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_DrawWindow
{
public:

    void setupUi(QWidget *DrawWindow)
    {
        if (DrawWindow->objectName().isEmpty())
            DrawWindow->setObjectName("DrawWindow");
        DrawWindow->resize(1146, 699);

        retranslateUi(DrawWindow);

        QMetaObject::connectSlotsByName(DrawWindow);
    } // setupUi

    void retranslateUi(QWidget *DrawWindow)
    {
        DrawWindow->setWindowTitle(QCoreApplication::translate("DrawWindow", "Form", nullptr));
    } // retranslateUi

};

namespace Ui {
    class DrawWindow: public Ui_DrawWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DRAWWINDOW_H
