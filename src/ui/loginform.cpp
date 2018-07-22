#include "loginform.h"
#include "ui_loginform.h"
#include "mainform.h"
#include <QMovie>
#include <QDebug>


LoginForm::LoginForm(QWidget *parent) :
    MoveableFramelessWindow(parent),
    ui(new Ui::LoginForm)
{
    ui->setupUi(this);

    QMovie *movie = new QMovie(":/sys/img/blue70-2.gif");
    ui->label->setMovie(movie);
    ui->label_minimize->installEventFilter(this);
    ui->label_shutdown->installEventFilter(this);
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
    return false; //继续转发
}


void LoginForm::doLoginButClick()
{

    MainForm *m=new MainForm;
    m->show();
    this->hide();
}
