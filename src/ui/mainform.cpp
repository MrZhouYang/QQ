#include "mainform.h"
#include "ui_mainform.h"

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
