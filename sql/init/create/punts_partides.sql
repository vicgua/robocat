CREATE VIEW punts_partides AS
    SELECT *,
    (CASE WHEN total1 > total2 THEN 3 WHEN total1 = total2 THEN 1 ELSE 0 END) AS punts1,
    (CASE WHEN total2 > total1 THEN 3 WHEN total2 = total1 THEN 1 ELSE 0 END) AS punts2
    FROM (
        SELECT *, (taps1 + bandera1 + extra1) AS total1, (taps2 + bandera2 + extra2) AS total2
        FROM partides
    );
