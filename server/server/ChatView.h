#ifndef CHATVIEW_H
#define CHATVIEW_H

#include <QWidget>
#include <QDateTime>
#include <QTcpSocket>

#include "chatItemWidget.h"
#include "mainwindow.h"

namespace Ui {
class ChatView;
}

class ChatView : public QWidget
{
    Q_OBJECT

public:
    explicit ChatView( QTcpSocket *_client, QWidget *parent = nullptr);
    ~ChatView();
    struct message {
        QString name ;
        int status ; // 1:online , 2:busy , 3:offline
        QString textMessage ;
    };

    void receiveMessage() ;
    void showMessage(QString _message , bool _isMyMessage) ;

signals :
    void setName(QTcpSocket *_client , QString _name) ;
    void setStatus(QTcpSocket *_client , int _status) ;


private slots:
    void on_send_pushButton_clicked();

private:
    Ui::ChatView *ui;
    QTcpSocket *client ;


};

#endif // CHATVIEW_H
