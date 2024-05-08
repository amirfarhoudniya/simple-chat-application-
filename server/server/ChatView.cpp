#include "ChatView.h"
#include "ui_ChatView.h"

ChatView::ChatView(QTcpSocket *_client , QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::ChatView)
    , client(_client)
{
    ui->setupUi(this);

    connect(client , &QTcpSocket::readyRead , this , &ChatView::receiveMessage) ;
    connect(client , &QTcpSocket::disconnected , this , &ChatView::clientIsDisconnecting) ;

}

ChatView::~ChatView()
{
    delete ui;
}

QDataStream &operator>>(QDataStream &in, ChatView::message &msg)
{
    in >> msg.name ;
    in >> msg.status ;
    in >> msg.textMessage;
    in >> msg.isTyping ;
    return in;
}

QDataStream &operator<<(QDataStream &out, ChatView::message &msg)
{
    out << msg.name ;
    out << msg.status;
    out << msg.textMessage ;
    out << msg.isTyping ;
    return out ;
}

void ChatView::receiveMessage()
{
    auto receivedData = client->readAll() ;

    /******* simple way to convert QbyteArray to Qstring *****************/

    // auto  data = QString::fromUtf8(receivedData);
    // //show the message in listWidget
    // showMessage(data , false);


    /************ here we are comverting QbyteArray to Struct again *********/
    message msg ;
    QDataStream dataIn(&receivedData , QIODevice::ReadOnly);
    dataIn >> msg ;

    if(msg.name != "") {
        clientName = msg.name ;
        emit setName(client , msg.name);
    }
    if(msg.status == 0||1||2) {
        emit setStatus(client , msg.status);
    }
    if (! msg.textMessage.isEmpty()) {
        showMessage(msg.textMessage , false);
    }
    if(msg.isTyping) {
        emit clientIsTyping(clientName) ;
    }

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

void ChatView::clientIsDisconnecting()
{
    emit clientDisconnected(client);
}




void ChatView::on_send_pushButton_clicked()
{
    /****************** a simple way to transfer text messages ************/

    //send data to server
    // auto message = ui->message_lineEdit->text().trimmed().toUtf8() ;
    // client->write(message) ;
    // showMessage(message , true);

    /**************** here we are sending more parameters as struct ************ */
    message msg ;
    msg.textMessage = ui->message_lineEdit->text() ;
    // QByteArray ba ;
    // QDataStream dataOut(&ba , QIODevice::WriteOnly) ;
    // dataOut << msg ;
    // client->write(ba) ;
    sendMessage(msg);
    showMessage(msg.textMessage , true);
}




void ChatView::on_message_lineEdit_textEdited(const QString &arg1)
{
    message msg ;
    msg.isTyping = true ;
    msg.name = clientName ;
    // QByteArray ba ;
    // QDataStream dataOut(&ba , QIODevice::WriteOnly) ;
    // dataOut << msg ;
    // client->write(ba) ;
    sendMessage(msg);
}

void ChatView::keyPressEvent(QKeyEvent *event)
{
    if(event->key() == Qt::Key_Return) {
        message msg ;
        msg.textMessage = ui->message_lineEdit->text() ;
        sendMessage(msg);
        showMessage(msg.textMessage , true);
        ui->message_lineEdit->clear();
    }
}

void ChatView::sendMessage(message _msg)
{
    QByteArray ba ;
    QDataStream dataOut(&ba , QIODevice::WriteOnly) ;
    dataOut << _msg ;
    client->write(ba) ;
}

