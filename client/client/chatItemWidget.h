#ifndef CHATITEMWIDGET_H
#define CHATITEMWIDGET_H

#include <QWidget>
#include <QDateTime>

namespace Ui {
class chatItemWidget;
}

class chatItemWidget : public QWidget
{
    Q_OBJECT

public:
    explicit chatItemWidget(QWidget *parent = nullptr);
    ~chatItemWidget();

    void setMessage(QString _message , bool _isMyMessage) ;

private:
    Ui::chatItemWidget *ui;
};

#endif // CHATITEMWIDGET_H
