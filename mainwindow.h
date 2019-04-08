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
        CONNECTADA,
        NO_CONNECTADA,
        CONNECTANT
    };

    void updateChronoButtons(bool running);
    void updateConnectat(bool connectat);

private slots:
    void canviEstatBd(EstatBd estat);
    void chronoTick();
    void canviBd(const ConnectionInfo &ci);
    void actualitzarDades();
    void gestionarFiConnexio(bool exitosa);
    void errorSql(const QSqlError &error);

};

#endif // MAINWINDOW_HH
