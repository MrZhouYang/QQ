#include "loginform.h"
#include "ui_loginform.h"
#include "mainform.h"
#include <QMovie>
#include <QDebug>
#include <QMessageBox>



LoginForm::LoginForm(QWidget *parent) :
    MoveableFramelessWindow(parent),
    ui(new Ui::LoginForm)
{
    ui->setupUi(this);

    QMovie *movie = new QMovie(":/sys/img/blue70-2.gif");
    ui->label->setMovie(movie);
    ui->label_minimize->installEventFilter(this);
    ui->label_shutdown->installEventFilter(this);
    //注册账号label
    ui->label_1->installEventFilter(this);
    movie->start();

    //关联登录按钮点击
    connect(ui->pushButton_login,SIGNAL(clicked(bool)),this,SLOT(doLoginButClick()) );


}

LoginForm::~LoginForm()
{
    delete ui;
}

QWidget *LoginForm::getDragnWidget()
{
    return ui->login_top_widget;
}

bool LoginForm::eventFilter(QObject *object, QEvent *e)
{
    if(e->type()==QEvent::MouseButtonPress&&object==ui->label_shutdown)
    {
         close();
         return true;
    }
    else if(e->type()==QEvent::MouseButtonPress&&object==ui->label_minimize){
        showMinimized();
        return true;//停止转发
    }
    else if(e->type()==QEvent::MouseButtonPress&&object==ui->label_1){
        RegisterDialog *rg_dialog = new RegisterDialog;
        rg_dialog->show();
    }
    return false; //继续转发
}

//登录按钮按下
void LoginForm::doLoginButClick()
{
    //获取用户输入的账号和密码
    QString userName = ui->lineEdit_un->text();
    QString userpwd = ui->lineEdit_pass->text();

    bool iscorrect = IsExisted(userName,userpwd);

    if(iscorrect==false)
    {
        QMessageBox::information(this, tr("提示"),
                                 tr("密码错误或者用户名不存在！"));
    }
    else
    {
        MainForm *m=new MainForm;
        m->show();
        this->hide();
    }
}

//判断数据库中是否存在用户userName且密码匹配
bool LoginForm::IsExisted(const QString &userName, const QString &pwd)
{
    QSqlDatabase db1 = QSqlDatabase::addDatabase("QSQLITE","connection1");
    db1.setDatabaseName("D:/MyQTCode(Win32)/test/sqlmodel/RegisteredInfo.db"); //该数据库中保存了注册成功的账号

    bool ok = db1.open();
    qDebug()<<"注册账号数据库链接："<<ok;

    QSqlQuery query1(db1);
    qDebug() << "connection1:";

    //先判断数据库中是否有该用户
    QString sql_str = QString("SELECT count(*) FROM user WHERE userName='%1'").arg(userName);//该数据库中的表名为user
    query1.exec(sql_str);
    int num1 = 0;
    while(query1.next())
    {
        num1 = query1.value(0).toInt();
        qDebug() <<"表中用户名为<<userName"<<"的数量为"<< num1;
    }
    if(num1<=0)
    {
        db1.close();
        return false;
    }

    //用户名存在，验证密码是否正确
    sql_str = QString("SELECT password FROM user WHERE userName='%1'").arg(userName);
    query1.exec(sql_str);
    while (query1.next()) {
        QString pwd_temp = query1.value("password").toString();
        qDebug()<<"数据库中读出的"<<userName<<"的密码为"<<pwd_temp;
        if(pwd_temp == pwd)
        {
            db1.close();
            return true;
        }
    }
    return false;
}

