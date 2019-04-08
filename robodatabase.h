#ifndef ROBODATABASE_H
#define ROBODATABASE_H

#include "data_objects/equip.h"
#include "data_objects/estadistiquesequip.h"
#include "data_objects/connectioninfo.h"
#include <QString>
#include <QObject>
#include <QMap>
#include <QSqlError>

class RoboDatabase : public QObject
{
    Q_OBJECT
public:
    void asPostgres(const QString &host, const QString &database,
                                    const QString &username, const QString &password);
    void asSqlite(const QString &database);

    void setup(const ConnectionInfo &ci);

    RoboDatabase();
    RoboDatabase(const RoboDatabase &other);

    bool isConnected() { return connected; }
    QMap<Equip, EstadistiquesEquip> equips();
    void afegirEquip(const Equip &equip);
    void modificarEquip(const Equip &equip);
    void eliminarEquip(const Equip &equip);
    bool estaInicialitzada() { return false; }
    void inicialitzar();

signals:
    void errorSql(const QSqlError &error);
    void connexioFinalitzada(bool exitosa);
    void desconnectada();

    void dataChanged();

public slots:
    void iniciaConnexio();
    void desconnecta();

private:
    enum DbType {
        NULL_DB,
        POSTGRES,
        SQLITE
    };

    bool connected;
    DbType dbType;
    QString dbDriver;
    QString sqlInit() const;

};

#endif // ROBODATABASE_H
