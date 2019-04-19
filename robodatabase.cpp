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
    model->setHeaderData(1, Qt::Horizontal, "Punts de classificació", Qt::DisplayRole);
    model->setHeaderData(2, Qt::Horizontal, "Punts de desempat", Qt::DisplayRole);
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

void RoboDatabase::populatePartides(QSqlQueryModel *model)
{
    QSqlQuery query;
    if (!query.exec(SentenciesSql::partides::selectPartides)) {
        emit errorSql(query.lastError());
        return;
    }
    model->clear();
    model->setQuery(query);
    model->setHeaderData(0, Qt::Horizontal, "Ronda", Qt::DisplayRole);
    model->setHeaderData(1, Qt::Horizontal, "Equip 1", Qt::DisplayRole);
    model->setHeaderData(2, Qt::Horizontal, "Equip 2", Qt::DisplayRole);
    model->setHeaderData(3, Qt::Horizontal, "Taps 1", Qt::DisplayRole);
    model->setHeaderData(4, Qt::Horizontal, "Taps 2", Qt::DisplayRole);
    model->setHeaderData(5, Qt::Horizontal, "Bandera 1", Qt::DisplayRole);
    model->setHeaderData(6, Qt::Horizontal, "Bandera 2", Qt::DisplayRole);
    model->setHeaderData(7, Qt::Horizontal, "Extra 1", Qt::DisplayRole);
    model->setHeaderData(8, Qt::Horizontal, "Extra 2", Qt::DisplayRole);
    model->setHeaderData(9, Qt::Horizontal, "TOTAL 1", Qt::DisplayRole);
    model->setHeaderData(10, Qt::Horizontal, "TOTAL 2", Qt::DisplayRole);
    model->setHeaderData(11, Qt::Horizontal, "Notes", Qt::DisplayRole);
}

#if 0
void RoboDatabase::populatePartides(QVector<Partida> &partides)
{
    QSqlQuery query;
    if (!query.exec(SentenciesSql::partides::selectPartides)) {
        emit errorSql(query.lastError());
        return;
    }
    partides.clear();
    int resultSize = query.size();
    if (resultSize != -1) {
        partides.reserve(resultSize);
    }
    while (query.next()) {
        Partida p;
        p.ronda = query.value(0).toInt();
        p.equip1 = query.value(1).toString();
        p.equip2 = query.value(2).toString();
        p.taps1 = query.value(3).toInt();
        p.taps2 = query.value(4).toInt();
        p.bandera1 = query.value(5).toBool();
        p.bandera2 = query.value(6).toBool();
        p.extra1 = query.value(7).toInt();
        p.extra2 = query.value(8).toInt();
        p.notes = query.value(9).toString(); // Els NULLs es converteixen en strings buits
        partides.append(p);
    }
}
#endif

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

Equip RoboDatabase::infoFromEquip(QString nomEquip)
{
    Equip e;
    e.nom = nomEquip;
    QSqlQuery query;
    query.prepare(SentenciesSql::equips::selectInfoFromEquip);
    query.bindValue(":nom", nomEquip);
    if (!query.exec()) {
        emit errorSql(query.lastError());
        return e;
    }
    if (query.next()) {
        e.puntsClassificacio = query.value(0).toInt();
        e.puntsDesempat = query.value(1).toInt();
    }
    return e;
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
