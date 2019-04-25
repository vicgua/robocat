#ifndef PANTALLADIALOG_H
#define PANTALLADIALOG_H

#include <QDialog>
#include <QStringList>
#include <QPair>
#include "data_objects/partida.h"
#include "robodatabase.h"

namespace Ui {
class PartidaDialog;
}

class PartidaDialog : public QDialog
{
    Q_OBJECT

public:
    explicit PartidaDialog(QWidget *parent = 0);
    explicit PartidaDialog(const QPair<int, int> &pkOriginal, QWidget *parent = 0);
    ~PartidaDialog();

    const Partida &partida();
    QPair<int, int> pkOriginal() const { return pkOriginal_; }

public slots:
    void setPartida(const Partida &partida);
    void queryInfo(RoboDatabase *db);
    void autoPartida(RoboDatabase *db);
    void setModel(QAbstractItemModel *model);

private:
    Ui::PartidaDialog *ui;
    Partida partida_;
    QPair<int, int> pkOriginal_;

    void collectData();
    void updateData();
    bool sanityCheck(QStringList &errors);

private slots:
    void on_buttonBox_accepted();
};

#endif // PANTALLADIALOG_H
