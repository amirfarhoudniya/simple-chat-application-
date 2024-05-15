#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    this->setWindowTitle("Server");
    setupServer();

    //show system IP address
    systemIpAddress();
}

void MainWindow::setupServer()
{
    ushort port = 6446 ;
    server = new QTcpServer(this) ;
    connect(server , &QTcpServer::newConnection , this , &MainWindow::clientRequestConnection) ;
    server->listen(QHostAddress::Any , port) ;
}

void MainWindow::clientRequestConnection()
{
    client = server->nextPendingConnection();
    clients << client ;
    auto id = clients.length() ;
    client->setProperty("id" , id) ;
    ChatView *clientChatView = new ChatView(client);
    connect(clientChatView , &ChatView::setName , this , &MainWindow::setName) ;
    connect(clientChatView , &ChatView::setStatus , this , &MainWindow::setStatus) ;
    connect(clientChatView , &ChatView::clientIsTyping , this , &MainWindow::clientIsTyping) ;
    connect(clientChatView , &ChatView::clientDisconnected , this , &MainWindow::clientDisconnected ) ;
    ui->chat_tabWidget->addTab(clientChatView, QString("client %1").arg(id));

}

void MainWindow::clientDisconnected(QTcpSocket *_client)
{
    QString clientName = _client->property("name").toString();

    //find client's tab in tabWidget by client's name
    for(int i=0 ; i < ui->chat_tabWidget->count() ; i++) {

        if(clientName == ui->chat_tabWidget->tabText(i)) {

            ui->chat_tabWidget->removeTab(i);
            ui->clients_listWidget->addItem(QString("%1 disconncetd").arg(clientName));

            break ;
        }
    }
}

void MainWindow::systemIpAddress()
{
    QList<QHostAddress> ipAddressesList = QNetworkInterface::allAddresses();
    foreach (const QHostAddress &address, ipAddressesList) {
        if(address.protocol() == QAbstractSocket::IPv4Protocol && address != QHostAddress::LocalHost) {
            ui->ip_label->setText(QString("Your IP address is : %1").arg(address.toString()));
        }
    }
}


MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setName(QTcpSocket *_client , QString _name)
{
    //set name of client to tab widget title
    auto id = _client->property("id").toInt() - 1 ;
    ui->chat_tabWidget->setTabText(id , _name);
    ui->clients_listWidget->addItem(QString("%1 added").arg(_name));
    client->setProperty("name" , _name) ;
}

void MainWindow::setStatus(QTcpSocket *_client, int _status)
{
    //add icons to tabWidget of client
    auto clientName = _client->property("name").toString();
    int id ;

    //find client's tabId in tabWidget by client's name
    for(int i=0 ; i < ui->chat_tabWidget->count() ; i++) {

        if(clientName == ui->chat_tabWidget->tabText(i)) {

            id = i ;

            break ;
        }
    }

    //set status png to TabIcon of client's tab
    if(_status == 0){
        ui->chat_tabWidget->setTabIcon(id , QIcon(":/icon/icons/greenCircle.png"));
    }else if(_status == 1) {
        ui->chat_tabWidget->setTabIcon(id , QIcon(":/icon/icons/yellowCircle.svg"));
    }else if(_status == 2) {
        ui->chat_tabWidget->setTabIcon(id , QIcon(":/icon/icons/redCircle.png"));
    }

}

void MainWindow::clientIsTyping(QString _name)
{
    ui->statusbar->showMessage(QString("%1 is Typing ..").arg(_name) , 1000);
}

void MainWindow::on_disconnect_pushButton_clicked()
{
    for (QTcpSocket* clientSocket : clients) {
        //close the client connection and clean up the socket object
        clientSocket->disconnectFromHost();
        clientSocket->deleteLater();
    }
    ui->clients_listWidget->addItem("\n*****************************\n"
                                    "All clients disconnected ...");
    ui->disconnect_pushButton->setText("close page");
}

