#include "pantallapuntuacio.h"
#include "ui_pantallapuntuacio.h"

PantallaPuntuacio::PantallaPuntuacio(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PantallaPuntuacio)
{
    ui->setupUi(this);
}

PantallaPuntuacio::~PantallaPuntuacio()
{
    delete ui;
}
