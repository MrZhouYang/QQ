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
    qDebug() << "鼠标双击";
    chatform_p = new ChatForm(Litter_nickName,sender_nickName,port_number);
    chatform_p->show();
}
