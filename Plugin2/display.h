#ifndef DISPLAY_H
#define DISPLAY_H

#include <QWidget>
#include "ui_display.h"

class Display : public QWidget
{
    Q_OBJECT

public:
    explicit Display(QWidget *parent = 0);
    ~Display();
    Ui::Display *ui;
};

#endif // DISPLAY_H
