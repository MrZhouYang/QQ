#include "litteriem.h"
#include "ui_litteriem.h"
#include <QDebug>

#include <QPixmap>

LitterIem::LitterIem(QString picPath,QWidget *parent) :
    QWidget(parent),
    ui(new Ui::LitterIem)
{
    ui->setupUi(this);

    QPixmap p(picPath);
    ui->label_pic->setPixmap(p);
}

LitterIem::LitterIem(QString picPath, int port, QString Name, QString senderName, QWidget *parent):
    QWidget(parent),port_number(port),Litter_nickName(Name),sender_nickName(senderName),
    ui(new Ui::LitterIem)
{
    ui->setupUi(this);

    QPixmap p(picPath);
    ui->label_pic->setPixmap(p);

    ui->label_name->setText(Litter_nickName);
}

LitterIem::~LitterIem()
{

    delete ui;
}

void LitterIem::mouseDoubleClickEvent(QMouseEvent *event){
    //qDebug() << "鼠标双击";
    int port = get_bind_port(sender_nickName); //注意应该读取的是本人的port
    qDebug() << "mainform用户port"<<port;
    emit wake_message_to(port,Litter_nickName);//mainform收到该信号后向mainform对应的端口发送Wake类型的UDP信息来激活ChatForm窗口
}

int LitterIem::get_bind_port(QString Name){
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
