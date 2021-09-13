/********************************************************************************
** Form generated from reading UI file 'Dialog_GetProjectName.ui'
**
** Created by: Qt User Interface Compiler version 5.10.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DIALOG_GETPROJECTNAME_H
#define UI_DIALOG_GETPROJECTNAME_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_Dialog_GetProjectName
{
public:
    QVBoxLayout *verticalLayout;
    QSpacerItem *verticalSpacer;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QLineEdit *lineEdit;
    QSpacerItem *verticalSpacer_2;
    QHBoxLayout *horizontalLayout_2;
    QSpacerItem *horizontalSpacer;
    QToolButton *Btn_Save;
    QToolButton *Btn_Cancel;

    void setupUi(QDialog *Dialog_GetProjectName)
    {
        if (Dialog_GetProjectName->objectName().isEmpty())
            Dialog_GetProjectName->setObjectName(QStringLiteral("Dialog_GetProjectName"));
        Dialog_GetProjectName->resize(300, 200);
        QFont font;
        font.setFamily(QString::fromUtf8("\345\276\256\350\275\257\351\233\205\351\273\221"));
        font.setPointSize(10);
        Dialog_GetProjectName->setFont(font);
        verticalLayout = new QVBoxLayout(Dialog_GetProjectName);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalSpacer = new QSpacerItem(20, 47, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        label = new QLabel(Dialog_GetProjectName);
        label->setObjectName(QStringLiteral("label"));
        label->setMinimumSize(QSize(0, 30));
        QFont font1;
        font1.setPointSize(12);
        label->setFont(font1);

        horizontalLayout->addWidget(label);

        lineEdit = new QLineEdit(Dialog_GetProjectName);
        lineEdit->setObjectName(QStringLiteral("lineEdit"));
        lineEdit->setMinimumSize(QSize(0, 30));
        lineEdit->setFont(font1);

        horizontalLayout->addWidget(lineEdit);

        horizontalLayout->setStretch(1, 4);

        verticalLayout->addLayout(horizontalLayout);

        verticalSpacer_2 = new QSpacerItem(20, 47, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer_2);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer);

        Btn_Save = new QToolButton(Dialog_GetProjectName);
        Btn_Save->setObjectName(QStringLiteral("Btn_Save"));
        Btn_Save->setMinimumSize(QSize(60, 30));
        Btn_Save->setFont(font1);

        horizontalLayout_2->addWidget(Btn_Save);

        Btn_Cancel = new QToolButton(Dialog_GetProjectName);
        Btn_Cancel->setObjectName(QStringLiteral("Btn_Cancel"));
        Btn_Cancel->setMinimumSize(QSize(60, 30));
        Btn_Cancel->setFont(font1);

        horizontalLayout_2->addWidget(Btn_Cancel);


        verticalLayout->addLayout(horizontalLayout_2);


        retranslateUi(Dialog_GetProjectName);

        QMetaObject::connectSlotsByName(Dialog_GetProjectName);
    } // setupUi

    void retranslateUi(QDialog *Dialog_GetProjectName)
    {
        Dialog_GetProjectName->setWindowTitle(QApplication::translate("Dialog_GetProjectName", "Dialog", nullptr));
        label->setText(QApplication::translate("Dialog_GetProjectName", "\351\241\271\347\233\256\345\220\215", nullptr));
        Btn_Save->setText(QApplication::translate("Dialog_GetProjectName", "\344\277\235\345\255\230", nullptr));
        Btn_Cancel->setText(QApplication::translate("Dialog_GetProjectName", "\345\217\226\346\266\210", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Dialog_GetProjectName: public Ui_Dialog_GetProjectName {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DIALOG_GETPROJECTNAME_H
