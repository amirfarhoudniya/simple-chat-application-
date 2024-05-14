#include "ConnectToServer.h"
#include "ui_ConnectToServer.h"

ConnectToServer::ConnectToServer(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::ConnectToServer)
{
    ui->setupUi(this);

    this->setFixedSize(400 , 250);

    //get the name of user
    ui->name_lineEdit->setAlignment(Qt::AlignCenter);

    //set default mode "connect to localServer"
    ui->localAddress_checkBox->setChecked(true);
    on_localAddressCheckBoxClicked();

    //get ip 3 numbers and no strings
    ui->ip_lineEdit1->setAlignment(Qt::AlignCenter);
    ui->ip_lineEdit1->setInputMask("000");
    ui->ip_lineEdit2->setAlignment(Qt::AlignCenter);
    ui->ip_lineEdit2->setInputMask("000");
    ui->ip_lineEdit3->setAlignment(Qt::AlignCenter);
    ui->ip_lineEdit3->setInputMask("000");
    ui->ip_lineEdit4->setAlignment(Qt::AlignCenter);
    ui->ip_lineEdit4->setInputMask("000");

    connect(ui->localAddress_checkBox, &QCheckBox::clicked, this, &ConnectToServer::on_localAddressCheckBoxClicked);

}

QString ConnectToServer::getName()
{
    return name ;
}

QHostAddress ConnectToServer::getIP()
{
    return ip ;
}

ConnectToServer::~ConnectToServer()
{
    delete ui;
}


void ConnectToServer::on_connectToServer_pushButton_clicked()
{
    //get name of user
    name = ui->name_lineEdit->text() ;

    if(ui->localAddress_checkBox->isChecked()) {
        ip = QHostAddress::LocalHost ;
    } else {
        QString ipFromClient = {
            ui->ip_lineEdit1->text() + "." +
            ui->ip_lineEdit1->text() + "." +
            ui->ip_lineEdit1->text() + "." +
            ui->ip_lineEdit1->text() };

        ip = QHostAddress(ipFromClient) ;
    }

    emit nameAndIpHasSet(this);
    this->close() ;
}

void ConnectToServer::on_localAddressCheckBoxClicked()
{
    if (ui->localAddress_checkBox->isChecked()) {
        ui->ip_lineEdit1->setEnabled(false);
        ui->ip_lineEdit2->setEnabled(false);
        ui->ip_lineEdit3->setEnabled(false);
        ui->ip_lineEdit4->setEnabled(false);
        ui->ip_label->setEnabled(false);
        ui->ip_lineEdit1->clear();
        ui->ip_lineEdit2->clear();
        ui->ip_lineEdit3->clear();
        ui->ip_lineEdit4->clear();
    } else {
        ui->ip_lineEdit1->setEnabled(true);
        ui->ip_lineEdit2->setEnabled(true);
        ui->ip_lineEdit3->setEnabled(true);
        ui->ip_lineEdit4->setEnabled(true);
        ui->ip_label->setEnabled(true);
    }
}









