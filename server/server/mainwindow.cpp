#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    this->setWindowTitle("Server");
    setupServer();
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
    ui->chat_tabWidget->addTab(clientChatView, QString("client %1").arg(id));
}


void MainWindow::clientDisconnected()
{
    ui->clients_listWidget->addItem("client disconncetd");
}


MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setName(QTcpSocket *_client , QString _name)
{
    auto id = _client->property("id").toInt() - 1 ;
    ui->chat_tabWidget->setTabText(id , _name);
    ui->clients_listWidget->addItem(QString("%1 added").arg(_name));
}

void MainWindow::setStatus(QTcpSocket *_client, int _status)
{
    auto id = _client->property("id").toInt() -  1 ;
    if(_status == 0){
        ui->chat_tabWidget->setTabIcon(id , QIcon(":/icon/icons/greenCircle.png"));
    }else if(_status == 1) {
        ui->chat_tabWidget->setTabIcon(id , QIcon(":/icon/icons/yellowCircle.svg"));
    }else if(_status == 2) {
        ui->chat_tabWidget->setTabIcon(id , QIcon(":/icon/icons/redCircle.png"));
    }

}
