/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.6.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionconnect;
    QAction *actionExit;
    QWidget *centralwidget;
    QWidget *layoutWidget;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout_2;
    QSpacerItem *horizontalSpacer;
    QComboBox *status_comboBox;
    QListWidget *chat_listWidget;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QLineEdit *message_lineEdit;
    QPushButton *send_pushButton;
    QMenuBar *menubar;
    QMenu *menufile;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(800, 600);
        actionconnect = new QAction(MainWindow);
        actionconnect->setObjectName("actionconnect");
        actionExit = new QAction(MainWindow);
        actionExit->setObjectName("actionExit");
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        layoutWidget = new QWidget(centralwidget);
        layoutWidget->setObjectName("layoutWidget");
        layoutWidget->setGeometry(QRect(80, 80, 631, 431));
        verticalLayout = new QVBoxLayout(layoutWidget);
        verticalLayout->setObjectName("verticalLayout");
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer);

        status_comboBox = new QComboBox(layoutWidget);
        status_comboBox->addItem(QString());
        status_comboBox->addItem(QString());
        status_comboBox->addItem(QString());
        status_comboBox->setObjectName("status_comboBox");

        horizontalLayout_2->addWidget(status_comboBox);


        verticalLayout->addLayout(horizontalLayout_2);

        chat_listWidget = new QListWidget(layoutWidget);
        chat_listWidget->setObjectName("chat_listWidget");

        verticalLayout->addWidget(chat_listWidget);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName("horizontalLayout");
        label = new QLabel(layoutWidget);
        label->setObjectName("label");

        horizontalLayout->addWidget(label);

        message_lineEdit = new QLineEdit(layoutWidget);
        message_lineEdit->setObjectName("message_lineEdit");

        horizontalLayout->addWidget(message_lineEdit);

        send_pushButton = new QPushButton(layoutWidget);
        send_pushButton->setObjectName("send_pushButton");

        horizontalLayout->addWidget(send_pushButton);


        verticalLayout->addLayout(horizontalLayout);

        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 800, 28));
        menufile = new QMenu(menubar);
        menufile->setObjectName("menufile");
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName("statusbar");
        MainWindow->setStatusBar(statusbar);

        menubar->addAction(menufile->menuAction());
        menufile->addAction(actionconnect);
        menufile->addAction(actionExit);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        actionconnect->setText(QCoreApplication::translate("MainWindow", "connect", nullptr));
        actionExit->setText(QCoreApplication::translate("MainWindow", "Exit", nullptr));
        status_comboBox->setItemText(0, QCoreApplication::translate("MainWindow", "online", nullptr));
        status_comboBox->setItemText(1, QCoreApplication::translate("MainWindow", "busy", nullptr));
        status_comboBox->setItemText(2, QCoreApplication::translate("MainWindow", "offline", nullptr));

        label->setText(QCoreApplication::translate("MainWindow", "message :", nullptr));
        send_pushButton->setText(QCoreApplication::translate("MainWindow", "send", nullptr));
        menufile->setTitle(QCoreApplication::translate("MainWindow", "file", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
