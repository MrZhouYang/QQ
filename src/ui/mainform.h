#ifndef MAINFORM_H
#define MAINFORM_H

#include <QWidget>
#include "moveableframelesswindow.h"
#include <QVBoxLayout>
#include "collapseview.h"
#include "colorpickform.h"

namespace Ui {
class MainForm;
}

class MainForm : public MoveableFramelessWindow
{
    Q_OBJECT

public:
    explicit MainForm(QString userName,QString nickName,int port,QWidget *parent = 0);
    ~MainForm();

protected:
      QWidget*getDragnWidget();

private:
    Ui::MainForm *ui;

    QVBoxLayout *page4_layout;

    int port_number; //用于保存用户的端口号

    CollapseView *collapseView_p;

private slots:
    void on_PB_minimize_clicked();
    void on_PB_shutdown_clicked();

    void doChangeColor();
    void onThemeColorChange(QString colorStr);

};

#endif // MAINFORM_H
