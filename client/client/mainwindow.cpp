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
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::receiveMessage()
{
    auto receivedData = client->readAll() ;
    auto  data = QString::fromUtf8(receivedData);

    //show the message in listWidget
    showMessage(data , false);
}

void MainWindow::on_actionconnect_triggered()
{
    ushort port = 6446 ;
    client->connectToHost(QHostAddress::LocalHost , port);
}

void MainWindow::connectedToHost()
{
    ui->centralwidget->setEnabled(true);
}

void MainWindow::disconnectedFromHost()
{
    ui->centralwidget->setEnabled(false);
}


void MainWindow::on_send_pushButton_clicked()
{
    //send data to server
    // auto message = ui->message_lineEdit->text().trimmed().toUtf8() ;
    // QByteArray ba ;
    // QDataStream out (&ba , QIODevice::WriteOnly) ;
    // out.setVersion(QDataStream::Qt_DefaultCompiledVersion);
    // out << message ;
    // client->write(message);

    // showMessage(message , true);

    //send data to server
    auto message = ui->message_lineEdit->text().trimmed().toUtf8() ;
    client->write(message) ;
    showMessage(message , true);
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

