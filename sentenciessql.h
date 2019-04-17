#ifndef SENTENCIESSQL_H
#define SENTENCIESSQL_H

#include <QSqlQuery>
#include <QString>
#include <QList>

namespace SentenciesSql {
using SqlPtr = const char *;
using SqlSentence = const char *;

namespace init {
constexpr SqlPtr dropEquips = ":/sql/init/drop/equips.sql";
constexpr SqlPtr dropPartides = ":/sql/init/drop/partides.sql";
constexpr SqlPtr dropPuntsPartides = ":/sql/init/drop/punts_partides.sql";
constexpr SqlPtr dropClassificacioRondes = ":/sql/init/drop/classificacio_rondes.sql";
constexpr SqlPtr dropClassificacioEquips = ":/sql/init/drop/classificacio_equips.sql";

constexpr SqlPtr createEquips = ":/sql/init/create/equips.sql";
constexpr SqlPtr createPartides = ":/sql/init/create/partides.sql";
constexpr SqlPtr createPuntsPartides = ":/sql/init/create/punts_partides.sql";
constexpr SqlPtr createClassificacioRondes = ":/sql/init/create/classificacio_rondes.sql";
constexpr SqlPtr createClassificacioEquips = ":/sql/init/create/classificacio_equips.sql";

QList<SqlPtr> initAll();
}

namespace equips {
constexpr SqlSentence selectEquipInfo = "SELECT\n"
                                        "    nom,\n"
                                        "    punts_totals,\n"
                                        "    partides_jugades\n"
                                        "FROM\n"
                                        "    classificacio_equips\n"
                                        "ORDER BY\n"
                                        "    nom ASC;\n";
constexpr SqlSentence selectEquips = "SELECT\n"
                                     "    nom\n"
                                     "FROM\n"
                                     "    equips\n"
                                     "ORDER BY\n"
                                     "    nom ASC;\n";
constexpr SqlSentence insertEquip = "INSERT\n"
                                    "    INTO\n"
                                    "        equips(nom)\n"
                                    "    VALUES (:nom);\n";
constexpr SqlSentence updateEquip = "UPDATE\n"
                                    "    equips\n"
                                    "SET\n"
                                    "    nom = :nomNou\n"
                                    "WHERE\n"
                                    "    nom = :nomAntic;\n";
constexpr SqlSentence deleteEquip = "DELETE\n"
                                    "FROM\n"
                                    "    equips\n"
                                    "WHERE\n"
                                    "    nom = :nom;\n";
}

QString getSql(SqlPtr ptr);
QSqlQuery execSql(SqlPtr ptr, bool &success);
bool execManySql(QList<SqlPtr> ptrlist, QSqlError &error);
}

#endif // SENTENCIESSQL_H
