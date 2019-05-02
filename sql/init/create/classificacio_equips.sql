CREATE
    VIEW classificacio_equips AS SELECT
        nom,
        categoria,
        SUM(punts_cl_ronda) AS punts_classificacio_totals,
        SUM(punts_de_ronda) AS punts_desempat_totals
    FROM
        classificacio_rondes
    GROUP BY
        nom,
        categoria;
