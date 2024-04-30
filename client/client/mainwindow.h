#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTcpSocket>

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


private slots:
    void on_actionconnect_triggered();
    void connectedToHost() ;
    void disconnectedFromHost() ;

    void on_send_pushButton_clicked();

private:
    Ui::MainWindow *ui;
    QTcpSocket *client ;

    void showMessage(QString _message, bool _isMyMessage) ;
};
#endif // MAINWINDOW_H
