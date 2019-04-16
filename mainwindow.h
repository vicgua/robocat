#ifndef MAINWINDOW_HH
#define MAINWINDOW_HH

#include <QMainWindow>
#include <QTimer>
#include <QSqlQueryModel>
#include "connectdialog.h"
#include "data_objects/connectioninfo.h"
#include "robodatabase.h"
#include "pantallacrono.h"
#include "constants.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

public slots:
    void startChrono();
    void stopChrono();
    void resetChrono();
    void actualitzarDades();

signals:
    void chronoStarted();
    void chronoStopped();
    void chronoTimedOut();
    void chronoTicked(int temps);

private:
    Ui::MainWindow *ui;
    ConnectDialog *connectDialog;
    PantallaCrono *pantallaCrono;
    QTimer* chrono;
    RoboDatabase *db;
    QSqlQueryModel *infoEquipsModel;
    QSqlQueryModel *equipsModel;

    //! Temps actual del crono (en segons)
    int tempsCrono;

    enum EstatBd {
        CONNECTANT,
        CONNECTADA,
        NO_CONNECTADA,
        NO_INICIALITZADA
    };

    void updateChronoButtons(bool running);
    void updateConnectat(bool connectat, bool inicialitzada = true);

private slots:
    void canviEstatBd(EstatBd estat);
    void chronoTick();
    void canviBd(const ConnectionInfo &ci);
    void gestionarFiConnexio(bool exitosa);
    void errorSql(const QSqlError &error);
    void obreDialegInicialitzacio();
    void obrePantallaCrono();
    void afegirEquip();
    void modificarEquip();
};

#endif // MAINWINDOW_HH
