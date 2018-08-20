#include "sqliteoperate.h"
#include <QDebug>
#include <QSqlError>

SqliteOperate::SqliteOperate(QSqlDatabase &db,QObject *parent) : m_db(db),QObject(parent)
{
}

SqliteOperate::~SqliteOperate()
{

}

//返回db中的相应表的行数
int SqliteOperate::row_of_table(const QString table_name)
{
    QSqlQuery query(m_db);
    //先判断该表是否存在
    bool exist = isTableExist(table_name);
    if(!exist)
    {
       return -1;//如果不存在该表，则返回-1
    }

    query.exec( QString("select * from %1").arg(table_name) );
    query.last();
    int numRows = query.at()+1;
    qDebug()<<"行数为："<<numRows;
    return numRows;
}

//返回db中相应表是否存在
bool SqliteOperate::isTableExist(const QString table_name)
{
    QSqlQuery query(m_db);
    query.exec(QString("select * from sqlite_master where type='table' and name='%1'").arg(table_name));
    bool exist = query.next();

    if(!exist)
    {
        qDebug() << "table does not exist";
        return false;
    }
    else
    {
        qDebug() << "table exists";
        return true;
    }

}

//在db中建立相应表
bool SqliteOperate::create_table(const QString table_name)
{
    QSqlQuery query(m_db);
    //先判断该表是否存在
    bool exist = isTableExist(table_name);
    if(exist)
    {
       return false;//如果已存在该表，返回false
    }

    QString sql = QString("create table '%1' (id INTEGER primary key autoincrement,userName varchar(40),ip varchar(30), "
                          "port varchar(10),phone varchar(20),email varchar(50))").arg(table_name);

    if(query.exec(sql))
        return true;
    else
    {
        qDebug()<<"Table Create failed";
        qDebug()<<query.lastError();
        return false;
    }

}

//为friend系列表添加数据
bool SqliteOperate::insert_into_friendtable(const QString table_name, const QString userName)
{
    QString sql = QString("INSERT INTO %1 VALUES (NULL,'%2',NULL,NULL,NULL,NULL)").arg(table_name).arg(userName);
    QSqlQuery query(m_db);
    //先判断该表是否存在
    bool exist = isTableExist(table_name);
    if(!exist)
    {
       return false;//如果不存在该表，返回false
    }

    bool userName_exist = is_userName_exist(table_name,userName);
    if(userName_exist){
        return false; //如果已存在该好友，则返回false
    }

    if(query.exec(sql))
        return true;
    else
    {
        qDebug()<<"Table insert failed";
        qDebug()<<query.lastError();
        return false;
    }
}

//读取用户的所有好友信息
UserInfo SqliteOperate::Get_ALL_Friend_Info(const QString table_name)
{
    UserInfo Friend_info;

    QString sql = QString("select * from %1").arg(table_name);
    QSqlQuery query(m_db);
    //先判断该表是否存在
    bool exist = isTableExist(table_name);
    if(!exist)
    {
       qDebug()<<"读取好友信息失败";
       return Friend_info;
    }

    query.exec(sql);
    while(query.next()){
        Friend_info.nickName_v.push_back( query.value("email").toString() );
        Friend_info.port_v.push_back( query.value("port").toString().toInt() );
    }

    return Friend_info;

}

//判断friend系列表中的userName是否存在
bool SqliteOperate::is_userName_exist(const QString table_name, const QString userName){
    QSqlQuery query(m_db);
    query.exec(QString("SELECT count(*) FROM %1 WHERE userName='%2'").arg(table_name).arg(userName));
    int num = 0;
    while(query.next()){
        num = query.value(0).toInt();
    }

    if(num>0){
        qDebug()<<table_name<<"表中已存在"<<userName;
        return true;
    }
    else{
        return false;
    }
}

