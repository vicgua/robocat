DROP
    TABLE
        IF EXISTS partides;

DROP
    TABLE
        IF EXISTS equips;

CREATE
    TABLE
        equips ( nom VARCHAR(80) PRIMARY KEY );

CREATE
    TABLE
        partides ( ronda SMALLINT CHECK (ronda > 0),
        equip1 VARCHAR(80) REFERENCES equips(nom) ON UPDATE CASCADE ON DELETE RESTRICT,
        equip2 VARCHAR(80) REFERENCES equips(nom) ON UPDATE CASCADE ON DELETE RESTRICT,
        taps1 SMALLINT NOT NULL CHECK (taps1 >= 0),
        taps2 SMALLINT NOT NULL CHECK (taps2 >= 0),
        bandera1 BOOLEAN NOT NULL,
        bandera2 BOOLEAN NOT NULL,
        extra1 INT NOT NULL DEFAULT 0,
        extra2 INT NOT NULL DEFAULT 0,
        notes TEXT NOT NULL DEFAULT "",
        PRIMARY KEY (ronda,
        equip1,
        equip2),
        CONSTRAINT equips_diferents CHECK (equip1 <> equip2),
        CONSTRAINT num_taps CHECK (taps1 + taps2 <= 200) );

DROP
    VIEW IF EXISTS total_partida;

CREATE
    VIEW total_partida AS SELECT
        ronda,
        equip1,
        equip2,
        (taps1 +
        CASE
            WHEN bandera1 THEN 25
            ELSE 0
        END + extra1) AS total1,
        (taps2 +
        CASE
            WHEN bandera2 THEN 25
            ELSE 0
        END + extra2) AS total2
    FROM
        partides;

DROP
    VIEW IF EXISTS punts_partida;

CREATE
    VIEW punts_partida AS SELECT
        ronda,
        equip1,
        equip2,
        (CASE
            WHEN total1 > total2 THEN 3
            WHEN total1 = total2 THEN 1
            ELSE 0
        END) AS punts1,
        (CASE
            WHEN total2 > total1 THEN 3
            WHEN total2 = total1 THEN 1
            ELSE 0
        END) AS punts2
    FROM
        total_partida;
DROP VIEW IF EXISTS punts_equip;
CREATE VIEW punts_equip AS
 SELECT
    pp.ronda AS ronda,
    e.nom AS equip,
    (
    SELECT
        SUM(CASE WHEN equip1 = e.nom THEN punts1 WHEN equip2 = e.nom THEN punts2 END)
    FROM
        punts_partida
    WHERE
        ronda = pp.ronda
        AND (equip1 = e.nom
        OR equip2 = e.nom) ) AS punts
FROM
    punts_partida AS pp
INNER JOIN equips AS e ON
    (pp.equip1 = e.nom
    OR pp.equip2 = e.nom)
GROUP BY
    pp.ronda,
    e.nom;
