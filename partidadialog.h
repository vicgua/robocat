#ifndef PANTALLADIALOG_H
#define PANTALLADIALOG_H

#include <QDialog>
#include <QStringList>
#include "data_objects/partida.h"

namespace Ui {
class PartidaDialog;
}

class PartidaDialog : public QDialog
{
    Q_OBJECT

public:
    explicit PartidaDialog(QWidget *parent = 0);
    ~PartidaDialog();

    const Partida &partida() const { return partida_; }

public slots:
    void setPartida(const Partida &partida);

private:
    Ui::PartidaDialog *ui;
    Partida partida_;

    void collectData();
    void updateData();
    bool sanityCheck(QStringList &errors);
};

#endif // PANTALLADIALOG_H
