#ifndef EXPORTADOR_H
#define EXPORTADOR_H

#include "robodatabase.h"
#include "data_objects/equip.h"
#include "data_objects/partida.h"
#include <QFile>
#include <QJsonObject>

class Exportador
{
public:
    void exportar(RoboDatabase *db);
    void escriureArxiu(QFile f);

private:
    QJsonObject root;
    void exportarEquip(const Equip &equip, QJsonObject &obj);
    void exportarPartida(const Partida &partida, QJsonObject &obj);
};

#endif // EXPORTADOR_H
