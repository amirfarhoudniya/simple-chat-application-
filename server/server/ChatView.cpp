#include "ChatView.h"
#include "ui_ChatView.h"

ChatView::ChatView(QTcpSocket *_client , QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::ChatView)
    , client(_client)
{
    ui->setupUi(this);

    connect(client , &QTcpSocket::readyRead , this , &ChatView::receiveMessage) ;
}

ChatView::~ChatView()
{
    delete ui;
}

void ChatView::receiveMessage()
{
    auto receivedData = client->readAll() ;
    auto  data = QString::fromUtf8(receivedData);

    //show the message in listWidget
    showMessage(data , false);
}

void ChatView::showMessage(QString _message, bool _isMyMessage)
{
    //put the data to chat list widget
    chatItemWidget *chatItem = new chatItemWidget(this) ;
    QListWidgetItem *listItemWidget = new QListWidgetItem() ;
    listItemWidget->setSizeHint(QSize(0 , 50));
    chatItem->setMessage(_message , _isMyMessage);
    ui->chat_listWidget->addItem(listItemWidget);
    if(! _isMyMessage) {
        listItemWidget->setBackground(Qt::darkGreen);
    } else {
        listItemWidget->setBackground(Qt::black);
    }
    ui->chat_listWidget->setItemWidget(listItemWidget , chatItem);
    ui->message_lineEdit->setText("");
}


void ChatView::on_send_pushButton_clicked()
{
    //send data to server
    auto message = ui->message_lineEdit->text().trimmed().toUtf8() ;
    client->write(message) ;
    showMessage(message , true);
}



