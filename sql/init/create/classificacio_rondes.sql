CREATE
    VIEW classificacio_ronda AS SELECT
        e.nom,
        p.ronda,
        COALESCE(SUM(CASE WHEN e.nom = p.equip1 THEN p.punts1 WHEN e.nom = p.equip2 THEN p.punts2 END),
        0) AS punts_cl_ronda,
        COALESCE(SUM(CASE WHEN e.nom = p.equip1 THEN p.total1 WHEN e.nom = p.equip2 THEN p.total2 END),
        0) AS punts_de_ronda
    FROM
        equips AS e
    LEFT OUTER JOIN punts_partides AS p ON
        (e.nom = p.equip1
        OR e.nom = p.equip2)
    GROUP BY
        e.nom,
        p.ronda;
