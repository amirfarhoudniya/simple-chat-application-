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
    client = server->nextPendingConnection() ;
    ui->clients_listWidget->addItem("client added");
    ChatView *clientChatView = new ChatView(client) ;
    ui->chat_tabWidget->addTab(clientChatView , "client") ;
}


void MainWindow::clientDisconnected()
{
    ui->clients_listWidget->addItem("client disconncetd");
}


// void MainWindow::receiveMessage()
// {
//     auto receivedData = client->readAll() ;
//     auto  data = QString::fromUtf8(receivedData);

//     //show the message in listWidget
//     ChatView *chatMessage = new ChatView(client) ;
//     chatMessage->showMessage(data , false);

// }

MainWindow::~MainWindow()
{
    delete ui;
}
