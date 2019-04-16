#ifndef EQUIPDIALOG_H
#define EQUIPDIALOG_H

#include <QDialog>

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

    QString nom() const;
    int puntsTotals() const;
    int partidesJugades() const;
    QString nomOriginal() const { return nomOriginal_; }

public slots:
    void setNom(const QString &nom);
    void setPuntsTotals(int puntsTotals);
    void setPartidesJugades(int partidesJugades);

private:
    Ui::EquipDialog *ui;
    QString nomOriginal_;

private slots:
    void on_buttonBox_accepted();
};

#endif // EQUIPDIALOG_H
