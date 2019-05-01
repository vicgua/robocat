#include "equipdialog.h"
#include "ui_equipdialog.h"
#include <QMessageBox>

EquipDialog::EquipDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::EquipDialog)
{
    ui->setupUi(this);
}

EquipDialog::EquipDialog(const QString &nomOriginal, QWidget *parent) :
    EquipDialog(parent)
{
    nomOriginal_ = nomOriginal;
    ui->nom->setText(nomOriginal);
}

EquipDialog::~EquipDialog()
{
    delete ui;
}

Equip EquipDialog::equip() const
{
    Equip e;
    e.nom = ui->nom->text();
    e.categoria = ui->categoria->currentText();
    e.puntsClassificacio = ui->puntsClassificacio->value();
    e.puntsDesempat = ui->puntsDesempat->value();
    return e;
}

void EquipDialog::queryInfo(RoboDatabase *db)
{
    setEquip(db->infoFromEquip(nomOriginal_));
}

void EquipDialog::setEquip(const Equip &e)
{
    ui->nom->setText(e.nom);
    ui->categoria->setCurrentText(e.categoria);
    ui->puntsClassificacio->setValue(e.puntsClassificacio);
    ui->puntsDesempat->setValue(e.puntsDesempat);
}

void EquipDialog::setDefaultCategoria(const QString &categoria)
{
    ui->categoria->setCurrentText(categoria);
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
    accept();
}
