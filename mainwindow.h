#ifndef MAINWINDOW_HH
#define MAINWINDOW_HH

#include <QMainWindow>
#include <QTimer>
#include "connectdialog.h"

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

    //! Temps actual del crono (en segons)
    int tempsCrono;

    constexpr static int maxTempsCrono = 20;//2 * 60; // 2 minuts
    constexpr static int warnTempsCrono = 15; // 15 segons

    enum EstatBd {
        CONNECTADA,
        NO_CONNECTADA,
        CONNECTANT
    };

    void updateChronoButtons(bool running);

private slots:
    void canviEstatBd(EstatBd estat);
    void openConnectDialog();
    void chronoTick();

};

#endif // MAINWINDOW_HH
