#ifndef EQUIP_H
#define EQUIP_H

#include <QString>

struct Equip {
    QString nom;
    QString categoria;
    int puntsClassificacio = 0;
    int puntsDesempat = 0;
};

#endif // EQUIP_H
