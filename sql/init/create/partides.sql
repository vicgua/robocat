CREATE TABLE partides (
    ronda SMALLINT CONSTRAINT ronda_valida CHECK (ronda > 0),
    partida SMALLINT CONSTRAINT partida_valida CHECK (partida > 0),
    equip1 VARCHAR(80) REFERENCES equips(nom) ON UPDATE CASCADE ON DELETE RESTRICT,
    equip2 VARCHAR(80) REFERENCES equips(nom) ON UPDATE CASCADE ON DELETE RESTRICT,
    taps1 SMALLINT NOT NULL CONSTRAINT taps1_valid CHECK (taps1 >= 0),
    taps2 SMALLINT NOT NULL CONSTRAINT taps2_valid CHECK (taps2 >= 0),
    bandera1 SMALLINT NOT NULL CONSTRAINT bandera1_valida CHECK (bandera1 = 0 OR bandera1 = 25),
    bandera2 SMALLINT NOT NULL CONSTRAINT bandera2_valida CHECK (bandera2 = 0 OR bandera2 = 25),
    -- Aquests punts permeten modificar manualment les puntuacions en cas d'una fallada del sistema
    -- o d'un imprevist durant la competició
    extra1 INTEGER NOT NULL DEFAULT 0,
    extra2 INTEGER NOT NULL DEFAULT 0,
    -- Notes a fer constar a la base de dades
    notes TEXT DEFAULT NULL,
    PRIMARY KEY (ronda, partida),
    CONSTRAINT equips_diferents CHECK (equip1 <> equip2),
    CONSTRAINT num_taps_possible CHECK (taps1 + taps2 <= 200),
    CONSTRAINT modificacions_justificades CHECK (notes IS NOT NULL OR (extra1 = 0 AND extra2 = 0))
);
