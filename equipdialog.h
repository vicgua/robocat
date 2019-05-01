#ifndef EQUIPDIALOG_H
#define EQUIPDIALOG_H

#include <QDialog>
#include <QString>
#include "robodatabase.h"
#include "data_objects/equip.h"

namespace Ui {
class EquipDialog;
}

class EquipDialog : public QDialog
{
    Q_OBJECT

public:
    explicit EquipDialog(QWidget *parent = 0);
    explicit EquipDialog(const QString &nomOriginal, QWidget *parent = 0);
    ~EquipDialog();

    QString nomOriginal() const { return nomOriginal_; }
    Equip equip() const;

public slots:
    void queryInfo(RoboDatabase *db);
    void setEquip(const Equip &e);
    void setDefaultCategoria(const QString &categoria);

private:
    Ui::EquipDialog *ui;
    QString nomOriginal_;

private slots:
    void on_buttonBox_accepted();
};

#endif // EQUIPDIALOG_H
