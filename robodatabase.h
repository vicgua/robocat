#ifndef ROBODATABASE_H
#define ROBODATABASE_H

#include "data_objects/connectioninfo.h"
#include "data_objects/partida.h"
#include "data_objects/equip.h"
#include "sentenciessql.h"
#include <QString>
#include <QPair>
#include <QObject>
#include <QMap>
#include <QSqlError>
#include <QSqlQueryModel>
#include <QVector>

class RoboDatabase : public QObject
{
    Q_OBJECT

public:
    void setup(const ConnectionInfo &ci);

    RoboDatabase();
    RoboDatabase(const RoboDatabase &other);

    bool isConnected() { return connected; }
    void populateInfoEquips(QSqlQueryModel *model);
    void populateEquips(QSqlQueryModel *model);
    void populatePartides(QSqlQueryModel *model);
    void populateClassificacio(QSqlQueryModel *model);
    bool estaInicialitzada();
    Equip infoFromEquip(QString nomEquip);
    Partida infoFromPartida(const QPair<int, int> &pkPartida);
    QPair<int, int> properaPartida();
    QVector<Partida> ultimesPartides();

    QMap<QString, int> categories();

signals:
    void errorSql(const QSqlError &error);
    void connexioFinalitzada(bool exitosa);
    void desconnectada();
    void inicialitzada();
    void dataChanged();

public slots:
    void iniciaConnexio();
    void desconnecta();
    void inicialitzar();
    void afegirEquip(const Equip &equip);
    void modificarEquip(const QString &nomAntic, const Equip &nouEquip);
    void eliminarEquip(const QString &nomEquip);
    void afegirPartida(const Partida &partida);
    void modificarPartida(const QPair<int, int> &antigaPk, const Partida &novaPartida);
    void eliminarPartida(const QPair<int, int> &pk);

private:
    bool connected;
    QString dbDriver;

};

#endif // ROBODATABASE_H
