#ifndef ESTADISTIQUESEQUIP_H
#define ESTADISTIQUESEQUIP_H

#include <QObject>

class EstadistiquesEquip
{
    Q_GADGET
    Q_PROPERTY(int puntuacio_total MEMBER puntuacio_total)
    Q_PROPERTY(int num_partides MEMBER num_partides)
public:
    int puntuacio_total;
    int num_partides;
};

#endif // ESTADISTIQUESEQUIP_H
