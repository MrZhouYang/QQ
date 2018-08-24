#include "mainform.h"
#include "ui_mainform.h"

#include <QDebug>
#include <QDesktopWidget>
#include <QApplication>


//主窗口与屏幕边缘的距离
int MAIN_FORM_OADDING =10;

MainForm::MainForm(QString userName, QString nickName, int port, QWidget *parent) :
    MoveableFramelessWindow(parent),port_number(port),m_nickName(nickName),
    ui(new Ui::MainForm)
{
    ui->setupUi(this);

    ui->label_nick->setText(nickName);

    page4_layout = new QVBoxLayout(this);
    page4_layout->setContentsMargins(0,0,0,0);//设置上下左右的边距均为0
    page4_layout->setSpacing(0); //This property holds the spacing between widgets inside the layout.
    ui->page_4->setLayout(page4_layout);

    //在布局中加入联系人列表
    collapseView_p = new CollapseView(userName,nickName);
    page4_layout->addWidget(collapseView_p);

    //为每个好友项的双击信号进行关联
    for(int i=0; i<collapseView_p->Get_item_contact_p()->Get_itemv_size(); ++i){
        connect(collapseView_p->Get_item_contact_p()->Get_item_P(i),SIGNAL(wake_message_to(int,QString)),this,SLOT(WakeChat(int,QString)));
    }

    //关联切换皮肤颜色按钮事件
    connect(ui->pushButton_skin,SIGNAL(clicked()),this,SLOT(doChangeColor()));

    //获取屏幕
    QDesktopWidget* desktopWidget = QApplication::desktop();

    //得到屏幕宽度
    int screenWidth = desktopWidget->width();

    //转移到右边
    this->move(screenWidth-MAIN_FORM_OADDING-this->width(),MAIN_FORM_OADDING);

    //udp相关
    m_udpSocket = new QUdpSocket(this);
    m_udpSocket->bind(port_number,QUdpSocket::ShareAddress | QUdpSocket::ReuseAddressHint);
    connect(m_udpSocket,SIGNAL(readyRead()),this,SLOT(processPendingDatagrams()) );


    connect(ui->pushButton_minimize,SIGNAL(pressed()),this,SLOT(on_PB_minimize_clicked()));
    connect(ui->pushButton_shutdown,SIGNAL(pressed()),this,SLOT(on_PB_shutdown_clicked()));
}

MainForm::~MainForm()
{
    delete collapseView_p;

    //删除仍存在的ChatForm对话框
    QMap<QString, ChatForm *>::iterator ite = chatform_map.begin();
    while(ite!=chatform_map.end()){
        delete ite.value();
    }

    delete ui;
}

QWidget *MainForm::getDragnWidget()
{
    return ui->main_top;
}

void MainForm::on_PB_minimize_clicked()
{
    this->showMinimized();
}

void MainForm::on_PB_shutdown_clicked()
{
    this->deleteLater();
}

void MainForm::doChangeColor()
{

    MY_COLOR_PICK_FORM.show();
    MY_COLOR_PICK_FORM.raise(); //Raises this widget to the top of the parent widget's stack.
    MY_COLOR_PICK_FORM.setFocus(); //Gives the keyboard input focus to this widget (or its focus proxy) if this widget or one of its parents is the active window.

    ColorPickForm *f= &(MY_COLOR_PICK_FORM);

    connect(f,SIGNAL(themColorChanged(QString)),this,SLOT(onThemeColorChange(QString)));

}

void MainForm::onThemeColorChange(QString colorStr)
{
    //组合成qcc样式表
    QString style=QString("#%1{background-color:%2;}").arg(ui->centralwidget->objectName(),colorStr);
    //定义样式
    ui->centralwidget->setStyleSheet(style);

}

void MainForm::sendMessage(MessageType type, int to_port, QString showname){
    QByteArray data;
    QDataStream out(&data, QIODevice::WriteOnly);
    out << type;

    switch (type) {
    case Wake:
        out<<showname;
        break;
    }
    m_udpSocket->writeDatagram(data.data(),data.size(),QHostAddress::Broadcast,to_port);
}

void MainForm::WakeChat(int port, QString showname)
{
    sendMessage(Wake,port,showname);
}

void MainForm::processPendingDatagrams(){
    while(m_udpSocket->hasPendingDatagrams()){
        QByteArray datagram,recordgram;
        datagram.resize(m_udpSocket->pendingDatagramSize());
        recordgram.resize(m_udpSocket->pendingDatagramSize());
        m_udpSocket->readDatagram(datagram.data(),datagram.size());
        recordgram = datagram; //用于再次发送给本用户
        QDataStream in(&datagram,QIODevice::ReadOnly);
        int Type;
        in >> Type;
        qDebug() <<"接受到的dup信息类型:"<< Type;
        QString time = QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss");

        switch (Type) {
        case Wake:
            {
                QString nickName_temp;
                in>>nickName_temp;
                int port_number_temp = get_bind_port(nickName_temp);
                bool isExisted = false;
                QMap<QString, ChatForm *>::iterator ite = chatform_map.find(nickName_temp);
                if(ite!=chatform_map.end()){
                    isExisted = true;
                }

                if(!isExisted){
                    ChatForm *chatform_p = new ChatForm(nickName_temp,m_nickName,port_number_temp);
                    chatform_map.insert(nickName_temp,chatform_p);
                    //为每个chatform的关闭信号进行信号-槽关联
                    connect(chatform_p,SIGNAL(destroy_chatname(QString)),this,SLOT(Erase_form_chatform_map(QString)));
                    chatform_p->show();
                }
            }
            break;

        case Message:
            {
                QString message,sendername;
                in>>sendername>>message;
                bool isExisted = false;
                qDebug() <<"udp从用户:"<< sendername<<"来";
                qDebug()<<"该用户发送了:"<<message;
                QMap<QString, ChatForm *>::iterator ite = chatform_map.find(sendername);
                if(ite!=chatform_map.end()){
                    isExisted = true;
                }

                if(!isExisted){
                    int port_number_temp = get_bind_port(sendername);
                    ChatForm *chatform_p = new ChatForm(sendername,m_nickName,port_number_temp);
                    chatform_map.insert(sendername,chatform_p);
                    //为每个chatform的关闭信号进行信号-槽关联
                    connect(chatform_p,SIGNAL(destroy_chatname(QString)),this,SLOT(Erase_form_chatform_map(QString)));
                    chatform_p->show();
                    //将该消息再转发一遍给自己，因为刚刚创建chatform
                    m_udpSocket->writeDatagram(recordgram.data(),recordgram.size(),QHostAddress::Broadcast,port_number);
                }
            }
            break;
    }
  }
}

void MainForm::Erase_form_chatform_map(QString name){
    QMap<QString, ChatForm *>::iterator ite = chatform_map.find(name);
    if(ite!=chatform_map.end()){
        chatform_map.erase(ite);
    }
}

int MainForm::get_bind_port(QString Name){
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE","connection6");
    db.setDatabaseName("D:/MyQTCode(Win32)/test/sqlmodel/RegisteredInfo.db");
    int ip = 0;

    bool ok = db.open();
    qDebug() << "数据库打开"<<ok;

    QSqlQuery query(db);
    QString sql_str = QString("SELECT * FROM user WHERE nickName='%1'").arg(Name);
    query.exec(sql_str);
    while(query.next()){
        ip = query.value("grade").toInt();
    }
    db.close();

    return ip;
}
