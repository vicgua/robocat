#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    connectDialog(new ConnectDialog),
    chrono(new QTimer(this))
{
    ui->setupUi(this);
    tempsCrono = maxTempsCrono;
    ui->cronometre->warningTime = warnTempsCrono;
    ui->cronometre->updateTicks(tempsCrono);
    connect(chrono, &QTimer::timeout, this, &MainWindow::chronoTick);
    //ui->centralWidget->setDisabled(true);
    ui->estatBd->setText("No connectada");
    canviEstatBd(NO_CONNECTADA);
}

MainWindow::~MainWindow()
{
    delete ui;
    delete connectDialog;
    delete chrono;
}

void MainWindow::startChrono()
{
    chrono->start(1000);
    updateChronoButtons(true);
    emit chronoStarted();
}

void MainWindow::stopChrono()
{
    chrono->stop();
    updateChronoButtons(false);
    emit chronoStopped();
}

void MainWindow::resetChrono()
{
    tempsCrono = maxTempsCrono;
    updateChronoButtons(false);
    emit chronoTicked(maxTempsCrono);
}

void MainWindow::updateChronoButtons(bool running)
{
    ui->playCrono->setEnabled(!running && tempsCrono > 0);
    ui->stopCrono->setEnabled(running && tempsCrono > 0);
    ui->resetCrono->setEnabled(!running && tempsCrono < maxTempsCrono);
}

void MainWindow::canviEstatBd(EstatBd estat)
{
    QPalette palette = ui->estatBd->palette();
    QString text = ui->estatBd->text();
    switch (estat) {
    case CONNECTADA:
        palette.setColor(QPalette::WindowText, Qt::darkGreen);
        text = "Connectada";
        break;
    case NO_CONNECTADA:
        palette.setColor(QPalette::WindowText, Qt::red);
        text = "No connectada";
        break;
    case CONNECTANT:
        palette.setColor(QPalette::WindowText, Qt::black);
        text = "Connectant";
    }
    ui->estatBd->setPalette(palette);
    ui->estatBd->setText(text);
}

void MainWindow::openConnectDialog()
{
    connectDialog->exec();
}

void MainWindow::chronoTick()
{
    --tempsCrono;
    emit chronoTicked(tempsCrono);
    if (tempsCrono == 0) {
        chrono->stop();
        emit chronoTimedOut();
    }
}
