#ifndef MAINWINDOW_HH
#define MAINWINDOW_HH

#include <QMainWindow>
#include <QTimer>
#include "connectdialog.h"
#include "data_objects/connectioninfo.h"
#include "robodatabase.h"

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
    QTimer* chrono;
    RoboDatabase *db;

    //! Temps actual del crono (en segons)
    int tempsCrono;

    constexpr static int maxTempsCrono = 2 * 60; // 2 minuts
    constexpr static int warnTempsCrono = 15; // 15 segons

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

};

#endif // MAINWINDOW_HH
