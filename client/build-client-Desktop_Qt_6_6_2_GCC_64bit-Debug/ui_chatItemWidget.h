/********************************************************************************
** Form generated from reading UI file 'chatItemWidget.ui'
**
** Created by: Qt User Interface Compiler version 6.6.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CHATITEMWIDGET_H
#define UI_CHATITEMWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_chatItemWidget
{
public:
    QWidget *widget;
    QHBoxLayout *horizontalLayout;
    QLabel *message_label;
    QLabel *time_label;

    void setupUi(QWidget *chatItemWidget)
    {
        if (chatItemWidget->objectName().isEmpty())
            chatItemWidget->setObjectName("chatItemWidget");
        chatItemWidget->resize(698, 71);
        widget = new QWidget(chatItemWidget);
        widget->setObjectName("widget");
        widget->setGeometry(QRect(10, 10, 671, 51));
        horizontalLayout = new QHBoxLayout(widget);
        horizontalLayout->setObjectName("horizontalLayout");
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        message_label = new QLabel(widget);
        message_label->setObjectName("message_label");

        horizontalLayout->addWidget(message_label);

        time_label = new QLabel(widget);
        time_label->setObjectName("time_label");

        horizontalLayout->addWidget(time_label);

        horizontalLayout->setStretch(0, 4);
        horizontalLayout->setStretch(1, 1);

        retranslateUi(chatItemWidget);

        QMetaObject::connectSlotsByName(chatItemWidget);
    } // setupUi

    void retranslateUi(QWidget *chatItemWidget)
    {
        chatItemWidget->setWindowTitle(QCoreApplication::translate("chatItemWidget", "Form", nullptr));
        message_label->setText(QCoreApplication::translate("chatItemWidget", "message", nullptr));
        time_label->setText(QCoreApplication::translate("chatItemWidget", "time", nullptr));
    } // retranslateUi

};

namespace Ui {
    class chatItemWidget: public Ui_chatItemWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CHATITEMWIDGET_H
