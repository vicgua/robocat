#include "exportador.h"
#include <QJsonArray>
#include <QJsonDocument>

void Exportador::exportar(RoboDatabase *db)
{
    QJsonObject classificacio;
    QStringList categories = db->exportarCategories();
    QMap<QString, QVector<Equip>> equips = db->exportarClassificacio(categories);
    foreach (QString cat, categories) {
        QJsonArray catObj;
        foreach (const Equip &e, equips[cat]) {
            QJsonObject obj;
            exportarEquip(e, obj);
            catObj.append(obj);
        }
        classificacio[cat] = catObj;
    }
    root["Classificació"] = classificacio;

    QJsonArray partidesObj;
    QVector<Partida> partides = db->exportarPartides();
    foreach (const Partida &p, partides) {
        QJsonObject obj;
        exportarPartida(p, obj);
        partidesObj.append(obj);
    }
    root["Partides"] = partidesObj;
}

void Exportador::escriureArxiu(QFile f)
{
    QJsonDocument doc(root);
    f.write(doc.toJson());
}

void Exportador::exportarEquip(const Equip &equip, QJsonObject &obj)
{
    obj["Nom"] = equip.nom;
    obj["Punts de classificació"] = equip.puntsClassificacio;
    obj["Punts de desempat"] = equip.puntsDesempat;
}

void Exportador::exportarPartida(const Partida &partida, QJsonObject &obj)
{
    obj["Ronda"] = partida.ronda;
    obj["Partida"] = partida.partida;
    QJsonObject equip1;
    equip1["Nom"] = partida.equip1;
    equip1["Taps"] = partida.taps1;
    equip1["Bandera"] = partida.bandera1;
    if (partida.extra1 != 0)
        equip1["Extra"] = partida.extra1;
    equip1["Vàlida"] = partida.valid1;
    obj["Equip 1"] = equip1;
    QJsonObject equip2;
    equip2["Nom"] = partida.equip2;
    equip2["Taps"] = partida.taps2;
    equip2["Bandera"] = partida.bandera2;
    if (partida.extra2 != 0)
        equip2["Extra"] = partida.extra2;
    equip2["Vàlida"] = partida.valid2;
    obj["Equip 2"] = equip2;
    if (!partida.notes.isEmpty())
        obj["Notes"] = partida.notes;
}
