/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.2.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionabout;
    QAction *actiontips;
    QWidget *centralWidget;
    QGridLayout *gridLayout;
    QHBoxLayout *horizontalLayout_3;
    QSpacerItem *horizontalSpacer_2;
    QPushButton *zip;
    QSpacerItem *horizontalSpacer;
    QPushButton *unzip;
    QSpacerItem *horizontalSpacer_3;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer_6;
    QLabel *label_2;
    QLabel *lb_status;
    QSpacerItem *horizontalSpacer_7;
    QHBoxLayout *horizontalLayout_2;
    QSpacerItem *horizontalSpacer_4;
    QLabel *label;
    QLineEdit *le;
    QPushButton *pb_choose;
    QSpacerItem *horizontalSpacer_5;
    QMenuBar *menuBar;
    QMenu *menumenu;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(400, 250);
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(MainWindow->sizePolicy().hasHeightForWidth());
        MainWindow->setSizePolicy(sizePolicy);
        MainWindow->setMinimumSize(QSize(400, 250));
        MainWindow->setMaximumSize(QSize(16777215, 16777215));
        actionabout = new QAction(MainWindow);
        actionabout->setObjectName(QString::fromUtf8("actionabout"));
        actiontips = new QAction(MainWindow);
        actiontips->setObjectName(QString::fromUtf8("actiontips"));
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        gridLayout = new QGridLayout(centralWidget);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_2);

        zip = new QPushButton(centralWidget);
        zip->setObjectName(QString::fromUtf8("zip"));
        QSizePolicy sizePolicy1(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(zip->sizePolicy().hasHeightForWidth());
        zip->setSizePolicy(sizePolicy1);
        QFont font;
        font.setFamilies({QString::fromUtf8("MS Shell Dlg 2")});
        font.setPointSize(14);
        zip->setFont(font);
        zip->setAutoDefault(true);

        horizontalLayout_3->addWidget(zip);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer);

        unzip = new QPushButton(centralWidget);
        unzip->setObjectName(QString::fromUtf8("unzip"));
        sizePolicy1.setHeightForWidth(unzip->sizePolicy().hasHeightForWidth());
        unzip->setSizePolicy(sizePolicy1);
        unzip->setFont(font);

        horizontalLayout_3->addWidget(unzip);

        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_3);

        horizontalLayout_3->setStretch(0, 1);
        horizontalLayout_3->setStretch(1, 2);
        horizontalLayout_3->setStretch(2, 1);
        horizontalLayout_3->setStretch(3, 2);
        horizontalLayout_3->setStretch(4, 1);

        gridLayout->addLayout(horizontalLayout_3, 2, 0, 1, 1);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalSpacer_6 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_6);

        label_2 = new QLabel(centralWidget);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        QFont font1;
        font1.setFamilies({QString::fromUtf8("\347\255\211\347\272\277")});
        font1.setPointSize(14);
        label_2->setFont(font1);

        horizontalLayout->addWidget(label_2);

        lb_status = new QLabel(centralWidget);
        lb_status->setObjectName(QString::fromUtf8("lb_status"));
        lb_status->setFont(font1);

        horizontalLayout->addWidget(lb_status);

        horizontalSpacer_7 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_7);

        horizontalLayout->setStretch(0, 1);
        horizontalLayout->setStretch(1, 8);
        horizontalLayout->setStretch(2, 20);
        horizontalLayout->setStretch(3, 1);

        gridLayout->addLayout(horizontalLayout, 1, 0, 1, 1);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        horizontalSpacer_4 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_4);

        label = new QLabel(centralWidget);
        label->setObjectName(QString::fromUtf8("label"));
        label->setFont(font1);

        horizontalLayout_2->addWidget(label);

        le = new QLineEdit(centralWidget);
        le->setObjectName(QString::fromUtf8("le"));
        le->setFont(font1);
        le->setFrame(true);

        horizontalLayout_2->addWidget(le);

        pb_choose = new QPushButton(centralWidget);
        pb_choose->setObjectName(QString::fromUtf8("pb_choose"));
        QSizePolicy sizePolicy2(QSizePolicy::Minimum, QSizePolicy::Fixed);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(pb_choose->sizePolicy().hasHeightForWidth());
        pb_choose->setSizePolicy(sizePolicy2);
        QFont font2;
        font2.setFamilies({QString::fromUtf8("MS Shell Dlg 2")});
        font2.setPointSize(12);
        pb_choose->setFont(font2);

        horizontalLayout_2->addWidget(pb_choose);

        horizontalSpacer_5 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_5);

        horizontalLayout_2->setStretch(0, 1);
        horizontalLayout_2->setStretch(1, 6);
        horizontalLayout_2->setStretch(2, 10);
        horizontalLayout_2->setStretch(3, 4);
        horizontalLayout_2->setStretch(4, 1);

        gridLayout->addLayout(horizontalLayout_2, 0, 0, 1, 1);

        gridLayout->setRowStretch(0, 5);
        gridLayout->setRowStretch(1, 5);
        gridLayout->setRowStretch(2, 2);
        gridLayout->setRowMinimumHeight(0, 5);
        gridLayout->setRowMinimumHeight(1, 5);
        gridLayout->setRowMinimumHeight(2, 2);
        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 400, 21));
        menumenu = new QMenu(menuBar);
        menumenu->setObjectName(QString::fromUtf8("menumenu"));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        MainWindow->setStatusBar(statusBar);

        menuBar->addAction(menumenu->menuAction());
        menumenu->addAction(actionabout);
        menumenu->addAction(actiontips);

        retranslateUi(MainWindow);

        zip->setDefault(true);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "\345\216\213\347\274\251\345\212\251\346\211\213", nullptr));
        actionabout->setText(QCoreApplication::translate("MainWindow", "\345\205\263\344\272\216", nullptr));
        actiontips->setText(QCoreApplication::translate("MainWindow", "tips", nullptr));
        zip->setText(QCoreApplication::translate("MainWindow", "\345\216\213\347\274\251", nullptr));
        unzip->setText(QCoreApplication::translate("MainWindow", "\350\247\243\345\216\213", nullptr));
        label_2->setText(QCoreApplication::translate("MainWindow", "\347\212\266\346\200\201\357\274\232", nullptr));
        lb_status->setText(QCoreApplication::translate("MainWindow", "\345\207\206\345\244\207\345\245\275\344\272\206^-^", nullptr));
        label->setText(QCoreApplication::translate("MainWindow", "\346\226\207\344\273\266\350\267\257\345\276\204\357\274\232", nullptr));
        le->setInputMask(QString());
        le->setText(QString());
        le->setPlaceholderText(QCoreApplication::translate("MainWindow", "\350\257\267\350\276\223\345\205\245\346\226\207\344\273\266\350\267\257\345\276\204", nullptr));
        pb_choose->setText(QCoreApplication::translate("MainWindow", "\351\200\211\346\213\251\346\226\207\344\273\266", nullptr));
        menumenu->setTitle(QCoreApplication::translate("MainWindow", "\347\202\271\350\277\231\351\207\214", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
