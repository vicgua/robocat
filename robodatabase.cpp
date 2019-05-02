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
    db.setPort(ci.port);
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
    model->setHeaderData(1, Qt::Horizontal, "Categoria", Qt::DisplayRole);
    model->setHeaderData(2, Qt::Horizontal, "Punts de classificació", Qt::DisplayRole);
    model->setHeaderData(3, Qt::Horizontal, "Punts de desempat", Qt::DisplayRole);
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
    model->setHeaderData(1, Qt::Horizontal, "Partida", Qt::DisplayRole);
    model->setHeaderData(2, Qt::Horizontal, "Equip 1", Qt::DisplayRole);
    model->setHeaderData(3, Qt::Horizontal, "Equip 2", Qt::DisplayRole);
    model->setHeaderData(4, Qt::Horizontal, "Taps 1", Qt::DisplayRole);
    model->setHeaderData(5, Qt::Horizontal, "Taps 2", Qt::DisplayRole);
    model->setHeaderData(6, Qt::Horizontal, "Bandera 1", Qt::DisplayRole);
    model->setHeaderData(7, Qt::Horizontal, "Bandera 2", Qt::DisplayRole);
    model->setHeaderData(8, Qt::Horizontal, "Vàlida 1", Qt::DisplayRole);
    model->setHeaderData(9, Qt::Horizontal, "Vàlida 2", Qt::DisplayRole);
    model->setHeaderData(10, Qt::Horizontal, "Extra 1", Qt::DisplayRole);
    model->setHeaderData(11, Qt::Horizontal, "Extra 2", Qt::DisplayRole);
    model->setHeaderData(12, Qt::Horizontal, "TOTAL 1", Qt::DisplayRole);
    model->setHeaderData(13, Qt::Horizontal, "TOTAL 2", Qt::DisplayRole);
    model->setHeaderData(14, Qt::Horizontal, "Notes", Qt::DisplayRole);
}

void RoboDatabase::populateClassificacio(QSqlQueryModel *model)
{
    QSqlQuery query;
    if (!query.exec(SentenciesSql::partides::selectClassificacio)) {
        emit errorSql(query.lastError());
        return;
    }
    model->clear();
    model->setQuery(query);
    model->setHeaderData(0, Qt::Horizontal, "Equip", Qt::DisplayRole);
    model->setHeaderData(1, Qt::Horizontal, "Punts", Qt::DisplayRole);
    model->setHeaderData(2, Qt::Horizontal, "Desempat", Qt::DisplayRole);
    model->setHeaderData(3, Qt::Horizontal, "Categoria", Qt::DisplayRole);
}

void RoboDatabase::afegirEquip(const Equip &equip)
{
    QSqlQuery query;
    query.prepare(SentenciesSql::equips::insertEquip);
    query.bindValue(":nom", equip.nom);
    query.bindValue(":categoria", equip.categoria);
    if (!query.exec()) {
        emit errorSql(query.lastError());
        return;
    }
    emit dataChanged();
}

void RoboDatabase::modificarEquip(const QString &nomAntic, const Equip &nouEquip)
{
    QSqlQuery query;
    query.prepare(SentenciesSql::equips::updateEquip);
    query.bindValue(":nomAntic", nomAntic);
    query.bindValue(":nomNou", nouEquip.nom);
    query.bindValue(":categoria", nouEquip.categoria);
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

void RoboDatabase::afegirPartida(const Partida &partida)
{
    QSqlQuery query;
    query.prepare(SentenciesSql::partides::insertPartida);
    query.bindValue(":ronda", partida.ronda);
    query.bindValue(":partida", partida.partida);
    query.bindValue(":equip1", partida.equip1);
    query.bindValue(":equip2", partida.equip2);
    query.bindValue(":taps1", partida.taps1);
    query.bindValue(":taps2", partida.taps2);
    query.bindValue(":bandera1", partida.bandera1);
    query.bindValue(":bandera2", partida.bandera2);
    query.bindValue(":valid1", partida.valid1);
    query.bindValue(":valid2", partida.valid2);
    query.bindValue(":extra1", partida.extra1);
    query.bindValue(":extra2", partida.extra2);
    if (partida.notes.isEmpty()) {
        query.bindValue(":notes", QString(/* NULL */));
    } else {
        query.bindValue(":notes", partida.notes);
    }
    if (!query.exec()) {
        emit errorSql(query.lastError());
        return;
    }
    emit dataChanged();
}

void RoboDatabase::modificarPartida(const QPair<int, int> &antigaPk, const Partida &novaPartida)
{
    QSqlQuery query;
    query.prepare(SentenciesSql::partides::updatePartida);
    query.bindValue(":ronda", novaPartida.ronda);
    query.bindValue(":partida", novaPartida.partida);
    query.bindValue(":equip1", novaPartida.equip1);
    query.bindValue(":equip2", novaPartida.equip2);
    query.bindValue(":taps1", novaPartida.taps1);
    query.bindValue(":taps2", novaPartida.taps2);
    query.bindValue(":bandera1", novaPartida.bandera1);
    query.bindValue(":bandera2", novaPartida.bandera2);
    query.bindValue(":valid1", novaPartida.valid1);
    query.bindValue(":valid2", novaPartida.valid2);
    query.bindValue(":extra1", novaPartida.extra1);
    query.bindValue(":extra2", novaPartida.extra2);
    if (novaPartida.notes.isEmpty()) {
        query.bindValue(":notes", QString(/* NULL */));
    } else {
        query.bindValue(":notes", novaPartida.notes);
    }
    query.bindValue(":rondaOriginal", antigaPk.first);
    query.bindValue(":partidaOriginal", antigaPk.second);
    if (!query.exec()) {
        emit errorSql(query.lastError());
        return;
    }
    emit dataChanged();
}

void RoboDatabase::eliminarPartida(const QPair<int, int> &pk)
{
    QSqlQuery query;
    query.prepare(SentenciesSql::partides::deletePartida);
    query.bindValue(":ronda", pk.first);
    query.bindValue(":partida", pk.second);
    if (!query.exec()) {
        emit errorSql(query.lastError());
        return;
    }
    emit dataChanged();
}

bool RoboDatabase::estaInicialitzada()
{
    QSqlDatabase db = QSqlDatabase::database();
    QStringList tables = db.tables();
    return tables.contains("equips") && tables.contains("partides");
}

Equip RoboDatabase::infoFromEquip(const QString &nomEquip)
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

Partida RoboDatabase::infoFromPartida(const QPair<int, int> &pkPartida)
{
    Partida p;
    p.ronda = pkPartida.first;
    p.partida = pkPartida.second;
    QSqlQuery query;
    query.prepare(SentenciesSql::partides::selectInfoFromPartida);
    query.bindValue(":ronda", pkPartida.first);
    query.bindValue(":partida", pkPartida.second);
    if (!query.exec()) {
        emit errorSql(query.lastError());
        return p;
    }
    if (query.next()) {
        p.equip1 = query.value(0).toString();
        p.equip2 = query.value(1).toString();
        p.taps1 = query.value(2).toInt();
        p.taps2 = query.value(3).toInt();
        p.bandera1 = query.value(4).toBool();
        p.bandera2 = query.value(5).toBool();
        p.valid1 = query.value(6).toBool();
        p.valid2 = query.value(7).toBool();
        p.extra1 = query.value(8).toInt();
        p.extra2 = query.value(9).toInt();
        p.notes = query.value(10).toString();
    }
    return p;
}

QPair<int, int> RoboDatabase::properaPartida()
{
    QSqlQuery query;
    QPair<int, int> pp(1, 1);
    if (!query.exec(SentenciesSql::partides::selectProperaPartida)) {
        emit errorSql(query.lastError());
        return pp;
    }
    if (!query.next()) {
        return pp;
    }
    pp.first = query.value(0).toInt();
    pp.second = query.value(1).toInt();
    return pp;
}

QVector<Partida> RoboDatabase::ultimesPartides()
{
    QSqlQuery query;
    QVector<Partida> partides;
    if (!query.exec(SentenciesSql::partides::selectUltimesPartides)) {
        emit errorSql(query.lastError());
        return partides;
    }
    partides.reserve(4);
    while (query.next()) {
        Partida p;
        p.equip1 = query.value(0).toString();
        p.equip2 = query.value(1).toString();
        p.taps1 = query.value(2).toInt();
        p.taps2 = query.value(3).toInt();
        p.bandera1 = query.value(4).toBool();
        p.bandera2 = query.value(5).toBool();
        p.valid1 = query.value(6).toBool();
        p.valid2 = query.value(7).toBool();
        p.extra1 = query.value(8).toInt();
        p.extra2 = query.value(9).toInt();
        partides.append(p);
    }
    return partides;
}

QMap<QString, int> RoboDatabase::categories()
{
    QSqlQuery query;
    QMap<QString, int> cats;
    if (!query.exec(SentenciesSql::equips::selectCategories)) {
        emit errorSql(query.lastError());
        return cats;
    }
    while (query.next()) {
        cats[query.value(0).toString()] = query.value(1).toInt();
    }
    return cats;
}

QVector<Equip> RoboDatabase::classificatsCategoria(const QString &categoria, int num)
{
    QSqlQuery query;
    QVector<Equip> classificats;
    query.prepare(SentenciesSql::equips::selectClassificatsCat);
    query.bindValue(":categoria", categoria);
    query.bindValue(":num", num);
    if (!query.exec()) {
        emit errorSql(query.lastError());
        return classificats;
    }
    classificats.reserve(num);
    while (query.next()) {
        Equip e;
        e.nom = query.value(0).toString();
        e.categoria = categoria;
        e.puntsClassificacio = query.value(1).toInt();
        e.puntsDesempat = query.value(2).toInt();
        classificats.append(e);
    }
    return classificats;
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
        db.close();
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
