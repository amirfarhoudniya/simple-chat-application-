#include "chatItemWidget.h"
#include "ui_chatItemWidget.h"

chatItemWidget::chatItemWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::chatItemWidget)
{
    ui->setupUi(this);
}

chatItemWidget::~chatItemWidget()
{
    delete ui;
}

void chatItemWidget::setMessage(QString _message, bool _isMyMessage)
{
    if(_isMyMessage) {
        ui->message_label->setAlignment(Qt::AlignRight);
    }else {
        ui->time_label->setAlignment(Qt::AlignLeft);
    }
    ui->message_label->setText(_message);
    ui->time_label->setText(QDateTime::currentDateTime().toString("HH:mm"));
}
