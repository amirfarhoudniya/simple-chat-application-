#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTcpServer>
#include <QTcpSocket>

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
    void clientDisconnected();
    // void receiveMessage() ;
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    QTcpServer *server ;
    QTcpSocket *client ;
    // void showMessage(QString _message) ;
};
#endif // MAINWINDOW_H
