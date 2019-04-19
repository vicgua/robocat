#ifndef PANTALLAPUNTUACIO_H
#define PANTALLAPUNTUACIO_H

#include <QWidget>

namespace Ui {
class PantallaPuntuacio;
}

class PantallaPuntuacio : public QWidget
{
    Q_OBJECT

public:
    explicit PantallaPuntuacio(QWidget *parent = 0);
    ~PantallaPuntuacio();

private:
    Ui::PantallaPuntuacio *ui;
};

#endif // PANTALLAPUNTUACIO_H
