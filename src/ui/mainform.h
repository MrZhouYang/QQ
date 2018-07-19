#ifndef MAINFORM_H
#define MAINFORM_H

#include <QWidget>
#include "moveableframelesswindow.h"
#include <QVBoxLayout>

namespace Ui {
class MainForm;
}

class MainForm : public MoveableFramelessWindow
{
    Q_OBJECT

public:
    explicit MainForm(QWidget *parent = 0);
    ~MainForm();

protected:
      QWidget*getDragnWidget();

private:
    Ui::MainForm *ui;

    QVBoxLayout *page4_layout;

private slots:
    void on_PB_minimize_clicked();
    void on_PB_shutdown_clicked();
};

#endif // MAINFORM_H
