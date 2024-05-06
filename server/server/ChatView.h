#ifndef CHATVIEW_H
#define CHATVIEW_H

#include <QWidget>
#include <QDateTime>
#include <QTcpSocket>
#include <QKeyEvent>

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
        bool isTyping ;
    };

    void receiveMessage() ;
    void showMessage(QString _message , bool _isMyMessage) ;

signals :
    void setName(QTcpSocket *_client , QString _name) ;
    void setStatus(QTcpSocket *_client , int _status) ;
    void clientIsTyping(QString _name) ;


private slots:
    void on_send_pushButton_clicked();
    void on_message_lineEdit_textEdited(const QString &arg1);
    void keyPressEvent(QKeyEvent *event);
    void sendMessage(message _msg);

private:
    Ui::ChatView *ui;
    QTcpSocket *client ;
    QString clientName ;


};

#endif // CHATVIEW_H
