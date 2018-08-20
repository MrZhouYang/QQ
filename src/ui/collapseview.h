#ifndef COLLAPSEVIEW_H
#define COLLAPSEVIEW_H

#include <QWidget>
#include <QVBoxLayout>
#include "collapseviewitem_contact.h"

namespace Ui {
class CollapseView;
}

class CollapseView : public QWidget
{
    Q_OBJECT

public:
    explicit CollapseView(QString userName,QWidget *parent = 0);
    ~CollapseView();

private slots:
    void butClick();

private:
    Ui::CollapseView *ui;

    QVBoxLayout *w_layout;
};

#endif // COLLAPSEVIEW_H
