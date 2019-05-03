#ifndef PANTALLAPUNTUACIO_H
#define PANTALLAPUNTUACIO_H

#include <QWidget>
#include <QLabel>
#include <QVector>
#include <QKeyEvent>
#include <QAbstractItemModel>
#include <QTimer>
#include "partidadialog.h"

namespace Ui {
class PantallaPuntuacio;
}

class PantallaPuntuacio : public QWidget
{
    Q_OBJECT

public:
    explicit PantallaPuntuacio(QWidget *parent = 0);
    ~PantallaPuntuacio();

public slots:
    void setUltimesPartides(const QVector<Partida> &ultimesPartides);
    void setModel(QAbstractItemModel* model);
    void dadesActualitzades();

protected:
    void keyPressEvent(QKeyEvent *event);

private:
    struct PartidaWidgetGroup {
        QLabel *equip1, *taps1, *bandera1, *punts1;
        QLabel *equip2, *taps2, *bandera2, *punts2;

        PartidaWidgetGroup() = default;
        PartidaWidgetGroup(QLabel *equip1, QLabel *taps1, QLabel *bandera1, QLabel *punts1,
                           QLabel *equip2, QLabel *taps2, QLabel *bandera2, QLabel *punts2)
            : equip1(equip1), taps1(taps1), bandera1(bandera1), punts1(punts1),
              equip2(equip2), taps2(taps2), bandera2(bandera2), punts2(punts2) {}
    };


    Ui::PantallaPuntuacio *ui;
    QVector<Partida> ultimesPartides;
    PartidaWidgetGroup ultimesWidgets[4];
    QTimer *scrollTimer;
    int scrollPoint;

    void updatePartides();
    void setPartida(PartidaWidgetGroup &group, const Partida &partida);
    void desactivarTot();

private slots:
    void updateScroll();
};

#endif // PANTALLAPUNTUACIO_H
