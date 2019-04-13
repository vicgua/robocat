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

QMap<Equip, EstadistiquesEquip> RoboDatabase::equips()
{
    QLatin1Literal sql("SELECT\n"
                       "    e.nom,\n"
                       "    COALESCE(SUM(pe.punts),\n"
                       "    0) AS total_punts,\n"
                       "    COUNT(pe.equip) AS num_partits\n"
                       "FROM\n"
                       "    equips AS e\n"
                       "LEFT OUTER JOIN punts_equip AS pe ON\n"
                       "    e.nom = pe.equip\n"
                       "GROUP BY\n"
                       "    e.nom;\n");
    QSqlQuery query;
    QMap<Equip, EstadistiquesEquip> resultat;
    if (!query.exec(sql)) {
        emit errorSql(query.lastError());
        return resultat;
    }
    while (query.next()) {
        EstadistiquesEquip est;
        est.puntuacio_total = query.value(1).toInt();
        est.num_partides = query.value(2).toInt();
        QString nomEquip = query.value(0).toString();
        resultat[Equip(nomEquip)] = est;
    }
    return resultat;
}

void RoboDatabase::afegirEquip(const Equip &equip)
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
}

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

QString RoboDatabase::sqlInit()
{
    QFile sqlFile(":/sql_scripts/init.sql");
    if (!sqlFile.open(QFile::ReadOnly | QFile::Text)) {
        throw "No es pot obrir script SQL";
    }
    QTextStream stream(&sqlFile);
    return stream.readAll();
}
