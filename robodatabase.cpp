#include "robodatabase.h"
#include <QFile>
#include <QString>
#include <QTextStream>
#include <QSqlQuery>
#include <QSqlDatabase>

void RoboDatabase::setup(const ConnectionInfo &ci)
{
    QSqlDatabase db = QSqlDatabase::addDatabase(ci.dbDriver);
    db.setHostName(ci.hostname);
    db.setDatabaseName(ci.database);
    db.setUserName(ci.username);
    db.setPassword(ci.password);
    connected = false;
    dbDriver = ci.dbDriver;
}

RoboDatabase::RoboDatabase() : QObject() {
    connected = false;
    dbDriver.clear();
}

RoboDatabase::RoboDatabase(const RoboDatabase &other) : QObject() {
    connected = other.connected;
    dbDriver = other.dbDriver;
}

void RoboDatabase::populateInfoEquips(QSqlQueryModel *model)
{
    QLatin1Literal sql("SELECT\n"
                       "    nom,\n"
                       "    punts_totals,\n"
                       "    partides_jugades\n"
                       "FROM\n"
                       "    classificacio_equips\n"
                       "ORDER BY\n"
                       "    nom ASC;\n");
    QSqlQuery query;
    if (!query.exec(sql)) {
        emit errorSql(query.lastError());
        return;
    }
    model->setQuery(query);
    model->setHeaderData(0, Qt::Horizontal, "Nom", Qt::DisplayRole);
    model->setHeaderData(1, Qt::Horizontal, "Punts totals", Qt::DisplayRole);
    model->setHeaderData(2, Qt::Horizontal, "Partides jugades", Qt::DisplayRole);
}

void RoboDatabase::populateEquips(QSqlQueryModel *model)
{
    QLatin1Literal sql("SELECT\n"
                       "    nom\n"
                       "FROM\n"
                       "    equips\n"
                       "ORDER BY\n"
                       "    nom ASC;\n");
    QSqlQuery query;
    if (!query.exec(sql)) {
        emit errorSql(query.lastError());
        return;
    }
    model->setQuery(query);
    model->setHeaderData(0, Qt::Horizontal, "Nom", Qt::DisplayRole);
}

/*void RoboDatabase::afegirEquip(const Equip &equip)
{
    QLatin1Literal sql("INSERT\n"
                       "    INTO\n"
                       "        equips(nom)\n"
                       "    VALUES (:nom);\n");
    QSqlQuery query;
    query.prepare(sql);
    query.bindValue(":nom", equip.nomEquip());
    if (!query.exec()) {
        emit errorSql(query.lastError());
    }
    emit dataChanged();
}

void RoboDatabase::modificarEquip(const Equip &equip)
{
    QLatin1Literal sql("UPDATE\n"
                       "    equips\n"
                       "SET\n"
                       "    nom = :nomNou\n"
                       "WHERE\n"
                       "    nom = :nomOriginal;\n");
    QSqlQuery query;
    query.prepare(sql);
    query.bindValue(":nomNou", equip.nomEquip());
    query.bindValue(":nomOriginal", equip.nomEquipOriginal());
    if (!query.exec()) {
        emit errorSql(query.lastError());
    }
    emit dataChanged();
}

void RoboDatabase::eliminarEquip(const Equip &equip)
{
    QLatin1Literal sql("DELETE\n"
                       "FROM\n"
                       "    equips\n"
                       "WHERE\n"
                       "    nom = :nom;\n");
    QSqlQuery query;
    query.prepare(sql);
    query.bindValue(":nom", equip.nomEquipOriginal());
    if (!query.exec()) {
        emit errorSql(query.lastError());
    }
    emit dataChanged();
}*/

bool RoboDatabase::estaInicialitzada()
{
    QSqlDatabase db = QSqlDatabase::database();
    QStringList tables = db.tables();
    return tables.contains("equips") && tables.contains("partides");
}

void RoboDatabase::inicialitzar()
{
    QSqlError error;
    if (!SentenciesSql::execManySql(SentenciesSql::init::initAll(), error)) {
        emit errorSql(error);
    } else {
        emit inicialitzada();
    }
}

void RoboDatabase::iniciaConnexio()
{
    QSqlDatabase db = QSqlDatabase::database();
    if (db.open()) {
        connected = true;
        emit connexioFinalitzada(true);
    } else {
        connected = false;
        emit connexioFinalitzada(false);
        emit errorSql(db.lastError());
    }
}

void RoboDatabase::desconnecta()
{
    QSqlDatabase db = QSqlDatabase::database();
    db.close();
    connected = false;
    emit desconnectada();
}
