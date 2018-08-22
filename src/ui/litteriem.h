#ifndef LITTERIEM_H
#define LITTERIEM_H

#include <QWidget>
#include "chatform.h"

namespace Ui {
class LitterIem;
}

class LitterIem : public QWidget
{
    Q_OBJECT

public:
    /**
     * @brief LitterIem
     * @param picPath 头像的文件路径
     * @param parent
     */
    explicit LitterIem(QString picPath,QWidget *parent = 0);

    /**
     * @brief LitterIem
     * @param picPath 头像的文件路径
     * @param port 用户的端口号
     * @param Name 用户的昵称
     * @param parent
     */
     explicit LitterIem(QString picPath,int port,QString Name,QString senderName,QWidget *parent = 0);
    ~LitterIem();

protected:
    void mouseDoubleClickEvent(QMouseEvent *event);

private:
    Ui::LitterIem *ui;

    int port_number;//用于保存用户的端口号
    QString sender_nickName; //用于保存用户昵称
    QString Litter_nickName; //用于保存该好友的昵称

    ChatForm *chatform_p;
};

#endif // LITTERIEM_H
