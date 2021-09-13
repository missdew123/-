/********************************************************************************
** Form generated from reading UI file 'Dialog_GetOpenProjectName.ui'
**
** Created by: Qt User Interface Compiler version 5.10.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DIALOG_GETOPENPROJECTNAME_H
#define UI_DIALOG_GETOPENPROJECTNAME_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_Dialog_GetOpenProjectName
{
public:
    QVBoxLayout *verticalLayout;
    QListWidget *ListWdt_Projects;
    QHBoxLayout *horizontalLayout;
    QLabel *label_ProName;
    QLineEdit *QLEdit_ProName;
    QSpacerItem *horizontalSpacer;
    QToolButton *Btn_New;
    QToolButton *Btn_Load;
    QToolButton *Btn_Delete;
    QToolButton *Btn_Cancel;

    void setupUi(QDialog *Dialog_GetOpenProjectName)
    {
        if (Dialog_GetOpenProjectName->objectName().isEmpty())
            Dialog_GetOpenProjectName->setObjectName(QStringLiteral("Dialog_GetOpenProjectName"));
        Dialog_GetOpenProjectName->resize(547, 428);
        verticalLayout = new QVBoxLayout(Dialog_GetOpenProjectName);
        verticalLayout->setSpacing(5);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setContentsMargins(10, 10, 10, 10);
        ListWdt_Projects = new QListWidget(Dialog_GetOpenProjectName);
        ListWdt_Projects->setObjectName(QStringLiteral("ListWdt_Projects"));
        ListWdt_Projects->setMinimumSize(QSize(180, 160));
        QFont font;
        font.setFamily(QString::fromUtf8("\345\276\256\350\275\257\351\233\205\351\273\221"));
        font.setPointSize(10);
        ListWdt_Projects->setFont(font);
        ListWdt_Projects->setFrameShape(QFrame::Box);
        ListWdt_Projects->setFrameShadow(QFrame::Plain);
        ListWdt_Projects->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
        ListWdt_Projects->setIconSize(QSize(120, 90));
        ListWdt_Projects->setResizeMode(QListView::Adjust);
        ListWdt_Projects->setViewMode(QListView::IconMode);

        verticalLayout->addWidget(ListWdt_Projects);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(10);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        label_ProName = new QLabel(Dialog_GetOpenProjectName);
        label_ProName->setObjectName(QStringLiteral("label_ProName"));
        QFont font1;
        font1.setFamily(QString::fromUtf8("\345\215\216\346\226\207\346\245\267\344\275\223"));
        font1.setPointSize(14);
        font1.setBold(true);
        font1.setWeight(75);
        label_ProName->setFont(font1);

        horizontalLayout->addWidget(label_ProName);

        QLEdit_ProName = new QLineEdit(Dialog_GetOpenProjectName);
        QLEdit_ProName->setObjectName(QStringLiteral("QLEdit_ProName"));
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(30);
        sizePolicy.setHeightForWidth(QLEdit_ProName->sizePolicy().hasHeightForWidth());
        QLEdit_ProName->setSizePolicy(sizePolicy);
        QLEdit_ProName->setMinimumSize(QSize(0, 30));
        QFont font2;
        font2.setFamily(QString::fromUtf8("\345\215\216\346\226\207\346\245\267\344\275\223"));
        font2.setPointSize(14);
        font2.setBold(false);
        font2.setWeight(50);
        QLEdit_ProName->setFont(font2);

        horizontalLayout->addWidget(QLEdit_ProName);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        Btn_New = new QToolButton(Dialog_GetOpenProjectName);
        Btn_New->setObjectName(QStringLiteral("Btn_New"));
        Btn_New->setMinimumSize(QSize(60, 30));
        Btn_New->setFont(font1);

        horizontalLayout->addWidget(Btn_New);

        Btn_Load = new QToolButton(Dialog_GetOpenProjectName);
        Btn_Load->setObjectName(QStringLiteral("Btn_Load"));
        Btn_Load->setMinimumSize(QSize(60, 30));
        Btn_Load->setFont(font1);

        horizontalLayout->addWidget(Btn_Load);

        Btn_Delete = new QToolButton(Dialog_GetOpenProjectName);
        Btn_Delete->setObjectName(QStringLiteral("Btn_Delete"));
        Btn_Delete->setMinimumSize(QSize(60, 30));
        Btn_Delete->setFont(font1);

        horizontalLayout->addWidget(Btn_Delete);

        Btn_Cancel = new QToolButton(Dialog_GetOpenProjectName);
        Btn_Cancel->setObjectName(QStringLiteral("Btn_Cancel"));
        Btn_Cancel->setMinimumSize(QSize(60, 30));
        Btn_Cancel->setFont(font1);

        horizontalLayout->addWidget(Btn_Cancel);


        verticalLayout->addLayout(horizontalLayout);


        retranslateUi(Dialog_GetOpenProjectName);

        QMetaObject::connectSlotsByName(Dialog_GetOpenProjectName);
    } // setupUi

    void retranslateUi(QDialog *Dialog_GetOpenProjectName)
    {
        Dialog_GetOpenProjectName->setWindowTitle(QApplication::translate("Dialog_GetOpenProjectName", "Dialog", nullptr));
        label_ProName->setText(QApplication::translate("Dialog_GetOpenProjectName", "\345\267\245\347\250\213\345\220\215\347\247\260\357\274\232", nullptr));
        Btn_New->setText(QApplication::translate("Dialog_GetOpenProjectName", "\346\226\260\345\273\272", nullptr));
        Btn_Load->setText(QApplication::translate("Dialog_GetOpenProjectName", "\345\212\240\350\275\275", nullptr));
        Btn_Delete->setText(QApplication::translate("Dialog_GetOpenProjectName", "\345\210\240\351\231\244", nullptr));
        Btn_Cancel->setText(QApplication::translate("Dialog_GetOpenProjectName", "\351\200\200\345\207\272", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Dialog_GetOpenProjectName: public Ui_Dialog_GetOpenProjectName {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DIALOG_GETOPENPROJECTNAME_H
