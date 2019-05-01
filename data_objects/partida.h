#ifndef PARTIDA_H
#define PARTIDA_H

#include <QString>

struct Partida {
    int ronda;
    int partida;
    QString equip1;
    QString equip2;
    int taps1 = 0;
    int taps2 = 0;
    bool bandera1 = false;
    bool bandera2 = false;
    bool valid1 = true;
    bool valid2 = true;
    int extra1 = 0;
    int extra2 = 0;
    QString notes;

    int total1() const {
        if (!valid1) return 0;
        return taps1 + (bandera1 ? 25 : 0) + extra1;
    }

    int total2() const {
        if (!valid2) return 0;
        return taps2 + (bandera2 ? 25 : 0) + extra2;
    }

    int punts1() const {
        if (!valid1) return 0;
        if (total1() > total2()) return 3;
        else if (total1() == total2()) return 1;
        else return 0;
    }

    int punts2() const {
        if (!valid2) return 0;
        if (total2() > total1()) return 3;
        else if (total2() == total1()) return 1;
        else return 0;
    }

    bool winner1() const {
        return valid1 && (total1() >= total2());
    }

    bool winner2() const {
        return valid2 && (total2() >= total1());
    }
};

#endif // PARTIDA_H
