#include "litteriem.h"
#include "ui_litteriem.h"

#include <QPixmap>

LitterIem::LitterIem(QString picPath,QWidget *parent) :
    QWidget(parent),
    ui(new Ui::LitterIem)
{
    ui->setupUi(this);

    QPixmap p(picPath);
    ui->label_pic->setPixmap(p);
}

LitterIem::LitterIem(QString picPath, int port, QString Name, QWidget *parent):
    QWidget(parent),port_number(port),nickName(Name),
    ui(new Ui::LitterIem)
{
    ui->setupUi(this);

    QPixmap p(picPath);
    ui->label_pic->setPixmap(p);

    ui->label_name->setText(nickName);
}

LitterIem::~LitterIem()
{
    delete ui;
}
