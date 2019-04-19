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

int EquipDialog::puntsClassificacio() const
{
    return ui->puntsClassificacio->value();
}

int EquipDialog::puntsDesempat() const
{
    return ui->puntsDesempat->value();
}

void EquipDialog::setNom(const QString &nom)
{
    ui->nom->setText(nom);
}

void EquipDialog::setPuntsClassificacio(int puntsClassificacio)
{
    ui->puntsClassificacio->setValue(puntsClassificacio);
}

void EquipDialog::setPuntsDesempat(int puntsDesempat)
{
    ui->puntsDesempat->setValue(puntsDesempat);
}

void EquipDialog::queryInfo(RoboDatabase *db)
{
    Equip e = db->infoFromEquip(nomOriginal_);
    setNom(e.nom);
    setPuntsClassificacio(e.puntsClassificacio);
    setPuntsDesempat(e.puntsDesempat);
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
