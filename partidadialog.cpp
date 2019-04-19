#include "partidadialog.h"
#include "ui_partidadialog.h"
#include <QDebug>

PartidaDialog::PartidaDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::PartidaDialog)
{
    ui->setupUi(this);
}

PartidaDialog::PartidaDialog(const Partida &partidaOriginal, QWidget *parent) :
    PartidaDialog(parent)
{
    pkOriginal_.first = partidaOriginal.ronda;
    pkOriginal_.second = partidaOriginal.partida;
    setPartida(partidaOriginal);
}

PartidaDialog::~PartidaDialog()
{
    delete ui;
}

void PartidaDialog::setPartida(const Partida &partida)
{
    partida_ = partida;
    updateData();
}

void PartidaDialog::collectData()
{
    partida_.ronda = ui->ronda->value();
    partida_.partida = ui->partida->value();
    partida_.equip1 = ui->equip1->currentText();
    partida_.taps1 = ui->taps1->value();
    partida_.bandera1 = ui->bandera1->isChecked();
    partida_.extra1 = ui->extra1->value();
    partida_.equip2 = ui->equip2->currentText();
    partida_.taps2 = ui->taps2->value();
    partida_.bandera2 = ui->bandera2->isChecked();
    partida_.extra2 = ui->extra2->value();
    partida_.notes = ui->notes->toPlainText();
}

void PartidaDialog::updateData()
{
    ui->ronda->setValue(partida_.ronda);
    ui->partida->setValue(partida_.partida);
    ui->equip1->setCurrentText(partida_.equip1);
    ui->taps1->setValue(partida_.taps1);
    ui->bandera1->setChecked(partida_.bandera1);
    ui->extra1->setValue(partida_.extra1);
    ui->equip2->setCurrentText(partida_.equip2);
    ui->taps2->setValue(partida_.taps2);
    ui->bandera2->setChecked(partida_.bandera2);
    ui->extra2->setValue(partida_.extra2);
    ui->notes->setPlainText(partida_.notes);
}

bool PartidaDialog::sanityCheck(QStringList &errors)
{
    bool ok = true;
    if (partida_.ronda <= 0) {
        qFatal("Ronda invàlida -- no hauria de ser possible");
    }
    if (partida_.taps1 < 0 || partida_.taps1 > 200) {
        qFatal("Taps 1 invàlid -- no hauria de ser possible");
    }
    if (partida_.taps2 < 0 || partida_.taps2 > 200) {
        qFatal("Taps 2 invàlid -- no hauria de ser possible");
    }
    if (partida_.equip1 == partida_.equip2) {
        ok = false;
        errors.append("Un equip no pot jugar contra sí mateix");
    }
    if (partida_.taps1 + partida_.taps2 > 200) {
        ok = false;
        errors.append("La suma de taps no pot ser major que 200");
    }
    if ((partida_.extra1 != 0 || partida_.extra2 != 0) && partida_.notes.isEmpty()) {
        ok = false;
        errors.append("Es requereix afegir una nota com a justificació dels punts extra");
    }
    return ok;
}
