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
                                        "    categoria,\n"
                                        "    punts_classificacio_totals,\n"
                                        "    punts_desempat_totals\n"
                                        "FROM\n"
                                        "    classificacio_equips\n"
                                        "ORDER BY\n"
                                        "    nom ASC;\n";
constexpr SqlSentence selectInfoFromEquip = "SELECT\n"
                                            "    categoria,\n"
                                            "    punts_classificacio_totals,\n"
                                            "    punts_desempat_totals\n"
                                            "FROM\n"
                                            "    classificacio_equips\n"
                                            "WHERE\n"
                                            "    nom = :nom;\n";
constexpr SqlSentence selectClassificacio = "SELECT\n"
                                            "    nom,\n"
                                            "    punts_classificacio_totals,\n"
                                            "    punts_desempat_totals\n"
                                            "FROM\n"
                                            "    classificacio_equips\n"
                                            "ORDER BY\n"
                                            "    punts_classificacio_totals DESC,\n"
                                            "    punts_desempat_totals DESC,\n"
                                            "    nom ASC;\n";
constexpr SqlSentence selectEquips = "SELECT\n"
                                     "    nom,\n"
                                     "    categoria\n"
                                     "FROM\n"
                                     "    equips\n"
                                     "ORDER BY\n"
                                     "    nom ASC;\n";
constexpr SqlSentence insertEquip = "INSERT\n"
                                    "    INTO\n"
                                    "        equips(nom, categoria)\n"
                                    "    VALUES (:nom, :categoria);\n";
constexpr SqlSentence updateEquip = "UPDATE\n"
                                    "    equips\n"
                                    "SET\n"
                                    "    nom = :nomNou,\n"
                                    "    categoria = :categoria\n"
                                    "WHERE\n"
                                    "    nom = :nomAntic;\n";
constexpr SqlSentence deleteEquip = "DELETE\n"
                                    "FROM\n"
                                    "    equips\n"
                                    "WHERE\n"
                                    "    nom = :nom;\n";
}

namespace partides {
constexpr SqlSentence selectPartides = "SELECT\n"
                                       "    ronda,\n"
                                       "    partida,\n"
                                       "    equip1,\n"
                                       "    equip2,\n"
                                       "    taps1,\n"
                                       "    taps2,\n"
                                       "    bandera1 = 25,\n"
                                       "    bandera2 = 25,\n"
                                       "    valid1,\n"
                                       "    valid2,\n"
                                       "    extra1,\n"
                                       "    extra2,\n"
                                       "    total1,\n"
                                       "    total2,\n"
                                       "    notes\n"
                                       "FROM\n"
                                       "    punts_partides\n"
                                       "ORDER BY\n"
                                       "    ronda DESC,\n"
                                       "    partida DESC;\n";
constexpr SqlSentence selectInfoFromPartida =
        "SELECT\n"
        "    equip1,\n"
        "    equip2,\n"
        "    taps1,\n"
        "    taps2,\n"
        "    bandera1 = 25,\n"
        "    bandera2 = 25,\n"
        "    valid1,\n"
        "    valid2,\n"
        "    extra1,\n"
        "    extra2,\n"
        "    notes\n"
        "FROM\n"
        "    partides\n"
        "WHERE\n"
        "    ronda = :ronda\n"
        "    AND partida = :partida;\n";
constexpr SqlSentence insertPartida = "INSERT\n"
                                      "    INTO\n"
                                      "        partides(ronda,\n"
                                      "        partida,\n"
                                      "        equip1,\n"
                                      "        equip2,\n"
                                      "        taps1,\n"
                                      "        taps2,\n"
                                      "        bandera1,\n"
                                      "        bandera2,\n"
                                      "        valid1,\n"
                                      "        valid2,\n"
                                      "        extra1,\n"
                                      "        extra2,\n"
                                      "        notes)\n"
                                      "    VALUES (:ronda,\n"
                                      "    :partida,\n"
                                      "    :equip1,\n"
                                      "    :equip2,\n"
                                      "    :taps1,\n"
                                      "    :taps2,\n"
                                      "    CASE\n"
                                      "        WHEN :bandera1 THEN 25\n"
                                      "        ELSE 0\n"
                                      "    END,\n"
                                      "    CASE\n"
                                      "        WHEN :bandera2 THEN 25\n"
                                      "        ELSE 0\n"
                                      "    END,\n"
                                      "    :valid1,\n"
                                      "    :valid2,\n"
                                      "    :extra1,\n"
                                      "    :extra2,\n"
                                      "    :notes);\n";
constexpr SqlSentence updatePartida = "UPDATE\n"
                                      "    partides\n"
                                      "SET\n"
                                      "    ronda = :ronda,\n"
                                      "    partida = :partida,\n"
                                      "    equip1 = :equip1,\n"
                                      "    equip2 = :equip2,\n"
                                      "    taps1 = :taps1,\n"
                                      "    taps2 = :taps2,\n"
                                      "    bandera1 =\n"
                                      "    CASE\n"
                                      "        WHEN :bandera1 THEN 25\n"
                                      "        ELSE 0\n"
                                      "    END,\n"
                                      "    bandera2 =\n"
                                      "    CASE\n"
                                      "        WHEN :bandera2 THEN 25\n"
                                      "        ELSE 0\n"
                                      "    END,\n"
                                      "    valid1 = :valid1,\n"
                                      "    valid2 = :valid2,"
                                      "    extra1 = :extra1,\n"
                                      "    extra2 = :extra2,\n"
                                      "    notes = :notes\n"
                                      "WHERE\n"
                                      "    ronda = :rondaOriginal\n"
                                      "    AND partida = :partidaOriginal;\n";
constexpr SqlSentence deletePartida = "DELETE\n"
                                      "FROM\n"
                                      "    partides\n"
                                      "WHERE\n"
                                      "    ronda = :ronda\n"
                                      "    AND partida = :partida;\n";
constexpr SqlSentence selectProperaPartida =
        "SELECT\n"
        "    ronda,\n"
        "    partida + 1\n"
        "FROM\n"
        "    partides\n"
        "ORDER BY\n"
        "    ronda DESC,\n"
        "    partida DESC\n"
        "LIMIT 1;\n";
constexpr SqlSentence selectUltimesPartides =
        "SELECT\n"
        "    equip1,\n"
        "    equip2,\n"
        "    taps1,\n"
        "    taps2,\n"
        "    bandera1 = 25,\n"
        "    bandera2 = 25,\n"
        "    valid1,\n"
        "    valid2,\n"
        "    extra1,\n"
        "    extra2\n"
        "FROM\n"
        "    partides\n"
        "ORDER BY\n"
        "    ronda DESC,\n"
        "    partida DESC\n"
        "LIMIT 4;\n";
constexpr SqlSentence selectClassificacio = "SELECT\n"
                                            "    nom,\n"
                                            "    punts_classificacio_totals,\n"
                                            "    punts_desempat_totals,\n"
                                            "    categoria\n"
                                            "FROM\n"
                                            "    classificacio_equips\n"
                                            "ORDER BY\n"
                                            "    punts_classificacio_totals DESC,\n"
                                            "    punts_desempat_totals DESC,\n"
                                            "    nom ASC;\n";
}

QString getSql(SqlPtr ptr);
QSqlQuery execSql(SqlPtr ptr, bool &success);
bool execManySql(QList<SqlPtr> ptrlist, QSqlError &error);
}

#endif // SENTENCIESSQL_H
