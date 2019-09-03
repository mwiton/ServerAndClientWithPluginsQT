#include "display.h"

Display::Display(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Display)
{
    ui->setupUi(this);
}

Display::~Display()
{
    delete ui;
}
