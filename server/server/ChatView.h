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

    // void sendMessage() ;
    void receiveMessage() ;
    void showMessage(QString _message , bool _isMyMessage) ;

private slots:
    void on_send_pushButton_clicked();

private:
    Ui::ChatView *ui;
    QTcpSocket *client ;
};

#endif // CHATVIEW_H
