#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTcpSocket>
#include <QMessageBox>
#include <QInputDialog>
#include <QDataStream>

#include "chatItemWidget.h"

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
    ~MainWindow();

    void receiveMessage() ;

    struct message {
        QString name ;
        int status ;
        QString textMessage ;
    };


private slots:
    void on_actionconnect_triggered();
    void connectedToHost() ;
    void disconnectedFromHost() ;

    void on_send_pushButton_clicked();

    void on_status_comboBox_currentIndexChanged(int index);

private:
    Ui::MainWindow *ui;
    QTcpSocket *client ;

    void sendMessage(message _msg) ;
    void showMessage(QString _message, bool _isMyMessage) ;
};
#endif // MAINWINDOW_H
