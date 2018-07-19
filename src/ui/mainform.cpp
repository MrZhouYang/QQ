#include "mainform.h"
#include "ui_mainform.h"

#include "collapseview.h"

#include <QDebug>
#include <QDesktopWidget>
#include <QApplication>


//主窗口与屏幕边缘的距离
int MAIN_FORM_OADDING =10;

MainForm::MainForm(QWidget *parent) :
    MoveableFramelessWindow(parent),
    ui(new Ui::MainForm)
{
    ui->setupUi(this);

    page4_layout = new QVBoxLayout(this);
    page4_layout->setContentsMargins(0,0,0,0);//设置上下左右的边距均为0
    page4_layout->setSpacing(0); //This property holds the spacing between widgets inside the layout.
    ui->page_4->setLayout(page4_layout);

    //在布局中加入联系人列表
    page4_layout->addWidget(new CollapseView());

    //获取屏幕
    QDesktopWidget* desktopWidget = QApplication::desktop();

    //得到屏幕宽度
    int screenWidth = desktopWidget->width();

    //转移到右边
    this->move(screenWidth-MAIN_FORM_OADDING-this->width(),MAIN_FORM_OADDING);
}

MainForm::~MainForm()
{
    delete ui;
}

QWidget *MainForm::getDragnWidget()
{
    return ui->main_top;
}
