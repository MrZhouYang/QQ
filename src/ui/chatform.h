#ifndef CHATFORM_H
#define CHATFORM_H

#include <QWidget>
#include "moveableframelesswindow.h"

namespace Ui {
class ChatForm;
}

class ChatForm : public MoveableFramelessWindow
{
    Q_OBJECT

public:
    explicit ChatForm(QWidget *parent = 0);
    ~ChatForm();

protected:
      QWidget*getDragnWidget();

private:
    Ui::ChatForm *ui;

private slots:
    void on_PB_minimize_clicked();
    void on_PB_shutdown_clicked();
};

#endif // CHATFORM_H
