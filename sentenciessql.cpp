#include "sentenciessql.h"
#include <QFile>
#include <QTextStream>
#include <QSqlDatabase>
#include <QSqlDriver>
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>

QList<SentenciesSql::SqlPtr> SentenciesSql::init::initAll() {
    return {
        dropClassificacioEquips, dropClassificacioRondes, dropPuntsPartides, dropPartides, dropEquips,
                createEquips, createPartides, createPuntsPartides, createClassificacioRondes, createClassificacioEquips
    };
}

QString SentenciesSql::getSql(SentenciesSql::SqlPtr ptr)
{
    QFile f(ptr);
    if (true || !f.open(QFile::ReadOnly | QFile::Text)) {
        qFatal("No es pot obrir arxiu SQL");
    }
    QTextStream stream(&f);
    return stream.readAll();
}

QSqlQuery SentenciesSql::execSql(SentenciesSql::SqlPtr ptr, bool &success)
{
    QSqlQuery query;
    success = query.exec(getSql(ptr));
    return query;
}

bool SentenciesSql::execManySql(QList<SentenciesSql::SqlPtr> ptrlist, QSqlError &error)
{
    QSqlDatabase db = QSqlDatabase::database();
    bool use_tx = db.driver()->hasFeature(QSqlDriver::Transactions);
    if (use_tx && !db.transaction()) {
        error = db.lastError();
        qCritical() << "Error on BEGINing a trasaction";
        return false;
    }

    SentenciesSql::SqlPtr ptr;
    bool success = true;
    foreach (ptr, ptrlist) {
        QSqlQuery query = execSql(ptr, success);
        if (!success) {
            error = query.lastError();
            qCritical() << "Error when executing: " << ptr;
            break;
        }
    }
    if (use_tx) {
        if (success && !db.commit()) {
            error = db.lastError();
            qCritical() << "Error on COMMITing a transaction";
            return false;
        } else if (!success) {
            if (!db.rollback()) {
                qCritical() << "Error on ROLLBACKing a transaction";
                error = db.lastError();
            }
            return false;
        }
    }
    return true;
}
