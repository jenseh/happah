#ifndef HAPPAH_H
#define HAPPAH_H

#include <QtGui/QWidget>
#include "ui_happah.h"

class Happah : public QWidget
{
    Q_OBJECT

public:
    Happah(QWidget *parent = 0);
    ~Happah();

private:
    Ui::HappahClass ui;
};

#endif // HAPPAH_H
