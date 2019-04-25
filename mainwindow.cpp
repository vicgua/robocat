#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QMessageBox>
#include <QColor>
#include <QDebug>
#include "equipdialog.h"
#include "partidadialog.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    connectDialog(new ConnectDialog),
    pantallaCrono(new PantallaCrono(this)),
    chrono(new QTimer(this)),
    db(new RoboDatabase),
    infoEquipsModel(new QSqlQueryModel),
    equipsModel(new QSqlQueryModel),
    partidesModel(new QSqlQueryModel)
{
    ui->setupUi(this);

    connect(chrono, &QTimer::timeout, this, &MainWindow::chronoTick);
    connect(this, &MainWindow::chronoTicked, pantallaCrono, &PantallaCrono::chronoTick);

    ui->cronometre->warningTime = constants::WARN_TIME;
    resetChrono();

    connect(ui->pantallaCronoIdle, SIGNAL(clicked(bool)), pantallaCrono, SLOT(setIdle()));
    connect(ui->pantallaCronoSeguents, SIGNAL(clicked(bool)), pantallaCrono, SLOT(setSeguents()));
    connect(ui->pantallaCronoCronometre, SIGNAL(clicked(bool)), pantallaCrono, SLOT(setCrono()));
    connect(ui->pantallaCronoTaula1, SIGNAL(toggled(bool)), pantallaCrono, SLOT(setTaula1Enabled(bool)));
    connect(ui->pantallaCronoE1T1, SIGNAL(currentIndexChanged(QString)), pantallaCrono, SLOT(setEquip1Taula1(QString)));
    connect(ui->pantallaCronoE2T1, SIGNAL(currentIndexChanged(QString)), pantallaCrono, SLOT(setEquip2Taula1(QString)));
    connect(ui->pantallaCronoTaula2, SIGNAL(toggled(bool)), pantallaCrono, SLOT(setTaula2Enabled(bool)));
    connect(ui->pantallaCronoE1T2, SIGNAL(currentIndexChanged(QString)), pantallaCrono, SLOT(setEquip1Taula2(QString)));
    connect(ui->pantallaCronoE2T2, SIGNAL(currentTextChanged(QString)), pantallaCrono, SLOT(setEquip2Taula2(QString)));

    connect(ui->actionConnectar_a_BD, SIGNAL(triggered()), connectDialog, SLOT(exec()));
    connect(ui->actionTancar_connexio, SIGNAL(triggered()), this, SLOT(desconnectaBd())); // TODO

    connect(connectDialog, &ConnectDialog::databaseSet, this, &MainWindow::canviBd);

    connect(db, &RoboDatabase::connexioFinalitzada, this, &MainWindow::gestionarFiConnexio);
    connect(db, &RoboDatabase::desconnectada, this, [=](){ canviEstatBd(NO_CONNECTADA); });
    connect(db, &RoboDatabase::inicialitzada, this, [=](){ gestionarFiConnexio(true); });
    connect(db, &RoboDatabase::errorSql, this, &MainWindow::errorSql);
    connect(db, &RoboDatabase::dataChanged, this, &MainWindow::actualitzarDades);

    ui->taulaEquips->setModel(infoEquipsModel);
    ui->pantallaCronoE1T1->setModel(equipsModel);
    ui->pantallaCronoE1T2->setModel(equipsModel);
    ui->pantallaCronoE2T1->setModel(equipsModel);
    ui->pantallaCronoE2T2->setModel(equipsModel);
    ui->taulaPartides->setModel(partidesModel);

    pantallaCrono->setTaula1Enabled(ui->pantallaCronoTaula1->isChecked());
    pantallaCrono->setEquip1Taula1(ui->pantallaCronoE1T1->currentText());
    pantallaCrono->setEquip2Taula1(ui->pantallaCronoE2T1->currentText());
    pantallaCrono->setTaula2Enabled(ui->pantallaCronoTaula2->isChecked());
    pantallaCrono->setEquip1Taula2(ui->pantallaCronoE1T2->currentText());
    pantallaCrono->setEquip2Taula2(ui->pantallaCronoE2T2->currentText());

    canviEstatBd(NO_CONNECTADA);
}

MainWindow::~MainWindow()
{
    delete ui;
    delete connectDialog;
    delete pantallaCrono;
    delete chrono;
    delete db;
    delete infoEquipsModel;
    delete equipsModel;
    delete partidesModel;
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
    tempsCrono = constants::MAX_TIME;
    updateChronoButtons(false);
    emit chronoTicked(constants::MAX_TIME);
}

void MainWindow::updateChronoButtons(bool running)
{
    ui->playCrono->setEnabled(!running && tempsCrono > 0);
    ui->stopCrono->setEnabled(running && tempsCrono > 0);
    ui->resetCrono->setEnabled(!running && tempsCrono < constants::MAX_TIME);
}

void MainWindow::updateConnectat(bool connectat, bool inicialitzada)
{
    ui->tabWidget->setEnabled(connectat && inicialitzada);
    ui->actionTancar_connexio->setEnabled(connectat);
    ui->actionInicialitzar_BD->setEnabled(connectat);
    ui->actionActualitzar_BD->setEnabled(connectat && inicialitzada);
    ui->menuPantalles->setEnabled(connectat && inicialitzada);
}

void MainWindow::resetModels()
{
    QSqlQueryModel *nouInfoEquipsModel = new QSqlQueryModel;
    QSqlQueryModel *nouEquipsModel = new QSqlQueryModel;
    ui->taulaEquips->setModel(nouInfoEquipsModel);
    ui->pantallaCronoE1T1->setModel(nouEquipsModel);
    ui->pantallaCronoE1T2->setModel(nouEquipsModel);
    ui->pantallaCronoE2T1->setModel(nouEquipsModel);
    ui->pantallaCronoE2T2->setModel(nouEquipsModel);
    delete infoEquipsModel;
    delete equipsModel;
    infoEquipsModel = nouInfoEquipsModel;
    equipsModel = nouEquipsModel;
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
    db->populateInfoEquips(infoEquipsModel);
    db->populateEquips(equipsModel);
    db->populatePartides(partidesModel);
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
    if (preguntaDialog.exec() == QMessageBox::Yes) {
        db->inicialitzar();
    }
}

void MainWindow::obrePantallaCrono()
{
    pantallaCrono->show();
}

void MainWindow::afegirEquip()
{
    EquipDialog dialog(this);
    if (dialog.exec() == QDialog::Accepted) {
        db->afegirEquip(dialog.nom());
    }
}

void MainWindow::modificarEquip()
{
    QItemSelectionModel *selection = ui->taulaEquips->selectionModel();
    if (!selection->hasSelection()) return;
    QModelIndexList current = selection->selectedRows();
    EquipDialog dialog(current.at(0).data().toString(), this);
    dialog.queryInfo(db);
    if (dialog.exec() == QDialog::Accepted) {
        db->modificarEquip(dialog.nomOriginal(), dialog.nom());
    }
}

void MainWindow::eliminarEquip()
{
    QItemSelectionModel *selection = ui->taulaEquips->selectionModel();
    if (!selection->hasSelection()) return;
    QString current = selection->selectedRows().at(0).data().toString();
    QMessageBox dialog(this);
    dialog.setIcon(QMessageBox::Question);
    QString text = QString("<b>Esborrar l'equip %1?</b><br />"
                           "(Si ha participat en partides, s'han d'esborrar aquestes primer")
            .arg(current);
    dialog.setText(text);
    dialog.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
    dialog.setDefaultButton(QMessageBox::No);
    if (dialog.exec() == QMessageBox::Yes) {
        db->eliminarEquip(current);
    }
}

void MainWindow::afegirPartida()
{
    PartidaDialog dialog(this);
    dialog.autoPartida(db);
    dialog.setModel(equipsModel);
    if (dialog.exec() == QDialog::Accepted) {
        db->afegirPartida(dialog.partida());
    }
}

void MainWindow::modificarPartida()
{
    QItemSelectionModel *selection = ui->taulaPartides->selectionModel();
    if (!selection->hasSelection()) return;
    QPair<int, int> pk;
    pk.first = selection->selectedRows(0).at(0).data().toInt();
    pk.second = selection->selectedRows(1).at(0).data().toInt();
    PartidaDialog dialog(pk, this);
    dialog.queryInfo(db);
    dialog.setModel(equipsModel);
    if (dialog.exec() == QDialog::Accepted) {
        db->modificarPartida(dialog.partida(), dialog.pkOriginal());
    }
}

void MainWindow::eliminarPartida()
{
    QItemSelectionModel *selection = ui->taulaPartides->selectionModel();
    if (!selection->hasSelection()) return;
    QPair<int, int> pk;
    pk.first = selection->selectedRows(0).at(0).data().toInt();
    pk.second = selection->selectedRows(1).at(0).data().toInt();
    QMessageBox dialog(this);
    dialog.setIcon(QMessageBox::Question);
    QString text = QString("<b>Esborrar la partida %1 de la ronda %2?</b>")
            .arg(pk.second).arg(pk.first);
    dialog.setText(text);
    dialog.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
    dialog.setDefaultButton(QMessageBox::No);
    if (dialog.exec() == QMessageBox::Yes) {
        db->eliminarPartida(pk);
    }
}

void MainWindow::desconnectaBd()
{
    resetModels();
    db->desconnecta();
}
