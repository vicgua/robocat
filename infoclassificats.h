#ifndef INFOCLASSIFICATS_H
#define INFOCLASSIFICATS_H

#include <QDialog>
#include <QVBoxLayout>
#include <QTreeWidget>
#include <QVector>
#include "data_objects/equip.h"

class InfoClassificats : public QDialog
{
    Q_OBJECT
public:
    explicit InfoClassificats(QWidget *parent = nullptr);

public slots:
    void afegirCategoria(const QString &categoria, const QVector<Equip> &classificats);

private:
    QVBoxLayout *layout;
    QTreeWidget *classificacio;
};

#endif // INFOCLASSIFICATS_H
