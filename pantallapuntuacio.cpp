#include "pantallapuntuacio.h"
#include "ui_pantallapuntuacio.h"
#include <QFont>

PantallaPuntuacio::PantallaPuntuacio(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PantallaPuntuacio)
{
    ui->setupUi(this);

    Qt::WindowFlags flags = windowFlags();
    flags |= Qt::Window | Qt::CustomizeWindowHint | Qt::WindowFullscreenButtonHint;
    flags &= ~Qt::WindowMaximizeButtonHint;
    setWindowFlags(flags);

    ultimesWidgets[0] = PartidaWidgetGroup(
                ui->equip11, ui->taps11, ui->bandera11, ui->punts11,
                ui->equip12, ui->taps12, ui->bandera12, ui->punts12
                );
    ultimesWidgets[1] = PartidaWidgetGroup(
                ui->equip21, ui->taps21, ui->bandera21, ui->punts21,
                ui->equip22, ui->taps22, ui->bandera22, ui->punts22
                );
    ultimesWidgets[2] = PartidaWidgetGroup(
                ui->equip31, ui->taps31, ui->bandera31, ui->punts31,
                ui->equip32, ui->taps32, ui->bandera32, ui->punts32
                );
    ultimesWidgets[3] = PartidaWidgetGroup(
                ui->equip41, ui->taps41, ui->bandera41, ui->punts41,
                ui->equip42, ui->taps42, ui->bandera42, ui->punts42
                );
}

PantallaPuntuacio::~PantallaPuntuacio()
{
    delete ui;
}

void PantallaPuntuacio::setUltimesPartides(const QVector<Partida> &ultimesPartides)
{
    this->ultimesPartides = ultimesPartides;
    updatePartides();
}

void PantallaPuntuacio::setModel(QAbstractItemModel *model)
{
    ui->taulaClassificacio->setModel(model);
}

void PantallaPuntuacio::keyPressEvent(QKeyEvent *event)
{
    event->accept();
    switch (event->key()) {
    case Qt::Key_F11:
        setWindowState(windowState() ^ Qt::WindowFullScreen);
        break;
    case Qt::Key_Escape:
        setWindowState(windowState() & ~Qt::WindowFullScreen);
        break;
    default:
        event->ignore();
    }
}

void PantallaPuntuacio::updatePartides()
{
    desactivarTot();
    switch (ultimesPartides.length()) {
    default:
    case 4:
        setPartida(ultimesWidgets[3], ultimesPartides.at(3));
        Q_FALLTHROUGH();
    case 3:
        setPartida(ultimesWidgets[2], ultimesPartides.at(2));
        Q_FALLTHROUGH();
    case 2:
        setPartida(ultimesWidgets[1], ultimesPartides.at(1));
        Q_FALLTHROUGH();
    case 1:
        setPartida(ultimesWidgets[0], ultimesPartides.at(0));
        Q_FALLTHROUGH();
    case 0:
        break;
    }
}

void PantallaPuntuacio::setPartida(PantallaPuntuacio::PartidaWidgetGroup &group, const Partida &partida)
{
    group.equip1->show();
    group.equip1->setText(partida.equip1);
    group.taps1->show();
    group.taps1->setText(QString::number(partida.taps1));
    group.bandera1->show();
    group.bandera1->setEnabled(partida.bandera1);
    group.punts1->show();
    group.punts1->setText(QString::number(partida.total1()));
    group.equip2->show();
    group.equip2->setText(partida.equip2);
    group.taps2->show();
    group.taps2->setText(QString::number(partida.taps2));
    group.bandera2->show();
    group.bandera2->setEnabled(partida.bandera2);
    group.punts2->show();
    group.punts2->setText(QString::number(partida.total2()));
    QFont font1 = group.punts1->font();
    font1.setBold(partida.winner1());
    group.punts1->setFont(font1);
    QFont font2 = group.punts2->font();
    font2.setBold(partida.winner2());
    group.punts2->setFont(font2);
}

void PantallaPuntuacio::desactivarTot()
{
    for (PartidaWidgetGroup &wg : ultimesWidgets) {
        wg.equip1->hide();
        wg.taps1->hide();
        wg.bandera1->hide();
        wg.punts1->hide();
        wg.equip2->hide();
        wg.taps2->hide();
        wg.bandera2->hide();
        wg.punts2->hide();
    }
}
