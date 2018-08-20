#ifndef SQLITEOPERATE_H
#define SQLITEOPERATE_H

#include <QObject>
#include <QSqlDatabase>
#include <QSqlQuery>
#include "data_pools.h"

/*
 * db中的user表中保存着注册成功的账号信息
 * userName表中保存着用户userName的所有好友名
 * */

class SqliteOperate : public QObject
{
    Q_OBJECT
public:
    explicit SqliteOperate(QSqlDatabase &db, QObject *parent = 0);
    ~SqliteOperate();

    //返回db中的相应表的行数
    int row_of_table(const QString table_name);

    //返回db中相应表是否存在
    bool isTableExist(const QString table_name);

    //在db中建立相应表 userName
    bool create_table(const QString table_name);

    //为friend系列表添加数据
    bool insert_into_friendtable(const QString table_name, const QString userName);

    //读取用户的所有好友信息
    UserInfo Get_ALL_Friend_Info(const QString table_name);

private:
    QSqlDatabase m_db;

    //判断friend系列表中的userName是否存在
    bool is_userName_exist(const QString table_name, const QString userName);

signals:

public slots:
};

#endif // SQLITEOPERATE_H
