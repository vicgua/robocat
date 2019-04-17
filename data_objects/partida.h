#ifndef PARTIDA_H
#define PARTIDA_H

#include <QString>

struct Partida {
    int ronda;
    QString equip1;
    QString equip2;
    int taps1;
    int taps2;
    bool bandera1;
    bool bandera2;
    int extra1;
    int extra2;
    QString notes;
};

#endif // PARTIDA_H
