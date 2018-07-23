#ifndef LOGINFORM_H
#define LOGINFORM_H

#include <QWidget>
#include "moveableframelesswindow.h"
#include <QSqlDatabase>
#include <QSqlQuery>
#include "registerdialog.h"


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

private:
    Ui::LoginForm *ui;

    //判断数据库中是否存在用户userName且密码匹配
    bool IsExisted(const QString &userName,const QString &pwd);
};

#endif // LOGINFORM_H
