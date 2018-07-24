#include "registerdialog.h"
#include "ui_registerdialog.h"


RegisterDialog::RegisterDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::RegisterDialog)
{
    ui->setupUi(this);
    ui->LE_pwd->setEchoMode(QLineEdit::Password);

    connect(ui->PB_sure,SIGNAL(clicked()),this,SLOT(PB_sure_clicked()));
    connect(ui->PB_cancel,SIGNAL(clicked()),this,SLOT(PB_cancle_clicked()));

    user_db = QSqlDatabase::addDatabase("QSQLITE","connect2");
    user_db.setDatabaseName("D:/MyQTCode(Win32)/test/sqlmodel/RegisteredInfo.db"); //该数据库中保存了注册成功的账号

    bool ok = user_db.open();
    qDebug()<<"注册账号数据库链接："<<ok;
}

RegisterDialog::~RegisterDialog()
{
    user_db.close();
    delete ui;
}

void RegisterDialog::PB_sure_clicked()
{
    //获取用户输入的账号和密码
    QString userName = ui->LE_username->text();
    QString userpwd = ui->LE_pwd->text();

    if(userName.isEmpty() || userpwd.isEmpty())
    {
        QMessageBox::information(this,tr("提示"),tr("请输入完整信息"));
        return;
    }

    QSqlQuery query(user_db);
    //先判断数据库中是否有该用户
    QString sql_str = QString("SELECT count(*) FROM user WHERE userName='%1'").arg(userName);//该数据库中的表名为user
    query.exec(sql_str);
    int num1 = 0;
    while(query.next())
    {
        num1 = query.value(0).toInt();
        qDebug() <<"表中用户名为<<userName"<<"的数量为"<< num1;
    }
    if(num1>0)//用户名已经存在
    {
        QMessageBox::information(this,tr("提示"),tr("用户名已经存在"));
        return;
    }

    //用户名不存在，则向数据库中添加数据
    query.prepare("INSERT INTO user (userName,password) VALUES (:userName,:password)");
    query.bindValue(":userName",userName);
    query.bindValue(":password",userpwd);
    if(query.exec())
        QMessageBox::information(this,tr("提示"),tr("注册成功"));

    //为注册用户在数据库建立其对应的的好友表用来保存好友信息
    SqliteOperate sql_opr(user_db,this);
    sql_opr.create_table(userName);
}

void RegisterDialog::PB_cancle_clicked()
{
    this->deleteLater();
}

