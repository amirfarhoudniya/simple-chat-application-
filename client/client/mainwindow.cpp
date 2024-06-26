#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->send_pushButton->setCursor(Qt::PointingHandCursor);
    this->centralWidget()->setEnabled(false);

    client = new QTcpSocket() ;

    connect(client , &QTcpSocket::connected , this , &MainWindow::connectedToHost);
    connect(client , &QTcpSocket::readyRead , this , &MainWindow::receiveMessage) ;
    connect(client , &QTcpSocket::disconnected , this , &MainWindow::disconnectedFromHost) ;

 }

MainWindow::~MainWindow()
{
    delete ui;
}
QDataStream &operator>>(QDataStream &in, MainWindow::message &msg)
{
    in >> msg.name ;
    in >> msg.status ;
    in >> msg.textMessage;
    in >> msg.isTyping ;
    return in;
}

QDataStream &operator<<(QDataStream &out, MainWindow::message &msg)
{
    out << msg.name ;
    out <<msg.status;
    out << msg.textMessage ;
    out << msg.isTyping ;
    return out ;
}

void MainWindow::receiveMessage()
{

    auto receivedData = client->readAll() ;

    /******* simple way to convert QbyteArray to Qstring *****************/
    // auto  data = QString::fromUtf8(receivedData);

    /************ here we are converting QbyteArray to Struct again *********/
    message msg ;
    QDataStream dataIn(&receivedData , QIODevice::ReadOnly);
    dataIn >> msg ;

    if(msg.isTyping){
        ui->statusbar->showMessage("Server is Typing .." , 1000);
    }

    //show the message in listWidget
    if(! msg.textMessage.isEmpty()) {
        showMessage(msg.textMessage , false);
    }

}

void MainWindow::on_actionconnect_triggered()
{
    ConnectToServer *cts = new ConnectToServer() ;
    cts->show();
    connect(cts , &ConnectToServer::nameAndIpHasSet , this , &MainWindow::connectToHost) ;
}

void MainWindow::connectToHost(ConnectToServer *_cts)
{
    message msg ;
    msg.name = _cts->name ;
    //status: 0:online , 1:busy , 2:offline
    msg.status = 0 ;

    //connect to Host
    ushort port = 6446 ;
    client->connectToHost(_cts->ip, port);
    client->waitForConnected(1000);

    //start a timer to check for connection timeout
    QTimer::singleShot(3000 , this , [this](){
        if(client->state() != QAbstractSocket::ConnectedState) {
            client->abort();
            QMessageBox::critical(this , "" ,"failed to connect Server");
        }
    });

    sendMessage(msg);
}

void MainWindow::connectedToHost()
{
    if(client->isOpen()) {
        ui->centralwidget->setEnabled(true);
    }
}

void MainWindow::disconnectedFromHost()
{
    ui->centralwidget->setEnabled(false);
    QMessageBox::critical(this , "" , "server disconnected !") ;
}


void MainWindow::on_send_pushButton_clicked()
{
    /****************** a simple way to transfer text messages ************/

    // auto message = ui->message_lineEdit->text().trimmed().toUtf8() ;
    // client->write(message) ;
    // showMessage(message , true);

    /**************** here we are sending more parameters as struct ************ */
    message msg ;
    msg.textMessage = ui->message_lineEdit->text() ;
    sendMessage(msg);

    showMessage(msg.textMessage , true);
}

void MainWindow::sendMessage(message _msg)
{
    QByteArray ba ;
    QDataStream dataOut(&ba , QIODevice::WriteOnly) ;
    dataOut << _msg ;

    client->write(ba) ;
}

void MainWindow::showMessage(QString _message , bool _isMyMessage)
{
    //put the data to chat list widget
    chatItemWidget *chatItem = new chatItemWidget(this) ;
    QListWidgetItem *listItemWidget = new QListWidgetItem() ;
    listItemWidget->setSizeHint(QSize(0 , 50));
    chatItem->setMessage(_message , _isMyMessage);
    if(! _isMyMessage) {
        listItemWidget->setBackground(Qt::darkGreen);
    } else {
        listItemWidget->setBackground(Qt::black);
    }
    ui->chat_listWidget->addItem(listItemWidget);
    ui->chat_listWidget->setItemWidget(listItemWidget , chatItem);
    ui->message_lineEdit->setText("");
}

void MainWindow::keyPressEvent(QKeyEvent *event)
{
    //send message as "Enter" key pressed
    if(event->key() == Qt::Key_Return) {
        message msg ;
        msg.textMessage = ui->message_lineEdit->text() ;
        sendMessage(msg);
        showMessage(msg.textMessage , true);
        ui->message_lineEdit->clear();
    }
}

void MainWindow::on_status_comboBox_currentIndexChanged(int index)
{
    index = ui->status_comboBox->currentIndex() ;
    message msg ;
    msg.status = index ;
    sendMessage(msg);
}


void MainWindow::on_message_lineEdit_textChanged(const QString &arg1)
{
    message msg ;
    msg.isTyping = true ;
    sendMessage(msg);
}

void MainWindow::on_actionExit_triggered()
{
    this->close() ;
}

