#include "infoclassificats.h"

InfoClassificats::InfoClassificats(QWidget *parent) :
    QDialog(parent),
    layout(new QVBoxLayout(this)),
    classificacio(new QTreeWidget)
{
    classificacio->setColumnCount(3);
    classificacio->setHeaderLabels({"Equip", "Punts classificació", "Punts desempat"});
    classificacio->setEditTriggers(QAbstractItemView::NoEditTriggers);
    classificacio->setAnimated(true);
    layout->addWidget(classificacio);
}

void InfoClassificats::afegirCategoria(const QString &categoria, const QVector<Equip> &classificats)
{
    QTreeWidgetItem *cat = new QTreeWidgetItem({categoria, "", ""});
    foreach (const Equip &e, classificats) {
        QTreeWidgetItem *par = new QTreeWidgetItem;
        par->setData(0, Qt::DisplayRole, e.nom);
        par->setData(1, Qt::DisplayRole, e.puntsClassificacio);
        par->setData(2, Qt::DisplayRole, e.puntsDesempat);
        cat->addChild(par);
    }
    classificacio->addTopLevelItem(cat);
    classificacio->expandAll();
}
