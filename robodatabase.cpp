#include "robodatabase.h"
#include <QFile>
#include <QString>
#include <QTextStream>
#include <QSqlQuery>
#include <QSqlDatabase>
#include <QSqlDriver>

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
    QSqlQuery query;
    if (!query.exec(SentenciesSql::equips::selectEquipInfo)) {
        emit errorSql(query.lastError());
        return;
    }
    model->clear();
    model->setQuery(query);
    model->setHeaderData(0, Qt::Horizontal, "Nom", Qt::DisplayRole);
    model->setHeaderData(1, Qt::Horizontal, "Punts totals", Qt::DisplayRole);
    model->setHeaderData(2, Qt::Horizontal, "Partides jugades", Qt::DisplayRole);
}

void RoboDatabase::populateEquips(QSqlQueryModel *model)
{
    QSqlQuery query;
    if (!query.exec(SentenciesSql::equips::selectEquips)) {
        emit errorSql(query.lastError());
        return;
    }
    model->clear();
    model->setQuery(query);
    model->setHeaderData(0, Qt::Horizontal, "Nom", Qt::DisplayRole);
}

void RoboDatabase::afegirEquip(const QString &nomEquip)
{
    QSqlQuery query;
    query.prepare(SentenciesSql::equips::insertEquip);
    query.bindValue(":nom", nomEquip);
    if (!query.exec()) {
        emit errorSql(query.lastError());
        return;
    }
    emit dataChanged();
}

void RoboDatabase::modificarEquip(const QString &nomAntic, const QString &nomNou)
{
    QSqlQuery query;
    query.prepare(SentenciesSql::equips::updateEquip);
    query.bindValue(":nomAntic", nomAntic);
    query.bindValue(":nomNou", nomNou);
    if (!query.exec()) {
        emit errorSql(query.lastError());
        return;
    }
    emit dataChanged();
}

void RoboDatabase::eliminarEquip(const QString &nomEquip)
{
    QSqlQuery query;
    query.prepare(SentenciesSql::equips::deleteEquip);
    query.bindValue(":nom", nomEquip);
    if (!query.exec()) {
        emit errorSql(query.lastError());
        return;
    }
    emit dataChanged();
}

/*void RoboDatabase::afegirEquip(const Equip &equip)
{
    QLatin1String sql("INSERT\n"
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
    QLatin1String sql("UPDATE\n"
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
    QLatin1String sql("DELETE\n"
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
        if (dbDriver == "QSQLITE") {
            // SQLite requereix habilitar explícitament les claus forànes
            QSqlQuery query;
            if (!query.exec("PRAGMA foreign_keys = ON;")) {
                emit errorSql(query.lastError());
                db.close();
                QSqlDatabase::removeDatabase(db.connectionName());
                return;
            }
        }
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
    QSqlDatabase::removeDatabase(db.connectionName());
    connected = false;
    emit desconnectada();
}
