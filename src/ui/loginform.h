#ifndef LOGINFORM_H
#define LOGINFORM_H

#include <QWidget>
#include "moveableframelesswindow.h"
#include <QSqlDatabase>
#include <QSqlQuery>
#include "registerdialog.h"
#include <QString>


namespace Ui {
class LoginForm;
}

class LoginForm : public MoveableFramelessWindow
{
    Q_OBJECT

public:
    explicit LoginForm(QWidget *parent = 0);
    ~LoginForm();

protected:
    QWidget* getDragnWidget();

    bool eventFilter(QObject *object, QEvent *e);

private slots:
    /**
     * @brief 登录按钮点击
     */
    void doLoginButClick();

signals:
    void LoginInfo(int port);

private:
    Ui::LoginForm *ui;

    //判断数据库中是否存在用户userName且密码匹配
    bool IsExisted(const QString &userName,const QString &pwd);

    //根据用户账号获取用户昵称
    QString Get_nickName(const QString &userName);

    //根据用户账号获取用户端口号
    int Get_port(const QString &userName);
};

#endif // LOGINFORM_H
