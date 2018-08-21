#ifndef COLLAPSEVIEWITEM_CONTACT_H
#define COLLAPSEVIEWITEM_CONTACT_H

#include <QWidget>
#include <QList>
#include <QVBoxLayout>
#include <QSqlDatabase>
#include <QSqlQuery>
#include "sqliteoperate.h"
#include <QTime>
#include "litteriem.h"
#include <QVector>

#define MAX_PERSON_PIC_NUM 8

namespace Ui {
class CollapseViewItem_Contact;
}

class CollapseViewItem_Contact : public QWidget
{
    Q_OBJECT

public:
    explicit CollapseViewItem_Contact(QString userName,QString titleText,QWidget *parent = 0);
    ~CollapseViewItem_Contact();

    /**
     * @brief 设置标题文字
     * @param titleText
     */
    void setTitleText(QString titleText);

    /**
     * @brief 添加展开抽屉后的内容项目
     * @param widgets 项目列表
     */
    void addSubItems(QList<QWidget *> widgets);

    /**
     * @brief 添加展开抽屉后的内容项目
     * @param widgets 项目
     */
    void addSubItem(QWidget*widget);

private slots:

    /**
     * @brief 点击按钮进行项目折叠
     */
    void onCollapseButClick();

private:
    Ui::CollapseViewItem_Contact *ui;

    QVBoxLayout *item_con_layout;

    QSqlDatabase user_db;

    UserInfo friend_info_s;

    QVector<LitterIem *> litteriem_p_v;

};

#endif // COLLAPSEVIEWITEM_CONTACT_H
