#ifndef CONNECTTOSERVER_H
#define CONNECTTOSERVER_H

#include <QWidget>
#include <QIntValidator>
#include <QHostAddress>
#include <QCheckBox>
#include <QDebug>
#include <QMessageBox>
#include <QMouseEvent>

namespace Ui {
class ConnectToServer;
}

class ConnectToServer : public QWidget
{
    Q_OBJECT

public:
    explicit ConnectToServer(QWidget *parent = nullptr);
    QString name ;
    QHostAddress ip ;

    QString getName() ;
    QHostAddress getIP() ;

    ~ConnectToServer();

signals:
    void nameAndIpHasSet(ConnectToServer *_cts) ;
    void clicked(QMouseEvent *event);

private slots:
    void on_connectToServer_pushButton_clicked();
    void on_localAddressCheckBoxClicked();

private:
    Ui::ConnectToServer *ui;


};

#endif // CONNECTTOSERVER_H
