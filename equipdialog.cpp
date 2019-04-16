#include "equipdialog.h"
#include "ui_equipdialog.h"
#include <QMessageBox>

EquipDialog::EquipDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::EquipDialog)
{
    ui->setupUi(this);
}

EquipDialog::EquipDialog(const QString &originalName, QWidget *parent) :
    EquipDialog(parent)
{
    nomOriginal_ = originalName;
    setNom(originalName);
}

EquipDialog::~EquipDialog()
{
    delete ui;
}

QString EquipDialog::nom() const
{
    return ui->nom->text();
}

int EquipDialog::puntsTotals() const
{
    return ui->puntsTotals->text().toInt();
}

int EquipDialog::partidesJugades() const
{
    return ui->partidesJugades->text().toInt();
}

void EquipDialog::setNom(const QString &nom)
{
    ui->nom->setText(nom);
}

void EquipDialog::setPuntsTotals(int puntsTotals)
{
    ui->puntsTotals->setText(QString::number(puntsTotals));
}

void EquipDialog::setPartidesJugades(int partidesJugades)
{
    ui->partidesJugades->setText(QString::number(partidesJugades));
}

void EquipDialog::on_buttonBox_accepted()
{
    if (ui->nom->text().isEmpty()) {
        QMessageBox errorDialog(this);
        errorDialog.setIcon(QMessageBox::Warning);
        errorDialog.setText("`Nom` buit però necessàri");
        errorDialog.exec();
        return;
    }
    emit accept();
}
