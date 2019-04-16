#ifndef ROBODATABASE_H
#define ROBODATABASE_H

#include "data_objects/connectioninfo.h"
#include "sentenciessql.h"
#include <QString>
#include <QObject>
#include <QMap>
#include <QSqlError>
#include <QSqlQueryModel>

class RoboDatabase : public QObject
{
    Q_OBJECT
    Q_PROPERTY(bool connected READ isConnected CONSTANT)
    Q_PROPERTY(bool inicialitzada READ estaInicialitzada CONSTANT)
public:
    void setup(const ConnectionInfo &ci);

    RoboDatabase();
    RoboDatabase(const RoboDatabase &other);

    bool isConnected() { return connected; }
    void populateInfoEquips(QSqlQueryModel *model);
    void populateEquips(QSqlQueryModel *model);
    /*void afegirEquip(const Equip &equip);
    void modificarEquip(const Equip &equip);
    void eliminarEquip(const Equip &equip);*/
    bool estaInicialitzada();
    void inicialitzar();

signals:
    void errorSql(const QSqlError &error);
    void connexioFinalitzada(bool exitosa);
    void desconnectada();
    void inicialitzada();
    void dataChanged();

public slots:
    void iniciaConnexio();
    void desconnecta();

private:
    bool connected;
    QString dbDriver;
    static QString sqlInit();

};

#endif // ROBODATABASE_H
