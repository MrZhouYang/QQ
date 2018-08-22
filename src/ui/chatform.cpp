#include "chatform.h"
#include "ui_chatform.h"

ChatForm::ChatForm(QWidget *parent) :
    MoveableFramelessWindow(parent),
    ui(new Ui::ChatForm)
{
    ui->setupUi(this);

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

void ChatForm::on_PB_minimize_clicked()
{
    this->showMinimized();
}

void ChatForm::on_PB_shutdown_clicked()
{
    this->deleteLater();
}
