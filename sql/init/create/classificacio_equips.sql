CREATE VIEW classificacio_equips AS
    SELECT nom, SUM(punts_ronda) AS punts_totals, SUM(partides_ronda) AS partides_jugades
    FROM classificacio_rondes
    GROUP BY nom;
