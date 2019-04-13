#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QMessageBox>
#include <QColor>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    connectDialog(new ConnectDialog),
    chrono(new QTimer(this)),
    db(new RoboDatabase)
{
    ui->setupUi(this);
    ui->cronometre->warningTime = warnTempsCrono;
    resetChrono();
    connect(chrono, &QTimer::timeout, this, &MainWindow::chronoTick);
    connect(ui->actionConnectar_a_BD, SIGNAL(triggered()), connectDialog, SLOT(exec()));
    connect(ui->actionTancar_connexio, SIGNAL(triggered()), db, SLOT(desconnecta()));
    connect(connectDialog, &ConnectDialog::databaseSet, this, &MainWindow::canviBd);
    connect(db, &RoboDatabase::connexioFinalitzada, this, &MainWindow::gestionarFiConnexio);
    connect(db, &RoboDatabase::desconnectada, this, [=](){ canviEstatBd(NO_CONNECTADA); });
    connect(db, &RoboDatabase::inicialitzada, this, [=](){ gestionarFiConnexio(true); });
    connect(db, &RoboDatabase::errorSql, this, &MainWindow::errorSql);
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

void MainWindow::updateConnectat(bool connectat, bool inicialitzada)
{
    ui->tabWidget->setEnabled(connectat && inicialitzada);
    ui->actionTancar_connexio->setEnabled(connectat);
    ui->actionInicialitzar_BD->setEnabled(connectat);
    //ui->menuPantalles->setEnabled(connectat && inicialitzada); // DEBUG
}

void MainWindow::canviEstatBd(EstatBd estat)
{
    QPalette palette = ui->estatBd->palette();
    QString text = ui->estatBd->text();
    switch (estat) {
    case CONNECTANT:
        palette.setColor(QPalette::WindowText, Qt::black);
        text = "Connectant";
        updateConnectat(false);
        ui->centralWidget->setCursor(Qt::WaitCursor);
        break;
    case CONNECTADA:
        palette.setColor(QPalette::WindowText, Qt::darkGreen);
        text = "Connectada";
        updateConnectat(true, true);
        ui->centralWidget->setCursor(Qt::ArrowCursor);
        break;
    case NO_CONNECTADA:
        palette.setColor(QPalette::WindowText, Qt::red);
        text = "No connectada";
        updateConnectat(false);
        ui->centralWidget->setCursor(Qt::ArrowCursor);
        break;
    case NO_INICIALITZADA:
        palette.setColor(QPalette::WindowText, QColor("orange"));
        text = "No inicialitzada";
        updateConnectat(true, false);
        ui->centralWidget->setCursor(Qt::ArrowCursor);
        break;
    }
    ui->estatBd->setPalette(palette);
    ui->estatBd->setText(text);
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

void MainWindow::canviBd(const ConnectionInfo &ci)
{
    db->setup(ci);
    canviEstatBd(CONNECTANT);
    db->iniciaConnexio();
}

void MainWindow::actualitzarDades()
{
    // TODO
}

void MainWindow::gestionarFiConnexio(bool exitosa)
{
    if (exitosa) {
        if (db->estaInicialitzada()) {
            canviEstatBd(CONNECTADA);
            actualitzarDades();
        } else {
            canviEstatBd(NO_INICIALITZADA);
        }
    } else {
        canviEstatBd(NO_CONNECTADA);
    }
}

void MainWindow::errorSql(const QSqlError &error)
{
    QMessageBox errorDialog(this);
    errorDialog.setIcon(QMessageBox::Critical);
    QString msgError("Hi ha hagut un error amb la base de dades:\n");
    msgError += error.text();
    errorDialog.setText(msgError);
    errorDialog.exec();
}

void MainWindow::obreDialegInicialitzacio()
{
    QMessageBox preguntaDialog(this);
    preguntaDialog.setIcon(QMessageBox::Warning);
    preguntaDialog.setText("ATENCIÓ: Inicialitzar la base de dades farà"
                           " que es perdin les dades preexistents. Continuar?");
    preguntaDialog.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
    switch (preguntaDialog.exec()) {
    case QMessageBox::Yes:
        db->inicialitzar();
        return;
    case QMessageBox::No:
        return;
    default:
        Q_UNREACHABLE();
    }
}
