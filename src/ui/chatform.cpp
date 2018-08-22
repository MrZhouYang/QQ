#include "chatform.h"
#include "ui_chatform.h"
#include <QDebug>

ChatForm::ChatForm(QString ChatName, QString senderName, int port, QWidget *parent) :
    MoveableFramelessWindow(parent),m_sendername(senderName),m_port_number(port),
    ui(new Ui::ChatForm)
{
    ui->setupUi(this);

    ui->pb_nickName->setText(ChatName);

    //udp相关
    m_udpSocket = new QUdpSocket(this);
    qDebug() << "udp套接字绑定端口："<<2000;
    m_udpSocket->bind(2000,QUdpSocket::ShareAddress | QUdpSocket::ReuseAddressHint);
    connect(m_udpSocket,SIGNAL(readyRead()),this,SLOT(processPendingDatagrams()) );
    connect(ui->pb_send,SIGNAL(clicked()),this,SLOT(pb_send_clicked()));


    connect(ui->pb_minimize,SIGNAL(pressed()),this,SLOT(on_PB_minimize_clicked()));
    connect(ui->pb_shutdown,SIGNAL(pressed()),this,SLOT(on_PB_shutdown_clicked()));
}

ChatForm::~ChatForm()
{
    delete ui;
}

QWidget *ChatForm::getDragnWidget()
{
    return ui->w_top;
}

void ChatForm::sendMessage(MessageType type)
{
    QByteArray data;
    QDataStream out(&data, QIODevice::WriteOnly);
    out << type;

    switch (type) {
    case Message:
        if(ui->textEdit_input->toPlainText() == ""){
            QMessageBox::information(0,tr("警告"),tr("发送内容不能为空"),QMessageBox::Ok);
            return;
        }
        QString msg = ui->textEdit_input->toHtml();
        ui->textEdit_input->clear();
        ui->textEdit_input->setFocus();
        out<< m_sendername<<msg;
        ui->textBrowser_show->verticalScrollBar()->setValue( ui->textBrowser_show->verticalScrollBar()->maximum() );
        break;
    }
    m_udpSocket->writeDatagram(data,data.length(),QHostAddress::Broadcast,m_port_number);
}

void ChatForm::processPendingDatagrams(){
    while(m_udpSocket->hasPendingDatagrams()){
        QByteArray datagram;
        datagram.resize(m_udpSocket->pendingDatagramSize());
        m_udpSocket->readDatagram(datagram.data(),datagram.size());
        QDataStream in(&datagram,QIODevice::WriteOnly);
        int messageType;
        in >> messageType;
        QString time = QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss");

        switch (messageType) {
        case Message:
            QString message,sendername;
            in>>sendername>>message;
            ui->textBrowser_show->setTextColor(Qt::blue);
            ui->textBrowser_show->setCurrentFont(QFont("Times New Roman",12));
            ui->textBrowser_show->append( "["+sendername+"]"+time );
            ui->textBrowser_show->append(message);
            break;
        }
    }
}

void ChatForm::pb_send_clicked()
{
    sendMessage(Message);
}

void ChatForm::on_PB_minimize_clicked()
{
    this->showMinimized();
}

void ChatForm::on_PB_shutdown_clicked()
{
    this->deleteLater();
}
