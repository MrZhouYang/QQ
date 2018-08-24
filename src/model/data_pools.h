#ifndef DATA_POOLS_H
#define DATA_POOLS_H

#include <QString>
#include <QVector>

struct UserInfo{
    QVector<QString> nickName_v;
    QVector<int> port_v;
};

enum MessageType{Message, Wake, FileName, Refuse};

#endif // DATA_POOLS_H
