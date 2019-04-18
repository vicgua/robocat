#ifndef ROBODATABASE_H
#define ROBODATABASE_H

#include "data_objects/connectioninfo.h"
#include "data_objects/partida.h"
#include "sentenciessql.h"
#include <QString>
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
    //void populatePartides(QVector<Partida> &partides);
    bool estaInicialitzada();

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
    void afegirEquip(const QString &nomEquip);
    void modificarEquip(const QString &nomAntic, const QString &nomNou);
    void eliminarEquip(const QString &nomEquip);

private:
    bool connected;
    QString dbDriver;

};

#endif // ROBODATABASE_H
