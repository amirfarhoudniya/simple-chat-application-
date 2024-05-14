#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTcpServer>
#include <QTcpSocket>
#include <QNetworkInterface>

#include "ChatView.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    void setupServer() ;
    void clientRequestConnection() ;
    void clientConnected() ;
    void clientDisconnected(QTcpSocket *_client);
    void systemIpAddress() ;
    ~MainWindow();

public slots:
    void setName(QTcpSocket *_client , QString _name);
    void setStatus(QTcpSocket *_client , int _status);
    void clientIsTyping(QString _name) ;

private slots:
    void on_disconnect_pushButton_clicked();

private:
    Ui::MainWindow *ui;
    QTcpServer *server ;
    QTcpSocket *client ;
    QList<QTcpSocket *> clients ;
};
#endif // MAINWINDOW_H
