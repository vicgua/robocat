#ifndef CONSTANTS_H
#define CONSTANTS_H

namespace constants
{
    /// Quan quedi WARN_TIME temps, el crono es posarà groc
    constexpr int WARN_TIME = 10; // 0:10
    /// Temps inicial del crono
    constexpr int MAX_TIME = 15; // 2:00 (0:15 en desenvolupament)
    /// Cada AUTOSCROLL_CYCLE_TIME, l'autoscroll de la pantalla de puntuacions
    /// haurà fet un cicle. Per tant, cada entrada estarà a la primera posició
    /// n_entrades / AUTOSCROLL_CYCLE_TIME
    constexpr int AUTOSCROLL_CYCLE_TIME = 60; // 60 segons
    /// Cada AUTOSCROLL_REFRESH_TIME s'executarà el codi d'actualització
    /// de l'autoscroll de la pantalla de puntuacions.
    /// Temps més baixos impliquen salts menys bruscs, però pot ralentitzar el programa.
    constexpr int AUTOSCROLL_REFRESH_TIME = 500; // 1 segon

    // No editar per sota d'aquesta línia
    // ===============

    constexpr int AUTOSCROLL_MAX =
            (AUTOSCROLL_CYCLE_TIME * 1000) / AUTOSCROLL_REFRESH_TIME;
    static_assert(AUTOSCROLL_MAX != 0,
                  "AUTOSCROLL_REFRESH_TIME és massa gran en comparació amb AUTOSCROLL_CYCLE_TIME");
}

#endif // CONSTANTS_H
