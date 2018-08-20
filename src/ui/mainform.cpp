#include "mainform.h"
#include "ui_mainform.h"

#include "collapseview.h"
#include "colorpickform.h"

#include <QDebug>
#include <QDesktopWidget>
#include <QApplication>


//主窗口与屏幕边缘的距离
int MAIN_FORM_OADDING =10;

MainForm::MainForm(QString userName, QString nickName, int port, QWidget *parent) :
    MoveableFramelessWindow(parent),port_number(port),
    ui(new Ui::MainForm)
{
    ui->setupUi(this);

    ui->label_nick->setText(nickName);

    page4_layout = new QVBoxLayout(this);
    page4_layout->setContentsMargins(0,0,0,0);//设置上下左右的边距均为0
    page4_layout->setSpacing(0); //This property holds the spacing between widgets inside the layout.
    ui->page_4->setLayout(page4_layout);

    //在布局中加入联系人列表
    page4_layout->addWidget(new CollapseView(userName));

    //关联切换皮肤颜色按钮事件
    connect(ui->pushButton_skin,SIGNAL(clicked()),this,SLOT(doChangeColor()));

    //获取屏幕
    QDesktopWidget* desktopWidget = QApplication::desktop();

    //得到屏幕宽度
    int screenWidth = desktopWidget->width();

    //转移到右边
    this->move(screenWidth-MAIN_FORM_OADDING-this->width(),MAIN_FORM_OADDING);

    connect(ui->pushButton_minimize,SIGNAL(pressed()),this,SLOT(on_PB_minimize_clicked()));
    connect(ui->pushButton_shutdown,SIGNAL(pressed()),this,SLOT(on_PB_shutdown_clicked()));
}

MainForm::~MainForm()
{
    delete ui;
}

QWidget *MainForm::getDragnWidget()
{
    return ui->main_top;
}

void MainForm::on_PB_minimize_clicked()
{
    this->showMinimized();
}

void MainForm::on_PB_shutdown_clicked()
{
    this->deleteLater();
}

void MainForm::doChangeColor()
{

    MY_COLOR_PICK_FORM.show();
    MY_COLOR_PICK_FORM.raise(); //Raises this widget to the top of the parent widget's stack.
    MY_COLOR_PICK_FORM.setFocus(); //Gives the keyboard input focus to this widget (or its focus proxy) if this widget or one of its parents is the active window.

    ColorPickForm *f= &(MY_COLOR_PICK_FORM);

    connect(f,SIGNAL(themColorChanged(QString)),this,SLOT(onThemeColorChange(QString)));

}

void MainForm::onThemeColorChange(QString colorStr)
{
    //组合成qcc样式表
    QString style=QString("#%1{background-color:%2;}").arg(ui->centralwidget->objectName(),colorStr);
    //定义样式
    ui->centralwidget->setStyleSheet(style);

}

