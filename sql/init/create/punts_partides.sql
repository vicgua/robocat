CREATE
    VIEW punts_partides AS SELECT
        *,
        (CASE
            WHEN valid1
            AND total1 > total2 THEN 3
            WHEN valid1
            AND total1 = total2 THEN 1
            ELSE 0
        END) AS punts1,
        (CASE
            WHEN valid2
            AND total2 > total1 THEN 3
            WHEN valid2
            AND total2 = total1 THEN 1
            ELSE 0
        END) AS punts2
    FROM
        (
        SELECT
            *,
            (CASE
                WHEN valid1 THEN (taps1 + bandera1 + extra1)
                ELSE 0
            END) AS total1,
            (CASE
                WHEN valid2 THEN (taps2 + bandera2 + extra2)
                ELSE 0
            END) AS total2
        FROM
            partides) AS punts_per_partida;
