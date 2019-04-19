# Requisits
Per a compilar i executar el programa, es necessita Qt 5 amb els següents mòduls:

- _Qt 5 Core_
- _Qt 5 Widgets_
- _Qt 5 SQL_

Tots ells haurien d'estar instal·lats per defecte.
Si es vol utilitzar una base de dades PostgreSQL, també es necessita un servidor (no necessàriament al mateix ordinador) Postgres.

# Estat
- [x] Gestió d'equips
- [ ] Gestió de partides (i suma de punts)
- [x] Cronòmetre

# Sobre les bases de dades
Si bé el programa està pensat per a ser executat amb una base de dades PostgreSQL, també es permet utilitzar,
especialment per provar el programa, SQLite.

## PostgreSQL
Es necessita una base de dades on es tingui els següents permisos:

- Creació i eliminació de taules i vistes.
- Lectura i escriptura (`SELECT`, `INSERT`, `UPDATE` i `DELETE`) a les taules creades.

Idealment, es crearà un usuari propietari de la base de dades.

## SQLite
A diferència de PostgreSQL, que guarda les dades a un servidor, SQLite guarda les dades a un arxiu, i la llibreria
necessària per operar amb SQLite està inclosa amb Qt, el que el fa especialment útil durant el desenvolupament i les
proves del programa. Amb la opció de SQLite, la majoria d'opcions de connexió no s'utilitzen (ja que no cal connectar-se
a un servidor). Al camp de "Base de dades" cal introduïr un dels següents:

- Un _path_ absolut a un arxiu. Per exemple `~/robocat.db` o `/home/user/robocat.db` (a Linux) o `C:\Users\user\robocat.db` (a Windows).
- Un _path_ relatiu al directori on es troba l'executable. Per exemple, `robocat.db` crearà la BD al mateix directori on
  es troba l'executable. **Nota:** Si es compila amb Qt Creator, l'executable no es crea a la carpeta del codi font (per defecte),
  si no a la carpeta `build-robocat-...` del directori superior. Per tant, per crear-la a la carpeta del codi font, cal introduïr
  `../robocat/robocat.db`.
- `:memory:` -- Això crearà una base de dades temporal, que no s'escriurà a cap arxiu. Cal tenir en compte que aquesta es destruirà
  tan bon punt es tanqui la connexió (o es tanqui el programa).

# Ús del programa
Un cop obert el programa, s'han de següir els següents pasos.

1. Connectar-se a la base de dades (Arxiu > Connectar a BD; Ctrl+O). En cas de dubte, a DBMS selecciona "SQLite". Els paràmetres s'especifiquen a l'apartat anterior.
2. Si s'obre per primer cop, s'ha d'inicialitzar (Arxiu > Incialitzar BD). Això esborrarà les dades preexistents, si n'hi havia.
3. Per afegir un equip, a la pestanya _Equips_, fem clic a afegir i li donem un nom.
4. Podem provar el cronòmetre: a la pestanya _Cronòmetre_ trobem tres seccions, que veurem desprès. Al menú _Pantalles_ cliquem la opció
	de cronòmetre. Hauria de sortir una petita finestra amb el logo de la RoboCAT. Si tenim més d'una pantalla, hem d'arrosegar aquesta finestra
	fins a la pantalla secondària. A la finestra principal veiem les opcions:
	- Estats de la pantalla: Controlen què es mostra a la pantalla auxiliar.
		- Idle: Logo de la RoboCAT. Aquest l'utilitzem quan no volguem que es mostri res a la pantalla (abans de començar la competició,
			quan estem canviant els equips...)
		- Següents: Mostra els següents equips en competir.
		- Cronòmetre: Mostra el temps i (opcionalment) els equips que estan competint.
	- Distribució d'equips: Podem escollir quins equips jugaran a cada taula. Si només calguès una taula, podem desmarcar la casella de la taula
		corresponent. Els canvis fets aquí es mostren a la pantalla auxiliar en els estats "Següents" i "Cronòmetre".
	- Cronòmetre: Permet controlar el temps (per fer les proves més ràpides, fem com si una partida fossin 15 segons, i en els últims 10
		es comptessin les banderes). El temps mostrat es sincronitza amb la pantalla auxiliar en estat "Cronòmetre".
5. El programa està incomplet i pot tenir alguns errors. Vegeu la secció Estat del README i [l'apartat _Issues_ del repositori][issues]

[issues]: https://github.com/vicgua/robocat/issues