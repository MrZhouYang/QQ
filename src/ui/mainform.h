#ifndef MAINFORM_H
#define MAINFORM_H

#include <QWidget>
#include "moveableframelesswindow.h"
#include <QVBoxLayout>
#include "collapseview.h"
#include "colorpickform.h"
#include <QtNetwork>
#include <QByteArray>
#include <QDataStream>
#include "chatform.h"
#include "litteriem.h"

namespace Ui {
class MainForm;
}

class MainForm : public MoveableFramelessWindow
{
    Q_OBJECT

public:
    explicit MainForm(QString userName,QString nickName,int port,QWidget *parent = 0);
    ~MainForm();

protected:
      QWidget*getDragnWidget();

private:
    Ui::MainForm *ui;

    QVBoxLayout *page4_layout;

    int port_number; //用于保存用户的端口号

    QString m_nickName;

    CollapseView *collapseView_p;

    QUdpSocket *m_udpSocket;

    /**
    * @brief 用于保存目前存在的charform
    */
    QMap<QString, ChatForm *> chatform_map;

    /**
    * @brief UDP发送函数
    * @param type 发送消息类型
    * @return
    */
    void sendMessage(MessageType type , int to_port, QString showname);

    int get_bind_port(QString Name);


private slots:
    void on_PB_minimize_clicked();
    void on_PB_shutdown_clicked();

    void doChangeColor();
    void onThemeColorChange(QString colorStr);

    /**
    * @brief UDP接受函数
    */
    void processPendingDatagrams();

    void WakeChat(int port,QString showname);

    /**
    * @brief 从chatform_map中删除键为name的项
    */
    void Erase_form_chatform_map(QString name);

};

#endif // MAINFORM_H
